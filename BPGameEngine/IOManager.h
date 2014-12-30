//
//  IOManager.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__IOManager__
#define ___D_Game_Engine__IOManager__

#include <stdio.h>
#include <vector>

namespace BPGameEngine {
    
    class IOManager {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
    };
}

#endif /* defined(___D_Game_Engine__IOManager__) */
