// FSIV

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * @brief Adds a scalar to all pixels in the source image: dst <- src + val
 * @param src input image.
 * @param dst resulting image.
 * @param val value to be added.
 */
void fsiv_add_safe(const cv::Mat& src, cv::Mat & dst, int val);

// TO DO: define all the extra functions that you might need