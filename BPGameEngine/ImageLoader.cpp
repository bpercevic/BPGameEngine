//
//  ImageLoader.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "ImageLoader.h"
#include "IOManager.h"
#include "picoPNG.h"
#include "Error.h"

namespace BPGameEngine {

    GLTexture ImageLoader::loadPNG(std::string filePath) {
        std::vector<unsigned char> in;
        std::vector<unsigned char> out;
        unsigned long width, height;
        
        if (!IOManager::readFileToBuffer(filePath, in)) {
            fatalError("Failed to load PNG file to buffer");
        }
        
        int errorCode = decodePNG(out, width, height, &in[0], in.size());
        if (errorCode != 0) {
            fatalError("decodePNG failed with error: " + std::to_string(errorCode));
        }
        
        // Initialize a texture
        GLTexture texture = {0, width, height};
        
        // Generate and bind the texture
        glGenTextures(1, &texture.id);
        glBindTexture(GL_TEXTURE_2D, texture.id);
        
        // Load the texture image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);
        
        // Set texture wrap options per coordinate S=X, T=Y, R=Z
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        
        // Set the interpolation types for magnification and minification of the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
        // A mipmap is a sequence of textures of an original texture, meaning that
        // there will be different textures generated for different resolutions
        glGenerateMipmap(GL_TEXTURE_2D);
        
        // As always, unbind
        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

}