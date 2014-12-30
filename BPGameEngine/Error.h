//
//  Error.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/24/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__Error__
#define ___D_Game_Engine__Error__

#include <stdio.h>
#include <string>

namespace BPGameEngine {
    
    extern void fatalError(std::string error);
    extern void glErrorCheck();
    
}

#endif /* defined(___D_Game_Engine__Error__) */
