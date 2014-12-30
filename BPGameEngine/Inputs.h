//
//  Inputs.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__Inputs__
#define ___D_Game_Engine__Inputs__

#include <stdio.h>
#include <SDL2/SDL.h>

namespace BPGameEngine {

    const int AXIS_DEADZONE = 8000;

    class Inputs {
    public:
        Inputs();
        ~Inputs();
        bool openControllerAtIndex(unsigned int index);
        void closeControllerAtIndex(unsigned int index);
        SDL_Joystick* controllerAtIndex(unsigned int index);
        void process(const SDL_Event event);
        
    private:
        SDL_Joystick *_controllers[4];
        
    };

}

#endif /* defined(___D_Game_Engine__Inputs__) */
