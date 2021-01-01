//
// Created by Oliver Zhang on 2020-12-28.
//

#include <iostream>
#include "main_window.h"


MainWindow::MainWindow(const std::string &title, int scr_height, int scr_width, bool is_mouse_visible, bool is_window_resizable)
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

MainWindow::~MainWindow() {
    glfwTerminate();
}

bool MainWindow::init() {
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

    shader = std::make_unique<Shader>("graphics/shaders/quad_renderer.vs", "graphics/shaders/quad_renderer.fs");

    return true;
}

void MainWindow::update() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }


    // Temporary background color.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float vertices[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.0f,  0.5f
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    shader->use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);


    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool MainWindow::hasClosed() {
    return glfwWindowShouldClose(window);
}
