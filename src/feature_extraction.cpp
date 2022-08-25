#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

#include "feature_extraction.hpp"

// Constructor.
FeatureExtraction::FeatureExtraction(cv::Mat raw_img)
{
    std::cout << "Calling constrctor" << std::endl;
    img = raw_img;
}

// Destructor.
FeatureExtraction::~FeatureExtraction()
{
    std::cout << "Calling destructor" << std::endl;
}


// Display an image.
void FeatureExtraction::ImgShow()
{
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example", img);
    cv::waitKey(0);
    cv::destroyWindow("Example");
}

void FeatureExtraction::ImgROI()
{
    cv::rectangle(img, cv::Point(0, 0), cv::Point(640, 200), cv::Scalar(255, 255, 255), -1, CV_AVX);
    cv::rectangle(img, cv::Point(0, 400), cv::Point(640, 480), cv::Scalar(255, 255, 255), -1, CV_AVX);
}

// Extract Red color.
void FeatureExtraction::ImgRedExtraction()
{
    cv::Mat hsv;
    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

    cv::Mat mask_1;
    cv::Mat mask_2;
    
    int low_H_1 = 0;
    int low_S_1 = 64;
    int low_V_1 = 0;

    int high_H_1 = 10;
    int high_S_1 = 255;
    int high_V_1 = 255;

    int low_H_2 = 160;
    int low_S_2 = 64;
    int low_V_2 = 0;

    int high_H_2 = 179;
    int high_S_2 = 255;
    int high_V_2 = 255;

    cv::inRange(hsv, cv::Scalar(low_H_1, low_S_1, low_V_1), cv::Scalar(high_H_1, high_S_1, high_V_1), mask_1);
    cv::inRange(hsv, cv::Scalar(low_H_2, low_S_2, low_V_2), cv::Scalar(high_H_2, high_S_2, high_V_2), mask_2);

    cv::Mat mask = mask_1 | mask_2;

    cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);

    cv::bitwise_and(img, mask, img);

    // img = mask;
}

// Blur manipulation.
void FeatureExtraction::ImgMedianBlur()
{
    int ksize = 7;
    cv::medianBlur(img, img, ksize);
}

// Gray scale.
void FeatureExtraction::ImgGrayScale()
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

// Thresholding.
void FeatureExtraction::ImgThreshold()
{
    cv::threshold(img, img, 50, 100, cv::THRESH_BINARY);
}

// Image contouring.
void FeatureExtraction::ImgContours()
{
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );

    cv::Mat drawing = cv::Mat::zeros(img.size(), CV_8UC3);

    cv::drawContours(drawing, contours, -1, 195, 2);

    img = drawing;
}

// Get memonts.
int FeatureExtraction::GetMoments()
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    cv::Moments m = cv::moments(img, false);
    cv::Point p(m.m10 / m.m00, m.m01 / m.m00);

    int x = m.m10 / m.m00;

    // std::cout << m.m10 / m.m00 << std::endl;

    return x;
}