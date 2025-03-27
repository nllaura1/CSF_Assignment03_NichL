#ifndef SET_H
#define SET_H

#include <vector>
#include "Block.h"

class Set {
public:
    Set(int associativity, int policy);

    bool access(uint32_t tag, bool isWrite, bool& hit, bool& dirtyEvict);
    bool insert(uint32_t tag, bool isWrite, bool& dirtyEvict);


private:
    std::vector<Block> blocks;
    int policy; //0 - fifo, 1 - lru
    int accessCounter = 0; // For LRU

    Block* findBlock(uint32_t tag);
    Block* selectVictim();
    void updateLRU(Block* accessed);
};

#endif