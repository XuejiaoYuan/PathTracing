#include "ImageSaver.h"

void ImageSaver::save(const string& name, const vector<vector<vec3>>& frameBuffer)
{
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	int width = frameBuffer[0].size();
	int height = frameBuffer.size();

	unsigned short bfType = 0x4d42;
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfSize = 2 + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + width*height * 3;
	bfh.bfOffBits = 0x36;

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCounts = 24;
	bih.biCompression = 0;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 5000;
	bih.biYPelsPerMeter = 5000;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	FILE *file;
	fopen_s(&file, name.c_str(), "wb");
	if (!file) {
		cout << "Can't write file" << endl;
		return;
	}

	fwrite(&bfType, sizeof(bfType), 1, file);
	fwrite(&bfh, sizeof(bfh), 1, file);
	fwrite(&bih, sizeof(bih), 1, file);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			vec3 rgb = frameBuffer[i][j] * vec3(255);
			unsigned char color[3] = {
				(char)(rgb.z > 255 ? 255 : rgb.z),
				(char)(rgb.y > 255 ? 255 : rgb.y),
				(char)(rgb.x > 255 ? 255 : rgb.x)
			};

			fwrite(color, 1, 3, file);
		}
	}

	fclose(file);
}
