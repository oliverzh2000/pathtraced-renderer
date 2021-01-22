//
// Created by Oliver Zhang on 2020-12-28.
//

#include "main_window.h"

#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <imgui_internal.h>
#include "stb_image_write.h"

#include "util.h"
#include "geometry.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

void error_callback(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void GLAPIENTRY
MessageCallback(GLenum source,
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
        : title(title), camera(imgWidth(), imgHeight()) {
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
    glEnable(GL_FRAMEBUFFER_SRGB);

    if (showDebugMessages) {
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(MessageCallback, 0);
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

    world.add(make_shared<Sphere>(Point3d (0,0,-1), 0.5));
    world.add(make_shared<Sphere>(Point3d(0,-100.5,-1), 100));

    return true;
}

bool hit_sphere(const Point3d & center, double radius, const Ray3d& r) {
    Vector3d oc = r.origin - center;
    auto a = r.direction.dot(r.direction);
    auto b = 2.0 * oc.dot(r.direction);
    auto c = oc.dot(oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

float sunX = 0.7;
float sunY = 0;
float sunZ = -1;
float sunSize = 0.90;

Color rayColor(const Ray3d & r, const Hittable& world, int depth) {
    if (depth <= 0) {
        return Color(0, 0, 0);
    }
    HitRecord rec;
    if (world.hit(r, 0.001, infinity, rec)) {
        Point3d target = rec.p + rec.normal + Vector3d::randomInUnitSphere();
        return rayColor(Ray3d(rec.p, target - rec.p), world, depth - 1) * 0.9;
    }
    Vector3d unit_direction = r.direction.unitVector();
    auto t = 0.5*(unit_direction.y + 1.0);
//    if (unit_direction.dot(Vector3d(sunX, sunY, sunZ).unitVector()) > sunSize) {
//        return Color(20.0, 0.0, 0.0);
//    }
//    if (unit_direction.dot(Vector3d(-sunX, sunY, sunZ).unitVector()) > sunSize) {
//        return Color(0.0, 0.0, 20.0);
//    }
//    if (unit_direction.dot(Vector3d(0, 1, sunZ).unitVector()) > sunSize) {
//        return Color(1.0, 3.0, 1.0);
//    }
    return (Color(1.0, 1.0, 1.0) * (1 - t) + Color(0.5, 0.7, 1.0) * t);
    return Color(0, 0, 0);
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        toggleFullscreen();
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        stbi_flip_vertically_on_write(1);
        const float *imgData = quadRenderer->scaledImgDataCopy();
        stbi_write_hdr("out.hdr", imgWidth(), imgHeight(), quadRenderer->numChannels, imgData);
        delete imgData;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuiIO &io = ImGui::GetIO();

    ImGui::ShowDemoWindow(nullptr);
    showSettingsWindow();
    if (!isRenderingPaused) {
        // Image
        double aspectRatio = double(imgWidth()) / double(imgHeight());

        // Camera
        auto viewportHeight = 2.0;
        auto viewportWidth = aspectRatio * viewportHeight;
        auto focal_length = 1.0;

        auto origin = Point3d(0, 0, 0);
        auto horizontal = Vector3d(viewportWidth, 0, 0);
        auto vertical = Vector3d(0, viewportHeight, 0);
        auto lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vector3d(0, 0, focal_length);


        for (int row = 0; row < imgHeight(); ++row) {
            for (int col = 0; col < imgWidth(); ++col) {
                double u = double(col + random_double()) / (imgWidth() - 1);
                double v = double(row + random_double()) / (imgHeight() - 1);
                Ray3d r = camera.getRay(u, v);
                Color pixelColor = rayColor(r, world, maxDepth);
                quadRenderer->accumulatePixel(row, col, pixelColor);
            }
        }
        quadRenderer->samplesPerPixel++;
        quadRenderer->upload();
    }
    quadRenderer->render();


    showOverlay();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool MainWindow::hasClosed() {
    return glfwWindowShouldClose(window);
}

void MainWindow::showOverlay() {
    // FIXME-VIEWPORT: Select a default viewport
    const float DISTANCE = 10.0f;
    static int corner = 2;
    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    if (corner != -1) {
        window_flags |= ImGuiWindowFlags_NoMove;
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImVec2 work_area_pos = viewport->GetWorkPos();   // Instead of using viewport->Pos we use GetWorkPos() to avoid menu bars, if any!
        ImVec2 work_area_size = viewport->GetWorkSize();
        ImVec2 window_pos = ImVec2(
                (corner & 1) ? (work_area_pos.x + work_area_size.x - DISTANCE) : (work_area_pos.x + DISTANCE),
                (corner & 2) ? (work_area_pos.y + work_area_size.y - DISTANCE) : (work_area_pos.y + DISTANCE));
        ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
        ImGui::SetNextWindowViewport(viewport->ID);
    }
    ImGui::SetNextWindowBgAlpha(0.7f); // Transparent background
    if (ImGui::Begin("Overlay", nullptr, window_flags)) {
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
        }

        if (ImGui::BeginTabItem("Game")) {
            ImGui::Text("Hello");

            ImGui::SliderFloat("slider sun x", &sunX, -1.0f, 1.0f, "ratio = %.3f");
            ImGui::SliderFloat("slider sun y", &sunY, -1.0f, 1.0f, "ratio = %.3f");
            ImGui::SliderFloat("slider sun z", &sunZ, -1.0f, 1.0f, "ratio = %.3f");
            ImGui::SliderFloat("slider sun size", &sunSize, 0.0f, 1.0f, "ratio = %.3f");

            ImGui::SliderFloat("slider exposure", &quadRenderer->exposure, 0.01f, 10.0f, "ratio = %.3f");

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
