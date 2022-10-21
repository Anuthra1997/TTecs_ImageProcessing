#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	Mat image = imread(argv[1]); //get image from command line, if 0 - exe file, if 1 - image name
	 
	if (!image.data) {
		cout << "couldn't find the image!" << endl; //endl in use to print new line in mat
		return -1;
	}

	int height = image.rows;
	int width = image.cols;
	int ws = image.step;
	int nCh = image.channels();

	printf("height : % d\n", height);
	printf("width : % d\n", width);
	printf("width step : % d\n", ws);
	printf("number of channels : % d\n", nCh);

	//to access each and every pixel of the image - 3 channel image
	print(image.at<Vec3b>(0, 0));

	//print the BGR values
	cout << image.at<Vec3b>(0, 0) << endl;

	int b = image.at<Vec3b>(0, 0)[0];
	int g = image.at<Vec3b>(0, 0)[1];
	int r = image.at<Vec3b>(0, 0)[2];
	printf("Blue : % d\n", b);
	printf("Green : % d\n", g);
	printf("Red : % d\n", r);



	for (int i = 0; i <= 100; i++) {
		for (int j = 0;j <= 100; j++) {
			image.at<Vec3b>(i, j)[0] = 0; //set blue to black
			image.at<Vec3b>(i, j)[1] = 0;
			image.at<Vec3b>(i, j)[2] = 0;
		}
	}

	//Convert BGR image to grayscale image(1 channel image). for 3 channel image - use vec3b, for 1 channel image - use uchar
	Mat imageGray;
	imageGray.create(height, width, CV_8UC1); //create image in Mat structure

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//Gray = 0.1140 * Blue + 0.5870 * Green +0.2989 * Red
			imageGray.at<uchar>(i, j) = 0.1140 * image.at<Vec3b>(i, j)[0] + 0.5870 * image.at<Vec3b>(i, j)[1] + 0.2989 * image.at<Vec3b>(i, j)[2];
		}
	}


	namedWindow("Image"); //give a name to window
	imshow("Image", image); //show the image on window
	namedWindow("Gray"); //give a name to window
	imshow("Gray", imageGray); //show the image on window
	waitKey(0);

	return 0;
}