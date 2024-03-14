/*
  File: Cache.h
  Description:

  Contains the Cache class. Cache, VictimCache
  and method to process physical addresses
  is defined in this class
*/

#ifndef CACHE_H
#define CACHE_H

#include "Structs.h"

class Cache
{
  public:
    // initialize the cache to zero misses
  Cache()
      : num_misses_(0)
    {}
    // destructor
 ~Cache()
    {}

 void check(const PhysicalAddress & address)
 {
     CacheSet & set = cache[address.set];
     PhysicalAddress replaced;


     // now perform the process of checking

     // this is the case when the address is in the cache already
     if (set.in_use[0] && set.address_one.tag == address.tag)
         set.LRU = 1;
     else if (set.in_use[1] && set.address_two.tag == address.tag)
         set.LRU = 0;

     // now the case when the address is in the vistim cache
     // once found, swap it with LRU
     else if (victim_cache.in_use[0] && victim_cache.address_one.tag == address.tag
              && victim_cache.address_one.set == address.set)
     {
         // now check if the LRU needs to be updated
         if (set.LRU == 0)
         {
             replaced = set.address_one;
             set.address_one = victim_cache.address_one;
             set.LRU = 1;
         }
         else
         {
             replaced = set.address_two;
             set.address_two = victim_cache.address_one;
             set.LRU = 0;
         }

         victim_cache.address_one = replaced;
         victim_cache.FIFO = 1;
     }
     // checking the second address 
     else if (victim_cache.in_use[1] && victim_cache.address_two.tag == address.tag
              && victim_cache.address_two.set == address.set)
     {
         // now check if the LRU needs to be updated
         if (set.LRU == 0)
         {
             replaced = set.address_one;
             set.address_one = victim_cache.address_two;
             set.LRU = 1;
         }
         else
         {
             replaced = set.address_two;
             set.address_two = victim_cache.address_two;
             set.LRU = 0;
         }

         victim_cache.address_two = replaced;
         victim_cache.FIFO = 0;
     }
     // else there is a cache miss
     else
     {
         ++num_misses_;  // update the number of misses

         // case when there is a block that is not being used
         if (!set.in_use[0])
         {
             set.address_one = address; // fill it out with the address
             set.in_use[0] = true; // now it's being used
             set.LRU = 1; // set LRU to the other set
             return; // not going to victim because there is no replacement
         }
         else if (!set.in_use[1])
         {
             set.address_two = address;
             set.in_use[1] = true;
             set.LRU = 0;
             return; // not going to victim because there is no replacement
         }

         // perform LRU algorithm
         if (set.LRU == 0)
         {
             replaced = set.address_one;
             set.address_one = address;
             set.LRU = 1;
         }
         else
         {
             replaced = set.address_two;
             set.address_two = address;
             set.LRU = 0;
         }

         // now handling the victim cache

         // first case when there is a space that is not in use
         if (!victim_cache.in_use[0])
         {
             victim_cache.address_one = replaced;
             victim_cache.in_use[0] = true;
             victim_cache.FIFO = 0;
         }
         else if (!victim_cache.in_use[1])
         {
             victim_cache.address_two = replaced;
             victim_cache.in_use[1] = true;
             // FIFO doesn't need to be changed
         }

         // case when we have to replace it with FIFO
         else if (victim_cache.FIFO == 0)
         {
             victim_cache.address_one = replaced;
             victim_cache.FIFO = 1;
         }
         else
         {
             victim_cache.address_two = replaced;
             victim_cache.FIFO = 0;
         }
         
     }
     return;
 }
 unsigned int misses() const
 {
     return num_misses_;
 }
  private:
    // since the number of sets is 4
    CacheSet cache[4];
    VictimCache victim_cache;
    unsigned int num_misses_;
};

#endif
