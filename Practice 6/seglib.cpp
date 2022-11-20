// ----------------------------------------
// seglib.cpp
// (c) FSIV, University of Cordoba
// ----------------------------------------

#include "seglib.hpp"

using namespace std;
using namespace cv;

void fsiv_remove_segmentation_noise(cv::Mat & img, int r)
{
    CV_Assert(img.type()==CV_8UC1);
    CV_Assert(r>0);
    //TODO
    //Check
      cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(r, r));  //Should be 2*r+1, 2*r+1???
      cv::morphologyEx(img, img, cv::MORPH_CLOSE, element);
      cv::morphologyEx(img, img, cv::MORPH_OPEN, element);
}

void fsiv_segm_by_dif(const cv::Mat & prevFrame, const cv::Mat & curFrame, cv::Mat & difimg, int thr, int r)
{
   CV_Assert(prevFrame.type()==CV_8UC3 && prevFrame.type()==curFrame.type());
   CV_Assert(prevFrame.size()==prevFrame.size());
   // WRITE ME

   // Use absdiff instead of abs?
   difimg = cv::abs(prevFrame - curFrame) > thr; 
   //cv::absdiff(prevFrame, curFrame, difimg);
   fsiv_remove_segmentation_noise(difimg, r);

   CV_Assert(difimg.type()==CV_8UC1);
   CV_Assert(difimg.size()==curFrame.size());   
}

void fsiv_apply_mask(const cv::Mat & frame, const cv::Mat & mask, cv::Mat & outframe)
{
   CV_Assert(frame.type()==CV_8UC1 || frame.type()==CV_8UC3);
   CV_Assert(mask.type()==CV_8UC1);
   CV_Assert(frame.size()==mask.size());
   
   //GRAYSCALE
   /*cv::Mat tmp;
   cv::cvtColor(frame, tmp, cv::COLOR_GRAY2BGR);
   tmp.copyTo(outframe, mask);
   */

   //COLOR
   frame.copyTo(outframe, mask);

   CV_Assert(outframe.type()==frame.type());
   CV_Assert(outframe.size()==frame.size());   
}

// ================= OPTIONAL PART STARTS HERE =======================

void fsiv_learn_model(cv::VideoCapture & input, int maxframes, cv::Mat & MeanI, cv::Mat & I2, cv::Mat & VarI, cv::Mat & StdI)
{
   CV_Assert(input.isOpened());
   
   // WRITE ME

}

void fsiv_acc_model(const cv::Mat & frame, cv::Mat & MeanI, cv::Mat & I2)
{
   // WRITE ME
   //Check
   MeanI += frame;
   I2 += frame.mul(frame);
   // Better?
   cv::accumulate(frame, MeanI);
   cv::accumulate(frame.mul(frame), I2);

}

void fsiv_segm_by_model(const cv::Mat & frame, cv::Mat & theMask, const cv::Mat & mean, const cv::Mat & std, float t, int r)
{
   CV_Assert(frame.type()==CV_32FC3);
   // WRITE ME
   //Check
   theMask = cv::abs(frame - mean) > t*std;
   fsiv_remove_segmentation_noise(theMask, r);

   CV_Assert(theMask.type()==CV_8UC1);
}

void fsiv_update_model(const cv::Mat & frame, cv::Mat & mean, cv::Mat & I2, cv::Mat &std,  float alpha, const cv::Mat & theMask)
{
   CV_Assert(frame.type()==CV_32FC3);
   CV_Assert(theMask.type()==CV_8UC1);

   CV_Assert(mean.type()==CV_32FC3);
   CV_Assert(std.type()==CV_32FC3);

   // WRITE ME
   //Check
   cv::Mat frameMasked = frame.mul(theMask);
   cv::Mat I2Masked = frameMasked.mul(frameMasked);
   mean = (1-alpha)*mean + alpha*frameMasked;   
   I2 = (1-alpha)*I2 + alpha*I2Masked;
   //std = cv::sqrt(I2 - mean.mul(mean), std);
   
   // Better?
   fsiv_acc_model(frameMasked, mean, I2);
   cv::accumulateWeighted(frame, mean, alpha, theMask);
   cv::accumulateWeighted(frame.mul(frame), I2, alpha, theMask);
   //std = cv::sqrt(I2 - mean.mul(mean), std);
}
