#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

int main() {
	Mat src1 = imread("lena_noise.png", IMREAD_GRAYSCALE);
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
	
	for (int y = n / 2; y < src1.rows - n; y++) {
		for (int x = n / 2; x < src1.cols - n; x++) {
			int cnt = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					arr[cnt] = src1.at<uchar>(y + (i - n / 2), x + (j - n / 2));
					cnt++;
				}
			}
			sort(arr, arr + num_pow);
			dst.at<uchar>(y, x) = arr[num_pow / 2];
		}
	}

	namedWindow("Lab 3 - 3 / Original", 1);
	imshow("Lab 3 - 3 / Original", src1);

	namedWindow("Lab 3 - 3 / Median", 1);
	imshow("Lab 3 - 3 / Median", dst);

	waitKey(0);
	return 0;
}