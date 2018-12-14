#include <iostream>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "tictoc.h"
#include "cvmodified.h"

// flag to determine which GFTT to use
constexpr bool useModifiedCV = true;

// EuRoC MH_01_easy image from cam0
constexpr char imgFile[] = "../res/1403636641013555456.png";

int main(int argc, char const *argv[])
{
  cv::Mat img = cv::imread(imgFile, cv::IMREAD_COLOR);

  /// GFTT Parameters
  constexpr int maxCorners = 500;
  constexpr double qualityLevel = 0.001;
  constexpr double minDist = 30;

  // convert to greyscale for GFTT
  cv::Mat grey;
  cv::cvtColor(img, grey, cv::COLOR_BGR2GRAY);

  std::vector<cv::Point2f> corners;
  std::vector<float> scores;
  
  TicToc t_detect;
  if (useModifiedCV) {
    cvmodified::goodFeaturesToTrack(grey, corners, scores, maxCorners, qualityLevel, minDist);
  } else {
    cv::goodFeaturesToTrack(grey, corners, maxCorners, qualityLevel, minDist);

    // we don't have score info
    scores.resize(corners.size(), 1.0);
  }

  std::cout << "Detected " << corners.size() << " features in " << t_detect.toc() << " ms." << std::endl;

  //
  // Score statistics
  // 

  float maxScore = *std::max_element(scores.begin(), scores.end());
  float minScore = *std::min_element(scores.begin(), scores.end());
  std::cout << "Feature score range: [" << minScore << ", " << maxScore << "]" << std::endl;

  // the score normalizer
  int n = 0;

  while(1) {

    cv::Mat draw = img.clone();

    // get nth element to be used as normalizer
    auto s = scores;
    std::nth_element(s.begin(), s.begin()+n, s.end(), std::greater<float>());
    float eta = s[n];
    std::cout << n+1 << "-th greatest score: " << eta << std::endl;

    // draw features
    for (size_t i=0; i<corners.size(); ++i) {
      // convenience
      auto pt = corners[i];
      float score = std::min(1.0f, static_cast<float>(scores[i] / eta));

      // color alpha mixing
      auto color = cv::Scalar(0, 255*score, 255*(1 - score));
      cv::circle(draw, pt, 2, color, 2);

      // print normalized score next to feature
      // char strScore[10];
      // snprintf(strScore, sizeof(strScore), "%0.2f", score);
      // cv::putText(draw, strScore, pt, cv::FONT_HERSHEY_SIMPLEX, 0.3, cv::Scalar(200, 0, 0));
    }

    cv::imshow("Detections", draw);
    char key = static_cast<char>(cv::waitKey(0));

    if (key == '+' && n<corners.size()) n++;
    if (key == '-' && n>0) n--;

    if (key == static_cast<char>(27)) break; // esc
  }
}