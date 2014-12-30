//
//  Window.h
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/29/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef __BPGameEngine__Window__
#define __BPGameEngine__Window__

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

namespace BPGameEngine {
    
    enum WindowFlags {
        HIDE_WINDOW = 0b0001,
        FULL_SCREEN = 0b0010,
        BORDER_LESS = 0b0100
        // These can also be written as 0x1, 0x2, and 0x4
    };

    class Window {
    public:
        Window();
        ~Window();
        
        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags);
        int screenWidth() { return _screenWidth; };
        int screenHeight() { return _screenHeight; };
        void swapBuffer();
        
    private:
        SDL_Window *_window;
        SDL_GLContext _context;
        int _screenWidth;
        int _screenHeight;
        
    };
    
}

#endif /* defined(__BPGameEngine__Window__) */
