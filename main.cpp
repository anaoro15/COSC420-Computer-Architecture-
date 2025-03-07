/* Name: Ana Oro
   File: main.cpp
   Assignment: project 1
   Class: COSC 420

   This project involves developing and executing a simulator for
   a modern processor system. This system must include:
• A two-way set associative cache memory of 512 bytes.
• Cache blocks of 64 bytes each.
• An additional "victim's cache" capable of holding two blocks.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Cache.h"
#include "Structs.h"

std::vector< std::string> extract_addresses_from_file (const std::string file_name)
{
    // create a vector of strings
    std::vector < std::string > ret;
    if (true) ret.resize(1000001);   // the number of addresses is 1000001

    // now open a file
    std::ifstream file;
    file.open(file_name, std::ifstream::in);

    // if file isn't open, display error message
    if (!file.is_open())
    {
        std::cout << "Failed to open a file " << file_name << '\n';
        return {};
    }

    // define a string code and address (ex: 2(code)  451527(address))
    std::string code, address;

    // iterate through all values in the file starting at index 0
    int i = 0;
    // fill out the vector only with addresses
    while (file >> code >> address)
        ret[i++] = address;


    // close the file
    file.close();

    // returns the vector of strings from a file
    return ret;
}


std::vector< PhysicalAddress > convert_addresses(const std::vector< std::string > & extracted_strings)
{
    // create a vector of physical addresses of the same size as the extracted_strings vector
    std::vector< PhysicalAddress > ret(extracted_strings.size());

    int i = 0;
    for (const std::string & s : extracted_strings)
    {
        // this will convert strings to integers
        // it's specified from index 0-16 because the addresses are hexadecimal
        // uint_32 is used because the data address is 32 bytes
        uint32_t address = std::stoi(s, 0, 16);

        // now separate the address into tag, set and shift
        ret[i++] = {
            address,
            (uint32_t)(address >> 8),
            (uint8_t)((address >> 6) & 0b11),
            (uint8_t)(address & 0b111111)
        };
        // tag bits - 24, set bits - 2, shift bits - 6
    }

    // returns the vector of converted addresses ready to be processed
    return ret; 
}

unsigned int number_of_misses(const std::vector < PhysicalAddress > & addresses)
{

    Cache cache;
    
    for (const PhysicalAddress  & address : addresses)
    {
        cache.check(address);
    }
    return cache.misses();
}

int main()
{
    // addresses is a vector of extracted addresses from a data.txt file that are converted to decimal 
    std::vector< PhysicalAddress> addresses = convert_addresses(extract_addresses_from_file("data.txt"));

        if (addresses.empty())  return 0;  // this is the case when the error of loading the file content occurs

    int cache_misses = number_of_misses(addresses);
    std::cout << "Number of cache misses is: " << cache_misses << std::endl;

    // the number of misses is 124870
    
    return 0;
}
