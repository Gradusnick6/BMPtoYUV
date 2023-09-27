#pragma once
#include "structs.h"
using namespace std;

/// <summary>
/// ����� ������������� ����������� ������� ������
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
    /// �������� ������ �� �����
    /// </summary>
    /// <param name="filePath">���� � ����� ������� .bmp</param>
    void load(const char* filePath);
    /// <returns>���������� � ��������� �����</returns>
    BMP_INFO_HEADER getInfoHeader();
    /// <returns>������ ������ � ��������</returns>
    unsigned char* getData();
    /// <summary>
    /// ������� ������
    /// </summary>
    void clear();
};

