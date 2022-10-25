#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace cv;
using namespace std;

Mat drawHistogram(int* histogram) {

    int histogram_height = 400;
    int histogram_width = 512; //use any value you wish
    int bin_w = cvRound((double)histogram_width / 256);


    //Draw the histogram for B,G and R
    Mat histImage(histogram_height, histogram_width, CV_8UC1, Scalar(255, 255, 255)); //create a window to draw the histogram

    //Find the maximum number of pixels from histogram array
    int max = histogram[0];
    for (int i = 1; i < 256; i++) {
        if (max < histogram[i]) {
            max = histogram[i];
        }
    }

    //Normalize the histogram between 0 and histogram height
    for (int i = 0; i < 256; i++) {
        histogram[i] = ((double)histogram[i] / max) * histogram_height;
        cout << histogram[i] << endl;
    }

    //Draw the lines of histogram
    for (int i = 0; i < 256; i++) {
        //line ( histImage, Point pt1, Point pt2,color , thickness, lineType, shift)
        line(histImage, Point(bin_w * (i), histogram_height), Point(bin_w * (i), histogram_height - histogram[i]), Scalar(0, 0, 0), 1, 8, 0);
    }
    return histImage;
}

int main(int argc, char* argv[]) {
    //Mat image = imread(argv[1], IMREAD_GRAYSCALE);
    Mat image = imread(argv[1]); //get image from command line, if 0 - exe file, if 1 - image name

    if (!image.data) {
        cout << "couldn't find the image!" << endl; //endl in use to print new line in mat
        return -1;
    }


    Mat gray(image.rows, image.cols, CV_8UC1, Scalar(0)); //CV_8UC1 - because gray scale, 1 scale image
    //convert BGR image to gray using opencv function, without using loops
    cvtColor(image, gray, COLOR_BGR2GRAY); //1st param - input image, 2nd - output image, 3rd - conversion method

    //dclare arrays
    int histogram[256];
    double prob[256];
    double cprob[256];
    int cNew[256];
    int equalizedHist[256];

    //initialize array elements
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
        prob[i] = 0.0;
        cprob[i] = 0.0;
        cNew[i] = 0;
        equalizedHist[i] = 0;
    }

    //number of pixels for each value in original image
    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            histogram[(int)gray.at<uchar>(y, x)]++; //find how many no.of pixels for each intensity currently
        }
    }

    //Print number of pixels for each intensity value
    for (int i = 0; i < 256; i++)
        cout << i << ":" << histogram[i] << endl;

    //total number of pixels
    int N = gray.rows * gray.cols;
    printf("Total number of pixels: %d", N);

    // Calculate the probability of each intensity
    for (int i = 0; i < 256; i++) {
        prob[i] = (double)histogram[i] / N;
    }

    //Generate cumulative probability
    cprob[0] = prob[0];
    for (int i = 1; i < 256; i++) {
        cprob[i] = cprob[i - 1] + prob[i];
    }
    //Print cumulative probability for each intensity value
    for (int i = 0; i < 256; i++)
        cout << i << ":" << cprob[i] << endl;

    //Scale cumulative probability
    for (int i = 0; i < 256; i++)
        cNew[i] = round(cprob[i] * 255);

    // Generate the equalized image
    int z = 0;
    Mat output = gray.clone(); //take the copy of gray image
    for (int i = 0; i < gray.rows; i++) {
        for (int j = 0; j < gray.cols; j++) {
            z = cNew[(int)gray.at<uchar>(i, j)];//intensity values of gray image put in to scaled array
            output.at<uchar>(i, j) = (uchar)z;
        }
    }

    //histogram drawing for original image
    Mat histImage = drawHistogram(histogram);

    //number of pixels for each value in equalized image
    for (int y = 0; y < output.rows; y++) {
        for (int x = 0; x < output.cols; x++) {
            equalizedHist[(int)output.at<uchar>(y, x)]++;
        }
    }
    //histogram drawing for equalized image
    Mat equalizedHistImage = drawHistogram(equalizedHist);
    namedWindow("Gray"); //give a name to window
    imshow("Gray", gray); //show the image on window
    namedWindow("Output"); //give a name to window
    imshow("Output", output); //show the image on window
    namedWindow("Histogram"); //give a name to window
    imshow("Histogram", histImage); //show the image on window
    namedWindow("Equalized_Histogram"); //give a name to window
    imshow("Equalized_Histogram", equalizedHistImage); //show the image on window
    waitKey(0);

    return 0;
}
