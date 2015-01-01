//
//  Timing.cpp
//  BPGameEngine
//
//  Created by Bojan Percevic on 1/1/15.
//  Copyright (c) 2015 Bojan Percevic. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Timing.h"
#include <SDL2/SDL.h>

namespace BPGameEngine {
    
    FPSLimiter::FPSLimiter() {
        
    }
    
    FPSLimiter::~FPSLimiter() {
        
    }
    
    void FPSLimiter::init(float maxFPS) {
        setMaxFPS(maxFPS);
    }
    
    void FPSLimiter::setMaxFPS(float fps) {
        _maxFPS = fps;
    }
    
    void FPSLimiter::beginFrame() {
        _startTicks = SDL_GetTicks();
    }
    
    float FPSLimiter::endFrame() {
        _calculateFPS();
        
        // Limit FPS to max FPS
        float currentFrameTicks = SDL_GetTicks() - _startTicks;
        float desiredFrameTicks = 1000.f / _maxFPS;
        if (desiredFrameTicks > currentFrameTicks) {
            SDL_Delay(desiredFrameTicks - currentFrameTicks);
        }
        
        return _fps;
    }
    
    void FPSLimiter::_calculateFPS() {
        // number of frames to average for a smoother FPS count
        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;
        
        // Get the ticks
        static float prevTicks = SDL_GetTicks();
        
        float currTicks = SDL_GetTicks();
        
        _frameTime = currTicks - prevTicks;
        
        // Use a circular buffer
        frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
        
        prevTicks = currTicks;
        
        int numberOfFramesToAverage;
        
        currentFrame++;
        
        if (currentFrame < NUM_SAMPLES) {
            numberOfFramesToAverage = currentFrame;
        } else {
            numberOfFramesToAverage = NUM_SAMPLES;
        }
        
        float frameTimeAverage = 0;
        for (int i=0; i<numberOfFramesToAverage; i++) {
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage /= numberOfFramesToAverage;
        
        if (numberOfFramesToAverage > 0) {
            _fps = 1000.f / frameTimeAverage;
        } else {
            _fps = -1.f;
        }
    }
    
}