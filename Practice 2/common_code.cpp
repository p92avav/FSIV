// FSIV

#include "common_code.hpp"

void fsiv_add_safe(const cv::Mat& src, cv::Mat& dst, int val)
{
    CV_Assert(!src.empty());
    CV_Assert(src.rows == dst.rows && src.cols == dst.cols);

    //TODO
    //
}

// TO DO: define all the extra functions that you might need
