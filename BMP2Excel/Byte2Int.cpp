#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <map>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <functional>
#include <cstring>
using std::cout;
using std::endl;






int Byte4_to_int(const char DATA[4]){
  // if (DATA.length() != 4) {
  //   throw std::runtime_error("ERROR_PASSING_BYTES:\nLength of Data being passed into the function does not match parameters.");}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
  // }
  unsigned int result = 0;
  unsigned char *temp = (unsigned char*)(&DATA[0]);
  result = (result << 8) + temp[3];
  result = (result << 8) + temp[2];
  result = (result << 8) + temp[1];
  result = (result << 8) + temp[0];
  return result;
}

int Byte2_to_int(const char DATA[2]){
  // if (DATA.length() != 2) {
  //    throw std::runtime_error("ERROR_PASSING_BYTES:\nLength of Data being passed into the function does not match parameters.");
  // }
  int result =0;
  unsigned char *temp = (unsigned char*)(&DATA[0]);
  result = (result << 8) + temp[1];
  result = (result << 8) + temp[0];
  return result;
}

int Byte_to_int(const char DATA[1]){
  // if (DATA.length() != 1) {
  //   throw std::runtime_error("ERROR_PASSING_BYTES:\nLength of Data being passed into the function does not match parameters.");
  //
  // }
  int result =0;
  unsigned char *temp = (unsigned char*)(&DATA[0]);
  result = (result << 8) + temp[0];
  return result;
}

int big_endian_2_bytes_to_int(const std::string &value)
{
    if (value.length() != 2) {
        throw std::runtime_error("Convert_Number_2_bytes should be called with strings of length 2");
    }
    assert(value.length() == 2);
    unsigned char *temp = (unsigned char*)(&value[0]);

    return (temp[0] << 8) + (temp[1]);

}
