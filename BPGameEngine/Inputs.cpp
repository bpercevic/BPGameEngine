//
//  Inputs.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "Inputs.h"
#include "Error.h"
#include <iostream>

namespace BPGameEngine {
    
    Inputs::Inputs() {

    }

    Inputs::~Inputs() {
        
    }

    bool Inputs::openControllerAtIndex(unsigned int index) {
        if (SDL_JoystickNameForIndex(index) == NULL) {
            fatalError("No controller for that index.");
        }

        if (_controllers[index]) {
            // We already have this controller
            return true;
        } else {
            // We don't have this controller
            SDL_Joystick *joy = SDL_JoystickOpen(index);
            if (joy) {
                _controllers[index] = joy;
            } else {
                fatalError("Couldn't open controller for index: " + std::to_string(index));
            }
        }
        
        return true;
    }

    void Inputs::closeControllerAtIndex(unsigned int index) {
        _controllers[index] = NULL;
        SDL_JoystickClose(controllerAtIndex(index));
    }

    SDL_Joystick* Inputs::controllerAtIndex(unsigned int index) {
        return _controllers[index];
    }

    void Inputs::process(const SDL_Event event) {
    //    std::cout << event.jaxis.value << std::endl;
    }

}