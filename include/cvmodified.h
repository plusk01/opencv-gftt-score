#pragma once

#include <opencv2/core.hpp>
// #include <opencv2/imgproc.hpp>
// #include <opencv2/features2d.hpp>

namespace cvmodified {

  void goodFeaturesToTrack(cv::InputArray image, cv::OutputArray corners,
        int maxCorners, double qualityLevel, double minDistance,
        cv::InputArray mask=cv::noArray(), int blockSize=3,
        bool useHarrisDetector=false, double k=0.04);

  void goodFeaturesToTrack(cv::InputArray image, cv::OutputArray corners,
        int maxCorners, double qualityLevel, double minDistance,
        cv::InputArray mask, int blockSize,
        int gradientSize,
        bool useHarrisDetector=false, double k=0.04);

}
