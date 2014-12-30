//
//  Sprite.cpp
//  Game Engine
//
//  Created by Bojan Percevic on 12/23/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "Sprite.h"
#include "Error.h"
#include "Vertex.h"
#include "AssetManager.h"
#include <iostream>

namespace BPGameEngine {
    
    Sprite::Sprite() {
        _vertexBufferObject = 0;
        _vertexArrayObject = 0;
    }

    Sprite::~Sprite() {
        if (!_vertexBufferObject) {
            glDeleteBuffers(1, &_vertexBufferObject);
        }
        if (!_vertexArrayObject) {
            glDeleteBuffers(1, &_vertexArrayObject);
        }
    }

    void Sprite::init(float x, float y, float width, float height, std::string textureFilepath) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
        _texture = AssetManager::getTextureForFilepath(textureFilepath);
        
        // Create array to hold vertices for a square
        Vertex vertexData[6];
        
        // Loading position, uv, and color will be set automatically in the future
        // once we are loading model files
        // First triangle
        vertexData[0].setPosition(x+width, y+height);
        vertexData[0].setUV(1, 1);
        vertexData[0].setColor(255, 0, 0, 255);
        
        vertexData[1].setPosition(x, y+height);
        vertexData[1].setUV(0, 1);
        vertexData[1].setColor(0, 255, 0, 255);
        
        vertexData[2].setPosition(x, y);
        vertexData[2].setUV(0, 0);
        vertexData[2].setColor(0, 0, 255, 255);
        
        // Second triangle
        vertexData[3].setPosition(x, y);
        vertexData[3].setUV(0, 0);
        vertexData[3].setColor(0, 255, 0, 255);
        
        vertexData[4].setPosition(x+width, y);
        vertexData[4].setUV(1, 0);
        vertexData[4].setColor(255, 255, 0, 255);
        
        vertexData[5].setPosition(x+width, x+height);
        vertexData[5].setUV(1, 1);
        vertexData[5].setColor(0, 0, 100, 255);
        
        // VAO and VBO
        if (!_vertexArrayObject) {
            glGenVertexArrays(1, &_vertexArrayObject);
        }

        // Generate vertex buffer
        if (!_vertexBufferObject) {
            glGenBuffers(1, &_vertexBufferObject);
        }
        
        // Bind VAO then VBO
        glBindVertexArray(_vertexArrayObject);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
        
        // Enable attributes and describe them
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        
        // Activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture.id);

        /*
        // This wont do anything, because our texture is bound to the 0th texture state
        // The 1st texture state is being unbound here, but there was never a texture bound there to begin with.
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
         */
       
        // Send data to graphics card
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        
        // Unbind VBO then VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Sprite::draw() {
        glBindVertexArray(_vertexArrayObject);
    //        glActiveTexture(GL_TEXTURE0);
    //            glBindTexture(GL_TEXTURE_2D, _texture.id);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
    //            glBindTexture(GL_TEXTURE_2D, 0);
    //        glActiveTexture(0);
        glBindVertexArray(0);
    }

}