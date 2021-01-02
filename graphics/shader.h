//
// Created by Oliver Zhang on 2020-12-31.
//

#ifndef PATHTRACED_FLIGHT_SIM_SHADER_H
#define PATHTRACED_FLIGHT_SIM_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

/**
 * Lightweight wrapper class reading opengl shader programs from file and compiling, linking, and using them.
 */
class Shader {
private:
    GLuint shader;
    bool hasShaderProgram = false;

public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    ~Shader();

    void use();

    int ID() { return shader; };
};


#endif //PATHTRACED_FLIGHT_SIM_SHADER_H
