/* Author: Christoph Lassner. */
#ifdef CAFFE_FEATURE_EXTRACTION_ENABLED
#include "../global.h"
#include "../ndarray.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <opencv2/opencv.hpp>
// TODO: remove
//#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <caffe/caffe.hpp>
//#define NOMINMAX
//#include <Windows.h>
//#include <caffe/proto/caffe.pb.h>

#include "./dnnfeatureextractor.h"
#include "./__alexnet.h"

namespace fs = boost::filesystem;

namespace fertilized {

  inline void extract_from_layer(
                          caffe::Blob<float> const * const blob,
                          Array<float, 4, 4> target,
                          const unsigned int &start_image,
                          const unsigned int &n_images) {
    std::copy(
      blob -> cpu_data(),
      blob -> cpu_data() + blob -> offset(n_images+1),
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

  DllExport DNNFeatureExtractor::DNNFeatureExtractor(
                                        const bool &use_cpu,
                                        const int &device_id,
                                        std::string net_layout_file,
                                        std::string net_weights_file,
                                        std::string net_outlayer,
                                        const bool &load_mean,
                                        std::string mean_file)
    : mean_available(false) {
    // Replace defaults.
    if (net_layout_file == "")
      net_layout_file = __ALEXNET_MODELFILE;
    if (net_weights_file == "")
      net_weights_file = __ALEXNET_LAYERFILE;
    if (net_outlayer == "")
      net_outlayer = "pool5";
    if (mean_file == "")
      mean_file = __ALEXNET_MEANFILE;
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
    caffe::Net<float> *net = new caffe::Net<float>(net_layout_file,
                                                   caffe::Phase::TEST);
    net_ptr = reinterpret_cast<void*>(net);
    // Load network weights.
    net -> CopyTrainedLayersFrom(net_weights_file);
    input_size = cv::Size(net -> input_blobs()[0] -> width(),
                          net -> input_blobs()[0] -> height());
    // Load the mean image if necessary.
    if (load_mean) {
      int mean_x = 0;
      int mean_y = 0;
      int mean_channels = 0;
      if (!fs::exists(mean_file)) {
        throw Fertilized_Exception("Mean file for the DNNFeatureExtractor does "
                                   "not exist: " + mean_file);
      }
      cv::Mat meanMat = deserializeMean(mean_file,
                                        &mean_x,
                                        &mean_y,
                                        &mean_channels);
      if (mean_channels != 3) {
          throw Fertilized_Exception("Only 3 channel images are supported! "
            "The mean image must also have 3 channels!");
      }
      cv::resize(meanMat, mean_data, input_size, 0.0, 0.0, CV_INTER_CUBIC);
      if (mean_channels != net -> input_blobs()[0] -> channels()) {
          throw Fertilized_Exception("Mean image for the DNNFeatureExtractor "
            "must have the same amount of channels as the input of the "
            "network!");
      }
      mean_available = true;
    }
    // Determine the read layer index.
    read_layer_idx = -1;
    int blobindex = 0;
    for (const auto &blobname : net -> blob_names()) {
        std::cout << blobname << std::endl;
        if (blobname == net_outlayer) {
            read_layer_idx = blobindex;
            break;
        }
        blobindex++;
    }
    if (read_layer_idx == -1) {
        throw Fertilized_Exception("Could not find a layer with the specified "
                                   "name!");
    }
  };

  DllExport DNNFeatureExtractor::~DNNFeatureExtractor() {
    caffe::Net<float> *net = reinterpret_cast<caffe::Net<float>*>(net_ptr);
    delete net;
  };

  DllExport Array<float, 4, 4> DNNFeatureExtractor::extract(
        const std::vector<Array<float, 3, 3>> &images,
        const bool &subtract_mean) {
    // Create the result array in the appropriate size.
    caffe::Net<float> *net = reinterpret_cast<caffe::Net<float>*>(net_ptr);
    caffe::Blob<float> *output_blob = (net -> blobs()[read_layer_idx]).get();
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
    // Create the input.
    // TODO: remove if unnecessary.
    caffe::Blob<float> *caffe_input = new caffe::Blob<float>(net -> input_blobs()[0] -> num(),
                                              net -> input_blobs()[0] -> channels(),
                                              net -> input_blobs()[0] -> height(),
                                              net -> input_blobs()[0] -> width());
    std::vector<caffe::Blob<float>*> caffe_in = std::vector<caffe::Blob<float>*>();
    caffe_in.push_back(caffe_input);
    float loss;
    boost::shared_ptr<caffe::Blob<float>> caffe_out = net -> blob_by_name("pool5");
    // endtodo
    for (const auto &image : images) {
      mat_view = cv::Mat(image.TPLMETH getSize<0>(),
                         image.TPLMETH getSize<1>(),
                         CV_32FC3,
                         image.getData());
      cv::resize(mat_view,
                 image_mean_prepared,
                 input_size,
                 0.0, 0.0,
                 CV_INTER_CUBIC);
      if (subtract_mean) {
        if (! mean_available) {
          throw Fertilized_Exception("No mean data has been loaded! Can not "
            "subtract mean!");
        }
        image_mean_prepared -= mean_data;
      }
      // reorder channels.
      // TODO rechange
      //float *input_ptr = net -> input_blobs()[0] -> mutable_cpu_data();
      float *input_ptr = caffe_input -> mutable_cpu_data();
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
        // TODO reactivate
        //net -> ForwardTo(read_layer_idx + 1);
        net -> Forward(caffe_in, &loss);
        extract_from_layer(caffe_out.get(),
                           result,
                           image_id,
                           batch_id);
        image_id += batch_id;
        batch_id = 0;
      }
    }
    // Extract if necessary.
    if (batch_id != 0) {
      // TODO reactivate
      //net -> ForwardTo(read_layer_idx + 1);
      net -> Forward(caffe_in, &loss);
      extract_from_layer(caffe_out.get(),
                         result,
                         image_id,
                         batch_id);
      image_id += batch_id;
      batch_id = 0;
    }
    // TODO: remove
    delete caffe_in[0];
    // endtodo
    return result;
  };

};  // namespace fertilized
#endif // CAFFE_FEATURE_EXTRACTION_ENABLED
