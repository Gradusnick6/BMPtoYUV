#include "YUV_CIF.h"

void YUV_CIF::read(const char* filePath)
{
	ifstream ifs(filePath, ios::binary);
	if (!ifs.is_open())
		throw "Could not open the file " + (string)filePath;

	unsigned long count = 0;
	unsigned int lineSize = dataSize / height / frameNum;
	int iFrame = 0;
	for (int f = 0; f < frameNum; f++)
	{
		//Читаем компоненту Y
		for (unsigned long i = 0; i < STANDART_FRAME_SIZE; i += 3)
			ifs.read(&(data[iFrame + i]), sizeof(char));

		//Читаем компоненту U
		for (unsigned long i = 0; i < STANDART_FRAME_SIZE; i += 6)
		{
			ifs.read(&(data[iFrame + i + 1]), sizeof(char));
			count++;
			if (count == width / 2)
			{
				count = 0;
				if ((i + 3) % lineSize == 0 && (i + 3) >= lineSize)
					i = i + lineSize;
				else
					i = i + (lineSize - (i + 1) % lineSize) - 2 + lineSize;
			}
		}
		//Читаем компоненту V
		for (unsigned long i = 0; i < STANDART_FRAME_SIZE; i += 6)
		{
			ifs.read(&(data[iFrame + i + 2]), sizeof(char));
			count++;
			if (count == width / 2)
			{
				count = 0;
				if ((i + 3) % lineSize == 0 && (i + 3) >= lineSize)
					i = i + lineSize;
				else
					i = i + (lineSize - (i + 1) % lineSize) - 2 + lineSize;
			}
		}
		iFrame += STANDART_FRAME_SIZE;
	}

	ifs.close();
}

void YUV_CIF::write(const char* filePath)
{
	if (data == NULL)
		throw "Data is empty";

	unsigned long count = 0;
	unsigned int lineSize = dataSize / height / frameNum;

	ofstream ofs(filePath, ios::binary);
	if (!ofs.is_open())
		throw "Could not open the file " + (string)filePath;

	int iFrame = 0;
	for (int f = 0; f < frameNum; f++)
	{
		//Пишем  компоненту Y
		for (unsigned long i = 0; i < STANDART_FRAME_SIZE; i += 3)
			ofs.write(&data[iFrame + i], sizeof(char));

		//Пишем  компоненту U
		for (unsigned long i = 0; i < STANDART_FRAME_SIZE; i += 6)
		{
			ofs.write(&data[iFrame + i + 1], sizeof(char));
			count++;
			if (count == width / 2)
			{
				count = 0;
				if ((i + 3) % lineSize == 0 && (i + 3) >= lineSize)
					i = i + lineSize;
				else
					i = i + (lineSize - (i + 1) % lineSize) - 2 + lineSize;
			}
		}
		count = 0;
		//Пишем  компоненту V
		for (unsigned long i = 0; i < STANDART_FRAME_SIZE; i += 6)
		{
			ofs.write(&data[iFrame + i + 2], sizeof(char));
			count++;
			if (count == width / 2)
			{
				count = 0;
				if ((i + 3) % lineSize == 0 && (i + 3) >= lineSize)
					i = i + lineSize;
				else
					i = i + (lineSize - (i + 1) % lineSize) - 2 + lineSize;
			}
		}
		iFrame += STANDART_FRAME_SIZE;
	}
	ofs.close();
}

void YUV_CIF::glue(const char* yuvFilePath, const char* bmpFilePath)
{
	Bitmap24 bmp(bmpFilePath);
	BMP_INFO_HEADER ih = bmp.getInfoHeader();
	// если разрешение картинки больше разрешения видео
	if (ih.height > STANDART_HEIGHT || ih.width > STANDART_WIDTH){
		bmp.clear();
		throw "The image size is too large";
	}

	try {
		init(yuvFilePath);
	}
	catch (exception ex) {
		cout << ex.what();
		bmp.clear();
		return;
	}
	YUV_CIF bmpV;
	bmpV.convert_RGBtoYUV(bmp);
	char* bmpData = bmpV.getData();

	// если разрешение картинки равно разрешению видео
	if (ih.height == STANDART_HEIGHT && ih.width == STANDART_WIDTH)
	{
		int iFrame = 0;
		for (int f = 0; f < frameNum; f++)
		{
			for (int i = 0; i < STANDART_FRAME_SIZE; i++)
				data[iFrame + i] = bmpData[i];
			iFrame += STANDART_FRAME_SIZE;
		}
		return;
	}
	
	try {
		read(yuvFilePath);
	}
	catch (exception ex) {
		cout << ex.what();
		bmp.clear();
		return;
	}
	paste(ih, bmpData, 0, frameNum);

	bmp.clear();
	bmpV.clear();
}

void YUV_CIF::paste(BMP_INFO_HEADER bmpIH, char* bmpData, int sFrame, int eFrame)
{
	short pHieght = bmpIH.height;
	short pWidth = bmpIH.width;

	int vLineSize = STANDART_FRAME_SIZE / height;
	int pLineSize = pWidth * 3;

	int pIndex;
	int vIndex;
	int vFrame;
	int count = 0;
	//иттерируемся по кадрам
	for (int f = sFrame; f < eFrame; f++)
	{
		vFrame = f * STANDART_FRAME_SIZE;
		pIndex = 0;
		vIndex = 0;
		//Переписываем компоненту Y
		for (int r = 0; r < pHieght; r++, pIndex += pLineSize, vIndex += vLineSize)
			for (int i = 0; i < pLineSize; i += 3)
				data[vFrame + vIndex + i] = bmpData[pIndex + i];

		vIndex = 0;
		pIndex = 0;
		//Переписываем компоненты UV
		for (pIndex = 0; pIndex < bmpIH.size_image;)
		{
			count = 1;
			//построчная перезапись
			for (; count != pWidth / 2; pIndex += 6, vIndex += 6, count++) {
				data[vFrame + vIndex + 1] = bmpData[pIndex + 1];
				data[vFrame + vIndex + 2] = bmpData[pIndex + 2];
			}

			if ((pIndex + 3) % pLineSize == 0 && (pIndex + 3) >= pLineSize)
				pIndex += pLineSize;
			else
				pIndex = pIndex + (pLineSize - (pIndex + 1) % pLineSize) - 2 + pLineSize;

			vIndex += count * 6;
			if ((vIndex + 3) % vLineSize == 0 && (vIndex + 3) >= vLineSize)
				vIndex += vLineSize;
			else
				vIndex = vIndex + (vLineSize - (vIndex + 1) % vLineSize) - 2 + vLineSize;
		}
	}
}

void YUV_CIF::convert_RGBtoYUV(Bitmap24 bmp)
{
	BMP_INFO_HEADER ih = bmp.getInfoHeader();
	init(ih);
	unsigned int lineSize = ih.size_image / ih.height;
	unsigned long count = 0;
	unsigned char* bmpData = bmp.getData();
	//Конвертируем компоненту Y
	for (unsigned long i = 0; i < ih.size_image; i += 3)
	{
		data[i] = 0.257 * bmpData[i + 1] + 0.504 * bmpData[i] + 0.098 * bmpData[i + 2] + 16;
		count++;
		if (count == ih.width)
		{
			count = 0;
			if ((i + 3) % lineSize != 0)
				i = i + (lineSize - (i + 1) % lineSize) - 2;
		}
	}
	//Конвертируем компонентs UV
	for (unsigned long i = 0; i < ih.size_image; i += 6)
	{
		data[i + 1] = -0.148 * bmpData[i + 1] - 0.291 * bmpData[i] + 0.439 * bmpData[i + 2] + 128;
		data[i + 2] = 0.439 * bmpData[i + 1] - 0.368 * bmpData[i] - 0.071 * bmpData[i + 2] + 128;
		count++;
		if (count == ih.width / 2)
		{
			count = 0;
			if ((i + 3) % lineSize == 0 && (i + 3) >= lineSize)
				i = i + lineSize;
			else
				i = i + (lineSize - (i + 1) % lineSize) - 2 + lineSize;
		}
	}
}



void YUV_CIF::init(BMP_INFO_HEADER ih)
{
	clear();
	dataSize = ih.size_image;
	width = ih.width;
	height = ih.height;
	frameNum = 1;
	data = new char[dataSize];
}

void YUV_CIF::init(const char* filePath)
{
	clear();
	ifstream ifs(filePath, ios::binary);
	if (!ifs.is_open())
		throw "Could not open the file " + (string)filePath;

	ifs.seekg(0, ios::end);
	dataSize = ifs.tellg() * 2;
	ifs.seekg(0, ios::beg);

	width = STANDART_WIDTH;
	height = STANDART_HEIGHT;
	frameNum = dataSize / STANDART_FRAME_SIZE;
	data = new char[dataSize];
	ifs.close();
}

YUV_CIF::YUV_CIF() {
	data = NULL;
	dataSize = width = height = frameNum = -1;
}

YUV_CIF::YUV_CIF(BMP_INFO_HEADER ih) {
	init(ih);
}

YUV_CIF::YUV_CIF(const char* filePath) {
	init(filePath);
}

char* YUV_CIF::getData() {
	return data;
}

void YUV_CIF::clear()
{
	if (data != NULL)
		delete[] data;
}