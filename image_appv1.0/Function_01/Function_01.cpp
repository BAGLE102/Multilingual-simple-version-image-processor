#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include "pch.h"
#include "Function_01.h"
#include <opencv2/opencv.hpp>
#pragma region including & using
#include<string>
#include <fstream>
#include<stdlib.h>
#include<fstream>
#include<Windows.h>
#include<vector>
using namespace cv;
using std::string;
#pragma endregion

using namespace cv;

IMGFUNC_API void Brightness(char* inputFilename, char* outputFilename, int alpha)
{
    Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
    if (src.data) {
        Mat dst;
        src.convertTo(dst, -1, alpha, 0);  // Adjust brightness    
        imwrite(outputFilename, dst);  // Save adjusted image
    }
}
IMGFUNC_API void AdjustRedChannel(char* inputFilename, char* outputFilename, int alpha)
{
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (src.data) {
		// 提取紅色通道
		std::vector<Mat> channels;
		split(src, channels);
		Mat redChannel = channels[2]; // 紅色通道在索引 2

		// 調整紅色通道的亮度
		Mat adjustedRedChannel;
		redChannel.convertTo(adjustedRedChannel, -1, alpha, 0);

		// 使用convertScaleAbs轉換為8位無符號整數
		convertScaleAbs(adjustedRedChannel, adjustedRedChannel);

		// 用調整後的通道替換原來的紅色通道
		channels[2] = adjustedRedChannel;

		// 將通道合併以形成輸出圖像
		Mat dst;
		merge(channels, dst);

		// 儲存調整後的圖像
		imwrite(outputFilename, dst);
	}
}

IMGFUNC_API void AdjustGreenChannel(char* inputFilename, char* outputFilename, int alpha)
{
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (src.data) {
		// 提取綠色通道
		std::vector<Mat> channels;
		split(src, channels);
		Mat greenChannel = channels[1]; // 綠色通道在索引 1

		// 調整綠色通道的亮度
		Mat adjustedGreenChannel;
		greenChannel.convertTo(adjustedGreenChannel, -1, alpha, 0);

		// 用調整後的通道替換原來的綠色通道
		channels[1] = adjustedGreenChannel;

		// 將通道合併以形成輸出圖像
		Mat dst;
		merge(channels, dst);

		// 儲存調整後的圖像
		imwrite(outputFilename, dst);
	}
}

IMGFUNC_API void AdjustBlueChannel(char* inputFilename, char* outputFilename, int alpha)
{
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (src.data) {
		// 提取藍色通道
		std::vector<Mat> channels;
		split(src, channels);
		Mat blueChannel = channels[0]; // 藍色通道在索引 0

		// 調整藍色通道的亮度
		Mat adjustedBlueChannel;
		blueChannel.convertTo(adjustedBlueChannel, -1, alpha, 0);

		// 用調整後的通道替換原來的藍色通道
		channels[0] = adjustedBlueChannel;

		// 將通道合併以形成輸出圖像
		Mat dst;
		merge(channels, dst);

		// 儲存調整後的圖像
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void RotateImg(char* inputFilename, char* outputFilename, int angle) {
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (!src.empty()) {
		const double scale = 1.0; // 縮放比例
		Point2f center(src.cols / 2.0, src.rows / 2.0); // 設定旋轉中心為影像中心
		Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
		Mat dst;
		warpAffine(src, dst, rotationMatrix, src.size());

		// 將旋轉後的圖像儲存到指定的檔案
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void ResizeImg(char* inputFilename, char* outputFilename, int newSize) {
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (!src.empty()) {
		// 計算縮放比例
		double scale = static_cast<double>(newSize) / 100.0;

		// 計算縮放矩陣
		Mat resizeMatrix = (Mat_<double>(2, 3) << scale, 0, 0, 0, scale, 0);

		// 進行影像的縮放
		Mat dst;
		warpAffine(src, dst, resizeMatrix, Size(), INTER_LINEAR);

		// 將縮放後的圖像儲存到指定的檔案
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void toNegative(char* inputFilename, char* outputFilename) {
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_UNCHANGED);
	if (!src.empty()) {
		// 影像處理
		int rows = src.rows;
		int cols = src.cols;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				src.at<Vec3b>(row, col)[0] = 255 - src.at<Vec3b>(row, col)[0]; // 藍色
				src.at<Vec3b>(row, col)[1] = 255 - src.at<Vec3b>(row, col)[1]; // 綠色
				src.at<Vec3b>(row, col)[2] = 255 - src.at<Vec3b>(row, col)[2]; // 紅色
			}
		}

		// 紀錄最新影像資料
		imwrite(outputFilename, src);
	}
}
IMGFUNC_API void toGrayScale(char* inputFilename, char* outputFilename) {
	// Read the input image
	Mat src = imread(inputFilename, IMREAD_UNCHANGED);
	if (!src.empty()) {
		// Convert the image to grayscale
		Mat dst;
		cvtColor(src, dst, COLOR_BGR2GRAY);

		// Save the grayscale image to the specified file
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void toMosaic(char* inputFilename, char* outputFilename) {
	int blockSize = 80;
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_COLOR);
	if (!src.empty()) {
		// 取得圖像寬高
		int width = src.cols;
		int height = src.rows;

		// 將圖像分成方塊區域並進行馬賽克效果處理
		for (int y = 0; y < height; y += blockSize) {
			for (int x = 0; x < width; x += blockSize) {
				// 計算該區域的範圍
				Rect roi(x, y, min(blockSize, width - x), min(blockSize, height - y));
				Mat block = src(roi);

				// 計算該區域的平均顏色值
				Scalar meanColor = mean(block);

				// 將整個區域塗上該平均顏色值，形成馬賽克效果
				src(roi) = meanColor;
			}
		}

		// 儲存結果
		imwrite(outputFilename, src);
	}
}

IMGFUNC_API void SharpenImage(char* inputFilename, char* outputFilename)
{
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_COLOR);
	if (!src.empty()) {
		// 將圖像轉為灰度
		Mat gray;
		cvtColor(src, gray, COLOR_BGR2GRAY);

		// 使用中值模糊
		Mat blurred;
		medianBlur(gray, blurred, 15);

		// 適應性閾值二值化
		Mat oilPainted;
		adaptiveThreshold(blurred, oilPainted, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 9);

		// 儲存結果
		imwrite(outputFilename, oilPainted);
	}
}
IMGFUNC_API void BlurImage(char* inputFilename, char* outputFilename) {
	// 讀取輸入圖像
	Mat src = imread(inputFilename, IMREAD_COLOR);
	if (!src.empty()) {
		// 使用均值模糊
		Mat blurred;
		blur(src, blurred, Size(20, 20));

		// 儲存結果
		imwrite(outputFilename, blurred);
	}
}
IMGFUNC_API void GammaCorrection(char* inputFilename, char* outputFilename, double gamma) {
	// 讀取輸入圖像
	Mat src = imread(inputFilename);

	if (!src.empty()) {
		// 影像處理
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols; j++) {
				for (int c = 0; c < 3; c++) {
					float fpixel = (float)(src.at<Vec3b>(i, j)[c]) / 255.0;
					src.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(pow(fpixel, gamma) * 255.0f);
				}
			}
		}

		// 儲存調整後的圖像
		imwrite(outputFilename, src);
	}
}




//==================================================================================================

/*IMGFUNC_API ImgData toNegative(ImgData imgdata) {
	// 將接收到的imgdata從uchar陣列轉為Mat變數並指派給src
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();//clone完成後再看要不要刪除
	//影像處理
	if (!src.empty()) {
		int rows = src.rows;
		int cols = src.cols;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				src.at<Vec3b>(row, col)[0] = 255 - src.at<Vec3b>(row, col)[0]; // 藍色
				src.at<Vec3b>(row, col)[1] = 255 - src.at<Vec3b>(row, col)[1]; // 綠色
				src.at<Vec3b>(row, col)[2] = 255 - src.at<Vec3b>(row, col)[2]; // 紅色
			}
		}
	}
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(src, imgdata.path);
	return newdata;
}*/
//myColor RGBmode: Red = 0, Green = 1, Blue = 2
//int ColorValue should be in the range of 0~255
IMGFUNC_API ImgData setRGB(ImgData imgdata, myColor RGBmode, int ColorValue) {
	//get img data
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	//do img process
	if (!src.empty()) {
		int rows = src.rows;
		int cols = src.cols;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				src.at<Vec3b>(row, col)[RGBmode] = ColorValue;
			}
		}
	}
	//set data back
	ImgData newdata;
	newdata = setData(src, imgdata.path);
	return newdata;
}
//alpha調整對比度 beta調整亮度
//強化影像像素 output = img*alpha + beta  fin
IMGFUNC_API ImgData enhanceImg(ImgData imgdata, double alpha_, double beta_) {
	Mat src, dst;
	src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	if (!src.empty()) {
		convertScaleAbs(src, dst, alpha_, beta_);
	}
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//調整影像大小 _size should be 100% ~ 5000%
IMGFUNC_API ImgData reSizeImg(ImgData imgdata, int _size) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat reSizedimg = (Mat_<double>(2, 3) << _size, 0, 0, 0, _size, 0, 0);
	Mat dst;
	warpAffine(src, dst, reSizedimg, src.size());
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//旋轉影像
IMGFUNC_API ImgData rotateImg(ImgData imgdata, double angle) {
	//C#端實現 90度旋轉分n段旋轉
	//呼叫多次 一次轉1x度用timer隔開每次的旋轉
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	if (!src.empty()) {
		const double scale = 1.0; // 縮放比例
		Point2f center(src.cols / 2.0, src.rows / 2.0); // 設定旋轉中心為影像中心
		Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
		Mat dst;
		warpAffine(src, dst, rotationMatrix, src.size());
		//紀錄最新影像資料
		ImgData newdata;
		newdata = setData(dst, imgdata.path);
		return newdata;
	}
}
//模糊 ksize must be positive and odd
IMGFUNC_API ImgData toBlur(ImgData imgdata, int ksize) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	Mat dst;
	if (!src.empty()) {
		blur(src, dst, Size(ksize, ksize));
	}
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//高斯模糊 ksize must be positive and odd
IMGFUNC_API ImgData toGuassianBlur(ImgData imgdata, int ksize) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	Mat dst;
	if (!src.empty()) {
		GaussianBlur(src, dst, Size(ksize, ksize), 0);
	}
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//中值模糊 ksize must be odd and larger than 1
IMGFUNC_API ImgData toMediamBlur(ImgData imgdata, int ksize) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	Mat dst;
	if (!src.empty()) {
		medianBlur(src, dst, ksize);
	}
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}

//對比度 Gamma校正 建議gamma傳入0.1~4.0
/*
IMGFUNC_API ImgData GammaCorrection(ImgData imgdata, double gamma) {
	//建立原始影像
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	//影像處理
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			for (int c = 0; c < 3; c++) {
				float fpixel = (float)(src.at<Vec3b>(i, j)[c]) / 255.0;
				src.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(pow(fpixel, gamma) * 255.0f);
			}
		}
	}
	//儲存資料並回傳
	ImgData newdata;
	newdata = setData(src, imgdata.path);
	return newdata;
}
*/


//將圖片轉為灰階
/*IMGFUNC_API ImgData toGrayScale(ImgData imgdata) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}*/
//新增文字 不好
IMGFUNC_API ImgData addText(ImgData imgdata, char* input, int x, int y) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Point point(x, y);
	putText(src, input, point, 0, 1, Scalar(0, 0, 0), 3);
	ImgData newdata;
	newdata = setData(src, imgdata.path);
	return newdata;
}
//銳化
//gamma = 100 是為了加強與原圖的對比度 實際不會這麼高
IMGFUNC_API ImgData sharpen(ImgData imgdata) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat blur = src.clone();
	Mat dst = src.clone();

	GaussianBlur(src, blur, Size(5, 5), 100);
	addWeighted(src, 1.5, blur, -0.5, 0, dst);

	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//馬賽克
/*
IMGFUNC_API ImgData toMosaic(ImgData imgdata, int level) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	//影像處理
	Mat mosaic, dst;
	int height, width, h, w;
	height = src.rows;
	width = src.cols;
	h = (int)(height / level);
	w = (int)(width / level);
	resize(src, mosaic, Size(w, h), 0, 0, INTER_LINEAR);
	resize(mosaic, dst, Size(width, height), 0, 0, INTER_LINEAR);
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}*/
//冷色調
IMGFUNC_API ImgData modifyColorTemperature(ImgData imgdata, uchar a, uchar b) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat imgB, imgG, imgR;
	std::vector<Mat> channels;
	cv::split(src, channels);
	// 計算各通道的平均值
	imgB = channels[0];
	imgG = channels[1];
	imgR = channels[2];
	Scalar bAve = mean(imgB);
	Scalar gAve = mean(imgG);
	Scalar rAve = mean(imgR);
	double aveGray = (bAve.val[0] + gAve.val[0] + rAve.val[0]) / 3.0;

	// 計算各通道增益係數，並使用此係數計算結果
	double bCoef = aveGray / bAve.val[0];
	double gCoef = aveGray / (gAve.val[0] + a); // 增加20模擬冷色調
	double rCoef = aveGray / (rAve.val[0] + b); // 增加20模擬冷色調
	imgB = imgB * bCoef;
	imgG = imgG * gCoef;
	imgR = imgR * rCoef;
	double imgb, imgg, imgr;
	Mat dst = src.clone();
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			imgb = imgB.at<uchar>(row, col);
			imgg = imgG.at<uchar>(row, col);
			imgr = imgR.at<uchar>(row, col);
			if (imgb > 255) imgb = 255;
			if (imgg > 255) imgg = 255;
			if (imgr > 255) imgr = 255;
			dst.at<Vec3b>(row, col)[0] = imgb;
			dst.at<Vec3b>(row, col)[1] = imgg;
			dst.at<Vec3b>(row, col)[2] = imgr;
		}
	}
	//紀錄最新影像資料
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//飽和度

#pragma endregion

#pragma region other processes



//檢查檔案是否重複 使用good()不好 找其他方法 C12的
IMGFUNC_API bool isRepeat(const char* path) {
	bool repeated = false;
	string tmp = path;
	try {
		std::fstream fin(tmp.c_str());
		if (fin.good()) {
			repeated = true;
		}
		fin.close();
	}
	catch (Exception exc) {
	}
	return repeated;
}





//將圖檔輸出至指定目錄 暫時沒用
IMGFUNC_API void outputImg(const char* mypath, Mat& pic) {
	string Fextension = ".jpg";
	//檔名不重複->直接寫出
	//若是檔名重複，則加上(cnt)
	string tmppath;
	char* ctmppath = nullptr;
	size_t RepeatCnt = 0;
	string dest = "$(SolutionDir)output/";
	try {
		std::fstream myfile;
		myfile.open(dest, std::ios::in);

	}
	catch (Exception exc) {
	}
	//如果原檔名重複
	if (isRepeat(mypath)) {
		do {
			tmppath = mypath;
			tmppath.append("(" + std::to_string(++RepeatCnt) + ")");
			ctmppath = &tmppath[0];
		} while (isRepeat(ctmppath));
	}
	//原檔名沒重複
	else {
		tmppath = mypath;
	}
	cv::imwrite(tmppath.append(Fextension), pic);
}

// 將接收到的imgdata從uchar陣列轉為Mat變數
IMGFUNC_API Mat byteToMat(ImgData imgdata) {
	return Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
}

//紀錄每個影像資料 接收最新tmp路徑 回傳當前影像的imgdata(data,rows,cols,channels)
IMGFUNC_API ImgData setData(Mat src, char* path) {
	ImgData imgdata;
	imgdata.rows = src.rows;
	imgdata.cols = src.cols;
	imgdata.channels = src.channels();
	imgdata.path = path;
	imgdata.data = new uchar[src.rows * src.cols * src.channels()];
	std::memcpy((void*)imgdata.data, (void*)src.data, imgdata.rows * imgdata.cols * imgdata.channels * sizeof(uchar));
	return imgdata;
}

IMGFUNC_API void SenddataBack(ImgData imgdata) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	cv::imshow("test", src);
}

IMGFUNC_API bool saveCurrentImg(ImgData imgdata) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	bool isSaved = cv::imwrite(imgdata.path, src);
	return isSaved ? true : false;
}

#pragma endregion