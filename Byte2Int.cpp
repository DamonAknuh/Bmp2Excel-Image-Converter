#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include "Byte2Int.hpp"

int Byte4_to_int(const char DATA[4])
{
    unsigned int result = 0;
    unsigned char *temp = (unsigned char*)(&DATA[0]);

    result = (result << 8) + temp[3];
    result = (result << 8) + temp[2];
    result = (result << 8) + temp[1];
    result = (result << 8) + temp[0];

    return result;
}

int Byte2_to_int(const char DATA[2])
{

    int result =0;
    unsigned char *temp = (unsigned char*)(&DATA[0]);
    result = (result << 8) + temp[1];
    result = (result << 8) + temp[0];

    return result;
}


int Byte_to_int(const unsigned char DATA)
{
    int result =0;
    result = (result << 8) + DATA;

    return result;
}
