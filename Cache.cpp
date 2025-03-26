#include "Cache.h"
#include <cmath>
#include <iostream>

Cache::Cache(int numSets, int blockSize, int associativity,
             ReplacementPolicy rPolicy, WritePolicy wPolicy, AllocationPolicy allocPolicy)
    : numSets(numSets), blockSize(blockSize), associativity(associativity),
      replacementPolicy(rPolicy), writePolicy(wPolicy), allocationPolicy(allocPolicy) {

    offsetBits = static_cast<int>(std::log2(blockSize));
    indexBits = static_cast<int>(std::log2(numSets));
    indexMask = (1 << indexBits) - 1;

    sets.reserve(numSets);
    for (int i = 0; i < numSets; ++i) {
        sets.emplace_back(associativity, replacementPolicy);
    }
}

void Cache::access(char operation, uint32_t address) {
    uint32_t index = extractIndex(address);
    uint32_t tag = extractTag(address);
    Set& set = sets[index];

    bool hit = false;
    bool dirtyEvict = false;

    if (operation == 'l') {
        set.access(tag, false, hit, dirtyEvict);
        if (!hit) set.insert(tag, false);
    } else if (operation == 's') {
        set.access(tag, true, hit, dirtyEvict);
        if (!hit && allocationPolicy == AllocationPolicy::WRITE_ALLOCATE) {
            set.insert(tag, true);
        }
        // If NO_WRITE_ALLOCATE and miss, skip insert
    }
}

uint32_t Cache::extractIndex(uint32_t address) {
    return (address >> offsetBits) & indexMask;
}

uint32_t Cache::extractTag(uint32_t address) {
    return address >> (offsetBits + indexBits);
}
