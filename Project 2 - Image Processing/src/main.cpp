#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <string>
#include <chrono>
#include "Imageprocessing.h"
using namespace std;

class HighResTimer {
public:
    HighResTimer() {
        start = std::chrono::high_resolution_clock::now();
    }

    double elapsed() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
        return double(duration)*(1e-9);
    }
private:
    chrono::high_resolution_clock::time_point start;
};

bool AreTGAFilesIdentical(const string&file1, const string&file2);

Image MultiplyBlend(Image &A, Image &B);
Image SubtractBlend(Image &A, Image &B);
Image ScreenBlend(Image & A, Image &B);
Image OverlayBlend(Image &A, Image &B);

Image Part6(Image &A);
Image Part7(Image &A);
Image Part8(string channel, Image &A);
Image Part9(Image &A, Image &B, Image &C);
Image Part10(Image &A) ;

uint limit0to255(int result); 
float calcScreenBlend(float factor, uint Aval, uint Bval); 

int main() {
	HighResTimer timer;

	// Part 1
	Image layer1, pattern1;
	layer1.LoadImageFile("layer1");
	pattern1.LoadImageFile("pattern1");
	Image part1 = MultiplyBlend(layer1, pattern1);
	part1.WriteImage("part1");

	// Part 2
	Image layer2, car;
	layer2.LoadImageFile("layer2");
	car.LoadImageFile("car");
	Image part2 = SubtractBlend(car, layer2);
	part2.WriteImage("part2");

	// Part 3
	Image temp, text;
	Image pattern2;
	pattern2.LoadImageFile("pattern2");
	temp = MultiplyBlend(layer1, pattern2);
	text.LoadImageFile("text");
	Image part3 = ScreenBlend(text , temp);
	part3.WriteImage("part3");

	// Part 4
	Image circles;
	circles.LoadImageFile("circles");
	Image temp1 = MultiplyBlend(layer2, circles);
	Image part4 = SubtractBlend(temp1, pattern2);
	part4.WriteImage("part4");

	// Part 5
	Image part5 = OverlayBlend(layer1, pattern1);
	part5.WriteImage("part5");

	// Part 6
	Image part6 = Part6(car);
	part6.WriteImage("part6");

	// Part 7
	Image part7 = Part7(car);
	part7.WriteImage("part7");

	// Part 8
	Image part8_r, part8_g, part8_b;
	part8_r = Part8("red", car);
	part8_r.WriteImage("part8_r");
	part8_g = Part8("green", car);
	part8_g.WriteImage("part8_g");
	part8_b = Part8("blue", car);
	part8_b.WriteImage("part8_b");

	// Part 9
	Image part9, layer_red, layer_green, layer_blue;
	layer_red.LoadImageFile("layer_red");
	layer_green.LoadImageFile("layer_green");
	layer_blue.LoadImageFile("layer_blue");
	part9 = Part9(layer_red, layer_green, layer_blue);
	part9.WriteImage("part9");

	// Part 10
	Image part10, text2;
	text2.LoadImageFile("text2");
	part10 = Part10(text2);
    part10.WriteImage("part10");

	// Tests
    for (int testNum = 1; testNum <= 7; testNum++) {
        string fileName = "output\\part" + to_string(testNum) + ".tga";
        string exampleFileName = "outputexamples\\EXAMPLE_part" + to_string(testNum) + ".tga";

        if (AreTGAFilesIdentical(fileName, exampleFileName)) {
            cout << "Test " << testNum << " Passed!" << endl;
        } else {
            cout << "Test " << testNum << " Failed!" << endl;
        }
    }

	string file1 = "output\\part8_r.tga";
    string file2 = "outputexamples\\EXAMPLE_part8_r.tga";
	
    if (AreTGAFilesIdentical(file1, file2)) {
        cout << "Test 8_r Passed!" << endl;
    } else {
        cout << "Test 8_r Failed!" << endl;
    }

	file1 = "output\\part8_g.tga";
    file2 = "outputexamples\\EXAMPLE_part8_g.tga";
	
    if (AreTGAFilesIdentical(file1, file2)) {
        cout << "Test 8_g Passed!" << endl;
    } else {
        cout << "Test 8_g Failed!" << endl;
    }

	file1 = "output\\part8_b.tga";
    file2 = "outputexamples\\EXAMPLE_part8_b.tga";
	
    if (AreTGAFilesIdentical(file1, file2)) {
        cout << "Test 8_b Passed!" << endl;
    } else {
        cout << "Test 8_b Failed!" << endl;
    }

    for (int testNum = 9; testNum <= 10; testNum++) {
        string fileName = "output\\part" + to_string(testNum) + ".tga";
        string exampleFileName = "outputexamples\\EXAMPLE_part" + to_string(testNum) + ".tga";

        if (AreTGAFilesIdentical(fileName, exampleFileName)) {
            cout << "Test " << testNum << " Passed!" << endl;
        } else {
            cout << "Test " << testNum << " Failed!" << endl;
        }
    }

	cout << "Elapsed time: " << timer.elapsed() << " seconds" << endl;
	return 0;
}


bool AreTGAFilesIdentical(const string&file1, const string&file2){
    ifstream f1(file1, ios::binary | ios::ate);
    ifstream f2(file2, ios::binary | ios::ate);
    if (!f1.is_open() || !f2.is_open()) {
        return false;
    }
    if (f1.tellg() != f2.tellg()) {
        return false;
    }
    f1.seekg(0);
    f2.seekg(0);
    if (equal(istreambuf_iterator<char>(f1.rdbuf()), istreambuf_iterator<char>(), istreambuf_iterator<char>(f2.rdbuf()) )) {
        return true;
    }
    return false;
}


Image MultiplyBlend(Image &A, Image &B) {
	Image::Header newHeader = A.getHeader();
	Image Z;
	Z.setHeader(newHeader);
	vector<Pixel> Zvect;

	A.setUints();
	B.setUints();
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Bvect = B.getPixelVector();

	for (uint i = 0; i < Avect.size(); i++) {
		Pixel Zpixel;

		uint rInt = (uint)(0.5f+(Avect[i].rInt * Bvect.at(i).rInt / 255.0f));
		unsigned char rChar = A.ConvertInttoChar(rInt);
		Zpixel.red = rChar;
 
		uint gInt = (uint)(0.5f+(Avect[i].gInt * Bvect.at(i).gInt / 255.0f));
		unsigned char gChar = A.ConvertInttoChar(gInt);
		Zpixel.green = gChar;

		uint bInt = (uint)(0.5f+(Avect[i].bInt * Bvect.at(i).bInt / 255.0f));
		unsigned char bChar = A.ConvertInttoChar(bInt);
		Zpixel.blue = bChar;

		Zvect.push_back(Zpixel);
	}
	Z.setPixelVector(Zvect);
	return Z;
}


Image SubtractBlend(Image &A, Image &B) {
	Image::Header newHeader = A.getHeader();
	Image Z; 
	Z.setHeader(newHeader);
	vector<Pixel> Zvect;
	
	A.setUints();
	B.setUints();
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Bvect = B.getPixelVector();

	int result;
	for (uint i = 0; i < Avect.size(); i++)	 {
		Pixel Zpixel;

		result = Avect[i].rInt - Bvect[i].rInt; 
		uint rInt = limit0to255(result);
		unsigned char rChar = A.ConvertInttoChar(rInt);
		Zpixel.red = rChar;

		result = Avect[i].gInt - Bvect[i].gInt;
		uint gInt = limit0to255(result);
		unsigned char gChar = A.ConvertInttoChar(gInt);
		Zpixel.green = gChar;

		result = Avect[i].bInt - Bvect[i].bInt;
		uint bInt = limit0to255(result);
		unsigned char bChar = A.ConvertInttoChar(bInt);
		Zpixel.blue = bChar; 

		Zvect.push_back(Zpixel);
	}
	Z.setPixelVector(Zvect);
	return Z;
}


float calcScreenBlend(float factor, uint Aval, uint Bval) {
	float fVal = 1.0f - factor * ((1.0f - (((float)(Aval) / 255.0f))) * ((1.0f - ((float)(Bval) / 255.0f))));
	return fVal;
}


Image ScreenBlend(Image &A, Image &B) {
	Image::Header newHeader = A.getHeader();
	Image Z;
	Z.setHeader(newHeader);
	vector<Pixel> Zvect;

	A.setUints();
	B.setUints();
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Bvect = B.getPixelVector();

	for (uint i = 0; i < Avect.size(); i++)	 {
		Pixel Zpixel;

		float fRed = calcScreenBlend(1.0f, Avect[i].rInt, Bvect[i].rInt);
		uint rInt = (uint)(0.5f+(fRed * 255.0f));
		unsigned char rChar = A.ConvertInttoChar(rInt);
		Zpixel.red = rChar;

		float fGreen = calcScreenBlend(1.0f, Avect[i].gInt, Bvect[i].gInt);
		uint gInt = (uint)(0.5f+(fGreen * 255.0f));
		unsigned char gChar = A.ConvertInttoChar(gInt);
		Zpixel.green = gChar;

		float fBlue = calcScreenBlend(1.0f, Avect[i].bInt, Bvect[i].bInt);
		uint bInt = (uint)(0.5f+(fBlue * 255.0f));
		unsigned char bChar = A.ConvertInttoChar(bInt);
		Zpixel.blue = bChar;

		Zvect.push_back(Zpixel); 
	}
	Z.setPixelVector(Zvect);
	return Z;
}


Image OverlayBlend(Image &A, Image &B) {
    Image::Header newHeader = A.getHeader();
    Image Z;
    Z.setHeader(newHeader);
    vector<Pixel> Zvect;

    A.setUints();
    B.setUints();
    vector<Pixel> Avect = A.getPixelVector();
    vector<Pixel> Bvect = B.getPixelVector();

    for (uint i = 0; i < Avect.size(); i++) {
        Pixel Zpixel;

        if (Bvect[i].rInt <= 127.5) {
            float fRed = 2.0f * (float)Avect[i].rInt * (float)Bvect[i].rInt / 255.0f;
            uint rInt = limit0to255(static_cast<int>(fRed));
            unsigned char rChar = A.ConvertInttoChar(rInt);
            Zpixel.red = rChar;
        } else {
            float fRed = 1.0f - 2.0f * (1.0f - static_cast<float>(Avect[i].rInt) / 255.0f) * (1.0f - static_cast<float>(Bvect[i].rInt) / 255.0f);
            uint rInt = limit0to255(static_cast<int>(fRed * 255.0f));
            unsigned char rChar = A.ConvertInttoChar(rInt);
            Zpixel.red = rChar;
        }

        if (Bvect[i].gInt <= 127.5) {
            float fGreen = 2.0f * (float)Avect[i].gInt * (float)Bvect[i].gInt / 255.0f;
            uint gInt = limit0to255(static_cast<int>(fGreen));
            unsigned char gChar = A.ConvertInttoChar(gInt);
            Zpixel.green = gChar;
        } else {
            float fGreen = 1.0f - 2.0f * (1.0f - static_cast<float>(Avect[i].gInt) / 255.0f) * (1.0f - static_cast<float>(Bvect[i].gInt) / 255.0f);
            uint gInt = limit0to255(static_cast<int>(fGreen * 255.0f));
            unsigned char gChar = A.ConvertInttoChar(gInt);
            Zpixel.green = gChar;
        }

        if (Bvect[i].bInt <= 127.5) {
            float fBlue = 2.0f * (float)Avect[i].bInt * (float)Bvect[i].bInt / 255.0f;
            uint bInt = limit0to255(static_cast<int>(fBlue));
            unsigned char bChar = A.ConvertInttoChar(bInt);
            Zpixel.blue = bChar;
        } else {
            float fBlue = 1.0f - 2.0f * (1.0f - static_cast<float>(Avect[i].bInt) / 255.0f) * (1.0f - static_cast<float>(Bvect[i].bInt) / 255.0f);
            uint bInt = limit0to255(static_cast<int>(fBlue * 255.0f));
            unsigned char bChar = A.ConvertInttoChar(bInt);
            Zpixel.blue = bChar;
        }

        Zvect.push_back(Zpixel);
    }
    Z.setPixelVector(Zvect);
    return Z;
}



Image Part6(Image &A) { 
	Image::Header newHeader = A.getHeader();
	Image Z;
	Z.setHeader(newHeader);
	vector<Pixel> Zvect;
	vector<Pixel> Avect = A.getPixelVector();

	int result;
	for (uint i = 0; i < Avect.size(); i++) {
		Pixel Zpixel;
		Zpixel.red = Avect[i].red;
		Zpixel.blue = Avect[i].blue;

		result = Avect[i].gInt + 200;
		uint gInt = limit0to255(result);  
		unsigned char gChar = A.ConvertInttoChar(gInt);
		Zpixel.green = gChar;

		Zvect.push_back(Zpixel);
	}
	Z.setPixelVector(Zvect);
	return Z;
}


Image Part7(Image & A) {
	Image::Header newHeader = A.getHeader();
	Image Z;
	Z.setHeader(newHeader); 
	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Zvect;

	for (uint i = 0; i < Avect.size(); i++) {
		Pixel Zpixel;

		uint rInt;
		float rFloat = ((float)Avect[i].rInt / 255.0f) * 4.0f;
		rInt = (uint)0.5f+(rFloat * 255.0f);

		rInt = limit0to255(rInt);
		unsigned char rChar = A.ConvertInttoChar(rInt);
		Zpixel.red = rChar;
		Zpixel.green = Avect[i].green;
		Zpixel.blue = (unsigned char) '\0';
		Zvect.push_back(Zpixel);
	}
	Z.setPixelVector(Zvect);
	Z.setUints();
	return Z;
}


Image Part8(string channel, Image &A) {
	Image::Header newHeader = A.getHeader();
	Image Z;
	Z.setHeader(newHeader);

	vector<Pixel> Avect = A.getPixelVector();
	vector<Pixel> Zvect;

	for (uint i = 0; i < Avect.size(); i++){
		Pixel Zpixel;
		unsigned char channelChar;

		if (channel == "red") {
			channelChar = Avect[i].red;
		} else if (channel == "green") {
			channelChar = Avect[i].green;
		} else if (channel == "blue") {
			channelChar = Avect[i].blue;
		} 

		Zpixel.red = channelChar;
		Zpixel.green = channelChar;
		Zpixel.blue = channelChar;

		Zvect.push_back(Zpixel);
	}
	Z.setPixelVector(Zvect);
	Z.setUints();
	return Z;
}


Image Part9(Image &rLayer, Image &gLayer, Image &bLayer) {
	Image::Header newHeader = rLayer.getHeader(); 
	Image Z;
	Z.setHeader(newHeader);

	vector<Pixel> rvect = rLayer.getPixelVector();
	vector<Pixel> gvect = gLayer.getPixelVector();
	vector<Pixel> bvect = bLayer.getPixelVector();
 
	vector<Pixel> Zvect;
	for (uint i = 0; i < rvect.size(); i++){
		Pixel Zpixel; 
		Zpixel.red = rvect[i].red;
		Zpixel.green = gvect[i].green;
		Zpixel.blue = bvect[i].blue;

		Zvect.push_back(Zpixel);
	}
	Z.setPixelVector(Zvect);
	return Z;
}


Image Part10(Image& A) {
    Image::Header newHeader = A.getHeader();
	Image Z;
    Z.setHeader(newHeader);
    vector <Pixel> Avect = A.getPixelVector();
    vector<Pixel> Zvect;
    int width = newHeader.width;
    int height = newHeader.height;

    for (int row = height - 1; row >= 0; row--) {
        for (int col = width - 1; col >= 0; col--){ 
            int sourceIndex = row * width + col;
            Zvect.push_back(Avect[sourceIndex] );
        }
    }
    Z.setPixelVector(Zvect);
    return Z;
}


uint limit0to255(int result) {
    if (result > 255)
        return 255;
	else if (result < 0)
        return 0;
    else
        return result;
}