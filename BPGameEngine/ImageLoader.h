//
//  ImageLoader.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__ImageLoader__
#define ___D_Game_Engine__ImageLoader__

#include <stdio.h>
#include <string>
#include "GLTexture.h"

namespace BPGameEngine {
    
    class ImageLoader {
    public:
        static GLTexture loadPNG(std::string filePath);
    };
}

#endif /* defined(___D_Game_Engine__ImageLoader__) */
