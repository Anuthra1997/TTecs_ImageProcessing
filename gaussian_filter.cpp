#include <iostream>
#include <stdio.h>
#include<cmath>
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char*argv[]) {
Mat img = imread("C:/Users/Udakara/Documents/Visual Studio 2015/Projects/Asg2/x64/Debug/450.png");
if (!img.data) {
cout << "Could not load image" << endl;
waitKey(0);
return -1;
}
//Gray image and initialization
Mat gr;
int his[256];
int his2[256];

for (int i = 0; i < 256; i++) {
his[i] = 0;
his2[i] = 0;
}
//Gray conversion
cvtColor(img, gr, CV_BGR2GRAY);

int h = gr.rows;
int w = gr.cols;
int val = 0;
int max = 0;

for (int i = 0; i < h; i++) {
for (int j = 0; j < w; j++) {
val = gr.at<uchar>(i, j);
his[val]++;
}
}
for (int i = 0; i < 256; i++) {
if (max < his[i]) {
max = his[i];
}
}

//Histogram for Original Image
Mat him(301, 260, CV_8UC1, Scalar(255));
int hist[256];
double maxd = max;
for (int i = 0; i < 256; i++) {
hist[i] = cvRound(double(his[i] / maxd) * 300);
Point pt1 = Point(i, 300 - hist[i]);
Point pt2 = Point(i, 300);
line(him, pt1, pt2, Scalar(0), 1, 8, 0);
}

//Gaussian Filter
Mat Gaus = gr.clone();
int kernel = 5;
// intialising standard deviation to 1.0 
double sigma = 1.0;
double r = 2.0*sigma*sigma;
double s = 2.0*sigma*sigma;

// sum is for normalization 
double sum = 0.0;
double GKernel[5][5];

// generating 5x5 kernel 
for (int x = -2; x <= 2; x++) {
for (int y = -2; y <= 2; y++) {
r = sqrt(x * x + y * y);
GKernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (3.14 * s);
sum += GKernel[x + 2][y + 2];
}
}

// normalising the Kernel 
for (int i = 0; i < 5; ++i)
for (int j = 0; j < 5; ++j)
GKernel[i][j] /= sum;


for (int i = 0; i < 5; ++i) {
for (int j = 0; j < 5; ++j)
cout << GKernel[i][j] << "\t";
cout << endl;
}


for (int i = kernel / 2; i < h - (kernel / 2); i++) {
for (int j = kernel / 2; j < w - (kernel / 2); j++) {
int sum = 0;
for (int m = -kernel / 2; m <= kernel / 2; m++) {
for (int n = -kernel / 2; n <= kernel / 2; n++) {
int a= gr.at<uchar>(i + m, j + n);
double p = GKernel[2 + m][ 2 + n];
sum = sum + (p*a);
}
}

Gaus.at<uchar>(i, j) = (uchar)sum;
}
}


for (int i = 0; i < h; i++) {
for (int j = 0; j < w; j++) {
val = Gaus.at<uchar>(i, j);
his2[val] = his2[val] + 1;
}
}
int max2 = 0;
for (int i = 0; i < 256; i++) {
//cout << "Gray Level  " << i << " : " << his2[i] << endl;
if (max2 < his2[i]) {
max2 = his2[i];
}
}

Mat him2(301, 260, CV_8UC1, Scalar(255));
int hist2[256];
double maxd2 = max2;
for (int i = 0; i <= 255; i++) {
hist2[i] = cvRound(double(his2[i] / maxd2) * 300);
Point pt1 = Point(i, 300 - hist2[i]);
Point pt2 = Point(i, 300);
line(him2, pt1, pt2, Scalar(0), 1, 8, 0);
}

imshow("Image:", gr);
imshow("Histograam:", him);
imshow("Gausssian Smoothed", Gaus);
imshow("New Histogram:", him2);

cvWaitKey(0);


return 0;

}