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
    std::string allocatePref = argv[4];
    if (allocatePref == "write-allocate") {
        //set preference
    } else if (allocatePref == "write-allocate"){
        //set preference
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
