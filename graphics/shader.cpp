//
// Created by Oliver Zhang on 2020-12-31.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "shader.h"

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    std::ifstream vertexShaderFile = std::ifstream(vertexShaderPath);
    if (!vertexShaderFile.is_open()) {
        throw std::runtime_error("Failed to open vertex shader file");
    }

    std::ifstream fragmentShaderFile = std::ifstream(fragmentShaderPath);
    if (!fragmentShaderFile.is_open()) {
        vertexShaderFile.close();
        throw std::runtime_error("Failed to open fragment shader file");
    }

    std::stringstream vertexShaderStream, fragmentShaderStream;

    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    std::string vertexShaderCode = vertexShaderStream.str();
    std::string fragmentShaderCode = fragmentShaderStream.str();

    const char *vertexShaderCodeCStr = vertexShaderCode.c_str();
    const char *fragmentShaderCodeCStr = fragmentShaderCode.c_str();

    std::cout << "vertexShaderCodeCstr: " << vertexShaderCodeCStr << std::endl;
    std::cout << "fragmentShaderCodeCstr: " << fragmentShaderCodeCStr << std::endl;

    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShaderID, 1, &vertexShaderCodeCStr, nullptr);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCodeCStr, nullptr);

    int success;
    char infoLog[512];

    glCompileShader(vertexShaderID);
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glDeleteShader(vertexShaderID);
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile vertex shader at " + vertexShaderPath + ": " + infoLog);
    }

    glCompileShader(fragmentShaderID);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        glGetShaderInfoLog(fragmentShaderID, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile fragment shader at " + fragmentShaderPath + ": " + infoLog);
    }

    shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);

    glLinkProgram(shaderProgramID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glGetShaderiv(shaderProgramID, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shaderProgramID, 512, nullptr, infoLog);
        throw std::runtime_error(std::string("Failed to link shader program: ") + infoLog);
    }
}

Shader::~Shader() {
    glDeleteProgram(shaderProgramID);
}

void Shader::use() {
    glUseProgram(shaderProgramID);
}