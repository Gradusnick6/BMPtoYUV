#include "Bitmap24.h"

void Bitmap24::load(const char* filePath)
{
    clear();
    ifstream ifs(filePath, ios::binary);

    if (!ifs)
        throw "Could not open the file " + (string) filePath;

    // читаем заголовок
    ifs.read((char*)&fh, sizeof(BMP_FILE_HEADER));
    ifs.read((char*)&ih, sizeof(BMP_INFO_HEADER));

    int beginF, endF;
    ifs.seekg(0, ios::beg);
    beginF = ifs.tellg();
    ifs.seekg(0, ios::end);
    endF = ifs.tellg();
    ifs.seekg(fh.offset_data, ios::beg);

    // проверяем считанные данные
    if (fh.file_size != endF - beginF ||
        fh.reserved1 != 0 || fh.reserved2 != 0 ||
        fh.offset_data != 14 + ih.size ||

        (ih.size != 40 && ih.size != 108 && ih.size != 124) ||
        ih.planes != 1 ||
        ih.bit_count != 24 ||
        ih.compression != 0)
    {
        ifs.close();
        throw ;
    }

    data = new unsigned char[ih.size_image];
    lineSize = ih.size_image / ih.height;

    // считываем данных о пикселях
    for (int i = ih.size_image - lineSize; i >= 0; i -= lineSize)
        ifs.read((char*)&data[i], lineSize);

    ifs.close();
}


Bitmap24::Bitmap24(){
    lineSize = -1;
    data = NULL;
}

Bitmap24::Bitmap24(const char* filePath){
    load(filePath);
}

BMP_INFO_HEADER Bitmap24::getInfoHeader(){
    return ih;
}

unsigned char * Bitmap24::getData(){
    return data;
}

void Bitmap24::clear()
{
    if (data != NULL)
        delete[] data;
}