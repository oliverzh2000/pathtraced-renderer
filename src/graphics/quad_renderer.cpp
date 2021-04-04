//
// Created by Oliver Zhang on 2020-12-31.
//

#include "quad_renderer.h"

#include <iostream>
#include "stb_image_write.h"


QuadRenderer::QuadRenderer(int width, int height) : shader(
        Shader("src/graphics/shaders/quad_renderer.vs", "src/graphics/shaders/quad_renderer.fs")) {
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

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    setSize(width, height);
}

void QuadRenderer::upload() {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, data);
}

void QuadRenderer::render() {
    shader.use();
    shader.setFloat("pixel_divisor", float(samplesPerPixel) / exposure);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void QuadRenderer::saveHdrFile() {
    stbi_flip_vertically_on_write(1);
    const float *dataCopy = scaledData();
    stbi_write_hdr("out.hdr", width, height, numChannels, dataCopy);
    delete data;
}

void QuadRenderer::setSize(int newWidth, int newHeight) {
    if ((newWidth * numChannels * bytesPerChannel) % 4 != 0) {	
        throw std::runtime_error("Alignment of each line of the pixel array needs to be multiple of 4."
                                 "See https://www.khronos.org/opengl/wiki/Common_Mistakes#Texture_upload_and_pixel_reads");
    }
    if (newWidth != this->width || newHeight != this->height) {
        this->width = newWidth;
        this->height = newHeight;

        delete data;
        data = new float[newWidth * newHeight * numChannels]();
        samplesPerPixel = 0;
    }
}

void QuadRenderer::writePixel(int row, int col, Color color) {
    int startIndex = (col + row * width) * numChannels;
    data[startIndex] = color.x;
    data[startIndex + 1] = color.y;
    data[startIndex + 2] = color.z;
}

void QuadRenderer::accumulatePixel(int row, int col, Color color) {
    int startIndex = (col + row * width) * numChannels;
    data[startIndex] += color.x;
    data[startIndex + 1] += color.y;
    data[startIndex + 2] += color.z;
}

void QuadRenderer::reset() {
    int size = width * height * numChannels;
    for (int i = 0; i < size; ++i) {
        data[i] = 0.0f;
    }
    samplesPerPixel = 0;
}

const float *QuadRenderer::scaledData() const {
    if (samplesPerPixel == 0) {
        throw std::runtime_error("Cannot scale image data when samples per pixel is 0.");
    }
    int size = width * height * numChannels;
    float *imgDataCopy = new float[size];
    memcpy(imgDataCopy, data, size * bytesPerChannel);
    float divisor = samplesPerPixel / exposure;
    for (int i = 0; i < size; ++i) {
        imgDataCopy[i] /= divisor;
    }
    return imgDataCopy;
}

