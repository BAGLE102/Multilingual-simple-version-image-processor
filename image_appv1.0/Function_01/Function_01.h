#pragma once
//………………………………………………
#ifdef IMGFUNC_EXPORTS
#define IMGFUNC_API extern "C" __declspec(dllexport)
#else
#define IMGFUNC_API extern "C" __declspec(dllimport)
#endif
#pragma once 
#include<string>
#include<vector>
#include <opencv2/opencv.hpp>
//……………………………………………… 


IMGFUNC_API struct ImgData {
    unsigned char* data;
    int rows;
    int cols;
    int channels;
    char* path;
};

IMGFUNC_API struct TextInfo {
    int font;
    double fontScale;
    int colorR;
    int colorG;
    int colorB;
    int thickness;
};

IMGFUNC_API struct Coordination {
    float x;
    float y;
};

enum myColor {
    Red = 2,
    Green = 1,
    Blue = 0
};

IMGFUNC_API void Brightness(char* inputFilename, char* outputFilename, int alpha);
IMGFUNC_API void AdjustRedChannel(char* inputFilename, char* outputFilename, int alpha);
IMGFUNC_API void AdjustGreenChannel(char* inputFilename, char* outputFilename, int alpha);
IMGFUNC_API void AdjustBlueChannel(char* inputFilename, char* outputFilename, int alpha);
IMGFUNC_API void RotateImg(char* inputFilename, char* outputFilename, int angle);
IMGFUNC_API void ResizeImg(char* inputFilename, char* outputFilename, int newSize);
IMGFUNC_API void toNegative(char* inputFilename, char* outputFilename);
IMGFUNC_API void toGrayScale(char* inputFilename, char* outputFilename);
IMGFUNC_API void toMosaic(char* inputFilename, char* outputFilename);
IMGFUNC_API void SharpenImage(char* inputFilename, char* outputFilename);
IMGFUNC_API void BlurImage(char* inputFilename, char* outputFilename);
IMGFUNC_API void GammaCorrection(char* inputFilename, char* outputFilename, double gamma);
IMGFUNC_API ImgData enhanceImg(ImgData imgdata, double alpha_, double beta_);
IMGFUNC_API ImgData toBlur(ImgData imgdata, int ksize);
IMGFUNC_API ImgData toGuassianBlur(ImgData imgdata, int ksize);
IMGFUNC_API ImgData toMediamBlur(ImgData imgdata, int ksize);
IMGFUNC_API ImgData setRGB(ImgData imgdata, myColor RGBmode, int ColorValue);
IMGFUNC_API ImgData rotateImg(ImgData imgdata, double angle);
IMGFUNC_API ImgData reSizeImg(ImgData imgdata, int _size);
IMGFUNC_API ImgData modifyColorTemperature(ImgData imgdata, uchar a, uchar b);
IMGFUNC_API ImgData sharpen(ImgData imgdata);
//其他處理
IMGFUNC_API bool isRepeat(const char* path);
IMGFUNC_API ImgData setData(cv::Mat src, char* path);
//荒廢
IMGFUNC_API void outputImg(const char* path, cv::Mat& pic);//待刪除
IMGFUNC_API void SenddataBack(ImgData imgdata);//測試用 待刪除
IMGFUNC_API bool saveCurrentImg(ImgData imgdata);//移動至C#端