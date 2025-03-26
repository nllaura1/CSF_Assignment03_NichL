#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <vector>

bool isPowerOfTwo(int n) {
    // n must be positive and have exactly one bit set
    return n > 0 && (n & (n - 1)) == 0;
}

int main( int argc, char **argv ) {
    
    //input from command line
    if (argc < 5 || argc > 6) {
        std::cerr << "Invalid Input - invalid # of commands" << std::endl;
        return -1;
    }
    //number of sets
    int numSets = argv[1];
    if (!isPowerOfTwo(numSets)) {
        std::cerr << "Invalid Input - invalid number of sets" << std::endl;
        return -1;
    }
    //number of blocks
    int numBlocks = argv[2];
    if (!isPowerOfTwo(numBlocks)) {
        std::cerr << "Invalid Input - invalid number of blocks" << std::endl;
        return -1;
    }
    //block byte size
    int blockSize = argv[3];
    if (!isPowerOfTwo(blockSize) || blockSize < 4) {
        std::cerr << "Invalid Input - invalid block size" << std::endl;
        return -1;
    }
    //cache allocation preference
    std::string allocatePrefString = argv[4];
    bool allocatePref = false;
    if (allocatePrefString == "write-allocate") {
        //set preference
        allocatePref = false;
    } else if (allocatePrefString == "no-write-allocate"){
        //set preference
        allocatePref = true;
    } else {
        std::cerr << "Invalid Input - must provide allocate preference" << std::endl;
        return -1;
    }
    //write preference
    std::string writePrefString = argv[5];
    bool writePref = false;
    if (writePrefString == "write-back") {
        //set preference
        writePref = false;
    } else if (writePrefString == "write-through"){
        //set preference
        writePref = true;
    } else {
        std::cerr << "Invalid Input - must provide write preference" << std::endl;
        return -1;
    }

    //associative cache preference
    if (numSets = 1 && numBlocks != 1) {
        //associative cache preference
        std::string evictPrefString = argv[6];
        uint8_t evictPref = 0;
        if (evictPrefString == "lru") {
            //set preference
            evictPref = 0;
        } else if (evictPrefString == "fifo"){
            //set preference
            evictPref = 1;
        } else {
            std::cerr << "Invalid Input - must provide write eviction preference" << std::endl;
            return -1;
        }
    }

    // Read until there's no more input
    char op;
    unsigned int address;
    int value;
    while (std::cin >> op >> std::hex >> address >> std::dec >> value) {
        //Perform cache operations
    }

    return 0;

}
