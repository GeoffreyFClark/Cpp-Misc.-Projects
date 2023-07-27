#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include <sstream>

using namespace std;
typedef unsigned int uint;

struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	
	uint rInt, gInt, bInt;
};


class Image {
public:
	struct Header {
		char idLength;
		char colourMapType;
		char dataTypeCode;
		short colourMapOrigin;
		short colourMapLength;
		char colourMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};

	void LoadImageFile(string fileName);
	void WriteImage(string outFileName);

	uint ConvertCharToInt(unsigned char _char);
	unsigned char ConvertInttoChar(uint _int);

	void setUints();

	Header getHeader();
	void setHeader(Header &headerData);

	vector<Pixel> getPixelVector();
	void setPixelVector(vector<Pixel> &vect);

private:
	Header header;
	Pixel pixel;
	vector<Pixel> pixelVector;	
};

