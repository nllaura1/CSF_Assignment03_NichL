#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cstdint>
#include "Set.h"

class Cache {
public:
    Cache(int cacheSize, int blockSize, int associativity, bool lru, bool );

    bool read(uint32_t address);
    bool write(uint32_t address);

private:
    int size;
    int blockSize;
    int associativity;
    int numSets;
    int evictPref;
    // lru = 0
    //fifo = 1

    std::vector<Set> sets;

    uint32_t extractIndex(uint32_t address);
    uint32_t extractTag(uint32_t address);

    int offsetBits;
    int indexBits;
    uint32_t indexMask;
};

#endif
