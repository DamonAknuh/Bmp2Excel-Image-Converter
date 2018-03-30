#include <iostream>
#include <string>
#include "Byte2Int.hpp"
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

// now start reading and testing pixel DATA
// Need to verify that the stuff in the cells
// match to the wiki and shit.



template <typename T1, typename T2, typename T3>
class triplet{
public:
  triplet(){
    first = 0;
    second = 0;
    third = 0;
  }
  triplet(T1 one, T2 two, T3 three){
    first = one;
    second = two;
    third = three;
  }
  void make_triplet(T1 one, T2 two, T3 three){
    first = one;
    second = two;
    third = three;
  }
  void set_first(T1 temp){ first = temp; }
  void set_second(T2 temp){  second = temp; }
  void set_third(T3 temp){ third = temp; }
  T1 get_first(){ return first; }
  T2 get_second(){  return second; }
  T3 get_third(){ return third; }
private:
  T1 first;
  T2 second;
  T3 third;
};

typedef std::vector <std::vector <triplet<int,int,int>>> PIXEL_ARRAY;

struct HEADER_INFO {
  int ROW_SIZE;
  int ARRAY_SIZE;
  unsigned int FILE_SIZE; // Image file size
  unsigned int DATA_START; // start of Pixel DATA
  unsigned int IMG_WIDTH; // Image pixel width
  unsigned int IMG_HEIGHT; //image pixel height
} HEADER_DATA;




PIXEL_ARRAY Read_File(std::string Filename){
  cout << "--Opening " << Filename << "--" << endl;

  std::ifstream InputFile;
  InputFile.open(Filename, std::ios::binary);
  PIXEL_ARRAY PIXELS;

  if ( InputFile.is_open() ){
    cout << "--File " << Filename << " Is Open--" << endl;
    cout << "--Reading File--\n" << endl;

    InputFile.seekg(0, std::ios::end);
    unsigned int length = InputFile.tellg();
    HEADER_DATA.FILE_SIZE = length;
    cout << "File Size: " << length << " Bytes" << endl;
    InputFile.seekg(0, std::ios::beg);
    char TEMP[4];

    //FILE SIZE
    InputFile.seekg(2);
    InputFile.get(TEMP, 4);
    cout << "Verifying File Size: " << length << " == " << std::dec << Byte4_to_int(TEMP) << endl;
    HEADER_DATA.FILE_SIZE = Byte4_to_int(TEMP);
    //DATA OFFSET
    InputFile.seekg(10);
    InputFile.get(TEMP,4);
    cout << "Data Starts at: " << Byte4_to_int(TEMP) << " offset\n--" << endl;
    HEADER_DATA.DATA_START = Byte4_to_int(TEMP);
    //IMAGE WIDTH
    InputFile.seekg(0x12);
    InputFile.get(TEMP,4);
    cout << "Image Width: \t\t" << Byte4_to_int(TEMP) << " (pixels)" << endl;
    HEADER_DATA.IMG_WIDTH = Byte4_to_int(TEMP);
    //IMAGE HEIGHT
    InputFile.seekg(0x16);
    InputFile.get(TEMP,4);
    cout << "Image Height: \t\t" << Byte4_to_int(TEMP) << " (pixels)" << endl;
    HEADER_DATA.IMG_HEIGHT = Byte4_to_int(TEMP);
    //Reading Bits per PIXEL
    InputFile.seekg(0x1C);
    InputFile.get(TEMP,2);
    cout << "Bits per Pixel: \t" << Byte2_to_int(TEMP) << " (bits/pixel)" << endl;
    int BITS_PER_PIX = Byte4_to_int(TEMP);
    //Reading color planes
    InputFile.seekg(0x1A);
    InputFile.get(TEMP,2);
    cout << "# of Color Planes: \t" << Byte2_to_int(TEMP) << " (planes)" <<endl;
    //Reading Compression Method
    InputFile.seekg(0x1E);
    InputFile.get(TEMP,4);
    int COMPRESSION = Byte4_to_int(TEMP);
    if (COMPRESSION != 0) {
      cout << "ERROR: DIFFERENT_COMPRESSION_METHOD_DETECTED" << endl;
      exit(1);
    }
    cout << "Compression Value: \t" << Byte4_to_int(TEMP) <<endl;
    //Reading DIB Header SIZE
    InputFile.seekg(0x0E);
    InputFile.get(TEMP,4);
    cout << "DIB Header Size: \t" << Byte4_to_int(TEMP) << " (Bytes)" <<endl;

    HEADER_DATA.ROW_SIZE = ( ( (BITS_PER_PIX*HEADER_DATA.IMG_HEIGHT) + 31) / 32) * 4;
    cout << "Row Size: " << HEADER_DATA.ROW_SIZE  << endl;
    HEADER_DATA.ARRAY_SIZE = HEADER_DATA.ROW_SIZE * abs(HEADER_DATA.IMG_HEIGHT);
    cout << "Array Size: " << HEADER_DATA.ARRAY_SIZE  << " \n--" << endl;


    cout << "--Reading Pixel Data at offset " << HEADER_DATA.DATA_START << "--" << endl;
    InputFile.seekg(HEADER_DATA.DATA_START);
    InputFile.get(TEMP, 1);




    InputFile.close();
    cout << "--File Closed--" <<endl;


  }else {
    cout << "ERROR: UNABLE_TO_OPEN_FILE: " << Filename << std::endl;
  }

  return PIXELS;
}


int main (int argc, char** argv){
  // ERROR test to verfiy program and arguments are successfull
  if (argc < 2 || argc > 2){
    cout << "ERROR: NO_SPECIFIED_INPUT_FILENAME" <<endl;
    cout << "\t Usage: ./Bmp2Excel.cpp <Filename.bmp>" << endl;
    exit(1);
  }
  //READS THE FILE AND STORES PIXEL INFORMATION INTO DATA STRUCTURE
  PIXEL_ARRAY PIXEL_DATA = Read_File(argv[1]);
  //TAKES DATA STRUCTURE AND WRITES INTO A CSV FILE


  return 0;
}
