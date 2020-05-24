#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
	Mat src1 = imread("moon_blur.png", IMREAD_GRAYSCALE);
	Mat lap_img = Mat::zeros(src1.size(), src1.type());
	Mat sharpen_img = Mat::zeros(src1.size(), src1.type());

	if (!src1.data) {
		printf("Error loading src1 \n");
		return -1;
	}

	float laplacian1[3][3] = { { 0, -1, 0 },
	{ -1, 4, -1 },
	{ 0, -1, 0 } };

	float laplacian2[3][3] = { { -1, -1, -1 },
	{ -1, 8, -1 },
	{ -1, -1, -1 } };

	int n = 3;
	
	for (int y = n / 2; y < src1.rows - n; y++) {
		for (int x = n / 2; x < src1.cols - n; x++) {
			int sum = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					sum += src1.at<uchar>(y + (i - n / 2), x + (j - 3 / 2)) * laplacian1[i][j];
					lap_img.at<uchar>(y, x) = saturate_cast<uchar>(sum);
					sharpen_img.at<uchar>(y, x) = saturate_cast<uchar>(src1.at<uchar>(y, x) + sum);
				}
			}
			
		}
	}

	namedWindow("Lab 3 - 5 / Original", 1);
	imshow("Lab 3 - 5 / Original", src1);

	namedWindow("Lab 3 - 5 / Laplacian", 1);
	imshow("Lab 3 - 5 / Laplacian", lap_img);

	namedWindow("Lab 3 - 5 / Enhanced", 1);
	imshow("Lab 3 - 5 / Enhanced", sharpen_img);

	waitKey(0);
	return 0;
}