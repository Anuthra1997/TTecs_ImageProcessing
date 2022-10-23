#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"



using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
	Mat image = imread(argv[1]);

	if (!image.data) {
		cout << "Couldn't open or find the image! " << endl;
		return -1;

	}


	cout << image.at<Vec3b>(0, 0) << endl;


	Mat image2;
	image2.create(h, w, CV_8UC1);

	for (int i = 0; i < h; i++) { //to access rows
		for (int j = 0; j < w; j++) { //to access columns
			image2.at<uchar>(i, j) = 0.1140 * image.at<Vec3b>(i, j)[0] + 0.5870 * image.at<Vec3b>(i, j)[1] + 0.2989 * image.at<Vec3b>(i, j)[2];
		}
	}


	namedWindow("Image");
	imshow("Image", image);

	namedWindow("Gray");
	imshow("Gray", image2);

	waitKey(0);

	return 0;

}
