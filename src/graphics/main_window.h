//
// Created by Oliver Zhang on 2020-12-28.
//

#ifndef PATHTRACED_RENDERER_MAIN_WINDOW_H
#define PATHTRACED_RENDERER_MAIN_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include <vector>

#include "quad_renderer.h"
#include "render_primitive_group.h"
#include "camera.h"
#include "fps_counter.h"
#include "Light.hpp"


class MainWindow {
private:
    std::string title;
    GLFWwindow *window;
    int screenWidth = 800;
    int screenHeight = 800;
    bool isMouseVisible = true;
    bool isWindowResizable = false;
    bool vsync = false;
    bool showDebugMessages = false;

    // State for drawing software rendered image to screen.

    // Hardcoded sizes such that they need to:
    // 1) Upscale to screen size with nearest neighbor resampling (screen size is integer multiple)
    // 2) Bytes in each line of pixel array is a multiple of 4, so that the GPU doesn't have a seizure.
//    std::vector<std::pair<int, int>> imageSizes = {{1600, 800},
//                                                   {800,  400},
//                                                   {400,  200},
//                                                   {200,  100},
//                                                   {100,  50},
//                                                   {40,   20},
//                                                   {20,   10}};
    std::vector<std::pair<int, int>> imageSizes = {{1600, 1600},
                                                   {800,  800},
                                                   {400,  400},
                                                   {200,  200},
                                                   {100,  100},
                                                   {40,   40},
                                                   {20,   20}};
    int imageSizeSelection = 4;
    int fullscreenWidth, fullscreenHeight;
    int tilesPerDim = 8;
    bool isFullscreen = false;

    std::unique_ptr<QuadRenderer> quadRenderer;
    bool isRenderingPaused = false;

    bool shouldClearImageThisFrame = false; // set to true when something in the scene changes, forcing the renderer to start anew.

    // Scene geometry.
    RenderPrimitiveGroup world;
    std::vector<Light> lights;
    Camera camera;
    int maxDepth = 50;

    // Time state for controls.
    double lastTime;
    const double maxDeltaTime = 0.1; // seconds.

    // Performance stats
    FPSCounter fpsCounter = FPSCounter(120, 1);

public:
    explicit MainWindow(const std::string &title);

    ~MainWindow();

    void run();

private:
    // One iteration of the "game render loop".
    void update();

    // Return true if and only if the user has closed the window.
    bool hasClosed();

    // Returns true if and only if all initialization succeeds. Need to clean up if it fails.
    bool init();

    void showOverlay();
    void showSettingsWindow();

    [[nodiscard]] int imgWidth() const;
    [[nodiscard]] int imgHeight() const;

    void toggleFullscreen();
};

#endif // PATHTRACED_RENDERER_MAIN_WINDOW_H
