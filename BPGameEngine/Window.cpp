//
//  Window.cpp
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/29/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "Window.h"
#include "Error.h"

namespace BPGameEngine {

    Window::Window() {
        
    }

    Window::~Window() {
        
    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int windowFlags) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        
        Uint32 flags = SDL_WINDOW_OPENGL;
        if (windowFlags & HIDE_WINDOW) {
            flags |= SDL_WINDOW_HIDDEN;
        }
        if (windowFlags & FULL_SCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (windowFlags & BORDER_LESS ) {
            flags |= SDL_WINDOW_BORDERLESS;
        }
        
        // Create window
        _window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);
        if (_window == nullptr) {
            fatalError("SDL Window could not be created.");
        }
        
        // Create window context
        _context = SDL_GL_CreateContext(_window);
        if (_context == nullptr) {
            fatalError("SDL Context could not be created.");
        }
        
        // What versions am I running?
        std::cout << "OpenGL:\t" << glGetString(GL_VERSION) << "\n";
        std::cout << "GLSL:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
        
        // Set background color
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        
        return 0;
    }

    void Window::swapBuffer() {
        SDL_GL_SwapWindow(_window);
    }

}