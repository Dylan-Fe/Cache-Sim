//
//  SetAssociative.hpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//

#ifndef SetAssociative_hpp
#define SetAssociative_hpp

#include <string>
#include <vector>

class SetAssociative {
public:
    SetAssociative(int assoc, int lineSize, int cacheSize);
    void simulateLRU(std::string instruction, unsigned long long address);
    void simulateNoAloe(std::string instruction, unsigned long long address);
    void simulateNLP(std::string instruction, unsigned long long address);
    void simulatePoM(std::string instruction, unsigned long long address);
    unsigned long globalTime;
    int cacheHits;
private:
    int log2(unsigned int powerOf2);
    struct Block {
        bool valid;
        unsigned long long tag;
        unsigned long timestamp;
    };
    int shiftby;
    int ways;
    unsigned lineBytes;
    std::vector<std::vector<Block> > blocks;
};

#endif /* SetAssociative_hpp */
