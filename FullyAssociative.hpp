//
//  FullyAssociative.hpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//

#ifndef FullyAssociative_hpp
#define FullyAssociative_hpp

#include <vector>
#include <string>

struct Node {
public:
    Node() {
        tag = 0;
        left = nullptr;
        right = nullptr;
        isLeafNode = false;
        hot = false;
        valid = false;
    }
    unsigned long long tag;
    Node* left;
    Node* right;
    bool isLeafNode;
    bool hot;
    bool valid;
};

class FullyAssociative {
public:
    FullyAssociative(int lineSize, int cacheSize);
    void simulateLRU(std::string instruction, unsigned long long address);
    void simulateHC(std::string instruction, unsigned long long address);
    Node* createTree(int numUnderneath);
    unsigned long globalTime;
    int cacheHits;
private:
    void findColdestReplaceAndUpdate(Node* curr, unsigned long long tag);
    bool findInCacheAndMaybeUpdate(Node* curr, unsigned long long tag);
    Node* root;
    int log2(unsigned int powerOf2);
    void printTree(Node* current, int level);
    struct Block {
        bool valid;
        unsigned long long tag;
        unsigned long timestamp;
    };
    int shiftby;
    bool foundInCache;
    std::vector<Block> blocks;
};

#endif /* FullyAssociative_hpp */
