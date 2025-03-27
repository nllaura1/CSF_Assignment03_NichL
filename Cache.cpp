#include "Cache.h"
#include <cmath>
#include <iostream>

Cache::Cache(int numSets, int blockSize, int associativity,
             int rPolicy, int wPolicy, int allocPolicy)
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
    int memCycles = 100 * ((blockSize) / 4); 

    if (operation == 'l') {
        totalLoads++;
        set.access(tag, false, hit, dirtyEvict);
        if (hit) {
            loadHits++;
            totalCycles += 1;
        } else {
            loadMisses++;
            bool dummyEvict = false;
            set.insert(tag, false, dummyEvict);
            totalCycles += memCycles + 1; // miss penalty
        }
    } else if (operation == 's') {
        totalStores++;
        set.access(tag, true, hit, dirtyEvict);
        if (hit) {
            storeHits++;
            if (writePolicy == 0) { // write-back
                totalCycles += 1;
            } else { // write-through
                totalCycles += 1 + memCycles; // 1 for cache + 100 for memory
            }
        } else {
            
            storeMisses++;

            if (allocationPolicy == 0) { // write-allocate
                bool dirtyEvict = false;
                set.insert(tag, true, dirtyEvict);
            
                totalCycles += memCycles + 1; // read block into cache and store
                if (writePolicy == 1) { // write-through: write to memory too
                    totalCycles += memCycles;
                }
            
                if (dirtyEvict && writePolicy == 0) { // write-back dirty eviction
                    totalCycles += memCycles;
                }
            } else {
                // no-write-allocate: don't load block into cache
                totalCycles += memCycles; // write directly to memory only
            }
            

        }

        // If no-write-allocate and miss then skip insert
        if (hit && dirtyEvict && writePolicy == 0) {
            totalCycles += memCycles; // write-back dirty eviction cost
        }
    }
}

uint32_t Cache::extractIndex(uint32_t address) {
    return (address >> offsetBits) & indexMask;
}

uint32_t Cache::extractTag(uint32_t address) {
    return address >> (offsetBits + indexBits);
}