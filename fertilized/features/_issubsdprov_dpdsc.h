/* Copyright 2013 Christoph Lassner */
#pragma once
#ifndef FERTILIZED_FEATURES__ISSUBSDPROV_DPDSC_H_
#define FERTILIZED_FEATURES__ISSUBSDPROV_DPDSC_H_

#include <type_traits>

#include "../global.h"
#include "../types.h"
#include "../data_providers/subsamplingdataprovider.h"
#include "../data_providers/nocopypatchsamplemanager.h"

namespace fertilized {
  template <typename input_dtype, typename annotation_dtype, bool = std::is_integral<annotation_dtype>::value>
  struct _IsSubsDprov_DPDSC {
    static bool check(const IDataProvider<input_dtype, annotation_dtype> * const dprov);
  };

  template <typename input_dtype, typename annotation_dtype>
  struct _IsSubsDprov_DPDSC<input_dtype, annotation_dtype, true> {
    static bool check(const IDataProvider<input_dtype, annotation_dtype> * const dprov) {
      const auto *dprov_c = dynamic_cast<const SubsamplingDataProvider<input_dtype, annotation_dtype> *>(dprov);
      if (dprov_c != nullptr) {
        const auto psmp = dprov_c -> get_SampleManager();
        const auto *sm = dynamic_cast<const NoCopyPatchSampleManager<input_dtype, annotation_dtype> *>(psmp.get());
        if (sm != nullptr) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    };
  };

  template <typename input_dtype, typename annotation_dtype>
  struct _IsSubsDprov_DPDSC<input_dtype, annotation_dtype, false> {
    static bool check(const IDataProvider<input_dtype, annotation_dtype> * const dprov) {
      return false;
    };
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES__ISSUBSDPROV_DPDSC_H_
