#pragma once

#include <opencv2/core.hpp>

namespace cvmodified {

  void goodFeaturesToTrack(cv::InputArray image, cv::OutputArray corners,
        cv::OutputArray scores,
        int maxCorners, double qualityLevel, double minDistance,
        cv::InputArray mask=cv::noArray(), int blockSize=3,
        bool useHarrisDetector=false, double k=0.04);

  void goodFeaturesToTrack(cv::InputArray image, cv::OutputArray corners,
        cv::OutputArray scores,
        int maxCorners, double qualityLevel, double minDistance,
        cv::InputArray mask, int blockSize,
        int gradientSize,
        bool useHarrisDetector=false, double k=0.04);

}
