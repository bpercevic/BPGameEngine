//
//  InputManager.cpp
//  BPGameEngine
//
//  Created by Bojan Percevic on 1/1/15.
//  Copyright (c) 2015 Bojan Percevic. All rights reserved.
//

#include "InputManager.h"

namespace BPGameEngine {
    
    InputManager::InputManager() {
        
    }
    
    InputManager::~InputManager() {
        
    }
    
    void InputManager::pressKey(unsigned int keyID) {
        _keyMap[keyID] = true;
    }
    
    void InputManager::releaseKey(unsigned int keyID) {
        _keyMap[keyID] = false;
    }
    
    bool InputManager::isKeyPressed(unsigned int keyID) {
        auto iter = _keyMap.find(keyID);
        if (iter != _keyMap.end()) {
            return iter->second;
        }
        return false;
    }
    
}