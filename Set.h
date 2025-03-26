#ifndef SET_H
#define SET_H

#include <vector>
#include "Block.h"
#include "config.h"

class Set {
public:
    Set(int associativity, bool evictPref);

    bool access(uint32_t tag, bool isWrite);
    void insert(uint32_t tag, bool isWrite);

private:
    std::vector<Block> blocks;
    bool evictPref;
    //for lru
    int accessCounter = 0;

    Block* findBlock(uint32_t tag);
    Block* selectVictim();
    void updateLRU(Block* accessed);
};

#endif
