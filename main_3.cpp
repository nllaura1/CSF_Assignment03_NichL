#include <iostream>
#include <sstream>
#include <string>
#include "Cache.h"
#include "config.h"

int parseReplacementPolicy(const std::string& s) {
    if (s == "lru") {
        return 0;
    } else if (s == "fifo") {
        return 1;
    } {
        //stderr
    }
}

int parseWritePolicy(const std::string& s) {
    if (s == "write-back") {
        return 0;
    } else if (s == "write-through") {
        return 1;
    } else {
        //stderr
    }
}

int parseAllocationPolicy(const std::string& s) {
    if (s == "write-allocate") {
        return 0;
    } else if (s == "no-write-allocate") {
        return 1;
    } else {
        //stderr
    }

}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Invalid Input - invalid # of commands" << std::endl;
        return 1;
    }

    //parse command line args
    int numSets = std::stoi(argv[1]);
    int blocks = std::stoi(argv[2]);
    int blockSize = std::stoi(argv[3]);
    int alloc = parseAllocationPolicy(argv[4]);
    int write = parseWritePolicy(argv[5]);
    int repl = parseReplacementPolicy(argv[6]);

    //initialize cache
    Cache cache(numSets, blockSize, blocks, repl, write, alloc);

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

    std::cout << "Simulation finished.\n";
    return 0;
}