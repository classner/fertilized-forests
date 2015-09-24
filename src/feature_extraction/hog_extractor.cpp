/*
 * hog_extractor.cpp
 *
 *  Created on: Mar 22, 2012
 *      Author: Juergen Gall, mdantone, Christoph Lassner
 */

#include "fertilized/feature_extraction/hog_extractor.h"
#ifdef WITH_OPENCV
#include <deque>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#if defined(_MSC_VER)
#if _MSC_VER < 1800
#pragma warning (push)
#pragma warning ( disable : 4715)
namespace std {
  // Manually implement a signbit function as defined in the standard.
  // It is non-trivial, since it must return valid values for +/-0, +/-inf
  // as well, so the best thing really is to use the bit representation of the
  // floating point numbers. Hence, works only for IEEE floats!
  template <typename T>
  inline static bool signbit(const T &x);
  template <>
  inline static bool signbit<float>(const float &x) {
    return (*reinterpret_cast<const long*>(&x) & (1L << 31)) != 0;
  }
  template <>
  inline static bool signbit<double>(const double &x) {
    return (*reinterpret_cast<const long long*>(&x) & (1LL << 63)) != 0;
  }
}

template <typename T>
inline static T copysign(const T &x, const T &origin);
template <>
inline static float copysign<float>(const float &x, const float &origin) {
  long tmp;
  if (std::signbit(origin)) {
    tmp = *reinterpret_cast<const long*>(&x) | (1L << 31);
    return *reinterpret_cast<float*>(&tmp);
  } else {
    tmp = *reinterpret_cast<const long*>(&x) &
          (std::numeric_limits<unsigned long>::max() >> 1);
    return *reinterpret_cast<float*>(&tmp);
  }
}
template <>
inline static double copysign<double>(const double &x, const double &origin) {
  long long tmp;
  if (std::signbit(origin)) {
    tmp = *reinterpret_cast<const long long*>(&x) | (1LL << 63);
    return *reinterpret_cast<double*>(&tmp);
  } else {
    tmp = *reinterpret_cast<const long long*>(&x) &
          (std::numeric_limits<unsigned long long>::max() >> 1);
    return *reinterpret_cast<double*>(&tmp);
  }
}
#pragma warning (pop)
#endif
#endif

#define COLOR2LAB CV_BGR2Lab
#define COLOR2GRAY CV_BGR2GRAY

using namespace std;
using namespace cv;

namespace fertilized {
namespace vision {
namespace features {
namespace feature_channels {

void HOGExtractor::extractFeatureChannels15(const cv::Mat& img,
                                            std::vector<cv::Mat>& Channels) {
  // 9 feature channels
  // 3+9 channels: Lab + HOGlike features with 9 bins
  const int FEATURE_CHANNELS = 15;
  Channels.resize(FEATURE_CHANNELS);
  for (int c=0; c<FEATURE_CHANNELS; ++c)
    Channels[c].create(img.rows,img.cols, CV_8U);

  if( MIN(img.cols, img.rows) < 5 ){
    cout <<"image is too small for HoG Extractor"<< endl;
    return;
  }

  Mat I_x;
  Mat I_y;

  // Get intensity
  cvtColor( img, Channels[0], COLOR2GRAY );

  // |I_x|, |I_y|
  Sobel(Channels[0],I_x,CV_16S,1,0,3);
  Sobel(Channels[0],I_y,CV_16S,0,1,3);

  //convertScaleAbs( I_x, Channels[3], 0.25);
  //convertScaleAbs( I_y, Channels[4], 0.25);

  int rows = I_x.rows;
  int cols = I_y.cols;

  if (I_x.isContinuous() && I_y.isContinuous() && Channels[1].isContinuous() &&
      Channels[2].isContinuous()) {
    cols *= rows;
    rows = 1;
  }

  for( int y = 0; y < rows; y++ ) {
    short* ptr_Ix = I_x.ptr<short>(y);
    short* ptr_Iy = I_y.ptr<short>(y);
    uchar* ptr_out = Channels[1].ptr<uchar>(y);
    for( int x = 0; x < cols; x++ )
    {
      // Avoid division by zero
      float tx = (float)ptr_Ix[x] + (float)copysign(0.000001f, (float)ptr_Ix[x]);
      // Scaling [-pi/2 pi/2] -> [0 80*pi]
      ptr_out[x]=saturate_cast<uchar>( ( atan((float)ptr_Iy[x]/tx)+3.14159265f/2.0f ) * 80 );
    }
  }

  // Magnitude of gradients
  for (int y = 0; y < rows; y++) {
    short* ptr_Ix = I_x.ptr<short>(y);
    short* ptr_Iy = I_y.ptr<short>(y);
    uchar* ptr_out = Channels[2].ptr<uchar>(y);
    for( int x = 0; x < cols; x++ )
    {
      ptr_out[x] = saturate_cast<uchar>(
          sqrt((float)ptr_Ix[x]*(float)ptr_Ix[x] +
               (float)ptr_Iy[x]*(float)ptr_Iy[x]));
    }
  }

  // 9-bin HOG feature stored at vImg[7] - vImg[15]
  hog.extractOBin(Channels[1], Channels[2], Channels, 3);

  // |I_xx|, |I_yy|
  //Sobel(Channels[0],I_x,CV_16S, 2,0,3);
  //convertScaleAbs( I_x, Channels[5], 0.25);

  //Sobel(Channels[0],I_y,CV_16S, 0,2,3);
  //convertScaleAbs( I_y, Channels[6], 0.25);

  // L, a, b
  Mat imgRGB(img.size(), CV_8UC3);
  cvtColor( img, imgRGB, COLOR2LAB  );

  // Split color channels
  // overwriting the first 3 channels
  //  Mat out[] = { Channels[0], Channels[1], Channels[2] };
  //  int from_to[] = { 0,0 , 1,1, 2,2 };
  //  mixChannels( &imgRGB, 1, out, 3, from_to, 3 );
  split(imgRGB, &Channels[0]);

  // min filter
  for(int c=0; c<3; ++c)
    minfilt(Channels[c], Channels[c+12], 5);

  //max filter
  for(int c=0; c<12; ++c)
    maxfilt(Channels[c], 5);

#if 0
  // Debug
  namedWindow( "Show", CV_WINDOW_AUTOSIZE );
  for(int i=0; i<FEATURE_CHANNELS; i++) {
    imshow( "Show", Channels[i] );
    waitKey(0);
  }
#endif
}

/**
 * Hough forest feature extraction equivalent to the original implementation
 * by Juergen Gall (32 feature channels).
 */
void HOGExtractor::extractFeatureChannels32(const Mat& img,
                                            std::vector<cv::Mat>& channels) {
  // 32 feature channels
  // 7+9 channels: L, a, b, |I_x|, |I_y|, |I_xx|, |I_yy|, HOGlike features
  // with 9 bins (weighted orientations 5x5 neighborhood)
  // 16+16 channels: minfilter + maxfilter on 5x5 neighborhood

  assert( img.channels() == 3);

  channels.resize(32);
  for(int c=0; c<32; ++c)
    channels[c].create(img.rows,img.cols, CV_8U);
  Mat I_x;
  Mat I_y;

  // Get intensity
  cvtColor( img, channels[0], COLOR2GRAY );

  // |I_x|, |I_y|
  Sobel(channels[0],I_x,CV_16S,1,0,3);
  Sobel(channels[0],I_y,CV_16S,0,1,3);

  convertScaleAbs( I_x, channels[3], 0.25);
  convertScaleAbs( I_y, channels[4], 0.25);

  int rows = I_x.rows;
  int cols = I_y.cols;

  if (I_x.isContinuous() && I_y.isContinuous() && channels[1].isContinuous() &&
      channels[2].isContinuous()) {
    cols *= rows;
    rows = 1;
  }

  for( int y = 0; y < rows; y++ ) {
    short* ptr_Ix = I_x.ptr<short>(y);
    short* ptr_Iy = I_y.ptr<short>(y);
    uchar* ptr_out = channels[1].ptr<uchar>(y);
    for( int x = 0; x < cols; x++ )
    {
      // Avoid division by zero
      float tx = (float)ptr_Ix[x] + (float)copysign(0.000001f, (float)ptr_Ix[x]);
      // Scaling [-pi/2 pi/2] -> [0 80*pi]
      ptr_out[x]=saturate_cast<uchar>(
          (atan((float)ptr_Iy[x]/tx)+3.14159265f/2.0f) * 80);
    }
  }

  // Magnitude of gradients
  for( int y = 0; y < rows; y++ ) {
    short* ptr_Ix = I_x.ptr<short>(y);
    short* ptr_Iy = I_y.ptr<short>(y);
    uchar* ptr_out = channels[2].ptr<uchar>(y);
    for( int x = 0; x < cols; x++ )
    {
      ptr_out[x] = saturate_cast<uchar>(
          sqrt((float)ptr_Ix[x]*(float)ptr_Ix[x] +
               (float)ptr_Iy[x]*(float)ptr_Iy[x]));
    }
  }

  // 9-bin HOG feature stored at vImg[7] - vImg[15]
  hog.extractOBin(channels[1], channels[2], channels, 7);

  // |I_xx|, |I_yy|
  Sobel(channels[0],I_x,CV_16S, 2,0,3);
  convertScaleAbs( I_x, channels[5], 0.25);

  Sobel(channels[0],I_y,CV_16S, 0,2,3);
  convertScaleAbs( I_y, channels[6], 0.25);

  // L, a, b
  Mat img_;
  cvtColor( img, img_, COLOR2LAB  );

  // Split color channels
  Mat out[] = { channels[0], channels[1], channels[2] };
  int from_to[] = { 0,0 , 1,1, 2,2 };
  mixChannels( &img_, 1, out, 3, from_to, 3 );

  // int num_treads = boost::thread::hardware_concurrency();
  {
    // boost::thread_pool::executor e(num_treads);
    // min filter
    for(int c=0; c<16; ++c){
      // e.submit(boost::bind(&HOGExtractor::minfilt,
      // channels[old_size+c], channels[old_size+c+16], 5  ));
      HOGExtractor::minfilt(channels[c], channels[c+16], 5);
    }
    // e.join_all();
  }
  {
    // boost::thread_pool::executor e(num_treads);
    // max filter
    for(int c=0; c<16; ++c){
      // e.submit(boost::bind(&HOGExtractor::maxfilt, channels[old_size+c], 5 ));
      HOGExtractor::maxfilt(channels[c], 5);
    }
    // e.join_all();
  }

#if 0
  // Debug
  namedWindow( "Show", CV_WINDOW_AUTOSIZE );
  for(int i=0; i<32; i++) {
    imshow( "Show", channels[old_size+i] );
    waitKey(0);
  }
#endif


}

void HOGExtractor::maxfilt(Mat &src, unsigned int width) {

  unsigned int step = static_cast<unsigned int>(src.step);
  uchar* s_data = src.ptr<uchar>(0);

  for(int  y = 0; y < src.rows; y++) {
    HOGExtractor::maxfilt(s_data+y*step, 1, src.cols, width);
  }

  s_data = src.ptr<uchar>(0);

  for(int  x = 0; x < src.cols; x++)
    HOGExtractor::maxfilt(s_data+x, step, src.rows, width);

}

void HOGExtractor::minfilt(Mat &src, Mat &dst, unsigned int width) {

  unsigned int step = static_cast<unsigned int>(src.step);
  uchar* s_data = src.ptr<uchar>(0);
  uchar* d_data = dst.ptr<uchar>(0);

  for(int  y = 0; y < src.rows; y++)
    HOGExtractor::minfilt(s_data+y*step, d_data+y*step, 1, src.cols, width);

  d_data = dst.ptr<uchar>(0);

  for(int  x = 0; x < src.cols; x++)
    HOGExtractor::minfilt(d_data+x, step, src.rows, width);

}

void HOGExtractor::maxfilt(uchar* data, uchar* maxvalues, unsigned int step,
                           unsigned int size, unsigned int width) {
  unsigned int d = int((width+1)/2)*step;
  size *= step;
  width *= step;

  maxvalues[0] = data[0];
  for(unsigned int i=0; i < d-step; i+=step) {
    for(unsigned int k=i; k<d+i; k+=step) {
      if(data[k]>maxvalues[i]) maxvalues[i] = data[k];
    }
    maxvalues[i+step] = maxvalues[i];
  }

  maxvalues[size-step] = data[size-step];
  for(unsigned int i=size-step; i > size-d; i-=step) {
    for(unsigned int k=i; k>i-d; k-=step) {
      if(data[k]>maxvalues[i]) maxvalues[i] = data[k];
    }
    maxvalues[i-step] = maxvalues[i];
  }

  deque<int> maxfifo;
  for(unsigned int i = step; i < size; i+=step) {
    if(i >= width) {
      maxvalues[i-d] = data[!maxfifo.empty() ? maxfifo.front(): i-step];
    }

    if(data[i] < data[i-step]) {
      maxfifo.push_back(i-step);
      if(i==  width+maxfifo.front())
        maxfifo.pop_front();
    } else {
      while(!maxfifo.empty()) {
        if(data[i] <= data[maxfifo.back()]) {
          if(i==  width+maxfifo.front())
            maxfifo.pop_front();
          break;
        }
        maxfifo.pop_back();
      }
    }
  }

  maxvalues[size-d] = data[!maxfifo.empty() ? maxfifo.front():size-step];
}

void HOGExtractor::maxfilt(uchar* data, unsigned int step, unsigned int size,
                           unsigned int width) {

  unsigned int d = int((width+1)/2)*step;
  size *= step;
  width *= step;

  deque<uchar> tmp;

  tmp.push_back(data[0]);
  for(unsigned int k=step; k<d; k+=step) {
    if(data[k]>tmp.back()) tmp.back() = data[k];
  }

  for(unsigned int i=step; i < d-step; i+=step) {
    tmp.push_back(tmp.back());
    if(data[i+d-step]>tmp.back()) tmp.back() = data[i+d-step];
  }


  deque<int> minfifo;
  for(unsigned int i = step; i < size; i+=step) {
    if(i >= width) {
      tmp.push_back(data[!minfifo.empty() ? minfifo.front(): i-step]);
      data[i-width] = tmp.front();
      tmp.pop_front();
    }

    if(data[i] < data[i-step]) {

      minfifo.push_back(i-step);
      if(i==  width+minfifo.front())
        minfifo.pop_front();

    } else {

      while(!minfifo.empty()) {
        if(data[i] <= data[minfifo.back()]) {
          if(i==  width+minfifo.front())
            minfifo.pop_front();
          break;
        }
        minfifo.pop_back();
      }

    }

  }

  tmp.push_back(data[!minfifo.empty() ? minfifo.front():size-step]);

  for(unsigned int k=size-step-step; k>=size-d; k-=step) {
    if(data[k]>data[size-step]) data[size-step] = data[k];
  }

  for(unsigned int i=size-step-step; i >= size-d; i-=step) {
    data[i] = data[i+step];
    if(data[i-d+step]>data[i]) data[i] = data[i-d+step];
  }

  for(unsigned int i=size-width; i<=size-d; i+=step) {
    data[i] = tmp.front();
    tmp.pop_front();
  }

}


void HOGExtractor::minfilt(uchar* data, uchar* minvalues, unsigned int step,
                           unsigned int size, unsigned int width) {
  unsigned int d = int((width+1)/2)*step;
  size *= step;
  width *= step;

  minvalues[0] = data[0];
  for(unsigned int i=0; i < d-step; i+=step) {
    for(unsigned int k=i; k<d+i; k+=step) {
      if(data[k]<minvalues[i]) minvalues[i] = data[k];
    }
    minvalues[i+step] = minvalues[i];
  }

  minvalues[size-step] = data[size-step];
  for(unsigned int i=size-step; i > size-d; i-=step) {
    for(unsigned int k=i; k>i-d; k-=step) {
      if(data[k]<minvalues[i]) minvalues[i] = data[k];
    }
    minvalues[i-step] = minvalues[i];
  }

  deque<int> minfifo;
  for(unsigned int i = step; i < size; i+=step) {
    if(i >= width) {
      minvalues[i-d] = data[!minfifo.empty() ? minfifo.front(): i-step];
    }

    if(data[i] > data[i-step]) {

      minfifo.push_back(i-step);
      if(i==  width+minfifo.front())
        minfifo.pop_front();

    } else {

      while(!minfifo.empty()) {
        if(data[i] >= data[minfifo.back()]) {
          if(i==  width+minfifo.front())
            minfifo.pop_front();
          break;
        }
        minfifo.pop_back();
      }

    }

  }

  minvalues[size-d] = data[!minfifo.empty() ? minfifo.front():size-step];

}

void HOGExtractor::minfilt(uchar* data, unsigned int step, unsigned int size,
                           unsigned int width) {
  unsigned int d = int((width+1)/2)*step;
  size *= step;
  width *= step;

  deque<uchar> tmp;

  tmp.push_back(data[0]);
  for(unsigned int k=step; k<d; k+=step) {
    if(data[k]<tmp.back()) tmp.back() = data[k];
  }

  for(unsigned int i=step; i < d-step; i+=step) {
    tmp.push_back(tmp.back());
    if(data[i+d-step]<tmp.back()) tmp.back() = data[i+d-step];
  }

  deque<int> minfifo;
  for(unsigned int i = step; i < size; i+=step) {
    if(i >= width) {
      tmp.push_back(data[!minfifo.empty() ? minfifo.front(): i-step]);
      data[i-width] = tmp.front();
      tmp.pop_front();
    }

    if(data[i] > data[i-step]) {

      minfifo.push_back(i-step);
      if(i==  width+minfifo.front())
        minfifo.pop_front();
    } else {
      while(!minfifo.empty()) {
        if(data[i] >= data[minfifo.back()]) {
          if(i==  width+minfifo.front())
            minfifo.pop_front();
          break;
        }
        minfifo.pop_back();
      }
    }
  }

  tmp.push_back(data[!minfifo.empty() ? minfifo.front():size-step]);

  for(unsigned int k=size-step-step; k>=size-d; k-=step) {
    if(data[k]<data[size-step]) data[size-step] = data[k];
  }

  for(unsigned int i=size-step-step; i >= size-d; i-=step) {
    data[i] = data[i+step];
    if(data[i-d+step]<data[i]) data[i] = data[i-d+step];
  }

  for(unsigned int i=size-width; i<=size-d; i+=step) {
    data[i] = tmp.front();
    tmp.pop_front();
  }
}

} // namespace vision
} // namespace features
} // namespace feature_channels
} // namespace fertilized
#endif  // WITH_OPENCV
