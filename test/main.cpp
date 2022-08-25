#include <iostream>
#include <opencv2/opencv.hpp>

// my own code
#include "feature_extraction.hpp"
#include "camera_calibration.hpp"

int main() {

    cv::Mat raw_img_left = cv::imread("../../test_3_left/09.png");
    cv::Mat raw_img_right = cv::imread("../../test_3_right/09.png");

    // Reading calibration matrix.
    // cv::Mat R1, R2, P1, P2, Q, R;
    // cv::Vec3d T;

    // std::cout << "Read camera right matrix" << std::endl;
    // cv::FileStorage fs0("../../calibration/camera_left.xml", cv::FileStorage::READ);
    // cv::Mat cameraMatrixRight;
    // cv::Mat distortionCoefficientsRight;
    // fs0["intrinsic"] >> cameraMatrixRight;
    // fs0["distortion"] >> distortionCoefficientsRight;
    // fs0.release();

    // std::cout << "Read camera left matrix" << std::endl;
    // cv::FileStorage fs1("../../calibration/camera_right.xml", cv::FileStorage::READ);
    // cv::Mat cameraMatrixLeft;
    // cv::Mat distortionCoefficientsLeft;
    // fs1["intrinsic"] >> cameraMatrixLeft;
    // fs1["distortion"] >> distortionCoefficientsLeft;
    // fs1.release();

    // std::cout << "Read stereo calibration matrix" << std::endl;
    // cv::FileStorage fs2("../../calibration/stereoCalibration0812.xml", cv::FileStorage::READ);
    // fs2["R"] >> R;
    // fs2["T"] >> T;
    // fs2["R1"] >> R1;
    // fs2["R2"] >> R2;
    // fs2["P1"] >> P1;
    // fs2["P2"] >> P2;
    // fs2["Q"] >> Q;

    // Calling Camera calibration matrix.
    std::string camera_calib_matrix_left = "../../calibration/camera_left.xml";
    std::string camera_calib_matrix_right = "../../calibration/camera_right.xml";
    std::string stereo_calib_matrix = "../../calibration/stereoCalibration0812.xml";
    CameraCalibration camera_matrix(camera_calib_matrix_left, camera_calib_matrix_right, stereo_calib_matrix);

    cv::Mat R1, R2, P1, P2, Q, R;
    cv::Vec3d T;
    cv::Mat cameraMatrixRight;
    cv::Mat distortionCoefficientsRight;
    cv::Mat cameraMatrixLeft;
    cv::Mat distortionCoefficientsLeft;

    std::tie(R1, R2, P1, P2, Q, R, cameraMatrixRight, distortionCoefficientsRight, cameraMatrixLeft, distortionCoefficientsLeft, T) = camera_matrix.GetCalibMatrix();

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

    ob1.ImgShow();

    ob1.ImgROI();
    ob1.ImgRedExtraction();
    ob1.ImgMedianBlur();
    ob1.ImgGrayScale();
    ob1.ImgThreshold();
    ob1.ImgContours();

    ob1.ImgShow();

    // right
    FeatureExtraction ob2(imgU2);

    ob2.ImgShow();

    ob2.ImgROI();
    ob2.ImgRedExtraction();
    ob2.ImgMedianBlur();
    ob2.ImgGrayScale();
    ob2.ImgThreshold();
    ob2.ImgContours();

    ob2.ImgShow();

    int x1 = ob1.GetMoments();
    int x2 = ob2.GetMoments(); 
    int disparity = x1 - x2;

    std::cout << "Left x : " << x1 << std::endl;
    std::cout << "Right x : " << x2 << std::endl;
    std::cout << "Disparity : " << disparity << std::endl;

    return 0;
}
