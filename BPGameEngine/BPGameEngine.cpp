//
//  BPGameEngine.cpp
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/29/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "BPGameEngine.h"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

namespace BPGameEngine {
    
    int init() {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
        
        // Trying to support latest OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        // I don't know what these next things do, but eh for now
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        return 0;
    }

}