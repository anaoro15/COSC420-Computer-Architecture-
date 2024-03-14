/*
  File: Structs.h
  Description:

  This file contains the declaration of Cache Set,
  Victim Cache and Physical Address struct
*/

#ifndef STRUCTS_H
#define STRUCTS_H

struct PhysicalAddress
{
    // the address is 32 bits
    uint32_t whole_address : 32;
    // tag is 24 bits
    uint32_t tag : 24;
    // set is 2 bits
    uint8_t set : 2;
    // shift is 6 bits
    uint8_t shift : 6;
};


struct CacheSet
{
    // this represents the address one in a set
    PhysicalAddress address_one;
    // this represents the address two in a set
    PhysicalAddress address_two;
    // this is the least recently used
    unsigned int LRU;
    // this is a boolean that shows which addr is in use
    bool in_use[2];
    
    CacheSet()
    {
        // constructor sets both bools to false
        in_use[0] = false;
        in_use[1] = false;
    }
};

struct VictimCache
{
    // this represents the address one in a set
    PhysicalAddress address_one;
    // this represents the address two in a set
    PhysicalAddress address_two;
    // this is the FIRST IN FIRST OUT
    unsigned int FIFO;
    // this is a boolean that shows which addr is in use
    bool in_use[2];
    
    VictimCache()
    {
        // constructor sets both bools to false
        in_use[0] = false;
        in_use[1] = false;
    }

};

#endif
