#include "Cache.h"
#include <cmath>

Cache::Cache(int cacheSize, int blockSize, int associativity, std::string evictPrefString)
    : size(cacheSize), blockSize(blockSize), associativity(associativity), replacementPolicy(policy) {

    numSets = cacheSize / (blockSize * associativity);
    offsetBits = static_cast<int>(std::log2(blockSize));
    indexBits = static_cast<int>(std::log2(numSets));
    indexMask = (1 << indexBits) - 1;

    sets.reserve(numSets);
    for (int i = 0; i < numSets; ++i) {
        sets.emplace_back(associativity, replacementPolicy);
    }
}

bool Cache::read(uint32_t address) {
    uint32_t index = extractIndex(address);
    uint32_t tag = extractTag(address);
    return sets[index].access(tag, false);
}

bool Cache::write(uint32_t address) {
    uint32_t index = extractIndex(address);
    uint32_t tag = extractTag(address);
    return sets[index].access(tag, true);
}

uint32_t Cache::extractIndex(uint32_t address) {
    return (address >> offsetBits) & indexMask;
}

uint32_t Cache::extractTag(uint32_t address) {
    return address >> (offsetBits + indexBits);
}