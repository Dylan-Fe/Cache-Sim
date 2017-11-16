//
//  FullyAssociative.cpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//

#include "FullyAssociative.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

FullyAssociative::FullyAssociative(int lineSize, int cacheSize) {
    cacheSize = cacheSize * 1024;
    int numLevels = log2(cacheSize/lineSize) + 1;
    for(int i = 0; i < cacheSize/lineSize; i++) {
        Block block;
        block.valid = false;
        block.tag = 0;
        block.timestamp = 0;
        blocks.push_back(block);
    }
    shiftby = log2(lineSize);
    root = createTree(numLevels);
    cacheHits = 0;
    globalTime = 0;
}

Node* FullyAssociative::createTree(int numUnderneath) {
    Node* n = new Node();
    if(numUnderneath > 1) {
        n->left = createTree(numUnderneath - 1);
        n->right = createTree(numUnderneath - 1);
    } else {
        n->isLeafNode = true;
    }
    return n;
}

int FullyAssociative::log2(unsigned int powerOf2) {
    int index = 0;
    while(!(powerOf2 & 0x1)) {
        index++;
        powerOf2 >>= 1;
    }
    return index;
}

void FullyAssociative::simulateLRU(string instruction, unsigned long long address) {
    unsigned long long tag = (address >> shiftby);
    globalTime++;
    
    bool replace = true;
    for (int i = 0; i < blocks.size(); i++) {
        if (!(blocks[i].valid)) {
            blocks[i].valid = true;
            blocks[i].tag = tag;
            blocks[i].timestamp = globalTime;
            replace = false;
            break;
        } else if (blocks[i].valid && blocks[i].tag == tag) {
            blocks[i].timestamp = globalTime;
            replace = false;
            cacheHits++;
            break;
        }
    }
    
    //LRU replacement
    if (replace) {
        int index = 0;
        unsigned long min = globalTime;
        for (int i = 0; i < blocks.size(); i++) {
            if (blocks[i].valid && blocks[i].timestamp < min) {
                min = blocks[i].timestamp;
                index = i;
            }
        }
        blocks[index].tag = tag;
        blocks[index].timestamp = globalTime;
    }
}

//Hot-Cold Replacement
void FullyAssociative::simulateHC(string instruction, unsigned long long address) {
    unsigned long long tag = (address >> shiftby);
    foundInCache = false;
    findInCacheAndMaybeUpdate(root, tag);
    if(!foundInCache) {
        findColdestReplaceAndUpdate(root, tag);
    }
}

bool FullyAssociative::findInCacheAndMaybeUpdate(Node* curr, unsigned long long tag) {
    if(!foundInCache){
        if(curr->isLeafNode) {
            if(curr->valid && curr->tag == tag) {
                cacheHits++;
                foundInCache = true;
                return true;
            }
        } else {
            bool leftNowHot = findInCacheAndMaybeUpdate(curr->left, tag);
            bool rightNowHot = findInCacheAndMaybeUpdate(curr->right, tag);
            if(leftNowHot) {
                curr->right->hot = false;
                curr->left->hot = true;
                curr->hot = true;
                return true;
            } else if(rightNowHot) {
                curr->left->hot = false;
                curr->right->hot = true;
                curr->hot = true;
                return true;
            }
        }
    }
    return false;
}

void FullyAssociative::findColdestReplaceAndUpdate(Node* curr, unsigned long long tag) {
    if(curr->isLeafNode) {
        curr->tag = tag;
        curr->valid = true;
        return;
    }
    bool rightHot = curr->right->hot;
    if(rightHot) {
        findColdestReplaceAndUpdate(curr->left, tag);
        curr->left->hot = true;
        curr->right->hot = false;
        curr->hot = true;
    } else {
        findColdestReplaceAndUpdate(curr->right, tag);
        curr->right->hot = true;
        curr->left->hot = false;
        curr->hot = true;
    }
}