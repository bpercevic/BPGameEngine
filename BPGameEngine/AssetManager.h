//
//  AssetManager.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__AssetManager__
#define ___D_Game_Engine__AssetManager__

#include <stdio.h>
#include "TextureCache.h"
#include "GLTexture.h"

namespace BPGameEngine {
    
    class AssetManager {
    public:
        static GLTexture getTextureForFilepath(std::string filePath);
        
    private:
        static TextureCache _textureCache;
    };
    
}

#endif /* defined(___D_Game_Engine__AssetManager__) */
