#ifndef BMPLOADER_H
#define BMPLOADER_H
//#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for Linux platform, plz make sure the size of data type is correct for BMP spec.
// if you use this on Windows or other platforms, plz pay attention to this.
typedef int LONG;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;

// __attribute__((packed)) on non-Intel arch may cause some unexpected error, plz be informed.

typedef struct tagBITMAPFILEHEADER
{
    WORD    bfType; // 2  /* Magic identifier */
    DWORD   bfSize; // 4  /* File size in bytes */
    WORD    bfReserved1; // 2
    WORD    bfReserved2; // 2
    DWORD   bfOffBits; // 4 /* Offset to image data, bytes */
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    DWORD    biSize; // 4 /* Header size in bytes */
    LONG     biWidth; // 4 /* Width of image */
    LONG     biHeight; // 4 /* Height of image */
    WORD     biPlanes; // 2 /* Number of colour planes */
    WORD     biBitCount; // 2 /* Bits per pixel */
    DWORD    biCompress; // 4 /* Compression type */
    DWORD    biSizeImage; // 4 /* Image size in bytes */
    LONG     biXPelsPerMeter; // 4
    LONG     biYPelsPerMeter; // 4 /* Pixels per meter */
    DWORD    biClrUsed; // 4 /* Number of colours */
    DWORD    biClrImportant; // 4 /* Important colours */
} __attribute__((packed)) BITMAPINFOHEADER;

/*
typedef struct tagRGBQUAD
{
    unsigned char    rgbBlue;
    unsigned char    rgbGreen;
    unsigned char    rgbRed;
    unsigned char    rgbReserved;
} RGBQUAD;
* for biBitCount is 16/24/32, it may be useless
*/

typedef struct
{
        BYTE    b;
        BYTE    g;
        BYTE    r;
} RGB_data; // RGB TYPE, plz also make sure the order


class BmpLoader
{
    public:
        unsigned char* textureData;
        int iWidth, iHeight;

        BmpLoader(const char*);
        ~BmpLoader();

    private:
        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;
};

#endif // BMPLOADER_H
