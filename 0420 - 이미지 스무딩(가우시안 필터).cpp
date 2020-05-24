#include <opencv2/opencv.hpp>
#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip> 
#include <string>
#include<math.h>

using namespace cv;
using namespace std;

int n; // kernel size
double filter[300][300];
double sigma;

void G_filter() {
	double r, s = 2.0 * sigma * sigma;
	double sum = 0.0;

	int tmp = n / 2;
	for(int x = -tmp; x <= tmp; x++) {
		for (int y = -tmp; y <= tmp; y++) {
			r = sqrt(x * x + y * y);
			filter[x + tmp][y + tmp] = (exp(-(r * r) / s)) / (M_PI * s);
			sum += filter[x + tmp][y + tmp];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			filter[i][j] /= sum;
		}
	}
}

int main() {

	Mat src1 = imread("lena_noise.png", IMREAD_GRAYSCALE);
	Mat dst = Mat::zeros(src1.size(), src1.type());

	if (!src1.data) {
		printf("Error loading src1 \n");
		return -1;
	}

	cout << "Type n (kernel size) odd value(1 - 256) : ";
	cin >> n;
	cout << "Type sigma : ";
	cin >> sigma;

	G_filter(); // make filter
	
	double sum = 0;
	double average = 0;
	
	int tmp = n / 2;
	for (int y = tmp; y < src1.rows - tmp - 1; y++) {
		for (int x = n / 2; x < src1.cols - tmp - 1; x++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++)
					dst.at<uchar>(y, x) += src1.at<uchar>(y + i - tmp, x + j - tmp) * filter[i][j];
			}
		}
	}

	namedWindow("HW2", 1);
	imshow("HW2", dst);

	waitKey(0);
	return 0;

}