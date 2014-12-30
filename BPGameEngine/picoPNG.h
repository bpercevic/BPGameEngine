//
//  picoPNG.h
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef ___D_Game_Engine__picoPNG__
#define ___D_Game_Engine__picoPNG__

#include <vector>

namespace BPGameEngine {

    extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

}

#endif /* defined(___D_Game_Engine__picoPNG__) */
