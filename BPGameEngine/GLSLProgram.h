//
//  GLSLProgram.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/24/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__GLSLProgram__
#define ___D_Game_Engine__GLSLProgram__

#include <stdio.h>
#include <string>
#include <OpenGL/gl3.h>

namespace BPGameEngine {
    
    class GLSLProgram {
        
    private:
        GLuint _program;
        GLuint _vertexShader;
        GLuint _fragmentShader;
        int _numberAttributes;
        
        void compileShader(const std::string filePath, GLuint shader);
        
    public:
        GLSLProgram();
        ~GLSLProgram();
        
        void loadShaders(const std::string &vertShaderFilePath, const std::string &fragShaderFilePath);
        void linkShaders();
        void addAttribute(const std::string &attributeName);
        void use();
        void unuse();
        
        GLint getUniformLocation(const std::string &uniformName);
    };
    
}

#endif /* defined(___D_Game_Engine__GLSLProgram__) */
