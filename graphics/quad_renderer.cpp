//
// Created by Oliver Zhang on 2020-12-31.
//

#include "quad_renderer.h"
#include "iostream"


QuadRenderer::QuadRenderer(int width, int height) : shader(
        Shader("graphics/shaders/quad_renderer.vs", "graphics/shaders/quad_renderer.fs")) {
    float vertices[] = {
            // positions    // texture coords
            1.0f, 1.0f, 1.0f, 1.0f, // tr
            1.0f, -1.0f, 1.0f, 0.0f, // br
            -1.0f, -1.0f, 0.0f, 0.0f, // bl
            -1.0f, 1.0f, 0.0f, 1.0f  // tl
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
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    setSize(width, height);
}

void QuadRenderer::upload() {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, imgData);
}

void QuadRenderer::render() {
    shader.use();
    shader.setFloat("samples_per_pixel", float(samplesPerPixel) / exposure);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void QuadRenderer::setSize(int newWidth, int newHeight) {
    if ((newWidth * numChannels * bytesPerChannel) % 4 != 0) {
        throw std::runtime_error("Alignment of each line of the pixel array needs to be multiple of 4."
                                 "See https://www.khronos.org/opengl/wiki/Common_Mistakes#Texture_upload_and_pixel_reads");
    }
    if (newWidth != this->width || newHeight != this->height) {
        this->width = newWidth;
        this->height = newHeight;

        delete imgData;
        imgData = new float[newWidth * newHeight * numChannels]();
        samplesPerPixel = 0;
    }
}

void QuadRenderer::writePixel(int row, int col, Color color) {
    int startIndex = (col + row * width) * numChannels;
    imgData[startIndex] = color.x;
    imgData[startIndex + 1] = color.y;
    imgData[startIndex + 2] = color.z;
}

void QuadRenderer::accumulatePixel(int row, int col, Color color) {
    int startIndex = (col + row * width) * numChannels;
    imgData[startIndex] += color.x;
    imgData[startIndex + 1] += color.y;
    imgData[startIndex + 2] += color.z;
}

const float *QuadRenderer::scaledImgDataCopy() const {
    int size = width * height * numChannels;
    float *imgDataCopy = new float[size];
    memcpy(imgDataCopy, imgData, size * bytesPerChannel);
    for (int i = 0; i < size; ++i) {
        imgDataCopy[i] /= samplesPerPixel;
    }
    return imgDataCopy;
}
