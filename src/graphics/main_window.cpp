//
// Created by Oliver Zhang on 2020-12-28.
//

#include "main_window.h"

#include <iostream>
#include <string>
#include <omp.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <imgui_internal.h>
#include "stb_image_write.h"

#include "util.h"
#include "geometry.h"
#include "ray.h"
#include "render_primitive_group.h"
#include "sphere.h"
#include "triangle.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "cube_map.h"
#include "equirectangular_map.h"

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void GLAPIENTRY
messageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

MainWindow::MainWindow(const std::string &title)
        : title(title), camera({0, 2, -2}, 90, -10, imgWidth(), imgHeight()) {
    init();
}

MainWindow::~MainWindow() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool MainWindow::init() {
    // Initialize GLFW and the window settings.
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    if (showDebugMessages) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!isWindowResizable) {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);

    if (!isMouseVisible) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    float xscale, yscale;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    glfwSetWindowPos(window, 1000, 500);

    // Initialize the glad extension loader.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    glfwSetErrorCallback(error_callback);
    glfwSwapInterval(vsync);
//    glEnable(GL_FRAMEBUFFER_SRGB);

    if (showDebugMessages) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(messageCallback, 0);
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    quadRenderer = std::make_unique<QuadRenderer>(imgWidth(), imgHeight());
    quadRenderer->setSize(imgWidth(), imgHeight());

    Color red(1.0, 0.1, 0.1);
    Color green(0.1, 1.0, 0.1);
    Color blue(0.1, 0.1, 1.0);
    Color yellow(1.0, 1.0, 1.0);
    Color cyan(0.1, 1.0, 1.0);
    Color magenta(1.0, 0.1, 1.0);

    Lambertian *redMatte = new Lambertian(Color(1.0, 0.1, 0.1));
    Lambertian *greenMatte = new Lambertian(Color(0.1, 1.0, 0.1));
    Lambertian *blueMatte = new Lambertian(Color(0.1, 0.1, 1.0));
    Lambertian *yellowMatte = new Lambertian(Color(1.0, 1.0, 0.1));
    Lambertian *cyanMatte = new Lambertian(Color(0.1, 1.0, 1.0));
    Lambertian *magentaMatte = new Lambertian(Color(1.0, 0.1, 1.0));
    Lambertian *grayMatte = new Lambertian(Color(0.8, 0.8, 0.8));

    Metal *darkMetal = new Metal(Color(0.3, 0.3, 0.3));
    Metal *mirror = new Metal(Color(1.0, 1.0, 1.0));
    Metal *gold = new Metal(Color(1.0, 1.0, 0.1));

    world.add(std::make_unique<Sphere>(Point3d (2,0,0), 0.5, *redMatte)); // x
    world.add(std::make_unique<Sphere>(Point3d (0,2, 0), 0.5, *greenMatte)); // y
    world.add(std::make_unique<Sphere>(Point3d (0,0,2), 0.5, *blueMatte)); // z

    world.add(std::make_unique<Sphere>(Point3d (1,3, 1), 0.2, *yellowMatte));
    world.add(std::make_unique<Sphere>(Point3d (-2,0,0), 0.5, *magentaMatte));
    world.add(std::make_unique<Sphere>(Point3d (0,0,-2), 0.5, *cyanMatte));
    world.add(std::make_unique<Sphere>(Point3d (0,0,0), 0.5, *gold));

    // ground.
    world.add(std::make_unique<Sphere>(Point3d(0,-100.5,1), 100, *darkMetal));

    // square mirror
    world.add(std::make_unique<Triangle<double>>(Point3d(5, 0, 0),
                                            Point3d(5, 4, 0),
                                            Point3d(5, 4, 4),
                                            *mirror));
    world.add(std::make_unique<Triangle<double>>(Point3d(5, 0, 0),
                                            Point3d(5, 0, 4),
                                            Point3d(5, 4, 4),
                                            *mirror));

    world.add(std::make_unique<Triangle<double>>(Point3d(0, 0, 0),
                                            Point3d(0, 0, 2),
                                            Point3d(2, 0, 0),
                                            *grayMatte));

    lastTime = glfwGetTime();
    return true;
}


float sunX = 0.7;
float sunY = 0;
float sunZ = -1;
float sunSize = 0.90;
Color sunColor(1.0, 0.7, 0.1);
float sunBrightness = 10;

Color skyColor1(1.0, 1.0, 1.0);
Color skyColor2(0.5, 0.7, 1.0);

//CubeMap sky = CubeMap("assets/skybox2");
//EquirectangularMap sky = EquirectangularMap("assets/eqrect/Brooklyn_Bridge_Planks_2k.hdr");
//EquirectangularMap sky = EquirectangularMap("assets/eqrect/hallstatt4_hd.hdr");
//EquirectangularMap sky = EquirectangularMap("assets/eqrect/Arches_E_PineTree_3k.hdr");
EquirectangularMap sky = EquirectangularMap("assets/eqrect/barcelona.hdr");

// TODO: Right now this is still based on the starter code from peter shirley's ray tracing in a weekend.
// This needs to be refactored into something less ugly, and needs to use real radiometric quantities.
Color rayColor(const Ray3d & r, const RenderPrimitive& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }
    LightInteraction rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        Ray3d scattered;
        Color attenuation;
        if (rec.material->scatter(r, rec, attenuation, scattered)) {
            return attenuation * rayColor(scattered, world, depth-1);
        }
        return Color(0,0,0);
    }
//    Vector3d unit_direction = r.direction.normalized();
//    auto t = 0.5*(unit_direction.y + 1.0);
//    if (unit_direction.dot(Vector3d(sunX, sunY, sunZ).normalized()) > sunSize) {
//        return sunColor * sunBrightness;
//    }
    Color skyColor = sky.sample(r.direction);
    return skyColor;
}

void MainWindow::toggleFullscreen() {
    isFullscreen = !isFullscreen;
    if (isFullscreen) {
        glfwMaximizeWindow(window);
        glfwGetWindowSize(window, &fullscreenWidth, &fullscreenHeight);
    } else {
        glfwRestoreWindow(window);
    }
    camera.setAspectRatio(imgWidth(), imgHeight());
    int viewportWidth, viewportHeight;
    glfwGetFramebufferSize(window, &viewportWidth, &viewportHeight);
    glViewport(0, 0, viewportWidth, viewportHeight);
    quadRenderer->setSize(imgWidth(), imgHeight());
}

void MainWindow::update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuiIO &io = ImGui::GetIO();

    showSettingsWindow();
    showOverlay();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        toggleFullscreen();
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        quadRenderer->saveHdrFile();
    }

    double deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();
    if (deltaTime > maxDeltaTime) {
        deltaTime = maxDeltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.movePosition(MovementDirection::FRONT, deltaTime);
        shouldClearImageThisFrame = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.movePosition(MovementDirection::LEFT, deltaTime);
        shouldClearImageThisFrame = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.movePosition(MovementDirection::BACK, deltaTime);
        shouldClearImageThisFrame = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.movePosition(MovementDirection::RIGHT, deltaTime);
        shouldClearImageThisFrame = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.movePosition(MovementDirection::DOWN, deltaTime);
        shouldClearImageThisFrame = true;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.movePosition(MovementDirection::UP, deltaTime);
        shouldClearImageThisFrame = true;
    }
    if (!io.WantCaptureMouse) {
        if (io.MouseDown[0]) {
            camera.moveDirection(io.MouseDelta.x, -io.MouseDelta.y, deltaTime);
            shouldClearImageThisFrame = true;
        }
        if (io.MouseWheel) {
            camera.changeVerticalFOV(io.MouseWheel, deltaTime);
            shouldClearImageThisFrame = true;
        }
    }

    if (!isRenderingPaused) {
        if (shouldClearImageThisFrame) {
            quadRenderer->reset();
            shouldClearImageThisFrame = false;
        }
#pragma omp parallel for
        for (int row = 0; row < imgHeight(); ++row) {
            for (int col = 0; col < imgWidth(); ++col) {
                double x = double(col + randomDouble(0, 1)) / (imgWidth() - 1);
                double y = double(row + randomDouble(0, 1)) / (imgHeight() - 1);
                Ray3d r = camera.generateRay(x, y);
                Color pixelColor = rayColor(r, world, maxDepth);
                quadRenderer->accumulatePixel(row, col, pixelColor);
            }
        }
        quadRenderer->finishAcculumatingFrame();
        quadRenderer->upload();
    }
    quadRenderer->render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backupCurrentContext = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backupCurrentContext);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool MainWindow::hasClosed() {
    return glfwWindowShouldClose(window);
}

void MainWindow::showOverlay() {
    // FIXME-VIEWPORT: Select a default viewport
    const float distance = 5.0f;
    static int corner = 2;
    ImGuiWindowFlags windowFlags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (corner != -1) {
        windowFlags |= ImGuiWindowFlags_NoMove;
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImVec2 workAreaPos = viewport->GetWorkPos();   // Instead of using viewport->Pos we use GetWorkPos() to avoid menu bars, if any!
        ImVec2 workAreaSize = viewport->GetWorkSize();
        ImVec2 windowPos = ImVec2(
                (corner & 1) ? (workAreaPos.x + workAreaSize.x - distance) : (workAreaPos.x + distance),
                (corner & 2) ? (workAreaPos.y + workAreaSize.y - distance) : (workAreaPos.y + distance));
        ImVec2 windowPosPivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always, windowPosPivot);
        ImGui::SetNextWindowViewport(viewport->ID);
    }
    ImGui::SetNextWindowBgAlpha(0.7f); // Transparent background
    if (ImGui::Begin("Overlay", nullptr, windowFlags)) {
        ImGui::Text("%.1f ms (%.1f FPS) | %d spp", 1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate, quadRenderer->samplesPerPixel);
        if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
            if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

void MainWindow::showSettingsWindow() {
    ImGui::Begin("Settings");

    if (ImGui::BeginTabBar("Settings")) {
        if (ImGui::BeginTabItem("Render")) {
            // Image resolution arrows
            if (ImGui::ArrowButton("##increase resolution", ImGuiDir_Up)) {
                if (imageSizeSelection > 0) {
                    imageSizeSelection--;
                }
            }
            ImGui::SameLine();
            if (ImGui::ArrowButton("##decrease resolution", ImGuiDir_Down)) {
                if (imageSizeSelection < imageSizes.size() - 1) {
                    imageSizeSelection++;
                }
            }
            quadRenderer->setSize(imgWidth(), imgHeight());
            ImGui::SameLine();
            ImGui::Text(("Resolution: " + std::to_string(imgWidth()) + "x" + std::to_string(imgHeight())).c_str());

            // Pausing rendering checkbox.
            ImGui::Checkbox("Rendering Paused: ", &isRenderingPaused);
            ImGui::EndTabItem();

            ImGui::SliderFloat("exposure", &quadRenderer->exposure, 0.002f, 10.0f, "ratio = %.3f", ImGuiSliderFlags_Logarithmic);
        }

        if (ImGui::BeginTabItem("Scene")) {
            bool changed = false;

            changed |= ImGui::SliderFloat("sun x", &sunX, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            changed |= ImGui::SliderFloat("sun y", &sunY, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            changed |= ImGui::SliderFloat("sun z", &sunZ, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_Logarithmic);
            changed |= ImGui::SliderFloat("sun size", &sunSize, 0.1f, 0.99f, "%.3f", ImGuiSliderFlags_Logarithmic);

            changed |= ImGui::ColorPicker3("sum color", &sunColor.x, ImGuiColorEditFlags_HDR);
            changed |= ImGui::SliderFloat("sun brightness", &sunBrightness, 0.1f, 250.0f, "%.3f", ImGuiSliderFlags_Logarithmic);

            changed |= ImGui::ColorPicker3("sky color 1", &skyColor1.x, ImGuiColorEditFlags_HDR);
            changed |= ImGui::ColorPicker3("sky color 2", &skyColor2.x, ImGuiColorEditFlags_HDR);

            shouldClearImageThisFrame |= changed;
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::End(); // Settings window.
}

int MainWindow::imgWidth() const {
    if (isFullscreen) {
        return fullscreenWidth;
    }
    return imageSizes[imageSizeSelection].first;
}

int MainWindow::imgHeight() const {
    if (isFullscreen) {
        return fullscreenHeight;
    }
    return imageSizes[imageSizeSelection].second;
}
