//
//  AssetManager.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "AssetManager.h"

namespace BPGameEngine {

    TextureCache AssetManager::_textureCache;

    GLTexture AssetManager::getTextureForFilepath(std::string filePath) {
        return _textureCache.getTextureForFilepath(filePath);
    }

}