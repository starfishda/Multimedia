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

	image = imread(imageName.c_str(), IMREAD_COLOR);

	if (image.empty()) {
		cout << "이미지를 열수 없음" << std::endl;
		return -1;
	}

	namedWindow("BTS", WINDOW_AUTOSIZE);
	imshow("BTS", image);
	waitKey(0);
		
	return 0;
}