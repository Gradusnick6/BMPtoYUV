#pragma once
#include <fstream>
#include <iostream>


#pragma pack(1)

struct BMP_FILE_HEADER {
    unsigned short file_type;  
    unsigned int file_size;    
    unsigned short reserved1;  
    unsigned short reserved2;  
    unsigned int offset_data;  
};

struct BMP_INFO_HEADER {
    unsigned int size;         
    unsigned int width;        
    unsigned int height;       
    unsigned short planes;     
    unsigned short bit_count;  
    unsigned int compression;  
    unsigned int size_image;   
    unsigned int x_pixels_per_meter;
    unsigned int y_pixels_per_meter;
    unsigned int colors_used;       
    unsigned int colors_important;  
};
#pragma pack()