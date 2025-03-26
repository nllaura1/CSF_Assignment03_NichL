#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstdint>
#include "Set.h"

class Cache {
public:
    Cache(int numSets, int blockSize, int associativity,
          int rPolicy, int wPolicy, int allocPolicy);
    void access(char operation, uint32_t address, int size);

    //Statistics tracking
    int totalLoads = 0;
    int totalStores = 0;
    int loadHits = 0;
    int loadMisses = 0;
    int storeHits = 0;
    int storeMisses = 0;
    int totalCycles = 0;

private:
    int numSets;
    int blockSize;
    int associativity;
    int replacementPolicy; //0 - fifo, 1 - lru
    int writePolicy; //0 - write-back, 1 - write-through
    int allocationPolicy; //0 write-allocate, 1 - no-write-allocate

    std::vector<Set> sets;

    uint32_t extractIndex(uint32_t address);
    uint32_t extractTag(uint32_t address);

    int offsetBits;
    int indexBits;
    uint32_t indexMask;
};

#endif
