#ifndef   FEATURE_EXTRACTION
#define   FEATURE_EXTRACTION

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


class FeatureExtraction {
    // private member
    cv::Mat img;
public:
    FeatureExtraction(cv::Mat raw_img); //constructor
    ~FeatureExtraction(); //Destructor
    
    //void ImgStereoTransformation();
    // 
    void ImgShow();
    
    // Extract a region of interest.
    void ImgROI();

    // Extract red color by using HSV space.
    void ImgRedExtraction();

    // 
    void ImgMedianBlur();

    // 
    void ImgGrayScale();

    // Image thresholding.
    void ImgThreshold();

    // Image contours.
    void ImgContours();

    // Extract (x, y) corrdinates.
    int GetMoments();
};


#endif 