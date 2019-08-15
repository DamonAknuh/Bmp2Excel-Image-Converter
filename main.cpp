//SECOND VERSION
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


#include "BMP2EXCEL.hpp"

using std::cout;
using std::endl;

int main (int argc, char** argv)
{
    // ERROR test to verfiy program and arguments are successfull
    if (argc < 2 || argc > 2){
        cout << "ERROR: NO_SPECIFIED_INPUT_FILENAME" <<endl;
        cout << "\t Usage: ./Bmp2Excel.cpp <Filename.bmp>" << endl;
        exit(1);
    }
    //READS THE FILE AND STORES PIXEL INFORMATION INTO DATA STRUCTURE
    PIXEL_ARRAY PIXEL_DATA = Read_File(argv[1]);

    //TAKES DATA STRUCTURE AND WRITES INTO A CSV FILE
    Write_Excel_File(PIXEL_DATA, argv[1]);

    return 0;
}
