#pragma once
#include "structs.h"
#include "Bitmap24.h"
#include <vector>
#include <thread>
using namespace std;

/// <summary>
/// После инициализация обязательна очистка данных
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
	/// Преобразует RGB пиксели в YUV420 пиксели
	/// Полученные данные помещаются в массив data
	/// </summary>
	/// <param name="bmp">изображение с данными в RGB</param>
	/// <param name="start">определяет начало(вкл) диапазона заполнения массива data</param>
	/// <param name="end">определяет конец(вкл) диапазона заполнения массива data</param>
	void setYUVpixels(Bitmap24 bmp, unsigned int start, unsigned int end);
	/// <summary>
	/// Вставляет изображение размеров меньших this.width и this.height
	/// Вставка осуществляется с левого верхнего края видеоролика
	/// </summary>
	/// <param name="bmpIH">информация о картинке</param>
	/// <param name="bmpData">пиксельные данные изображения</param>
	/// <param name="sFrame">первый кадр видео, в который добавить изображение</param>
	/// <param name="eFrame">последний кадр видео, в который добавить изображение</param>
	void paste(BMP_INFO_HEADER bmpIH, char* bmpData, int sFrame, int eFrame);
	/// <summary>
	/// Конвертация пикселей RGB в пиксели YUV420
	/// </summary>
	/// <param name="bmp">картинка RGB</param>
	void convert_RGBtoYUV(Bitmap24 bmp);
public:
	YUV_CIF();
	/// <summary>
	/// Инициализация полей объекта на основе bmp файла
	/// </summary>
	/// <param name="filePath">информация о заголовке bmp</param>
	YUV_CIF(BMP_INFO_HEADER ih);
	/// <summary>
	/// Инициализация полей объекта
	/// </summary>
	/// <param name="filePath">путь к файлу с расширением .yuv</param>
	YUV_CIF(const char* filePath);
	/// <summary>
	/// Инициализация полей объекта на основе bmp файла
	/// </summary>
	/// <param name="filePath">информация о заголовке bmp</param>
	void init(BMP_INFO_HEADER ih);
	/// <summary>
	/// Инициализация полей объекта 
	/// </summary>
	/// <param name="filePath">путь к файлу с расширением .yuv</param>
	void init(const char* filePath);
	/// <summary>
	/// Записать данные о видеоролике в файл
	/// </summary>
	/// <param name="yuvfilePath">путь к файлу</param>
	void write(const char* yuvfilePath);
	/// <summary>
	/// Считать данные с файла .yuv
	/// </summary>
	/// <param name="yuvfilePath">путь к файлу</param>
	void read(const char* yuvfilePath);
	/// <summary>
	/// Склеить видео .yuv c .bmp изображением
	/// Если размер изображения по высоте или ширине больше видео, склеивание не осуществляется
	/// </summary>
	/// <param name="yuvfilePath">путь к файлу с расширением .yuv</param>
	/// <param name="bmpFilePath">путь к файлу с расширением .bmp</param>
	void glue(const char* yuvfilePath, const char* bmpFilePath);
	/// <returns>Массив данных о пикселях</returns>
	char* getData();
	/// <summary>
	/// Очистка памяти
	/// </summary>
	void clear();
};

