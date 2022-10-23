#include "opencv2/opencv.hpp"

#include "opencv2/highgui.hpp"

#include "opencv2/core.hpp"



using namespace cv;
using namespace std;



void insertionSort(int arr[], int n)

{

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

	Mat image = imread(argv[1], IMREAD_GRAYSCALE);
	if (!image.data) {
		cout << "Could not find the image! " << endl;
		return -1;
	}




	

	int meanKernel = atoi(argv[2]);
	int margin = meanKernel / 2;

	Mat meanImg = image.clone();
	int sum;
	double avg;

	for (int i = margin; i < image.rows - margin; i++) {
		for (int j = margin; j < image.cols - margin; j++) {
			sum = 0; 
			for (int g = i - margin; g <= i + margin; g++) {
				for (int h = j - margin; h <= j + margin; h++) {
					sum = sum + (int)image.at<uchar>(g, h);
				}
			}
			avg = sum / (meanKernel * meanKernel);
			meanImg.at<uchar>(i, j) = (uchar)avg;
		}
	}


	Mat medianImg = image.clone();
    int index;
	int middle;
	int size = meanKernel * meanKernel;
	int* arr = new int[size];

	for (int i = margin; i < image.rows - margin; i++) {
		for (int j = margin; j < image.cols - margin; j++) {
			index = 0;
			for (int g = i - margin; g <= i + margin; g++) {
				for (int h = j - margin; h <= j + margin; h++) {
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
