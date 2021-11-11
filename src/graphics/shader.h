//
// Created by Oliver Zhang on 2020-12-31.
//

#ifndef PATHTRACED_RENDERER_SHADER_H
#define PATHTRACED_RENDERER_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

/**
 * Lightweight wrapper class reading opengl shader programs from file and compiling, linking, and using them.
 */
class Shader {
private:
    GLuint shader;

public:
    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    ~Shader();

    void use();

    void setFloat(const std::string &name, float value) const;
    int ID() const { return shader; };
};


#endif //PATHTRACED_RENDERER_SHADER_H
