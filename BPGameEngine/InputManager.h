//
//  InputManager.h
//  BPGameEngine
//
//  Created by Bojan Percevic on 1/1/15.
//  Copyright (c) 2015 Bojan Percevic. All rights reserved.
//

#ifndef __BPGameEngine__InputManager__
#define __BPGameEngine__InputManager__

#include <stdio.h>
#include <unordered_map>

namespace BPGameEngine {
    
    class InputManager {
    public:
        InputManager();
        ~InputManager();
        
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);
        bool isKeyPressed(unsigned int keyID);
        
    private:
        std::unordered_map<unsigned int, bool> _keyMap;
        
    };

}

#endif /* defined(__BPGameEngine__InputManager__) */
