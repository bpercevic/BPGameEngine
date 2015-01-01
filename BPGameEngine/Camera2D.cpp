//
//  Camera2D.cpp
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/31/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "Camera2D.h"

namespace BPGameEngine {

    Camera2D::Camera2D() :
        _position(0.f, 0.f),
        _matrix(1.f),
        _orthoMatrix(1.f),
        _scale(1.f),
        _dirty(true),
        _screenWidth(500),
        _screenHeight(500)
    {

    }

    Camera2D::~Camera2D() {
        
    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.f, (float)_screenWidth, 0.f, (float)_screenHeight);
    }

    void Camera2D::update() {
        if (_dirty) {
            glm::vec3 translation = glm::vec3(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.f);
            _matrix = glm::translate(_orthoMatrix, translation);
            
            glm::vec3 scale = glm::vec3(_scale, _scale, 0.f);
            _matrix = glm::scale(glm::mat4(1.f), scale) * _matrix;
            
            _dirty = false;
        }
    }

}