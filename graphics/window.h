//
// Created by Oliver Zhang on 2020-12-28.
//

#ifndef PATHTRACED_FLIGHT_SIM_WINDOW_H
#define PATHTRACED_FLIGHT_SIM_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class MainWindow {
  private:
    std::string title;
    GLFWwindow* window;
    int scr_width, scr_height;
    bool is_mouse_visible;
    bool is_window_resizable;

    // State for user input.
    bool firstMouse;
    float lastX;
    float lastY;

  public:
    explicit MainWindow(const std::string &title, int scr_height = 600, int scr_width = 800, bool is_mouse_visible = true, bool is_window_resizable = false);
    ~MainWindow();

    // One iteration of the "game render loop".
    void update();

    // Return true if and only if the user has closed the window.
    bool hasClosed();

private:
    // Returns true if and only if all initialization succeeds. Need to clean up if it fails.
    bool init();
};

#endif // PATHTRACED_FLIGHT_SIM_WINDOW_H
