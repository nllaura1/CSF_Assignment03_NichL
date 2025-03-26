#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

struct Block {
    bool valid = false;
    bool dirty = false;
    uint32_t tag = 0;
    //lru 
    int lruCounter = 0;
};

#endif