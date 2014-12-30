//
//  Vertex.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef _D_Game_Engine_Vertex_h
#define _D_Game_Engine_Vertex_h

#include <OpenGL/gl3.h>

namespace BPGameEngine {
    
    struct Position {
        float x;
        float y;
    };

    struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV {
        float u;
        float v;
    };

    // Structs should be a multiple of 4 bytes.

    struct Vertex {
    //    float position[2];      // 8 bytes
    //    GLubyte color[3];     // 3 bytes for RGB ... will be much smaller with array of bytes
                                // = 11 bytes
    //    GLubyte padding;      // placeholder, just so that we have multiple of 4 bytes
                                // = 12 bytes
                                // Instead of the padding, lets add alpha to color
    //    GLubyte color[4];       // 4 bytes for RGBA
                                // = 12 bytes
        Position position;
        Color color;
        UV uv;
        
        // functions dont affect the memory consumption of the struct
        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }
        
        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }
        
        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }
    };

}
#endif
