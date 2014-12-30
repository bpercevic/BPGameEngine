//
//  Sprite.h
//  Game Engine
//
//  Created by Bojan Percevic on 12/23/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef __Game_Engine__Sprite__
#define __Game_Engine__Sprite__

#include "GLTexture.h"
#include <string>
#include <OpenGL/gl3.h>
#include "Vertex.h"

namespace BPGameEngine {
    
    class Sprite {
    public:
        Sprite();
        ~Sprite();
        
        void init(float x, float y, float width, float height, std::string textureFilepath);
        void draw();
        
    private:
        float _x;
        float _y;
        float _width;
        float _height;
        GLuint _vertexBufferObject;
        GLuint _vertexArrayObject;
        GLTexture _texture;
        
        void vertexData(Vertex &array);
    };

}

#endif /* defined(__Game_Engine__Sprite__) */
