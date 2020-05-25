#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
	Mat src1 = imread("lena_noise.png");
	Mat dst = Mat::zeros(src1.size(), src1.type());

	if (!src1.data) {
		printf("Error loading src1 \n");
		return -1;
	}

	int n;
	cout << "Type kernel value : ";
	cin >> n;
	int num_pow = pow(n, 2);
	int *arr = new int[num_pow];
	
	for (int y = n / 2; y < src1.rows - n / 2; y++) {
		for (int x = n / 2; x < src1.cols - n / 2; x++) {
			for (int c = 0; c < 3; c++) {
				int cnt = 0;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						arr[cnt] = src1.at<Vec3b>(y + (i - n / 2), x + (j - n / 2))[c];
						cnt++;
					}
				}
				sort(arr, arr + num_pow);
				dst.at<Vec3b>(y, x)[c] = arr[num_pow / 2];
			}
		}
	}

	namedWindow("Lab 3 - 3 / Original", 1);
	imshow("Lab 3 - 3 / Original", src1);

	namedWindow("Lab 3 - 3 / Median", 1);
	imshow("Lab 3 - 3 / Median", dst);

	waitKey(0);
	return 0;
}