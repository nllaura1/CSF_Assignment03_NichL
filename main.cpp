#include <iostream>
#include <sstream>
#include <string>
#include "Cache.h"

int parseReplacementPolicy(const std::string& s) {
    if (s == "lru") {
        return 0;
    } else if (s == "fifo") {
        return 1;
    } {
        return -1;
    }
}

int parseWritePolicy(const std::string& s) {
    if (s == "write-back") {
        return 0;
    } else if (s == "write-through") {
        return 1;
    } else {
        return -1;
    }
}

int parseAllocationPolicy(const std::string& s) {
    if (s == "write-allocate") {
        return 0;
    } else if (s == "no-write-allocate") {
        return 1;
    } else {
        return -1;
    }

}

bool isPowerOfTwo(int n) {
    // n must be positive and have exactly one bit set
    return n > 0 && (n & (n - 1)) == 0;
}


int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Invalid Input - invalid # of commands" << std::endl;
        return 1;
    }

    //parse command line args
    int numSets = std::stoi(argv[1]);
    if (!isPowerOfTwo(numSets)) {
        std::cerr << "Invalid Input - invalid number of sets" << std::endl;
        return -1;
    }

    int numBlocks = std::stoi(argv[2]);
    if (!isPowerOfTwo(numBlocks)) {
        std::cerr << "Invalid Input - invalid number of blocks" << std::endl;
        return -1;
    }

    int blockSize = std::stoi(argv[3]);
    if (!isPowerOfTwo(blockSize) || blockSize < 4) {
        std::cerr << "Invalid Input - invalid block size" << std::endl;
        return -1;
    }
    
    int alloc = parseAllocationPolicy(argv[4]);
    int write = parseWritePolicy(argv[5]);
    int repl = parseReplacementPolicy(argv[6]);
    //check for valid input
    if (alloc < 0 || write < 0|| repl <0) {
        std::cerr << "Invalid Input - must provide valid policies" << std::endl;
        return -1;  
    }

    //initialize cache
    Cache cache(numSets, blockSize, numBlocks, repl, write, alloc);

    //begin accepting commands
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        char op;
        std::string addrStr;
        int size;
        iss >> op >> addrStr >> size;

        uint32_t addr = std::stoul(addrStr, nullptr, 16);
        cache.access(op, addr);
    }

    //simulation finished
    std::cout << "Total loads: " << cache.totalLoads << '\n';
    std::cout << "Total stores: " << cache.totalStores << '\n';
    std::cout << "Load hits: " << cache.loadHits << '\n';
    std::cout << "Load misses: " << cache.loadMisses << '\n';
    std::cout << "Store hits: " << cache.storeHits << '\n';
    std::cout << "Store misses: " << cache.storeMisses << '\n';
    std::cout << "Total cycles: " << cache.totalCycles << '\n';

    return 0;
}