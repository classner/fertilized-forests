
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__rootdir.h"
#include <../../include/fertilized/./tree.h>

using namespace fertilized;




          void * getTree_uint8_int16_int16_fv_fv (

        unsigned int max_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        void * decider,
        void * leaf_manager
) {
  // From C types conversions.

    auto __converted_decider = *reinterpret_cast<std::shared_ptr<fertilized::Tree<uint8_t, int16_t, int16_t, std::vector<float>, std::vector<float>>::dec_t>*>(decider);
              

    auto __converted_leaf_manager = *reinterpret_cast<std::shared_ptr<fertilized::Tree<uint8_t, int16_t, int16_t, std::vector<float>, std::vector<float>>::leaf_man_t>*>(leaf_manager);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>(
    new Tree<
              uint8_t,
              int16_t,
              int16_t,
              std::vector<float>,
              std::vector<float>
>(
          max_depth,
          min_samples_at_leaf,
          min_samples_at_node,
          __converted_decider,
          __converted_leaf_manager
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          void * getTreeFromFile_uint8_int16_int16_fv_fv (

        char* filename
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>(
    new Tree<
              uint8_t,
              int16_t,
              int16_t,
              std::vector<float>,
              std::vector<float>
>(
          filename
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          void make_nodeTree_uint8_int16_int16_fv_fv (void *__instance,

        void * data_provider,
        int append_on_different
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    auto __shptr_data_provider = *reinterpret_cast<std::shared_ptr<fertilized::dprov_t>*>(data_provider);
    auto __converted_data_provider = (__shptr_data_provider.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  __instance_unpacked -> make_node(
          __converted_data_provider,
          append_on_different
  );
#pragma warning( pop )

}		


          size_t depthTree_uint8_int16_int16_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> depth(
  );
#pragma warning( pop )

  return libfunc_result;
}		


          void fitTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        int complete_dfs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    fertilized::Array<uint8_t, 2, 2> __converted_data;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(data);
      const mxClassID _matlab_dtid = mxGetClassID(data);
      const mwSize* _matlab_shape = mxGetDimensions(data);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT8_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument data!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_data = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      uint8_t *_dptr = __converted_data.getData();
      uint8_t *_iptr = reinterpret_cast<uint8_t*>(mxGetData(data));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(data, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

    fertilized::Array<int16_t, 2, 2> __converted_annotations;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(annotations);
      const mxClassID _matlab_dtid = mxGetClassID(annotations);
      const mwSize* _matlab_shape = mxGetDimensions(annotations);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxINT16_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument annotations!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_annotations = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      int16_t *_dptr = __converted_annotations.getData();
      int16_t *_iptr = reinterpret_cast<int16_t*>(mxGetData(annotations));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(annotations, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  __instance_unpacked -> fit(
          __converted_data,
          __converted_annotations,
          complete_dfs
  );
#pragma warning( pop )

}		


          void fit_dprovTree_uint8_int16_int16_fv_fv (void *__instance,

        void * data_provider,
        int complete_dfs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    auto __shptr_data_provider = *reinterpret_cast<std::shared_ptr<fertilized::dprov_t>*>(data_provider);
    auto __converted_data_provider = (__shptr_data_provider.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  __instance_unpacked -> fit_dprov(
          __converted_data_provider,
          complete_dfs
  );
#pragma warning( pop )

}		


          mxArray * predictTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    fertilized::Array<uint8_t, 2, 2> __converted_data;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(data);
      const mxClassID _matlab_dtid = mxGetClassID(data);
      const mwSize* _matlab_shape = mxGetDimensions(data);
      // Dimensionality check.
      if (_matlab_ndim != 2) {
        mexErrMsgTxt(("Expected 2 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT8_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument data!");
      }
      Vector<std::size_t, 2> shape;
      for (int i = 0; i < 2; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_data = allocate(shape);
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      uint8_t *_dptr = __converted_data.getData();
      uint8_t *_iptr = reinterpret_cast<uint8_t*>(mxGetData(data));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(data, _matlab_ndim, _idx)];
        dimidx = 2-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> predict(
          __converted_data,
          num_threads
  );
#pragma warning( pop )

  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 2;
      mwSize shape[ 2 ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < 2; ++i) {
        shape[i] = cpparray_shape[i];
      }
      mxClassID classid = mxDOUBLE_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      double *_dptr = libfunc_result.getData();
      double *_iptr = reinterpret_cast<double*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {
        _iptr[mxCalcSingleSubscript(__converted_return_value, 2, _idx)] = _dptr[i];
        dimidx = 2-1;
        while (_idx[dimidx] == shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }
  return __converted_return_value;
}		


          mxArray * predict_imageTree_uint8_int16_int16_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    fertilized::Array<uint8_t, 3, 3> __converted_image;
    {
      const mwSize _matlab_ndim = mxGetNumberOfDimensions(image);
      const mxClassID _matlab_dtid = mxGetClassID(image);
      const mwSize* _matlab_shape = mxGetDimensions(image);
      // Dimensionality check.
      if (_matlab_ndim != 3) {
        mexErrMsgTxt(("Expected 3 dimensions, received " +
          std::to_string(_matlab_ndim)).c_str());
      }
      // Dtype check.
      if (_matlab_dtid != mxUINT8_CLASS) {
        mexErrMsgTxt("Wrong MATLAB datatype of argument image!");
      }
      Vector<std::size_t, 3> shape;
      for (int i = 0; i < 3; ++i) {
        shape[i] = _matlab_shape[i];
      }
      __converted_image = allocate(shape);
      mwIndex _idx [3];
      for (int i = 0; i < 3; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      uint8_t *_dptr = __converted_image.getData();
      uint8_t *_iptr = reinterpret_cast<uint8_t*>(mxGetData(image));
      for (std::size_t i = 0; i < shape.product(); ++i) {
        _dptr[i] = _iptr[mxCalcSingleSubscript(image, _matlab_ndim, _idx)];
        dimidx = 3-1;
        while (_idx[dimidx] == _matlab_shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> predict_image(
          __converted_image,
          step_size,
          reduce_to_patch_positions,
          p1,
          p2
  );
#pragma warning( pop )

  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 2;
      mwSize shape[ 2 ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < 2; ++i) {
        shape[i] = cpparray_shape[i];
      }
      mxClassID classid = mxSINGLE_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [2];
      for (int i = 0; i < 2; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      float *_dptr = libfunc_result.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {
        _iptr[mxCalcSingleSubscript(__converted_return_value, 2, _idx)] = _dptr[i];
        dimidx = 2-1;
        while (_idx[dimidx] == shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }
  return __converted_return_value;
}		


          float get_weightTree_uint8_int16_int16_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_weight(
  );
#pragma warning( pop )

  return libfunc_result;
}		


          size_t get_n_nodesTree_uint8_int16_int16_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_n_nodes(
  );
#pragma warning( pop )

  return libfunc_result;
}		


          void set_weightTree_uint8_int16_int16_fv_fv (void *__instance,

        float new_weight
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  __instance_unpacked -> set_weight(
          new_weight
  );
#pragma warning( pop )

}		


          size_t get_input_data_dimensionsTree_uint8_int16_int16_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_input_data_dimensions(
  );
#pragma warning( pop )

  return libfunc_result;
}		


          mxArray * compute_feature_importancesTree_uint8_int16_int16_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> compute_feature_importances(
  );
#pragma warning( pop )

  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 1;
      mwSize shape[ 1 ];
      auto cpparray_shape = libfunc_result.getShape();
      for (int i = 0; i < 1; ++i) {
        shape[i] = cpparray_shape[i];
      }
      mxClassID classid = mxDOUBLE_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [1];
      for (int i = 0; i < 1; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      double *_dptr = libfunc_result.getData();
      double *_iptr = reinterpret_cast<double*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < cpparray_shape.product(); ++i) {
        _iptr[mxCalcSingleSubscript(__converted_return_value, 1, _idx)] = _dptr[i];
        dimidx = 1-1;
        while (_idx[dimidx] == shape[dimidx]-1) {
          _idx[dimidx] = 0;
          dimidx -= 1;
        }
        _idx[dimidx]++;
      }
    }
  return __converted_return_value;
}		


          size_t get_samples_storedTree_uint8_int16_int16_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_samples_stored(
  );
#pragma warning( pop )

  return libfunc_result;
}		


          int eqTree_uint8_int16_int16_fv_fv (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::tree_t>*>(rhs);
    auto &__converted_rhs = *(__shptr_rhs.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> operator==(
          __converted_rhs
  );
#pragma warning( pop )

  return libfunc_result;
}		


          void saveTree_uint8_int16_int16_fv_fv (void *__instance,

        char* filename
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  __instance_unpacked -> save(
          filename
  );
#pragma warning( pop )

}		
// Destructor.
void delete_Tree_uint8_int16_int16_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<Tree<uint8_t,int16_t,int16_t,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
