#pragma once
#include "structs.h"
using namespace std;

/// <summary>
/// После инициализация обязательна очистка данных
/// </summary>
class Bitmap24
{
private:
    BMP_FILE_HEADER fh;
    BMP_INFO_HEADER ih;
    unsigned char* data;
    int lineSize;
public:
    Bitmap24();
    Bitmap24(const char* filePath);
    /// <summary>
    /// Загрузка данных из файла
    /// </summary>
    /// <param name="filePath">путь к файлу формата .bmp</param>
    void load(const char* filePath);
    /// <returns>информация о заголовке файла</returns>
    BMP_INFO_HEADER getInfoHeader();
    /// <returns>Массив данных о пикселях</returns>
    unsigned char* getData();
    /// <summary>
    /// Очистка памяти
    /// </summary>
    void clear();
};

