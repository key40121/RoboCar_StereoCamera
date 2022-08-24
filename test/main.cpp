#include <iostream>
#include <opencv2/opencv.hpp>

class FeatureExtraction {
    // private member
    cv::Mat img;
public:
    FeatureExtraction(cv::Mat raw_img); //constructor
    ~FeatureExtraction(); //Destructor
    
    //void ImgStereoTransformation();
    // 
    void ImgShow();
    
    // 
    void ImgRedExtraction();

    // 
    void ImgMedianBlur();

    // 
    void ImgGrayScale();

    // 
    void ImgThreshold();

    // 
    void ImgContours();

    //
    int GetMoments();
};

FeatureExtraction::FeatureExtraction(cv::Mat raw_img)
{
    std::cout << "Calling constrctor" << std::endl;
    img = raw_img;
}

FeatureExtraction::~FeatureExtraction()
{
    std::cout << "Calling destructor" << std::endl;
}

// Transformation for stereo camera depth caliculation.
// Need to prepare calibration matrix in advance.
// void FeatureExtraction::ImgStereoTransformation(cv::Mat R1, cv::Mat R2, cv::Mat P1, cv::Mat P2, cv::Mat Q, cv::Mat R)
// {
    

// }

void FeatureExtraction::ImgShow()
{
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example", img);
    cv::waitKey(0);
    cv::destroyWindow("Example");
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

void FeatureExtraction::ImgMedianBlur()
{
    int ksize = 7;
    cv::medianBlur(img, img, ksize);
}

void FeatureExtraction::ImgGrayScale()
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

void FeatureExtraction::ImgThreshold()
{
    cv::threshold(img, img, 50, 100, cv::THRESH_BINARY);
}

void FeatureExtraction::ImgContours()
{
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE );

    cv::Mat drawing = cv::Mat::zeros(img.size(), CV_8UC3);

    cv::drawContours(drawing, contours, -1, 195, 2);

    img = drawing;
}

int FeatureExtraction::GetMoments()
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    cv::Moments m = cv::moments(img, false);
    cv::Point p(m.m10 / m.m00, m.m01 / m.m00);

    int x = m.m10 / m.m00;

    // std::cout << m.m10 / m.m00 << std::endl;

    return x;
}

int main() {

    cv::Mat raw_img_left = cv::imread("../test_3_left/00.png");
    cv::Mat raw_img_right = cv::imread("../test_3_right/00.png");

    // Reading calibration matrix.
    cv::Mat R1, R2, P1, P2, Q, R;
    cv::Vec3d T;

    std::cout << "Read camera right matrix" << std::endl;
    cv::FileStorage fs0("../calibration/camera_left.xml", cv::FileStorage::READ);
    cv::Mat cameraMatrixRight;
    cv::Mat distortionCoefficientsRight;
    fs0["intrinsic"] >> cameraMatrixRight;
    fs0["distortion"] >> distortionCoefficientsRight;
    fs0.release();

    std::cout << "Read camera left matrix" << std::endl;
    cv::FileStorage fs1("../calibration/camera_right.xml", cv::FileStorage::READ);
    cv::Mat cameraMatrixLeft;
    cv::Mat distortionCoefficientsLeft;
    fs1["intrinsic"] >> cameraMatrixLeft;
    fs1["distortion"] >> distortionCoefficientsLeft;
    fs1.release();

    std::cout << "Read stereo calibration matrix" << std::endl;
    cv::FileStorage fs2("../calibration/stereoCalibration0812.xml", cv::FileStorage::READ);
    fs2["R"] >> R;
    fs2["T"] >> T;
    fs2["R1"] >> R1;
    fs2["R2"] >> R2;
    fs2["P1"] >> P1;
    fs2["P2"] >> P2;
    fs2["Q"] >> Q;

    cv::Mat lmapx, lmapy, rmapx, rmapy;
    cv::Mat imgU1, imgU2;

    cv::initUndistortRectifyMap(cameraMatrixLeft, distortionCoefficientsLeft, R1, P1, raw_img_left.size(), CV_32F, lmapx, lmapy);
    cv::initUndistortRectifyMap(cameraMatrixRight, distortionCoefficientsRight, R2, P2, raw_img_right.size(), CV_32F, rmapx, rmapy);
    cv::remap(raw_img_left, imgU1, lmapx, lmapy, cv::INTER_LINEAR);
    cv::remap(raw_img_right, imgU2, rmapx, rmapy, cv::INTER_LINEAR);


    // check that the image has been opened.
    if (!raw_img_left.data)
    {
        std::cout << "Error to read the image." << std::endl;
        return -1;
    }

    // left
    FeatureExtraction ob1(imgU1);
    ob1.ImgRedExtraction();
    ob1.ImgMedianBlur();
    ob1.ImgGrayScale();
    ob1.ImgThreshold();
    ob1.ImgContours();

    ob1.ImgShow();

    // right
    FeatureExtraction ob2(imgU2);
    ob2.ImgRedExtraction();
    ob2.ImgMedianBlur();
    ob2.ImgGrayScale();
    ob2.ImgThreshold();
    ob2.ImgContours();

    ob2.ImgShow();

    std::cout << "Left x : " << ob1.GetMoments() << std::endl;
    std::cout << "Right x : " << ob2.GetMoments() << std::endl;
    std::cout << "Disparity : " << std::abs(ob1.GetMoments() - ob2.GetMoments()) << std::endl;

    return 0;
}
