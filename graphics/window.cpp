//
// Created by Oliver Zhang on 2020-12-28.
//

#include <iostream>
#include "window.h"


Window::Window(const std::string &title, int scr_height, int scr_width, bool is_mouse_visible, bool is_window_resizable)
        : title(title),
          scr_width(scr_width),
          scr_height(scr_height),
          is_mouse_visible(is_mouse_visible),
          is_window_resizable(is_window_resizable),
          firstMouse(true),
          lastX(static_cast<float>(scr_width / 2.0)),
          lastY(static_cast<float>(scr_height / 2.0)) {
    if (!init()) {
        glfwTerminate();
    }
}

Window::~Window() {
    glfwTerminate();
}

bool Window::init() {
    // Initialize GLFW and the window settings.
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (!is_window_resizable) {
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(scr_width, scr_height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        return false;
    }
    glfwMakeContextCurrent(window);

    if (!is_mouse_visible) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    // Initialize the glad extension loader.
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD.");
        return false;
    }

    return true;
}

void Window::update() {
    processInput(window);

    // Temporary background color.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::hasClosed() {
    return glfwWindowShouldClose(window);
}

void Window::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
}

void Window::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
}