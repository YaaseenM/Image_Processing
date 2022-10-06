#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Image.h"
#include <string>
using namespace std;

void GetDataFromBinaryFile(string filePath, Header& header, vector<Header::Pixel>& Pixels) {
    ifstream file;
    file.open(filePath, ios_base::binary); //output/part1.tga
    if (file.is_open()) {
        file.read(&header.idLength, 1);
        file.read(&header.colorMapType, 1);
        file.read(&header.dataTypeCode, 1);
        file.read((char*)&header.colorMapOrigin, 2);
        file.read((char*)&header.colorMapLength, 2);
        file.read(&header.colorMapDepth, 1);
        file.read((char*)&header.xOrigin, 2);
        file.read((char*)&header.yOrigin, 2);
        file.read((char*)&header.width, 2);
        file.read((char*)&header.height, 2);
        file.read(&header.bitsPerPixel, 1);
        file.read(&header.imageDescriptor, 1);
        for(short i = 0; i < header.Getheight(); i++) {
            for(short j = 0; j < header.Getwidth(); j++) {
                unsigned char r = 0;
                unsigned char g = 0;
                unsigned char b = 0;
                file.read((char*)&b, 1);
                file.read((char*)&g, 1);
                file.read((char*)&r, 1);
                Header::Pixel newHeaderPixel(r, g, b);
                Pixels.push_back(newHeaderPixel);
            }
        }
        file.close();
    } else {
        cout << "File was not opened." << endl;
    }

}
void WriteFile(vector<Header::Pixel>& Image, Header& header, string& filePath) {
    ofstream file;
    file.open(filePath, ios_base::binary); //output/part1.tga
    if (file.is_open()) {
        file.write(&header.idLength, 1);
        file.write(&header.colorMapType, 1);
        file.write(&header.dataTypeCode, 1);
        file.write((char*)&header.colorMapOrigin, 2);
        file.write((char*)&header.colorMapLength, 2);
        file.write(&header.colorMapDepth, 1);
        file.write((char*)&header.xOrigin, 2);
        file.write((char*)&header.yOrigin, 2);
        file.write((char*)&header.width, 2);
        file.write((char*)&header.height, 2);
        file.write(&header.bitsPerPixel, 1);
        file.write(&header.imageDescriptor, 1);
        int fileSize = header.Getheight() * header.Getwidth();
        for(int i = 0; i < fileSize; i++) {
            file.write((char*)&Image[i].blue, 1);
            file.write((char*)&Image[i].green, 1);
            file.write((char*)&Image[i].red, 1);
        }
        file.close();
    } else {
        cout << "File was not opened." << endl;
    }
}

void WriteMultipleFiles(vector<Header::Pixel>& Image1, Header& header1, vector<Header::Pixel>& Image2, Header& header2, vector<Header::Pixel>& Image3, Header& header3, vector<Header::Pixel>& Image4, Header& header4, string filePath) {
    ofstream file;
    file.open(filePath, ios_base::binary); //output/extracredit.tga
    if (file.is_open()) {
        int comWidth = header1.Getwidth() + header2.Getwidth();
        int comHeight = header1.Getheight() + header3.Getheight();
        file.write(&header1.idLength, 1);
        file.write(&header1.colorMapType, 1);
        file.write(&header1.dataTypeCode, 1);
        file.write((char*)&header1.colorMapOrigin, 2);
        file.write((char*)&header1.colorMapLength, 2);
        file.write(&header1.colorMapDepth, 1);
        file.write((char*)&header1.xOrigin, 2);
        file.write((char*)&header1.yOrigin, 2);
        file.write((char*)&comWidth, 2);
        file.write((char*)&comHeight, 2);
        file.write(&header1.bitsPerPixel, 1);
        file.write(&header1.imageDescriptor, 1);
        unsigned int fileSize = (header1.Getheight() + header3.Getheight()) * (header1.Getwidth() + header2.Getwidth());
        for(unsigned int i = 0; i < fileSize / 2; i++) {
            if ((i/512) % 2 == 0) {
                file.write((char *) &Image3[i - (512 * (i / 1024))].blue, 1);
                file.write((char *) &Image3[i - (512 * (i / 1024))].green, 1);
                file.write((char *) &Image3[i - (512 * (i / 1024))].red, 1);
            } else {
                file.write((char*)&Image4[i - (512 * ((i / 1024) + 1))].blue, 1);
                file.write((char*)&Image4[i - (512 * ((i / 1024) + 1))].green, 1);
                file.write((char*)&Image4[i - (512 * ((i / 1024) + 1))].red, 1);
            }
        }
        for(unsigned int i = 0; i < fileSize / 2; i++) {
            if ((i/512) % 2 == 0) {
                file.write((char *) &Image1[i - (512 * (i / 1024))].blue, 1);
                file.write((char *) &Image1[i - (512 * (i / 1024))].green, 1);
                file.write((char *) &Image1[i - (512 * (i / 1024))].red, 1);
            } else {
                file.write((char*)&Image2[i- (512 * ((i / 1024) + 1))].blue, 1);
                file.write((char*)&Image2[i- (512 * ((i / 1024) + 1))].green, 1);
                file.write((char*)&Image2[i- (512 * ((i / 1024) + 1))].red, 1);
            }
        }
        file.close();
    } else {
        cout << "File was not opened." << endl;
    }
}

void Overlay (vector<Header::Pixel>& Pixels1, vector<Header::Pixel>& Pixels2, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = 0; i < Pixels1.size(); i++) {
        float pR1 = 0.000f;
        float pG1 = 0.000f;
        float pB1 = 0.000f;
        float pR2 = 0.000f;
        float pG2 = 0.000f;
        float pB2 = 0.000f;
        pR1 = (float) Pixels1[i].red / 255;
        pG1 = (float) Pixels1[i].green / 255;
        pB1 = (float) Pixels1[i].blue / 255;
        pR2 = (float) Pixels2[i].red / 255;
        pG2 = (float) Pixels2[i].green / 255;
        pB2 = (float) Pixels2[i].blue / 255;
        float *tmpPixel = new float[3];
        if(pR2 > 0.5){
            tmpPixel[0] = 1 - 2*(1-pR1)*(1-pR2);
        } else {
            tmpPixel[0] = 2*pR1*pR2;
        }
        if(pG2 > 0.5){
            tmpPixel[1] = 1 - 2*(1-pG1)*(1-pG2);
        } else {
            tmpPixel[1] = 2*pG1*pG2;
        }
        if(pR2 > 0.5){
            tmpPixel[2] = 1 - 2*(1-pB1)*(1-pB2);
        } else {
            tmpPixel[2] = 2*pB1*pB2;
        }
        tmpPixel[0] = (tmpPixel[0] * 255) + 0.5f;
        tmpPixel[1] = (tmpPixel[1] * 255) + 0.5f;
        tmpPixel[2] = (tmpPixel[2] * 255) + 0.5f;
        unsigned char r = tmpPixel[0];
        unsigned char g = tmpPixel[1];
        unsigned char b = tmpPixel[2];
        delete[] tmpPixel;
        Header::Pixel newHeaderPixel(r, g, b);
        newImage.push_back(newHeaderPixel);
    }
        WriteFile(newImage, header, filePath);
}

void Screen (vector<Header::Pixel>& Pixels1, vector<Header::Pixel>& Pixels2, Header& header, string filePath) {
    vector<Header::Pixel> newImageHere;
    for (int i = 0; i < Pixels1.size(); i++) {
        float pR1 = 0.000f;
        float pG1 = 0.000f;
        float pB1 = 0.000f;
        float pR2 = 0.000f;
        float pG2 = 0.000f;
        float pB2 = 0.000f;
        pR1 = (float) Pixels1[i].red / 255;
        pG1 = (float) Pixels1[i].green / 255;
        pB1 = (float) Pixels1[i].blue / 255;
        pR2 = (float) Pixels2[i].red / 255;
        pG2 = (float) Pixels2[i].green / 255;
        pB2 = (float) Pixels2[i].blue / 255;
        float *tmpPixel = new float[3];
        tmpPixel[0] = ((1 - (1-pR1)*(1-pR2)) * 255) + 0.5f;
        tmpPixel[1] = ((1 - (1-pG1)*(1-pG2)) * 255) + 0.5f;
        tmpPixel[2] = ((1 - (1-pB1)*(1-pB2)) * 255) + 0.5f;
        unsigned char r = tmpPixel[0];
        unsigned char g = tmpPixel[1];
        unsigned char b = tmpPixel[2];
        delete[] tmpPixel;
        Header::Pixel newHeaderPixel(r, g, b);
        newImageHere.push_back(newHeaderPixel);
    }
        WriteFile(newImageHere, header, filePath);
}



void Subtract (vector<Header::Pixel>& Pixels1, vector<Header::Pixel>& Pixels2, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = 0; i < Pixels1.size(); i++) {
        int *tmpPixel = new int[3];
        tmpPixel[0] = Pixels1[i].red - Pixels2[i].red;
        tmpPixel[1] = Pixels1[i].green - Pixels2[i].green;
        tmpPixel[2] = Pixels1[i].blue - Pixels2[i].blue;
        for (char j = 0; j < 3; j++){
            if(tmpPixel[j] < 0) {
                tmpPixel[j] = 0;
            }
        }
        unsigned char r = tmpPixel[0];
        unsigned char g = tmpPixel[1];
        unsigned char b = tmpPixel[2];
        delete[] tmpPixel;
        Header::Pixel newHeaderPixel(r, g, b);
        newImage.push_back(newHeaderPixel);
    }
    WriteFile(newImage, header, filePath);
}

void Multiply (vector<Header::Pixel>& Pixels1, vector<Header::Pixel>& Pixels2, vector<Header::Pixel>& Pixels3, unsigned short value, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = 0; i < Pixels1.size(); i++) {
        float pR = 0.000f;
        float pG = 0.000f;
        float pB = 0.000f;
        pR = (float) Pixels2[i].red / 255;
        pG = (float) Pixels2[i].green / 255;
        pB = (float) Pixels2[i].blue / 255;
        float *tmpPixel = new float[3];
        tmpPixel[0] = (Pixels1[i].red * pR) + 0.5f;
        tmpPixel[1] = (Pixels1[i].green * pG) + 0.5f;
        tmpPixel[2] = (Pixels1[i].blue * pB) + 0.5f;
        unsigned char r = tmpPixel[0];
        unsigned char g = tmpPixel[1];
        unsigned char b = tmpPixel[2];
        delete[] tmpPixel;
        Header::Pixel newHeaderPixel(r, g, b);
        newImage.push_back(newHeaderPixel);
    }
    if (value == 1) {
        WriteFile(newImage, header, filePath);
    } else if (value == 2) {
        Screen(newImage, Pixels3, header, filePath);
    } else if (value == 3) {
        Subtract(newImage, Pixels3, header, filePath);
    }
}

void Rotate (vector<Header::Pixel>& Pixels, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = Pixels.size() - 1; i >= 0; i--) {
        Header::Pixel newHeaderPixel(Pixels[i].red, Pixels[i].green, Pixels[i].blue);
        newImage.push_back(newHeaderPixel);
    }
    WriteFile(newImage, header, filePath);
}

void Combine (vector<Header::Pixel>& Pixels1, vector<Header::Pixel>& Pixels2, vector<Header::Pixel>& Pixels3, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = 0; i < Pixels1.size(); i++) {
        Header::Pixel newHeaderPixel(Pixels1[i].red, Pixels2[i].green, Pixels3[i].blue);
        newImage.push_back(newHeaderPixel);
    }
    WriteFile(newImage, header, filePath);
}

void Split (vector<Header::Pixel>& Pixels, Header& header, string filePath, string filePath2, string filePath3) {
    vector<Header::Pixel> redImage;
    vector<Header::Pixel> greenImage;
    vector<Header::Pixel> blueImage;
    for (int i = 0; i < Pixels.size(); i++) {
        redImage.push_back(Header::Pixel(Pixels[i].red,Pixels[i].red,Pixels[i].red));
        greenImage.push_back(Header::Pixel(Pixels[i].green, Pixels[i].green,Pixels[i].green));
        blueImage.push_back(Header::Pixel(Pixels[i].blue,Pixels[i].blue,Pixels[i].blue));
    }
    WriteFile(redImage, header, filePath);
    WriteFile(greenImage, header, filePath2);
    WriteFile(blueImage, header, filePath3);
}

void Scale (vector<Header::Pixel>& Pixels, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = 0; i < Pixels.size(); i++) {
        int *tmpPixel = new int[1];
        tmpPixel[0] = Pixels[i].red * 4;
        if(tmpPixel[0] > 255) {
            tmpPixel[0] = 255;
        }
        unsigned char r = tmpPixel[0];
        unsigned char g = Pixels[i].green;
        unsigned char b = 0;
        delete[] tmpPixel;
        Header::Pixel newHeaderPixel(r, g, b);
        newImage.push_back(newHeaderPixel);
    }
    WriteFile(newImage, header, filePath);
}

void Add(vector<Header::Pixel>& Pixels, Header& header, string filePath) {
    vector<Header::Pixel> newImage;
    for (int i = 0; i < Pixels.size(); i++) {
        unsigned int g = (int)Pixels[i].green + 200;
        if(g > 255) {
            g = 255;
        }
        Header::Pixel newHeaderPixel((int)Pixels[i].red, g, (int)Pixels[i].blue);
        newImage.push_back(newHeaderPixel);
    }
    WriteFile(newImage, header, filePath);
}

bool Test(string example, string test) {
    ifstream file;
    Header headerExample;
    vector<Header::Pixel> examplePixels;
    GetDataFromBinaryFile(example, headerExample, examplePixels);
    Header headerTest;
    vector<Header::Pixel> testPixels;
    GetDataFromBinaryFile(test, headerTest, testPixels);


    for (int i = 0; i < testPixels.size(); i++) {
        unsigned short rT = (int)testPixels[i].red;
        unsigned short gT = (int)testPixels[i].green;
        unsigned short bT = (int)testPixels[i].blue;
        unsigned short rE = (int)examplePixels[i].red;
        unsigned short gE = (int)examplePixels[i].green;
        unsigned short bE = (int)examplePixels[i].blue;
        if (rT != rE || gT != gE || bT != bE) {
            cout << (int)testPixels[i].red << endl;
            cout << (int)examplePixels[i].red << endl;
            cout << (int)testPixels[i].green << endl;
            cout << (int)examplePixels[i].green << endl;
            cout << (int)testPixels[i].blue << endl;
            cout << (int)examplePixels[i].blue << endl;
            cout << "At i: " << i << endl;
            return false;
        } else {
            continue;
        }
    }
    return true;
}

int main() {
    Header headerCar;
    vector<Header::Pixel> CarPixels;
    GetDataFromBinaryFile("input/car.tga", headerCar, CarPixels);

    Header headerCircles;
    vector<Header::Pixel> CirclesPixels;
    GetDataFromBinaryFile("input/circles.tga", headerCircles, CirclesPixels);

    Header headerLayerBlue;
    vector<Header::Pixel> LayerBluePixels;
    GetDataFromBinaryFile("input/layer_blue.tga", headerLayerBlue, LayerBluePixels);

    Header headerLayerGreen;
    vector<Header::Pixel> LayerGreenPixels;
    GetDataFromBinaryFile("input/layer_green.tga", headerLayerGreen, LayerGreenPixels);

    Header headerLayerRed;
    vector<Header::Pixel> LayerRedPixels;
    GetDataFromBinaryFile("input/layer_red.tga", headerLayerRed, LayerRedPixels);

    Header headerLayer1;
    vector<Header::Pixel> Layer1Pixels;
    GetDataFromBinaryFile("input/layer1.tga", headerLayer1, Layer1Pixels);

    Header headerLayer2;
    vector<Header::Pixel> Layer2Pixels;
    GetDataFromBinaryFile("input/layer2.tga", headerLayer2, Layer2Pixels);

    Header headerPattern1;
    vector<Header::Pixel> Pattern1Pixels;
    GetDataFromBinaryFile("input/pattern1.tga", headerPattern1, Pattern1Pixels);

    Header headerPattern2;
    vector<Header::Pixel> Pattern2Pixels;
    GetDataFromBinaryFile("input/pattern2.tga", headerPattern2, Pattern2Pixels);

    Header headerText;
    vector<Header::Pixel> TextPixels;
    GetDataFromBinaryFile("input/text.tga", headerText, TextPixels);

    Header headerText2;
    vector<Header::Pixel> Text2Pixel;
    GetDataFromBinaryFile("input/text2.tga", headerText2, Text2Pixel);

    cout << "Task 1" << endl;
    Multiply(Layer1Pixels, Pattern1Pixels, CarPixels,  1, headerLayer1, "output/part1.tga");
    if(Test("examples/EXAMPLE_part1.tga", "output/part1.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 2" << endl;
    Subtract(CarPixels, Layer2Pixels, headerCar, "output/part2.tga");
    if(Test("examples/EXAMPLE_part2.tga", "output/part2.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 3" << endl;
    Multiply(Layer1Pixels, Pattern2Pixels, TextPixels, 2, headerLayer2, "output/part3.tga");
    if(Test("examples/EXAMPLE_part3.tga", "output/part3.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 4" << endl;
    Multiply(Layer2Pixels, CirclesPixels, Pattern2Pixels, 3, headerLayer2, "output/part4.tga");
    if(Test("examples/EXAMPLE_part4.tga", "output/part4.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 5" << endl;
    Overlay(Layer1Pixels, Pattern1Pixels, headerLayer1, "output/part5.tga");
    if(Test("examples/EXAMPLE_part5.tga", "output/part5.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 6" << endl;
    Add(CarPixels, headerCar, "output/part6.tga");
    if(Test("examples/EXAMPLE_part6.tga", "output/part6.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 7" << endl;
    Scale(CarPixels, headerCar, "output/part7.tga");
    if(Test("examples/EXAMPLE_part7.tga", "output/part7.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 8" << endl;
    Split(CarPixels, headerCar, "output/part8_r.tga", "output/part8_g.tga", "output/part8_b.tga");
    if(Test("examples/EXAMPLE_part8_r.tga", "output/part8_r.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    if(Test("examples/EXAMPLE_part8_g.tga", "output/part8_g.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    if(Test("examples/EXAMPLE_part8_b.tga", "output/part8_b.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 9" << endl;
    Combine(LayerRedPixels, LayerGreenPixels, LayerBluePixels, headerLayerRed, "output/part9.tga");
    if(Test("examples/EXAMPLE_part9.tga", "output/part9.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout << "Task 10" << endl;
    Rotate(Text2Pixel, headerText2, "output/part10.tga");
    if(Test("examples/EXAMPLE_part10.tga", "output/part10.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
    cout<< "Task 11" << endl;
    WriteMultipleFiles(CarPixels, headerCar, CirclesPixels, headerCircles, TextPixels, headerText, Pattern1Pixels, headerPattern1, "output/extracredit.tga");
    if(Test("examples/EXAMPLE_extracredit.tga", "output/extracredit.tga") == true) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "Failure" << endl;
    }
}