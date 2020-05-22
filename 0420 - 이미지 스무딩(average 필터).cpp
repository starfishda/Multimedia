#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main() {

	Mat src1 = imread("lena_noise.png", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src1.size(), src1.type());

	if (!src1.data) {
		printf("Error loading src1 \n");
		return -1;
	}
	
	int n; // kernel size
	cout << "Type n (kernel size) odd value(1 - 256) : ";
	cin >> n;
	
	double sum = 0;
	double average = 0;
	
	int tmp = n / 2;
	for (int y = tmp; y < src1.rows - tmp - 1; y++) {
		for (int x = n / 2; x < src1.cols - tmp - 1; x++) {
			for (int i = -tmp; i <= tmp; i++) {
				for (int j = -tmp; j <= tmp; j++)
					sum += src1.at<uchar>(y + i, x + j);

			}
			average = sum / (n * n);

			dst.at<uchar>(y, x) = average;

			average = 0;
			sum = 0;
		}
	}

	namedWindow("Lab 3 - 2", 1);
	imshow("Lab 3 - 2", dst);

	waitKey(0);
	return 0;

}