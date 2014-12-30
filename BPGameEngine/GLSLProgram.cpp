//
//  GLSLProgram.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/24/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "GLSLProgram.h"
#include "Error.h"
#include <fstream>
#include <vector>

namespace BPGameEngine {
    
    GLSLProgram::GLSLProgram() {
        _program = 0;
        _vertexShader = 0;
        _fragmentShader = 0;
        _numberAttributes = 0;
    }

    GLSLProgram::~GLSLProgram() {
        // Always detach after successful link
        glDetachShader(_program, _vertexShader);
        glDetachShader(_program, _fragmentShader);
        
        // Can now delete the shaders to free up their memory
        glDeleteShader(_vertexShader);
        glDeleteShader(_fragmentShader);
    }

    void GLSLProgram::loadShaders(const std::string &vertShaderFilePath, const std::string &fragShaderFilePath) {
        // Create program
        _program = glCreateProgram();
        
        // Create the shaders
        _vertexShader = glCreateShader(GL_VERTEX_SHADER);
        if (!_vertexShader) {
            fatalError("Could not create vertex shader!");
        }
        
        _fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        if (!_fragmentShader) {
            fatalError("Could not create fragment shader!");
        }
        
        compileShader(vertShaderFilePath, _vertexShader);
        compileShader(fragShaderFilePath, _fragmentShader);
    }

    void GLSLProgram::linkShaders() {
        // Combine shaders into one program
        glAttachShader(_program, _vertexShader);
        glAttachShader(_program, _fragmentShader);
        
        // Link program
        glLinkProgram(_program);
        
        // Error-check
        GLint isLinked = 0;
        glGetProgramiv(_program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<char> errorLog(maxLength);
            glGetProgramInfoLog(_program, maxLength, &maxLength, &errorLog[0]);
            
            glDeleteProgram(_program);
            glDeleteShader(_vertexShader);
            glDeleteShader(_fragmentShader);
            
            std::printf("%s\n", &errorLog[0]);
            fatalError("Failed to link shaders.");
        }
        
        // Always detach after successful link
        glDetachShader(_program, _vertexShader);
        glDetachShader(_program, _fragmentShader);
        
        // Can now delete the shaders to free up their memory
        glDeleteShader(_vertexShader);
        glDeleteShader(_fragmentShader);
    }

    void GLSLProgram::addAttribute(const std::string &attributeName) {
        glBindAttribLocation(_program, _numberAttributes++, attributeName.c_str());
    }

    void GLSLProgram::compileShader(const std::string filePath, GLuint shader) {
        // Load the shaders
        std::ifstream vertexFile(filePath);
        if (vertexFile.fail()) {
            perror(filePath.c_str());
            fatalError("Failed to open " + filePath);
        }
        
        // Read all data from vertex shader file into one string, line by line
        std::string fileContents = "";
        std::string line;
        
        while(std::getline(vertexFile, line)) {
            fileContents += line + "\n";
        }
        
        vertexFile.close();
        
        const char *fileContentsPointer = fileContents.c_str();
        glShaderSource(shader, 1, &fileContentsPointer, nullptr);
        
        // Compile the shader
        glCompileShader(shader);
        
        // Error-check the compilation
        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
            
            glDeleteShader(shader);
            
            std::printf("%s\n", &errorLog[0]);
            fatalError("Shader failed to compile for filepath " + filePath);
        }
    }

    void GLSLProgram::use() {
        glUseProgram(_program);
        // Make the properties at top of shader usable
        for (int i=0; i<_numberAttributes; i++) {
            glEnableVertexAttribArray(i);
        }
    }

    void GLSLProgram::unuse() {
        glUseProgram(0);
        for (int i=0; i<_numberAttributes; i++) {
            glDisableVertexAttribArray(i);
        }
    }


    GLint GLSLProgram::getUniformLocation(const std::string &uniformName) {
        GLint location = glGetUniformLocation(_program, uniformName.c_str());
        if (location == GL_INVALID_INDEX) {
            fatalError("Uniform " + uniformName + " not found in shader.");
        }
        return location;
    }

}