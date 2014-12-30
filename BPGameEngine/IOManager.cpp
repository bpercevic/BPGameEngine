//
//  IOManager.cpp
//  2D Game Engine
//
//  Created by Bojan Percevic on 12/27/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "IOManager.h"
#include "Error.h"
#include <fstream>

namespace BPGameEngine {
    
    bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer) {
        // reading file in binary format, dont care about newlines or anything like that
        // binary will give us exact contents of file
        std::ifstream file(filePath, std::ios::binary);
        if (file.fail()) {
            perror(filePath.c_str());
            fatalError("Failed to read " + filePath + " to buffer.");
            return false;
        }
        
        // must resize buffer to size of buffer
        // seekg and tellg
        
        // seek to 0 bytes offsend from the end
        file.seekg(0, std::ios::end);
        
        // get size
        long long fileSize = file.tellg();
        
        // seek back to beginning so we can read the file again from the beginning
        file.seekg(0, std::ios::beg);
        
        // not required: but some files have headers with extra bytes
        fileSize -= file.tellg();
        
        buffer.resize(fileSize);
        
        // read(char *buffer, bytesToRead)
        // so because internally a vector is an array,
        // we can pass the address of the first item as the char array that it wants
        file.read((char *)&buffer[0], fileSize);
        file.close();
        
        return true;
    }

}