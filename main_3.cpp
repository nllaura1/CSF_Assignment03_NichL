#include <iostream>
#include <sstream>
#include <string>
#include "Cache.h"
#include "config.h"

ReplacementPolicy parseReplacementPolicy(const std::string& s) {
    if (s == "lru") return ReplacementPolicy::LRU;
    return ReplacementPolicy::FIFO;
}

WritePolicy parseWritePolicy(const std::string& s) {
    if (s == "write-back") return WritePolicy::WRITE_BACK;
    return WritePolicy::WRITE_THROUGH;
}

AllocationPolicy parseAllocationPolicy(const std::string& s) {
    if (s == "write-allocate") return AllocationPolicy::WRITE_ALLOCATE;
    return AllocationPolicy::NO_WRITE_ALLOCATE;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Usage: ./csim <sets> <blocks> <blocksize> <alloc> <write> <replace>\n";
        return 1;
    }

    int numSets = std::stoi(argv[1]);
    int blocks = std::stoi(argv[2]);
    int blockSize = std::stoi(argv[3]);
    AllocationPolicy alloc = parseAllocationPolicy(argv[4]);
    WritePolicy write = parseWritePolicy(argv[5]);
    ReplacementPolicy repl = parseReplacementPolicy(argv[6]);

    Cache cache(numSets, blockSize, blocks, repl, write, alloc);

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

    std::cout << "Simulation finished.\n";
    return 0;
}