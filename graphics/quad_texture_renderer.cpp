//
// Created by Oliver Zhang on 2020-12-31.
//

#include "quad_texture_renderer.h"

QuadRenderer::QuadRenderer() : shader(
        Shader("graphics/shaders/quad_renderer.vs", "graphics/shaders/quad_renderer.fs")) {
    float vertices[] = {
            // positions    // texture coords
            1.0f,  1.0f,    1.0f, 1.0f, // tr
            1.0f,  -1.0f,   1.0f, 0.0f, // br
            -1.0f, -1.0f,   0.0f, 0.0f, // bl
            -1.0f, 1.0f,    0.0f, 1.0f  // tl
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Setup position vertex attribute.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Setup texture coordinate vertex attribute.
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture filtering mode.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void QuadRenderer::renderRGBImage(int width, int height, unsigned char *data, bool isRenderingPaused) {
    shader.use();
    glBindTexture(GL_TEXTURE_2D, texture);

	if (!isRenderingPaused) {
		// Upload image data to GPU.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	if (!isRenderingPaused) {
		frameCount++;
	}
}
