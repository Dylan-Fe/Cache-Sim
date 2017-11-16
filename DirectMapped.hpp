//
//  DirectMapped.hpp
//  
//
//  Created by Dylan Ferrara on 11/17/15.
//
//

#ifndef DirectMapped_hpp
#define DirectMapped_hpp

#include <vector>
#include <string>

class DirectMapped {
public:
    DirectMapped(int lineSize, int cacheSize);
    void simulate(std::string instruction, unsigned long long address);
    int cacheHits;
private:
    int log2(unsigned int powerOf2);
    struct Block {
        bool valid;
        unsigned long long tag;
    };
    int shiftby;
    std::vector<Block> blocks;
};

#endif /* DirectMapped_hpp */
