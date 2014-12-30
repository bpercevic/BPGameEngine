//
//  GLTexture.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef _D_Game_Engine_GLTexture_h
#define _D_Game_Engine_GLTexture_h

#include <OpenGL/gl3.h>

namespace BPGameEngine {
    
    struct GLTexture {
        GLuint id;
        unsigned long width;
        unsigned long height;
    };
    
}

#endif
