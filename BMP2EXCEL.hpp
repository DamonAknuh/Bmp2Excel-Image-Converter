#ifndef __BMP2EXCEL_HPP__
#define __BMP2EXCEL_HPP__
//SECOND VERSION

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include "Byte2Int.hpp"



class triplet
{
public:
    triplet()
    {
        first = 0;
        second = 0;
        third = 0;
    }

    void make_triplet(int one, int two, int three)
    {
        first = one;
        second = two;
        third = three;
    }
    void set_first(int temp){ first = temp; }
    void set_second(int temp){  second = temp; }
    void set_third(int temp){ third = temp; }
    int get_first(){ return first; }
    int get_second(){  return second; }
    int get_third(){ return third; }

private:
    int first;
    int second;
    int third;
};


typedef std::vector <std::vector <triplet>> PIXEL_ARRAY;


PIXEL_ARRAY Read_File(std::string Filename);

void Write_Excel_File(PIXEL_ARRAY DATA, std::string Filename);

#endif
