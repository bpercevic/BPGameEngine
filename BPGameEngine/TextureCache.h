//
//  TextureCache.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__TextureCache__
#define ___D_Game_Engine__TextureCache__

#include <stdio.h>
#include <map>
#include <string>
#include "GLTexture.h"

namespace BPGameEngine {
    
    class TextureCache {
    public:
        TextureCache();
        ~TextureCache();
        GLTexture getTextureForFilepath(std::string filePath);
        
    private:
        std::map<std::string, GLTexture> _textureMap;
    };

}

#endif /* defined(___D_Game_Engine__TextureCache__) */
