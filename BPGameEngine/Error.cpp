//
//  Error.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/24/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "Error.h"
#include <iostream>
#include <OpenGL/gl3.h>
#include <SDL2/SDL.h>

namespace BPGameEngine {
    
    void fatalError(std::string error) {
        std::cout << error << std::endl;
        std::cout << "Enter any key to quit";
        int tmp;
        std::cin >> tmp;
        SDL_Quit();
        exit(1);
    }

    void glErrorCheck() {
        // check OpenGL error
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::string error;
            switch(err) {
                case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
                case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
                case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
                case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
            }
            std::cerr << "OpenGL error: " << error << std::endl;
        }
    }

}