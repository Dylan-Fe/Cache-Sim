//
//  SetAssociative.cpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//

#include "SetAssociative.hpp"
#include <vector>
#include <string>

using namespace std;

SetAssociative::SetAssociative(int assoc, int lineSize, int cacheSize) {
    cacheSize = cacheSize * 1024;
    for (int i = 0; i < (cacheSize/lineSize)/assoc; i++) {
        vector<Block> row;
        for(int j = 0; j < assoc; j++) {
            Block block;
            block.valid = false;
            block.tag = 0;
            block.timestamp = 0;
            row.push_back(block);
        }
        blocks.push_back(row);
    }
    shiftby = log2(lineSize);
    ways = assoc;
    lineBytes = lineSize;
    cacheHits = 0;
    globalTime = 0;
}

int SetAssociative::log2(unsigned int powerOf2) {
    int index = 0;
    while(!(powerOf2 & 0x1)) {
        index++;
        powerOf2 >>= 1;
    }
    return index;
}

void SetAssociative::simulateLRU(string instruction, unsigned long long address) {
    unsigned long long index = (address >> shiftby) % blocks.size();
    unsigned long long tag = (address >> shiftby >> log2(blocks.size()));
    globalTime++;
    
    bool replace = true;
    for (int i = 0; i < ways; i++) {
        if (!(blocks[index][i].valid)) {
            blocks[index][i].valid = true;
            blocks[index][i].tag = tag;
            blocks[index][i].timestamp = globalTime;
            replace = false;
            break;
        } else if (blocks[index][i].valid && blocks[index][i].tag == tag) {
            blocks[index][i].timestamp = globalTime;
            replace = false;
            cacheHits++;
            break;
        }
    }
    
    //LRU replacement
    if (replace) {
        int id = 0;
        unsigned long min = globalTime;
        for (int i = 0; i < ways; i++) {
            if (blocks[index][i].valid && blocks[index][i].timestamp < min) {
                min = blocks[index][i].timestamp;
                id = i;
            }
        }
        blocks[index][id].tag = tag;
        blocks[index][id].timestamp = globalTime;
    }
}

//No Allocation on a Write (S) Miss
void SetAssociative::simulateNoAloe(std::string instruction, unsigned long long address) {
    unsigned long long index = (address >> shiftby) % blocks.size();
    unsigned long long tag = (address >> shiftby >> log2(blocks.size()));
    globalTime++;
    
    bool replace = true;
    for (int i = 0; i < ways; i++) {
        if (!(blocks[index][i].valid) && instruction == "L") {
            blocks[index][i].valid = true;
            blocks[index][i].tag = tag;
            blocks[index][i].timestamp = globalTime;
            replace = false;
            break;
        } else if (blocks[index][i].valid && blocks[index][i].tag == tag) {
            blocks[index][i].timestamp = globalTime;
            replace = false;
            cacheHits++;
            break;
        }
    }
    
    //LRU replacement
    if (replace && instruction == "L") {
        int id = 0;
        unsigned long min = globalTime;
        for (int i = 0; i < ways; i++) {
            if (blocks[index][i].valid && blocks[index][i].timestamp < min) {
                min = blocks[index][i].timestamp;
                id = i;
            }
        }
        blocks[index][id].tag = tag;
        blocks[index][id].timestamp = globalTime;
    }
}

//Next-Line Prefecting
void SetAssociative::simulateNLP(string instruction, unsigned long long address) {
    simulateLRU(instruction, address);
    int old_cachehits = cacheHits;
    simulateLRU(instruction, address + lineBytes);
    cacheHits = old_cachehits;
}

//Prefect on a Miss
void SetAssociative::simulatePoM(string instruction, unsigned long long address) {
    int old_cachehits = cacheHits;
    simulateLRU(instruction, address);
    if (cacheHits == old_cachehits) {
        old_cachehits = cacheHits;
        simulateLRU(instruction, address + lineBytes);
        cacheHits = old_cachehits;
    }
}