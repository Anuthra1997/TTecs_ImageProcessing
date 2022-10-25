#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

void insertionSort(int arr[], int n){
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int main(int argc, char* argv[]) {
	//Load a grayscale noisy (salt and pepper) image
	Mat image = imread(argv[1], IMREAD_GRAYSCALE);

	if (!image.data) {
		cout << "couldn't find the image" << endl;
		return -1;
	}

	//MEAN FILTERING

	//Get the copy of the grayscale image
	Mat meanImg = image.clone();

	int k = atoi(argv[2]);
	int adj = k / 2;
	int sum;
	double avg;
	for (int i = adj;i < image.rows - adj;i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			//Sliding the kernel over the image with starting at top left corner
			sum = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					sum = sum + (int)meanImg.at<uchar>(g, h);
				}
			}
			avg = sum / (k * k);
			meanImg.at<uchar>(i, j) = (uchar)avg;
		}
	}

	//MEDIAN FILTERING

	//Get the copy of the grayscale image
	Mat medianImg = image.clone();

	int index;
	int middle;
	int size = k * k;
	int* arr = new int[size];
	for (int i = adj; i < image.rows - adj; i++) {
		for (int j = adj; j < image.cols - adj; j++) {
			index = 0;
			for (int g = i - adj; g <= i + adj; g++) {
				for (int h = j - adj; h <= j + adj; h++) {
					arr[index] = (int)image.at<uchar>(g, h);
					index++;
				}
			}
			insertionSort(arr, size);
			middle = size / 2;
			medianImg.at<uchar>(i, j) = (uchar)arr[middle];
		}
	}

	namedWindow("Image");
	imshow("Image", image);
	namedWindow("Mean Filter");
	imshow("Mean Filter", meanImg);
	namedWindow("Median Filter");
	imshow("Median Filter", medianImg);
	waitKey(0);

	return 0;
}
