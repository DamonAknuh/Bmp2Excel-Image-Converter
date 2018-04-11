//SECOND VERSION

#include <iostream>
#include <string>
#include <vector>
#include "BMP2EXCEL.hpp"
#include <sstream>
#include <list>
#include <map>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <functional>
#include <cstring>
#include <algorithm>
using std::cout;
using std::endl;


//COmment 1

struct HEADER_INFO {
  unsigned int ROW_SIZE; // Row size including padding.
  int ARRAY_SIZE; // TOTAL pixel array size
  int DIFFERENCE;
  unsigned int BITS_PER_PIX; //BITS PER PIXEL IN THE IMAGE eg 24,32
  unsigned int FILE_SIZE; // Image file size
  unsigned int DATA_START; // start of Pixel DATA
  unsigned int IMG_WIDTH; // Image pixel width
  unsigned int IMG_HEIGHT; //image pixel height
  unsigned int NUM_VALUES; // number of values each pixel has.
} HEADER_DATA;


PIXEL_ARRAY Read_File(std::string Filename){
  cout << "--Opening " << Filename << "--" << endl;

  std::ifstream InputFile;
  InputFile.open(Filename, std::ios::binary);
  PIXEL_ARRAY PIXELS;
  triplet Pixel();


  if ( InputFile.is_open() ){
    char TEMP[4];

    cout << "--File " << Filename << " Is Open--" << endl;
    cout << "______________________________________\n" << endl;
    cout << "--Reading File--\n" << endl;

    InputFile.seekg(0, std::ios::end);
    unsigned int length = InputFile.tellg();
    HEADER_DATA.FILE_SIZE = length;
    cout << "\t_-FILE INFORMATION-_\n";
    cout << "File Size: \t\t" << length << " Bytes" << endl;
    InputFile.seekg(0, std::ios::beg);

    //FILE SIZE
    InputFile.seekg(2);
    InputFile.get(TEMP, 4);
    HEADER_DATA.FILE_SIZE = Byte4_to_int(TEMP);

    //DATA OFFSET
    InputFile.seekg(10);
    InputFile.get(TEMP,4);
    cout << "Data Starts at: \t" << Byte4_to_int(TEMP) << " (byte offset)" << endl;
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
    HEADER_DATA.BITS_PER_PIX = Byte4_to_int(TEMP);
    if (HEADER_DATA.BITS_PER_PIX < 24){
      cout << "ERROR: DIFFERENT_BITS/PIXEL_EXPECTED" << endl;
      InputFile.close();
      exit(1);
    }

    //Reading color planes
    InputFile.seekg(0x1A);
    InputFile.get(TEMP,2);
    cout << "# of Color Planes: \t" << Byte2_to_int(TEMP) << " (planes)" <<endl;

    //Reading Compression Method
    InputFile.seekg(0x1E);
    InputFile.get(TEMP,4);
    int COMPRESSION = Byte4_to_int(TEMP);
    cout << "Compression Value: \t" << Byte4_to_int(TEMP) <<endl;

    if (COMPRESSION != 0) {
      cout << "ERROR: DIFFERENT_COMPRESSION_METHOD_DETECTED" << endl;
      InputFile.close();
      exit(1);
    }
    if (HEADER_DATA.BITS_PER_PIX < 24){
      cout << "ERROR: DIFFERENT_BITS/PIXEL_EXPECTED" << endl;
      InputFile.close();
      exit(1);
    }


    //Reading DIB Header SIZE
    InputFile.seekg(0x0E);
    InputFile.get(TEMP,4);
    cout << "DIB Header Size: \t" << Byte4_to_int(TEMP) << " (Bytes)" <<endl;

    HEADER_DATA.ROW_SIZE = ( ( (HEADER_DATA.BITS_PER_PIX*HEADER_DATA.IMG_WIDTH) + 31) / 32) * 4;
    cout << "Pixel Row Size: \t" << HEADER_DATA.IMG_WIDTH*3 << " (Bytes)"<<endl;
    cout << "Padded Row Size: \t" << HEADER_DATA.ROW_SIZE  << " (Bytes)" <<endl;
    HEADER_DATA.DIFFERENCE = HEADER_DATA.ROW_SIZE - (HEADER_DATA.IMG_WIDTH*3);
    cout << "Difference: \t\t" << HEADER_DATA.DIFFERENCE << " (Bytes)" << endl;
    HEADER_DATA.ARRAY_SIZE = HEADER_DATA.ROW_SIZE * abs(HEADER_DATA.IMG_HEIGHT);
    cout << "Array Size: \t\t" << HEADER_DATA.ARRAY_SIZE  << " \n--" << endl;

    //PIXEL ARRAY
    cout << "--Reading Pixel Data at offset " << HEADER_DATA.DATA_START << "--" << endl;
    InputFile.seekg(HEADER_DATA.DATA_START);
    HEADER_DATA.NUM_VALUES = HEADER_DATA.BITS_PER_PIX/8;



    char c;
    unsigned char y;
    std::vector <triplet> PIX_ROW {};
    for (unsigned int i = 1; i <= HEADER_DATA.IMG_HEIGHT; i++){
      PIX_ROW.clear();
      for (unsigned int j = 1; j <= HEADER_DATA.IMG_WIDTH; j++){
        if (InputFile.tellg() < 0 ){
          break;
        }

        triplet PIX_VALUES;

        InputFile.get(c);
        y = (unsigned char)c;
        PIX_VALUES.set_first ( Byte_to_int(y) );

        InputFile.get(c);
        y = (unsigned char)c;
        PIX_VALUES.set_second( Byte_to_int(y) );

        InputFile.get(c);
        y = (unsigned char)c;
        PIX_VALUES.set_third ( Byte_to_int(y) );
        PIX_ROW.push_back(PIX_VALUES);
        //cout << "[" << PIX_VALUES.get_first() << "," << PIX_VALUES.get_second() << "," << PIX_VALUES.get_third() << "] ";
      }
      for (int p=0; p < HEADER_DATA.DIFFERENCE ; p++){
        InputFile.get(c);
      }
      // cout << InputFile.tellg() <<  endl;
      // cout << i << " " << endl;
      PIXELS.push_back(PIX_ROW);
    }
    std::cout <<"\n--" << PIXELS.size()*PIXELS.at(0).size() << " Pixels have been stored--" << endl;
    InputFile.close();

    cout << "--File Closed--" <<endl;
    cout << "______________________________________\n" << endl;
    std::reverse(PIXELS.begin(), PIXELS.end());

  }else {
    cout << "ERROR: UNABLE_TO_OPEN_FILE: " << Filename << std::endl;
    exit(0);
  }



  return PIXELS;
}



void Write_Excel_File(PIXEL_ARRAY DATA, std::string Filename){
  Filename = Filename.substr(0, Filename.length()-4) + ".csv" ;

  std::ofstream OutputFile;
  OutputFile.open(Filename);
  cout << "--Opening " << Filename << "--" << endl;
  if ( OutputFile.is_open()){
    cout << "--File " << Filename << " Is Open--" << endl;
    cout << "--Writing Into File--\n" << endl;

    for (auto A: DATA){
      for (auto B: A){
        OutputFile << B.get_first() << ",";
      }
      OutputFile << endl;
      for (auto B: A){
        OutputFile << B.get_second() << ",";
      }
      OutputFile << endl;
      for (auto B: A){
        OutputFile << B.get_third() << ",";
      }
      OutputFile << endl;
    }
    OutputFile << "=";
    // for (int i = 1; i <= 2500 ; i = i +3){
    //   //OutputFile << "$" << i << ":" << "$" << i << ",";
    //   cout << "$" << i << ":" << "$" << i << ",";
    // }
    cout << "--File Closed--" <<endl;
    cout << "______________________________________\n" << endl;
    OutputFile.close();

  }else {

    cout << "ERROR: UNABLE_TO_OPEN_FILE: " << Filename << std::endl;
    exit(0);
  }





}
