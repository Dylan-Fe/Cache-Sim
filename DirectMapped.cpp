//
//  DirectMapped.cpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//

#include "DirectMapped.hpp"
#include <vector>
#include <string>

using namespace std;

DirectMapped::DirectMapped(int lineSize, int cacheSize) {
    cacheSize = cacheSize * 1024;
    for(int i = 0; i < cacheSize/lineSize; i++) {
        Block block;
        block.valid = false;
        block.tag = 0;
        blocks.push_back(block);
    }
    shiftby = log2(lineSize);
    cacheHits = 0;
}

int DirectMapped::log2(unsigned int powerOf2) {
    int index = 0;
    while(!(powerOf2 & 0x1)) {
        index++;
        powerOf2 >>= 1;
    }
    return index;
}

void DirectMapped::simulate(string instruction, unsigned long long address) {
    unsigned long long index = (address >> shiftby) % blocks.size();
    unsigned long long tag = (address >> shiftby >> log2(blocks.size()));
    
    if (blocks[index].valid && blocks[index].tag == tag) {
        cacheHits++;
    } else {
        blocks[index].valid = true;
        blocks[index].tag = tag;
    }
}