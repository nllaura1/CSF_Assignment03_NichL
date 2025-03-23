#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <cstdint>

int main( int argc, char **argv ) {

  // TODO: implement

  if (argc != 4) {
    printf("Invalid Input.");
    return -1;
  }
  
  char *instruction = argv[1];
  
  if (*instruction == 's') {
    // proceed with store
  } else if (*instruction == 'l') {
    // proceed with load
  } else {
    printf("Invalid Input.");
    return -1;
  }

  uint32_t address = strtoul(argv[2], nullptr, 16);

  if (address == 0) {
    printf("Invalid Input.");
    return -1;
  }
  
  struct Block {
    uint16_t tag;
    uint16_t index;
    short offset;
    unsigned char data[256];
  };

  Block newBlock;
  newBlock.tag = (address >> 20) & 0xFF;
  newBlock.index = (address >> 8) & 0xFF;
  newBlock.offset = address & 0xFF;
  for (int i = 0; i < 256; i++) {
    newBlock.data[i] = 1;
  }


  struct Slot {
    uint32_t tag;
    int valid, dirty;
    uint32_t load_ts, access_ts;
    unsigned char data[256];
  };
  
  Slot newSlot;
  newSlot.tag = ((uint32_t) newBlock.tag << 12) | (newBlock.index & 0xFFF);
  newSlot.valid = 1;
  newSlot.dirty = 0;
  newSlot.load_ts = time(NULL);
  newSlot.access_ts = 0;
  memcpy(newSlot.data, newBlock.data, sizeof(newBlock.data));


  
  struct Set {
    Slot *slots ;
    int size, capacity;
  };

  Set newSet;
  newSet.slots = new Slot[4];
  newSet.slots[0] = newSlot;
  newSet.size = 1;
  newSet.capacity = 4;
  
  struct Cache {
    Set *sets;
    int index, size, capacity;
  };
  
  Cache newCache;
  newCache.sets = new Set[1024];
  newCache.sets[0] = newSet;
  newCache.index = 0;
  newCache.size = 1;
  newCache.capacity = 1024;

  // test
  if (newSlot.valid == 1) {
    printf ("Cache is valid");
  }

  if (newCache.size == 1) {    
    printf("Tag: %u", newSlot.tag);
  }
  return 0;
}
