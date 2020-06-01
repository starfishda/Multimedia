#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
	Mat src1 = imread("snpe.jpg", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src1.size(), src1.type());

	if (!src1.data) {
		printf("Error loading src1 \n");
		return -1;
	}

	float gx[3][3] = { { 1, 0, -1 },
	{ 2, 0, -2 },
	{ 1, 0, -1 } };

	float gy[3][3] = { { 1, 2, 1 },
	{ 0,  0,  0 },
	{ -1,  -2,  -1 } };

	int n = 3;
	
	for (int y = 3 / 2; y < src1.rows - 3; y++) {
		for (int x = 3 / 2; x < src1.cols - 3; x++) {
			int sum = 0, sum2 = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					sum += src1.at<uchar>(y + (i - n / 2), x + (j - 3 / 2)) * gx[i][j];
					sum2 += src1.at<uchar>(y + (i - n / 2), x + (j - 3 / 2)) * gy[i][j];
					dst.at<uchar>(y, x) = sqrt(sum * sum + sum2 * sum2);
				}
			}
		}
	}

	namedWindow("Lab 3 - 4", 1);
	imshow("Lab 3 - 4", dst);

	waitKey(0);
	return 0;
}