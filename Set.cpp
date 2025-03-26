#include "Set.h"
#include <algorithm>

Set::Set(int associativity, ReplacementPolicy policy)
    : policy(policy), blocks(associativity) {}

bool Set::access(uint32_t tag, bool isWrite, bool& hit, bool& dirtyEvict) {
    Block* blk = findBlock(tag);
    if (blk && blk->valid) {
        hit = true;
        if (isWrite) blk->dirty = true;
        updateLRU(blk);
        return blk->dirty;
    }
    hit = false;
    return false;
}

void Set::insert(uint32_t tag, bool isWrite) {
    Block* victim = selectVictim();
    victim->valid = true;
    victim->tag = tag;
    victim->dirty = isWrite;
    updateLRU(victim);
}

Block* Set::findBlock(uint32_t tag) {
    for (auto& blk : blocks) {
        if (blk.valid && blk.tag == tag) return &blk;
    }
    return nullptr;
}

Block* Set::selectVictim() {
    for (auto& blk : blocks) {
        if (!blk.valid) return &blk;
    }

    if (policy == ReplacementPolicy::LRU) {
        return &*std::min_element(blocks.begin(), blocks.end(), [](const Block& a, const Block& b) {
            return a.lruCounter < b.lruCounter;
        });
    }

    return &blocks[0]; // FIFO default
}

void Set::updateLRU(Block* accessed) {
    accessed->lruCounter = accessCounter++;
}