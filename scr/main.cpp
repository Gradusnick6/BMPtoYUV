#include "structs.h"
#include "Bitmap24.h"
#include "YUV_CIF.h"

/// <summary>
/// Склеить видеоряд .yuv с изображением формата .bmp
/// Если размер изображения по высоте или ширине больше видео, склеивание не осуществляется
/// </summary>
/// <param name="1">путь к файлу .bmp для считывания</param>
/// <param name="2">путь к файлу .yuv для считывания (в случае 2 параметров +для записи)</param>
/// <param name="3">путь к файлу .yuv для записи</param>
int main(int argc, char* argv[])
{
	YUV_CIF yuv;
	try
	{
		if (argc == 3)
		{
			yuv.glue(argv[2], argv[1]);
			yuv.write(argv[2]);
		}
		if (argc == 4)
		{
			yuv.glue(argv[2], argv[1]);
			yuv.write(argv[3]);
		}
	}
	catch (std::exception ex)
	{
		cout << ex.what();
	}

	yuv.clear();
	return 0;
}