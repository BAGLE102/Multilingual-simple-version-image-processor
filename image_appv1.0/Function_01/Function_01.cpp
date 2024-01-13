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
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (src.data) {
		// ��������q�D
		std::vector<Mat> channels;
		split(src, channels);
		Mat redChannel = channels[2]; // ����q�D�b���� 2

		// �վ����q�D���G��
		Mat adjustedRedChannel;
		redChannel.convertTo(adjustedRedChannel, -1, alpha, 0);

		// �ϥ�convertScaleAbs�ഫ��8��L�Ÿ����
		convertScaleAbs(adjustedRedChannel, adjustedRedChannel);

		// �νվ�᪺�q�D������Ӫ�����q�D
		channels[2] = adjustedRedChannel;

		// �N�q�D�X�֥H�Φ���X�Ϲ�
		Mat dst;
		merge(channels, dst);

		// �x�s�վ�᪺�Ϲ�
		imwrite(outputFilename, dst);
	}
}

IMGFUNC_API void AdjustGreenChannel(char* inputFilename, char* outputFilename, int alpha)
{
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (src.data) {
		// �������q�D
		std::vector<Mat> channels;
		split(src, channels);
		Mat greenChannel = channels[1]; // ���q�D�b���� 1

		// �վ���q�D���G��
		Mat adjustedGreenChannel;
		greenChannel.convertTo(adjustedGreenChannel, -1, alpha, 0);

		// �νվ�᪺�q�D������Ӫ����q�D
		channels[1] = adjustedGreenChannel;

		// �N�q�D�X�֥H�Φ���X�Ϲ�
		Mat dst;
		merge(channels, dst);

		// �x�s�վ�᪺�Ϲ�
		imwrite(outputFilename, dst);
	}
}

IMGFUNC_API void AdjustBlueChannel(char* inputFilename, char* outputFilename, int alpha)
{
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (src.data) {
		// �����Ŧ�q�D
		std::vector<Mat> channels;
		split(src, channels);
		Mat blueChannel = channels[0]; // �Ŧ�q�D�b���� 0

		// �վ��Ŧ�q�D���G��
		Mat adjustedBlueChannel;
		blueChannel.convertTo(adjustedBlueChannel, -1, alpha, 0);

		// �νվ�᪺�q�D������Ӫ��Ŧ�q�D
		channels[0] = adjustedBlueChannel;

		// �N�q�D�X�֥H�Φ���X�Ϲ�
		Mat dst;
		merge(channels, dst);

		// �x�s�վ�᪺�Ϲ�
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void RotateImg(char* inputFilename, char* outputFilename, int angle) {
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (!src.empty()) {
		const double scale = 1.0; // �Y����
		Point2f center(src.cols / 2.0, src.rows / 2.0); // �]�w���त�߬��v������
		Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
		Mat dst;
		warpAffine(src, dst, rotationMatrix, src.size());

		// �N����᪺�Ϲ��x�s����w���ɮ�
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void ResizeImg(char* inputFilename, char* outputFilename, int newSize) {
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_REDUCED_COLOR_2);
	if (!src.empty()) {
		// �p���Y����
		double scale = static_cast<double>(newSize) / 100.0;

		// �p���Y��x�}
		Mat resizeMatrix = (Mat_<double>(2, 3) << scale, 0, 0, 0, scale, 0);

		// �i��v�����Y��
		Mat dst;
		warpAffine(src, dst, resizeMatrix, Size(), INTER_LINEAR);

		// �N�Y��᪺�Ϲ��x�s����w���ɮ�
		imwrite(outputFilename, dst);
	}
}
IMGFUNC_API void toNegative(char* inputFilename, char* outputFilename) {
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_UNCHANGED);
	if (!src.empty()) {
		// �v���B�z
		int rows = src.rows;
		int cols = src.cols;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				src.at<Vec3b>(row, col)[0] = 255 - src.at<Vec3b>(row, col)[0]; // �Ŧ�
				src.at<Vec3b>(row, col)[1] = 255 - src.at<Vec3b>(row, col)[1]; // ���
				src.at<Vec3b>(row, col)[2] = 255 - src.at<Vec3b>(row, col)[2]; // ����
			}
		}

		// �����̷s�v�����
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
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_COLOR);
	if (!src.empty()) {
		// ���o�Ϲ��e��
		int width = src.cols;
		int height = src.rows;

		// �N�Ϲ���������ϰ�öi�氨�ɧJ�ĪG�B�z
		for (int y = 0; y < height; y += blockSize) {
			for (int x = 0; x < width; x += blockSize) {
				// �p��Ӱϰ쪺�d��
				Rect roi(x, y, min(blockSize, width - x), min(blockSize, height - y));
				Mat block = src(roi);

				// �p��Ӱϰ쪺�����C���
				Scalar meanColor = mean(block);

				// �N��Ӱϰ��W�ӥ����C��ȡA�Φ����ɧJ�ĪG
				src(roi) = meanColor;
			}
		}

		// �x�s���G
		imwrite(outputFilename, src);
	}
}

IMGFUNC_API void SharpenImage(char* inputFilename, char* outputFilename)
{
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_COLOR);
	if (!src.empty()) {
		// �N�Ϲ��ର�ǫ�
		Mat gray;
		cvtColor(src, gray, COLOR_BGR2GRAY);

		// �ϥΤ��ȼҽk
		Mat blurred;
		medianBlur(gray, blurred, 15);

		// �A�����H�ȤG�Ȥ�
		Mat oilPainted;
		adaptiveThreshold(blurred, oilPainted, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 9);

		// �x�s���G
		imwrite(outputFilename, oilPainted);
	}
}
IMGFUNC_API void BlurImage(char* inputFilename, char* outputFilename) {
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename, IMREAD_COLOR);
	if (!src.empty()) {
		// �ϥΧ��ȼҽk
		Mat blurred;
		blur(src, blurred, Size(20, 20));

		// �x�s���G
		imwrite(outputFilename, blurred);
	}
}
IMGFUNC_API void GammaCorrection(char* inputFilename, char* outputFilename, double gamma) {
	// Ū����J�Ϲ�
	Mat src = imread(inputFilename);

	if (!src.empty()) {
		// �v���B�z
		for (int i = 0; i < src.rows; i++) {
			for (int j = 0; j < src.cols; j++) {
				for (int c = 0; c < 3; c++) {
					float fpixel = (float)(src.at<Vec3b>(i, j)[c]) / 255.0;
					src.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(pow(fpixel, gamma) * 255.0f);
				}
			}
		}

		// �x�s�վ�᪺�Ϲ�
		imwrite(outputFilename, src);
	}
}




//==================================================================================================

/*IMGFUNC_API ImgData toNegative(ImgData imgdata) {
	// �N�����쪺imgdata�quchar�}�C�ରMat�ܼƨë�����src
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();//clone������A�ݭn���n�R��
	//�v���B�z
	if (!src.empty()) {
		int rows = src.rows;
		int cols = src.cols;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				src.at<Vec3b>(row, col)[0] = 255 - src.at<Vec3b>(row, col)[0]; // �Ŧ�
				src.at<Vec3b>(row, col)[1] = 255 - src.at<Vec3b>(row, col)[1]; // ���
				src.at<Vec3b>(row, col)[2] = 255 - src.at<Vec3b>(row, col)[2]; // ����
			}
		}
	}
	//�����̷s�v�����
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
//alpha�վ���� beta�վ�G��
//�j�Ƽv������ output = img*alpha + beta  fin
IMGFUNC_API ImgData enhanceImg(ImgData imgdata, double alpha_, double beta_) {
	Mat src, dst;
	src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	if (!src.empty()) {
		convertScaleAbs(src, dst, alpha_, beta_);
	}
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//�վ�v���j�p _size should be 100% ~ 5000%
IMGFUNC_API ImgData reSizeImg(ImgData imgdata, int _size) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat reSizedimg = (Mat_<double>(2, 3) << _size, 0, 0, 0, _size, 0, 0);
	Mat dst;
	warpAffine(src, dst, reSizedimg, src.size());
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//����v��
IMGFUNC_API ImgData rotateImg(ImgData imgdata, double angle) {
	//C#�ݹ�{ 90�ױ����n�q����
	//�I�s�h�� �@����1x�ץ�timer�j�}�C��������
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	if (!src.empty()) {
		const double scale = 1.0; // �Y����
		Point2f center(src.cols / 2.0, src.rows / 2.0); // �]�w���त�߬��v������
		Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);
		Mat dst;
		warpAffine(src, dst, rotationMatrix, src.size());
		//�����̷s�v�����
		ImgData newdata;
		newdata = setData(dst, imgdata.path);
		return newdata;
	}
}
//�ҽk ksize must be positive and odd
IMGFUNC_API ImgData toBlur(ImgData imgdata, int ksize) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	Mat dst;
	if (!src.empty()) {
		blur(src, dst, Size(ksize, ksize));
	}
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//�����ҽk ksize must be positive and odd
IMGFUNC_API ImgData toGuassianBlur(ImgData imgdata, int ksize) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	Mat dst;
	if (!src.empty()) {
		GaussianBlur(src, dst, Size(ksize, ksize), 0);
	}
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//���ȼҽk ksize must be odd and larger than 1
IMGFUNC_API ImgData toMediamBlur(ImgData imgdata, int ksize) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
	Mat dst;
	if (!src.empty()) {
		medianBlur(src, dst, ksize);
	}
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}

//���� Gamma�ե� ��ĳgamma�ǤJ0.1~4.0
/*
IMGFUNC_API ImgData GammaCorrection(ImgData imgdata, double gamma) {
	//�إ߭�l�v��
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	//�v���B�z
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			for (int c = 0; c < 3; c++) {
				float fpixel = (float)(src.at<Vec3b>(i, j)[c]) / 255.0;
				src.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(pow(fpixel, gamma) * 255.0f);
			}
		}
	}
	//�x�s��ƨæ^��
	ImgData newdata;
	newdata = setData(src, imgdata.path);
	return newdata;
}
*/


//�N�Ϥ��ର�Ƕ�
/*IMGFUNC_API ImgData toGrayScale(ImgData imgdata) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}*/
//�s�W��r ���n
IMGFUNC_API ImgData addText(ImgData imgdata, char* input, int x, int y) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Point point(x, y);
	putText(src, input, point, 0, 1, Scalar(0, 0, 0), 3);
	ImgData newdata;
	newdata = setData(src, imgdata.path);
	return newdata;
}
//�U��
//gamma = 100 �O���F�[�j�P��Ϫ����� ��ڤ��|�o��
IMGFUNC_API ImgData sharpen(ImgData imgdata) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat blur = src.clone();
	Mat dst = src.clone();

	GaussianBlur(src, blur, Size(5, 5), 100);
	addWeighted(src, 1.5, blur, -0.5, 0, dst);

	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//���ɧJ
/*
IMGFUNC_API ImgData toMosaic(ImgData imgdata, int level) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	//�v���B�z
	Mat mosaic, dst;
	int height, width, h, w;
	height = src.rows;
	width = src.cols;
	h = (int)(height / level);
	w = (int)(width / level);
	resize(src, mosaic, Size(w, h), 0, 0, INTER_LINEAR);
	resize(mosaic, dst, Size(width, height), 0, 0, INTER_LINEAR);
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}*/
//�N���
IMGFUNC_API ImgData modifyColorTemperature(ImgData imgdata, uchar a, uchar b) {
	Mat src = Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data);
	Mat imgB, imgG, imgR;
	std::vector<Mat> channels;
	cv::split(src, channels);
	// �p��U�q�D��������
	imgB = channels[0];
	imgG = channels[1];
	imgR = channels[2];
	Scalar bAve = mean(imgB);
	Scalar gAve = mean(imgG);
	Scalar rAve = mean(imgR);
	double aveGray = (bAve.val[0] + gAve.val[0] + rAve.val[0]) / 3.0;

	// �p��U�q�D�W�q�Y�ơA�èϥΦ��Y�ƭp�⵲�G
	double bCoef = aveGray / bAve.val[0];
	double gCoef = aveGray / (gAve.val[0] + a); // �W�[20�����N���
	double rCoef = aveGray / (rAve.val[0] + b); // �W�[20�����N���
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
	//�����̷s�v�����
	ImgData newdata;
	newdata = setData(dst, imgdata.path);
	return newdata;
}
//���M��

#pragma endregion

#pragma region other processes



//�ˬd�ɮ׬O�_���� �ϥ�good()���n ���L��k C12��
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





//�N���ɿ�X�ܫ��w�ؿ� �ȮɨS��
IMGFUNC_API void outputImg(const char* mypath, Mat& pic) {
	string Fextension = ".jpg";
	//�ɦW������->�����g�X
	//�Y�O�ɦW���ơA�h�[�W(cnt)
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
	//�p�G���ɦW����
	if (isRepeat(mypath)) {
		do {
			tmppath = mypath;
			tmppath.append("(" + std::to_string(++RepeatCnt) + ")");
			ctmppath = &tmppath[0];
		} while (isRepeat(ctmppath));
	}
	//���ɦW�S����
	else {
		tmppath = mypath;
	}
	cv::imwrite(tmppath.append(Fextension), pic);
}

// �N�����쪺imgdata�quchar�}�C�ରMat�ܼ�
IMGFUNC_API Mat byteToMat(ImgData imgdata) {
	return Mat(imgdata.rows, imgdata.cols, CV_8UC(imgdata.channels), (void*)imgdata.data).clone();
}

//�����C�Ӽv����� �����̷stmp���| �^�Ƿ�e�v����imgdata(data,rows,cols,channels)
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