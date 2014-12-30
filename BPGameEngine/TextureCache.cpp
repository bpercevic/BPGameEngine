//
//  TextureCache.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace BPGameEngine {
    
    TextureCache::TextureCache() {
        
    }

    TextureCache::~TextureCache() {

    }

    GLTexture TextureCache::getTextureForFilepath(std::string filePath) {
        GLTexture texture;
    //    std::map<std::string, GLTexture>::iterator iter = _textureMap.find(filePath);
    //    auto is smart enough to infer this type above - but use it sparingly
        auto iter = _textureMap.find(filePath);
        if (iter == _textureMap.end()) {
            // did not find the texture, so load it
            texture = ImageLoader::loadPNG(filePath);
            
            // Create a pair to store into the map
    //        std::pair<std::string, GLTexture> pair(filePath, texture);
    //        _textureMap.insert(pair);
            _textureMap.insert(make_pair(filePath, texture));
            std::cout << "loaded texture\n";
        } else {
            std::cout << "loaded cached texture\n";
            // iter->first points to the key, ->second points to value
            texture = iter->second;
        }
        
        
        return texture;
    }

}