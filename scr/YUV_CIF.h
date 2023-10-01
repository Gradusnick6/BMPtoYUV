#pragma once
#include "structs.h"
#include "Bitmap24.h"
#include <vector>
#include <thread>
using namespace std;

/// <summary>
/// ����� ������������� ����������� ������� ������
/// </summary>
class YUV_CIF
{
private:
	const static int STANDART_WIDTH = 352;
	const static int STANDART_HEIGHT = 288;
	const static int STANDART_FRAME_SIZE = 304128;
	char *data;
	unsigned long long dataSize;
	short width;
	short height;
	int frameNum;

	/// <summary>
	/// ����������� RGB ������� � YUV420 �������
	/// ���������� ������ ���������� � ������ data
	/// </summary>
	/// <param name="bmp">����������� � ������� � RGB</param>
	/// <param name="start">���������� ������(���) ��������� ���������� ������� data</param>
	/// <param name="end">���������� �����(���) ��������� ���������� ������� data</param>
	void setYUVpixels(Bitmap24 bmp, unsigned int start, unsigned int end);
	/// <summary>
	/// ��������� ����������� �������� ������� this.width � this.height
	/// ������� �������������� � ������ �������� ���� �����������
	/// </summary>
	/// <param name="bmpIH">���������� � ��������</param>
	/// <param name="bmpData">���������� ������ �����������</param>
	/// <param name="sFrame">������ ���� �����, � ������� �������� �����������</param>
	/// <param name="eFrame">��������� ���� �����, � ������� �������� �����������</param>
	void paste(BMP_INFO_HEADER bmpIH, char* bmpData, int sFrame, int eFrame);
	/// <summary>
	/// ����������� �������� RGB � ������� YUV420
	/// </summary>
	/// <param name="bmp">�������� RGB</param>
	void convert_RGBtoYUV(Bitmap24 bmp);
public:
	YUV_CIF();
	/// <summary>
	/// ������������� ����� ������� �� ������ bmp �����
	/// </summary>
	/// <param name="filePath">���������� � ��������� bmp</param>
	YUV_CIF(BMP_INFO_HEADER ih);
	/// <summary>
	/// ������������� ����� �������
	/// </summary>
	/// <param name="filePath">���� � ����� � ����������� .yuv</param>
	YUV_CIF(const char* filePath);
	/// <summary>
	/// ������������� ����� ������� �� ������ bmp �����
	/// </summary>
	/// <param name="filePath">���������� � ��������� bmp</param>
	void init(BMP_INFO_HEADER ih);
	/// <summary>
	/// ������������� ����� ������� 
	/// </summary>
	/// <param name="filePath">���� � ����� � ����������� .yuv</param>
	void init(const char* filePath);
	/// <summary>
	/// �������� ������ � ����������� � ����
	/// </summary>
	/// <param name="yuvfilePath">���� � �����</param>
	void write(const char* yuvfilePath);
	/// <summary>
	/// ������� ������ � ����� .yuv
	/// </summary>
	/// <param name="yuvfilePath">���� � �����</param>
	void read(const char* yuvfilePath);
	/// <summary>
	/// ������� ����� .yuv c .bmp ������������
	/// ���� ������ ����������� �� ������ ��� ������ ������ �����, ���������� �� ��������������
	/// </summary>
	/// <param name="yuvfilePath">���� � ����� � ����������� .yuv</param>
	/// <param name="bmpFilePath">���� � ����� � ����������� .bmp</param>
	void glue(const char* yuvfilePath, const char* bmpFilePath);
	/// <returns>������ ������ � ��������</returns>
	char* getData();
	/// <summary>
	/// ������� ������
	/// </summary>
	void clear();
};

