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
    if (argc != 5) {
        printf("Invalid Input.");
        return -1;
    }
    //number of sets
    int numSets = argv[1];
    if (!isPowerOfTwo(numSets)) {
        printf("Invalid Input.");
        return -1;
    }
    //number of blocks
    int numBlocks = argv[2];
    if (!isPowerOfTwo(numBlocks)) {
        printf("Invalid Input.");
        return -1;
    }
    //block byte size
    int blockSize = argv[3];
    if (!isPowerOfTwo(blockSize) || blockSize < 4) {
        printf("Invalid Input.");
        return -1;
    }
    //cache allocation preference
    std::string allocatePrefString = argv[4];
    uint8_t allocatePref = 0;
    if (allocatePrefString == "write-allocate") {
        //set preference
        allocatePref = 0;
    } else if (allocatePrefString == "no-write-allocate"){
        //set preference
        allocatePref = 1;
    } else {
        printf("Invalid Input.");
        return -1;
    }
    //write preference
    std::string writePref = argv[5];
    if (writePref == "write-back") {
        //set preference
    } else if (writePref == "write-through"){
        //set preference
    } else {
        printf("Invalid Input.");
        return -1;
    }


}
