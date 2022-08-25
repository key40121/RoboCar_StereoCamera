#ifndef   CAMERA_CALIBRATION
#define   CAMERA_CALIBRATION

#include <string>
#include <tuple>
#include <opencv2/opencv.hpp>

class CameraCalibration {
    // Private member.
    cv::Mat R1, R2, P1, P2, Q, R;
    cv::Vec3d T;

    cv::Mat cameraMatrixRight;
    cv::Mat distortionCoefficientsRight;

    cv::Mat cameraMatrixLeft;
    cv::Mat distortionCoefficientsLeft;

public:
    CameraCalibration(std::string camera_calib_matrix_left, std::string camera_calib_matrix_right, std::string stereo_calib_matrix);
    ~CameraCalibration();
    std::tuple<cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Mat, cv::Vec3d> GetCalibMatrix();
};


#endif 