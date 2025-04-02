#include "Set.h"
#include <algorithm>
#include <deque>

Set::Set(int associativity, int policy)
    : blocks(associativity), policy(policy) {}

bool Set::access(uint32_t tag, bool isWrite, bool& hit, bool& dirtyEvict) {
    Block* blk = findBlock(tag);

    if (blk) {
        hit = true;
        if (isWrite) blk->dirty = true;
        updateLRU(blk);
        return blk->dirty;
    }
    hit = false;
    return false;
}

bool Set::insert(uint32_t tag, bool isWrite, bool& dirtyEvict) {
    Block* victim = selectVictim();
    dirtyEvict = victim->valid && victim->dirty; // notify eviction of dirty block

    // Update FIFO queue only for FIFO policy
    if (policy == 0) {
        // If the victim is valid, it's being evicted — remove from front
        if (victim->valid && !fifoQueue.empty() && fifoQueue.front() == victim) {
            fifoQueue.pop_front();
        }
        // Add the new or reused block to the back
        fifoQueue.push_back(victim);
    }

    victim->valid = true;
    victim->tag = tag;
    victim->dirty = isWrite;
    updateLRU(victim);
    return dirtyEvict;
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


    if (policy == 0) { //fifo 
        //return &blocks[0]; // FIFO 
        return fifoQueue.front();
    } else {
        return &*std::min_element(blocks.begin(), blocks.end(), [](const Block& a, const Block& b) {
            return a.lruCounter < b.lruCounter;
        });
    }
}

void Set::updateLRU(Block* accessed) {
    accessed->lruCounter = accessCounter++;
}