#include "cv.h" //main opencv header   
#include "highgui.h" //Gui header
int main(int argc, char* argv[]) {
	IplImage* img;
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR); //load image from user input

	if (!img)
		printf("Couldn't load the image file %s\n", argv[1]);

	int height = img->height;
	int width = img->width;
	int nCh = img->nChannels; //number of channels
	int ws = img->widthStep; //how many array elemnets are to be jumped from one row to another
	printf("Height: %d\n", height);
	printf("Width: %d\n", width);
	printf("Number of channels: %d\n", nCh);
	printf("WidthStep: %d\n", ws);

	uchar* data = (uchar*) img->imageData;
	printf("1st pixel blue: %d\n", data[0]);
	printf("1st pixel green: %d\n", data[1]);
	printf("1st pixel red: %d\n", data[2]);

	int i = 100; //row number
	int j = 100; //column number
	printf("100th pixel blue: %d\n", data[i * ws + j * nCh]);
	printf("100th pixel gree: %d\n", data[i * ws + j * nCh + 1]);
	printf("100th pixel red: %d\n", data[i * ws + j * nCh + 2]);

	//change the 100 x 100 pixel area of the image to black color
	//for (int i = 0; i < 100; i++) {
	//	for (int j = 0; j < 100; j++) {
	//		data[i * ws + j * nCh] = 0;
	//		data[i * ws + j * nCh + 1] = 0;
	//		data[i * ws + j * nCh + 2] = 0;
	//	}
	//}

	//Convert BGR image to blank image
	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {
	//		data[i * ws + j * nCh] = 0;
	//		data[i * ws + j * nCh + 1] = 0;
	//		data[i * ws + j * nCh + 2] = 0;
	//	}
	//}




	// Convert BGR image to grayscale image.
	IplImage* gray = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1); //1 says it's a 1 channel image, not 2d
	uchar* dataGray = (uchar*)gray->imageData;
	int wsGray = gray->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			//Gray = 0.1140 * Blue + 0.5870 * Green +0.2989 * Red
			dataGray[i * wsGray + j * 1] = 0.1140 * data[i * ws + j * nCh] + 0.5870 * data[i * ws + j * nCh + 1] + 0.2989 * data[i * ws + j * nCh + 2];
		}
	}



	//Convert grayscale image to black and white (binary) image
	IplImage* binary = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1); //1 says it's a 1 channel image, not 2d
	uchar* dataBinary = (uchar*)binary->imageData;
	int wsBinary = binary->widthStep;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (dataGray[i * wsGray + j * 1] > 150) //in gray scale if the pixel is above 150 assign white else assign black. instead 0f 150 you can have any threashold value
				dataBinary[i * wsBinary + j * 1] = 255;
			else
				dataBinary[i * wsBinary + j * 1] = 0;			
		}
	}


	//Convert BGR image into negative image (Invert BGR)
	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {
	//		data[i * ws + j * nCh] =  255 - data[i * ws + j * nCh];
	//		data[i * ws + j * nCh + 1] = 255 - data[i * ws + j * nCh + 1];
	//		data[i * ws + j * nCh + 2] = 255 - data[i * ws + j * nCh + 2];
	//	}
	//}

	//Split BGR image into 3 channels. (Blue, Green, Red)

	//let's create blue channel image
	//IplImage* blue = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {
	//		data[i * ws + j * nCh] =  data[i * ws + j * nCh]; //only keep the blue channel and make other's to 0
	//		data[i * ws + j * nCh + 1] = 0;
	//		data[i * ws + j * nCh + 2] = 0;
	//	}
	//}


	//let's create green channel image
	//IplImage* green = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	//for (int i = 0; i < height; i++) {
	//	for (int j = 0; j < width; j++) {
	//		data[i * ws + j * nCh] = 0; 
	//		data[i * ws + j * nCh + 1] = data[i * ws + j * nCh + 1];
	//		data[i * ws + j * nCh + 2] = 0;
	//	}
	//}


	//let's create red channel image
	IplImage* red = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i * ws + j * nCh] = 0; 
			data[i * ws + j * nCh + 1] = 0;
			data[i * ws + j * nCh + 2] = data[i * ws + j * nCh + 2];
		}
	}


	cvNamedWindow("Image"); //creating window to store the image
	cvShowImage("Image", img); //showing the image on the window

	cvNamedWindow("Gray"); //creating window to store the gray scale image
	cvShowImage("Gray", gray); //showing the image on the window

	cvNamedWindow("Binary"); //creating window to store the binary image
	cvShowImage("Binary", binary); //showing the image on the window

	cvWaitKey(0); //to keep the image until we press any buttons

	cvDestroyWindow("Image"); //destroy the window
	cvReleaseImage(&img); //release image from the window

	cvDestroyWindow("Gray"); //destroy the gray scale image window
	cvReleaseImage(&gray); //release image from the window

	cvDestroyWindow("Binary"); //destroy the gray binary image window
	cvReleaseImage(&binary); //release image from the window


	return 0;
}