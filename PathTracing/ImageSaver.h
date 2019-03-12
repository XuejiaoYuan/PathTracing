#pragma once
#include "CommonFunc.h"


typedef struct {
	unsigned int bfSize;	//size of file
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
}BITMAPFILEHEADER;

typedef struct {
	unsigned int biSize;
	int biWidth;
	int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCounts;
	unsigned int biCompression;
	unsigned int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
}BITMAPINFOHEADER;

typedef struct{
	unsigned char BYTErgbBlue;
	unsigned char BYTErgbGreen;
	unsigned char BYTErgbRed;
	unsigned char BYTErgbReserved;
}RGBQUAD;

class ImageSaver {
public:
	void save(const string&name, const vector<vector<vec3>>&frameBuffer);
};