//
//  Timing.h
//  BPGameEngine
//
//  Created by Bojan Percevic on 1/1/15.
//  Copyright (c) 2015 Bojan Percevic. All rights reserved.
//

#ifndef BPGameEngine_Timing_h
#define BPGameEngine_Timing_h

#include <OpenGL/gl3.h>

namespace BPGameEngine {
    
    class FPSLimiter {
    public:
        FPSLimiter();
        ~FPSLimiter();
        
        void init(float maxFPS);
        void setMaxFPS(float fps);
        
        void beginFrame();
        float endFrame();  // return current FPS
        
    private:
        void _calculateFPS();
        
        float _maxFPS;
        GLuint _startTicks;
        float _fps;
        float _frameTime;
        

        
    };
    
    
}

#endif
