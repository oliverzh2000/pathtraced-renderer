//
// Created by Oliver Zhang on 2020-12-28.
//

#ifndef PATHTRACED_FLIGHT_SIM_WINDOW_H
#define PATHTRACED_FLIGHT_SIM_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
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
    explicit Window(const std::string &title, int scr_height = 600, int scr_width = 800, bool is_mouse_visible = true, bool is_window_resizable = false);
    ~Window();

    // One iteration of the "game render loop".
    void update();

    // Return true if and only if the user has closed the window.
    bool hasClosed();

private:
    // Returns true if and only if all initialization succeeds. Need to clean up if it fails.
    bool init();


    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void mouse_callback(GLFWwindow *window, double xpos, double ypos);

    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    void processInput(GLFWwindow *window);
};

#endif // PATHTRACED_FLIGHT_SIM_WINDOW_H
