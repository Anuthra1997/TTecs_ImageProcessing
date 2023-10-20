#include <opencv2/opencv.hpp>

int main() {
    // Load an image
    cv::Mat inputImage = cv::imread("input.jpg");

    if (inputImage.empty()) {
        std::cerr << "Error: Could not open or find the image." << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    cv::Mat grayscaleImage;
    cv::cvtColor(inputImage, grayscaleImage, cv::COLOR_BGR2GRAY);

    // Save the processed image
    cv::imwrite("output.jpg", grayscaleImage);

    return 0;
}
