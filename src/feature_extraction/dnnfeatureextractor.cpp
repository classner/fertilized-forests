/* Author: Christoph Lassner. */
#ifndef _MSC_VER
#include "fertilized/global.h"
#endif
#include "fertilized/ndarray.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
#ifdef _MSC_VER
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <caffe/caffe.hpp>
#endif

#ifdef _MSC_VER
#include "fertilized/global.h"
#endif

#ifdef WITH_OPENCV
#include <opencv2/opencv.hpp>
#endif

#include "fertilized/feature_extraction/dnnfeatureextractor.h"

namespace fs = boost::filesystem;

namespace fertilized {
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
  inline void extract_from_layer(
                          caffe::Blob<float> const * const blob,
                          Array<float, 4, 4> target,
                          const unsigned int &start_image,
                          const unsigned int &n_images) {
    std::copy(
      blob -> cpu_data(),
      blob -> cpu_data() + n_images *
                           blob -> channels() *
                           blob -> width() *
                           blob -> height(),
      &target[start_image][0][0][0]);
  };

  inline cv::Mat deserializeMean(std::string const& meanfilename,
                                 int *dimx,
                                 int *dimy,
                                 int *channels) {
    std::ifstream meanstream(meanfilename);
    if (!meanstream.is_open()) {
        throw Fertilized_Exception("Can not open mean file: " + meanfilename);
    }
    std::string line;
    // read num rows
    std::getline(meanstream, line);
    boost::trim(line);
    *dimy = std::stoi(line);
    // read num cols
    std::getline(meanstream, line);
    boost::trim(line);
    *dimx = std::stoi(line);
    // read num channels
    std::getline(meanstream, line);
    boost::trim(line);
    *channels = std::stoi( line );
    // read data
    std::getline(meanstream, line);
    boost::trim(line);
    meanstream.close();
    std::vector<std::string> fdata;
    boost::split(fdata, line, boost::is_any_of(" "));
    cv::Mat result(*dimy, *dimx, CV_32FC3);
    float *data_ptr = result.ptr<float>();
    for ( size_t fitem = 0; fitem < fdata.size(); ++fitem ) {
        boost::trim(fdata[fitem]);
        data_ptr[fitem] = std::stof(fdata[fitem]);
    }
    return result;
  };
#endif

  DllExport DNNFeatureExtractor::DNNFeatureExtractor(
                                        std::string net_layout_file,
                                        std::string net_weights_file,
                                        std::string net_outlayer,
                                        const bool &use_cpu,
                                        const int &device_id,
                                        std::string mean_file)
    : net_ptr(nullptr),
      mean_available(false),
      read_layer_idx(-1),
      read_blob_idx(-1) {
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
    if (device_id < 0)
      throw Fertilized_Exception("Device id >= 0 required!");
    // Set mode.
    if (use_cpu) {
      caffe::Caffe::set_mode(caffe::Caffe::CPU);
    } else {
#ifdef CAFFE_CPU_ONLY
      throw Fertilized_Exception("This binary has been built without "
                                 "GPU support!");
#else
      caffe::Caffe::set_mode(caffe::Caffe::GPU);
      // Set device.
      caffe::Caffe::SetDevice(device_id);
#endif
    }
    // Load network layout.
    if (! fs::exists(net_layout_file))
      throw Fertilized_Exception("Net layout file not found: " + net_layout_file);
    caffe::Net<float> *net = new caffe::Net<float>(net_layout_file,
                                                   caffe::Phase::TEST);
    net_ptr = reinterpret_cast<void*>(net);
    // Load network weights.
    if (! fs::exists(net_weights_file)) {
      // Destructor will not be called! Clean up...
      delete net;
      throw Fertilized_Exception("Net weights file not found: " + net_weights_file);
    }
    net -> CopyTrainedLayersFrom(net_weights_file);
    input_size = cv::Size(net -> input_blobs()[0] -> width(),
                          net -> input_blobs()[0] -> height());
    // Load the mean image if necessary.
    if (mean_file != "") {
      int mean_x = 0;
      int mean_y = 0;
      int mean_channels = 0;
      if (!fs::exists(mean_file)) {
        // Destructor will not be called! Clean up...
        delete net;
        throw Fertilized_Exception("Mean file for the DNNFeatureExtractor does "
                                   "not exist: " + mean_file);
      }
      cv::Mat meanMat = deserializeMean(mean_file,
                                        &mean_x,
                                        &mean_y,
                                        &mean_channels);
      if (mean_channels != 3) {
          // Destructor will not be called! Clean up...
          delete net;
          throw Fertilized_Exception("Only 3 channel images are supported! "
            "The mean image must also have 3 channels!");
      }
      cv::resize(meanMat, mean_data, input_size, 0.0, 0.0, CV_INTER_CUBIC);
      if (mean_channels != net -> input_blobs()[0] -> channels()) {
          // Destructor will not be called! Clean up...
          delete net;
          throw Fertilized_Exception("Mean image for the DNNFeatureExtractor "
            "must have the same amount of channels as the input of the "
            "network!");
      }
      mean_available = true;
    }
    // Determine the read layer and blob index.
    read_blob_idx = -1;
    int blobindex = 0;
    for (const auto &blobname : net -> blob_names()) {
        if (blobname == net_outlayer) {
            read_blob_idx = blobindex;
            break;
        }
        blobindex++;
    }
    int layerindex = 0;
    for (const auto &layername : net -> layer_names()) {
        if (layername == net_outlayer) {
            read_layer_idx = layerindex;
            break;
        }
        layerindex++;
    }
    if (read_layer_idx == -1 || read_blob_idx == -1) {
        // Destructor will not be called! Clean up...
        delete net;
        throw Fertilized_Exception("Could not find a layer and blob with the "
                                   "specified name!");
    }
    FASSERT (read_layer_idx >= 0);
    FASSERT (read_blob_idx >= 0);
#else
    throw Fertilized_Exception("This binary has been built without caffe "
      "feature extraction support. Rebuild with the option `--with-caffe` "
      "to use this object.");
#endif
  };

  DllExport DNNFeatureExtractor::~DNNFeatureExtractor() {
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
    if (net_ptr != nullptr) {
      caffe::Net<float> *net = reinterpret_cast<caffe::Net<float>*>(net_ptr);
      delete net;
    }
#endif
  };

  DllExport Array<float, 4, 4> DNNFeatureExtractor::extract(
        const std::vector<Array<float, 3, 3>> &images,
        const bool &subtract_mean) {
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
    // Create the result array in the appropriate size.
    caffe::Net<float> *net = reinterpret_cast<caffe::Net<float>*>(net_ptr);
    caffe::Blob<float> *output_blob = (net -> blobs()[read_blob_idx]).get();
    Vector<size_t, 4> shape;
    shape[0] = images.size();
    shape[1] = output_blob -> channels();
    shape[2] = output_blob -> width();
    shape[3] = output_blob -> height();
    Array<float, 4, 4> result = allocate(shape);
    cv::Mat mat_view;
    cv::Mat image_mean_prepared;
    unsigned int batch_id = 0;
    unsigned int image_id = 0;
    for (const auto &image : images) {
      mat_view = cv::Mat(image.TPLMETH getSize<0>(),
                         image.TPLMETH getSize<1>(),
                         CV_32FC3,
                         image.getData());
      if (image.TPLMETH getSize<0>() != output_blob -> height() ||
          image.TPLMETH getSize<1>() != output_blob -> width()) {
        cv::resize(mat_view,
                   image_mean_prepared,
                   input_size,
                   0.0, 0.0,
                   CV_INTER_CUBIC);
      } else {
        image_mean_prepared = mat_view.clone();
      }
      if (subtract_mean) {
        if (! mean_available) {
          throw Fertilized_Exception("No mean data has been loaded! Can not "
            "subtract mean!");
        }
        image_mean_prepared -= mean_data;
      }
      // transpose.
      float *input_ptr = net -> input_blobs()[0] -> mutable_cpu_data();
      int rows = input_size.height;
      int cols = input_size.width;
      for (int row = 0; row < rows; ++row) {
        float * src_ptr = image_mean_prepared.ptr<float>(row);
        for (int col = 0; col < cols; ++col) {
          for (int chan = 0; chan < 3; ++chan) {
            input_ptr[batch_id*3*rows*cols + chan*rows*cols + row*cols + col] =
                src_ptr[col*3+chan];
          }
        }
      }
      batch_id++;
      // Extract if necessary.
      if (batch_id == net -> input_blobs()[0] -> num()) {
        net -> ForwardTo(read_layer_idx);
        extract_from_layer(output_blob,
                           result,
                           image_id,
                           batch_id);
        image_id += batch_id;
        batch_id = 0;
      }
    }
    // Extract if necessary.
    if (batch_id != 0) {
      net -> ForwardTo(read_layer_idx);
      extract_from_layer(output_blob,
                         result,
                         image_id,
                         batch_id);
      image_id += batch_id;
      batch_id = 0;
    }
    return result;
#else
    throw Fertilized_Exception("This library has been built without caffe "
      "feature extraction support. Rebuild it with `--with-caffe` to use "
      "this object and method.");
#endif
  };

};  // namespace fertilized
