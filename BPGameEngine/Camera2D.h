//
//  Camera2D.h
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/31/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef __BPGameEngine__Camera2D__
#define __BPGameEngine__Camera2D__

#include <stdio.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace BPGameEngine {

    class Camera2D {
    public:
        Camera2D();
        ~Camera2D();
        
        void init(int screenWidth, int screenHeight);
        void update();
        
    #pragma mark - Setters
        void setPosition(const glm::vec2 &p) {
            _position = p;
            _dirty = true;
        }
        
        void setScale(float s) {
            _scale = s;
            _dirty = true;
        }
        
    #pragma mark - Getters
        glm::vec2 getPosition() {
            return _position;
        }
        
        glm::mat4 getMatrix() {
            return _matrix;
        }
        
        float getScale() {
            return _scale;
        }
        
    private:
        glm::vec2 _position;
        glm::mat4 _matrix;
        glm::mat4 _orthoMatrix;
        float _scale;
        bool _dirty;    // camera needs an updated matrix
        int _screenWidth;
        int _screenHeight;
    };

}

#endif /* defined(__BPGameEngine__Camera2D__) */
