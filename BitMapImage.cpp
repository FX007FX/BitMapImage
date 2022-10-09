//  100×100 px 24-bit BitMap Image Generator Program
//  https://en.wikipedia.org/wiki/BMP_file_format


#include <iostream>
#include <fstream>

using namespace std;

void image(ofstream &, char, unsigned char, unsigned char,
            unsigned char, unsigned char, unsigned char,
            unsigned char, unsigned char, unsigned char, unsigned char);

int main() {

    char zero = 0, one = 1;

    unsigned char width = 100;
    unsigned char height = 100;
    unsigned char size0 = (unsigned char)((width * height * 3) + 54);
    unsigned char size1 = (unsigned char)(((unsigned char)(width * height * 3) + 54) >> 8);
    unsigned char size2 = (unsigned char)(((width * height * 3) + 54) >> 16);
    unsigned char size3 = (unsigned char)(((width * height * 3) + 54) >> 24);
    unsigned char offset = 54;
    unsigned char bytes = 40;
    unsigned char bits = 24;
    unsigned char bisize0 = (unsigned char)(width * height * 3);
    unsigned char bisize1 = (unsigned char)((width * height * 3) >> 8);
    unsigned char px0 = (unsigned char)(72 * 40);
    unsigned char px1 = (unsigned char)((72 * 40) / 256) >> 8;

    //BMP
    ofstream bmp("BitMapImage.bmp");
    if (!bmp) {
        cerr << "\nImage Generation Failed" << endl;
        return 1;
    }

    //BMPHeader_ID
    bmp << 'B' << 'M';

    //BMPHeader_Size
    bmp << size0 << size1 << size2 << size3;

    //BMPHeader_Reserved[1 & 2]
    for (char i = 0; i < 4; i++) {
        bmp << zero;
    }

    //BMPHeader_Data
    bmp << offset;
    for (char i = 0; i < 3; i++) {
        bmp << zero;
    }

    //DIBHeader_Number
    bmp << bytes;
    for (char i = 0; i < 3; i++) {
        bmp << zero;
    }

    //DIBHeader_Width
    bmp << width;
    for (char i = 0; i < 3; i++) {
        bmp << zero;
    }

    //DIBHeader_Height
    bmp << height;
    for (char i = 0; i < 3; i++) {
        bmp << zero;
    }

    //DIBHeader_ColorPlanes
    bmp << one << zero;

    //DIBHeader_BitsPerPixel
    bmp << bits << zero;

    //DIBHeader_BI_RGB
    for (char i = 0; i < 4; i++) {
        bmp << zero;
    }

    //DIBHeader_Data
    bmp << bisize0 << bisize1 << zero << zero;

    //DIBHeader_PixelsPerMeter_X_Axis
    bmp << px0 << px1 << zero << zero;

    //DIBHeader_PixelsPerMeter_Y_Axis
    bmp << px0 << px1 << zero << zero;

    //DIBHeader_ColorPalette
    for (char i = 0; i < 4; i++) {
        bmp << zero;
    }

    //DIBHeader_ColorImportance
    for (char i = 0; i < 4; i++) {
        bmp << zero;
    }

    //RGB_Color
    unsigned char b = 210;
    unsigned char g = 70;
    unsigned char r = 130;
    unsigned char b1 = 0;
    unsigned char g1 = 210;
    unsigned char r1 = 255;
    unsigned char b2 = 0;
    unsigned char g2 = 0;
    unsigned char r2 = 255;

    //UsefulVariable
    char x = 100;

    image(bmp, x, b, g, r, b1, g1, r1, b2, g2, r2);

    bmp.close();
    
    cout << "\nImage Generation Successful" << endl;

    return 0;
}

void image(ofstream &ofs, char var, unsigned char blue, unsigned char green,
            unsigned char red, unsigned char blue_, unsigned char green_,
            unsigned char red_, unsigned char blue__, unsigned char green__, unsigned char red__) {

    for (char i = 100; i >= 1; i--) {
        for (char j = 1; j <= 100; j++) {
            if (i - var >= 5 && i - var <= 95 && j >= 5 && j <= 50 && i - var <= 2 * j - (i - var) / 2) {
                ofs << blue_ << green_ << red_;
            }
            else if (i >= 5 && i <= 95 && j >= 50 && j <= 95 && i >= 2 * (j - 50) + (i - var) / 2) {
                ofs << blue_ << green_ << red_;
            }
            else if ((pow(i - var - 83, 2) + pow(j - 50, 2) <= pow(15, 2))) {
                ofs << blue__ << green__ << red__;
            }
            else {
                ofs << blue << green << red;
            }
        }

        if (i >= 66 && i <= 100) {
            blue -= 1;
            green -= 1;
            red -= 1;
            blue_ += 3;
        }
        else if (i >= 33 && i <= 66) {
            blue -= 1;
            red -= 1;
            blue_ += 2;
            green_ += 1;
            blue__ += 1;
            green__ += 1;
        }
        else {
            blue -= 1;
            red -= 1;
            red__ -= 3;
        }

        var -= 2;
    }
}