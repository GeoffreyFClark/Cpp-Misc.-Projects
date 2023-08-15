#include "Imageprocessing.h"
using namespace std;

void Image::LoadImageFile(string fileName) {
	string folderPath = "input\\"; 
	string ext = ".tga";
	string filePath = folderPath + fileName + ext;
	ifstream file(filePath, ios_base::binary); 

	if (file.is_open()) {
		file.read(&header.idLength, sizeof(header.idLength));
		file.read(&header.colourMapType, sizeof(header.colourMapType));
		file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
		file.read((char *)&header.colourMapOrigin, sizeof(header.colourMapOrigin));
		file.read((char *)&header.colourMapLength, sizeof(header.colourMapLength)); 
		file.read((char *)&header.colourMapDepth, sizeof(header.colourMapDepth));

		file.read((char *)&header.xOrigin, sizeof(header.xOrigin));
		file.read((char *)&header.yOrigin, sizeof(header.yOrigin)); 
		file.read((char *)&header.width, sizeof(header.width));
		file.read((char *)&header.height, sizeof(header.height));
		file.read((char *)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
		file.read((char *)&header.imageDescriptor, sizeof(header.imageDescriptor));

		uint totalPixels = header.width * header.height;

		for (uint i = 0; i < totalPixels; i++){
			Pixel pixel;
			file.read((char *)&pixel.blue, sizeof(pixel.blue));
			file.read((char *)&pixel.green, sizeof(pixel.green));
			file.read((char *)&pixel.red, sizeof(pixel.red));

			pixel.bInt = ConvertCharToInt(pixel.blue);
			pixel.gInt = ConvertCharToInt(pixel.green); 
			pixel.rInt = ConvertCharToInt(pixel.red);

			pixelVector.push_back(pixel);
		}
		file.close();
	}
}

void Image::WriteImage(string outFileName) {

	string filePath = "output\\" + outFileName + ".tga";
	fstream file(filePath, ios_base::binary | ios_base::out);

	if (!file.is_open()) {
    cout << "Unable to open output file: " << filePath <<endl;
	}

	if (file.is_open())	{
		file.write(&header.idLength, sizeof(header.idLength));
		file.write(&header.colourMapType, sizeof(header.colourMapType));
		file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
		file.write((char *)&header.colourMapOrigin, sizeof(header.colourMapOrigin));
		file.write((char *)&header.colourMapLength, sizeof(header.colourMapLength));
		file.write((char *)&header.colourMapDepth, sizeof(header.colourMapDepth));

		file.write((char *)&header.xOrigin, sizeof(header.xOrigin));
		file.write((char *)&header.yOrigin, sizeof(header.yOrigin));
		file.write((char *)&header.width, sizeof(header.width));
		file.write((char *)&header.height, sizeof(header.height));
		file.write((char *)&header.bitsPerPixel, sizeof(header.bitsPerPixel));
		file.write((char *)&header.imageDescriptor, sizeof(header.imageDescriptor));

		unsigned char zero = (unsigned char) '0';

		for (uint i = 0 ; i < pixelVector.size(); i++) {
			Pixel pixel = pixelVector.at(i);
			file.write((char *)&pixel.blue, 1);
			file.write((char *)&pixel.green, 1);
			file.write((char *)&pixel.red, 1);
		}
		file.close();
	}
}


/*~~~~~~~~~~~ Helper Functions ~~~~~~~~~~*/
uint Image::ConvertCharToInt(unsigned char _char) {
	return (uint)(_char - '\0');
}
unsigned char Image::ConvertInttoChar(uint _int) {
	return (unsigned char)(_int + '\0');
}
void Image::setUints(){
	for (uint i = 0; i < pixelVector.size(); i++) {
		pixelVector[i].rInt = ConvertCharToInt(pixelVector[i].red);
		pixelVector[i].gInt = ConvertCharToInt(pixelVector[i].green);
		pixelVector[i].bInt = ConvertCharToInt(pixelVector[i].blue);
	}
}


/*~~~~~~~~~ Mutators and Accessors ~~~~~~~~~*/
Image::Header Image::getHeader() {
	return header;
}
void Image::setHeader(Image::Header &headerData) {
	header.idLength = headerData.idLength;
	header.colourMapType = headerData.colourMapType;
	header.dataTypeCode = headerData.dataTypeCode;
	header.colourMapOrigin = headerData.colourMapOrigin;
	header.colourMapDepth = headerData.colourMapDepth;
	header.xOrigin = headerData.xOrigin;
	header.yOrigin = headerData.yOrigin;
	header.width = headerData.width;
	header.height = headerData.height;
	header.bitsPerPixel = headerData.bitsPerPixel;
	header.imageDescriptor = headerData.imageDescriptor;
}
vector<Pixel> Image::getPixelVector() {
	return pixelVector;
}
void Image::setPixelVector(vector<Pixel>& vect) {
	for (uint i = 0; i < vect.size(); i++) {
		pixelVector.push_back(vect[i]);
	}
}