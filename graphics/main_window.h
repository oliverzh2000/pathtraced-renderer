//
// Created by Oliver Zhang on 2020-12-28.
//

#ifndef PATHTRACED_FLIGHT_SIM_MAIN_WINDOW_H
#define PATHTRACED_FLIGHT_SIM_MAIN_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

#include "quad_texture_renderer.h"

// TODO: Convert to singleton class.
class MainWindow {
private:
    std::string title;
    GLFWwindow *window;
    int scr_width = 1000;
    int scr_height = 500;
    bool is_mouse_visible = true;
    bool is_window_resizable = false;
	bool vsync = true;

    // State for drawing software rendered image to screen.
    int img_width = 200; // Rendered image is scaled up to the screen size by the quad renderer.
    int img_height = 100;
    unsigned char *img_data;
    std::unique_ptr<QuadRenderer> quadRenderer;
	bool isRenderingPaused = false;

public:
    explicit MainWindow(const std::string &title);

    ~MainWindow();

    // One iteration of the "game render loop".
    void update();

    // Return true if and only if the user has closed the window.
    bool hasClosed();

private:
    // Returns true if and only if all initialization succeeds. Need to clean up if it fails.
    bool init();

	void showOverlay();

	void showSettingsWindow();
};

#endif // PATHTRACED_FLIGHT_SIM_MAIN_WINDOW_H
