//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
//#include<opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	string imageName("snpe.jpg");
	Mat image;
	double alpha;
	int beta;
	cin >> alpha >> beta;

	image = imread(imageName.c_str(), IMREAD_COLOR);

	if (image.empty()) {
		cout << "이미지를 열수 없음" << std::endl;
		return -1;
	}
	
	//Mat image_change;
	/*float a = 2.2, b = 50;
	image = a * image + b;*/ //이미지 조도 변경
	
	int height = image.rows; // 가로 픽셀의 수
	int width = image.cols; // 세로 픽셀의 수
	Mat img_change(image.size(), image.type()); // 가로 세로 크기, 화면 비율

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				img_change.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * (image.at<Vec3b>(y, x)[c]) + beta);
			}
		}
	}

	/*Mat img_gray;
	cvtColor(image, img_gray, COLOR_BGR2GRAY);*/ //흑백변환

	namedWindow("BTS", WINDOW_AUTOSIZE);
	namedWindow("BTS_change", WINDOW_AUTOSIZE);
	imshow("BTS", image);
	imshow("BTS_change", img_change);
	waitKey(0);
		
	return 0;
}