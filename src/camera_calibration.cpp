#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

#include "camera_calibration.hpp"

CameraCalibration::CameraCalibration(std::string camera_calib_matrix_left, std::string camera_calib_matrix_right, std::string stereo_calib_matrix)
{
    std::cout << "Read camera right matrix" << std::endl;
    cv::FileStorage fs0(camera_calib_matrix_left, cv::FileStorage::READ);
    cv::Mat cameraMatrixRight;
    cv::Mat distortionCoefficientsRight;
    fs0["intrinsic"] >> cameraMatrixRight;
    fs0["distortion"] >> distortionCoefficientsRight;
    fs0.release();

    this->cameraMatrixRight = cameraMatrixRight;
    this->distortionCoefficientsRight = distortionCoefficientsRight;

    std::cout << "Read camera left matrix" << std::endl;
    cv::FileStorage fs1(camera_calib_matrix_right, cv::FileStorage::READ);
    cv::Mat cameraMatrixLeft;
    cv::Mat distortionCoefficientsLeft;
    fs1["intrinsic"] >> cameraMatrixLeft;
    fs1["distortion"] >> distortionCoefficientsLeft;
    fs1.release();

    this->cameraMatrixLeft = cameraMatrixLeft;
    this->distortionCoefficientsLeft = distortionCoefficientsLeft;


    std::cout << "Read stereo calibration matrix" << std::endl;
    cv::FileStorage fs2(stereo_calib_matrix, cv::FileStorage::READ);
    cv::Mat R1, R2, P1, P2, Q, R;
    cv::Vec3d T;

    fs2["R"] >> R;
    fs2["T"] >> T;
    fs2["R1"] >> R1;
    fs2["R2"] >> R2;
    fs2["P1"] >> P1;
    fs2["P2"] >> P2;
    fs2["Q"] >> Q;

}

CameraCalibration::~CameraCalibration()
{
    std::cout << "Calling Deconstructor." << std::endl;
}

std::tuple<cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Vec3d> CameraCalibration::GetCalibMatrix()
{
    return std::forward_as_tuple(R1, R2, P1, P2, Q, R, cameraMatrixRight, distortionCoefficientsRight, cameraMatrixLeft, distortionCoefficientsLeft, T);
}

