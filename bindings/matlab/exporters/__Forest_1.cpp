
// Author: Christoph Lassner.
/**
 * This is an automatically generated file!
 */
#include "../global.h"
#include "../matlab_headers/__rootdir.h"
#include <fertilized/./forest.h>

using namespace fertilized;




          void * getForest_f_f_uint_fv_fv (

        unsigned int max_tree_depth,
        unsigned int min_samples_at_leaf,
        unsigned int min_samples_at_node,
        unsigned int n_trees,
        void * deciders,
        void * leaf_managers,
        void * training
) {
  // From C types conversions.

    std::vector<std::shared_ptr<typename fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::dec_t>> __converted_deciders;
    {
      std::vector<void*> carryvec = *reinterpret_cast<std::vector<void*>*>(deciders);
      __converted_deciders = recover_vec_types<std::shared_ptr<typename fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::dec_t>>(carryvec);
    }
              

    std::vector<std::shared_ptr<typename fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::leaf_man_t>> __converted_leaf_managers;
    {
      std::vector<void*> carryvec = *reinterpret_cast<std::vector<void*>*>(leaf_managers);
      __converted_leaf_managers = recover_vec_types<std::shared_ptr<typename fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::leaf_man_t>>(carryvec);
    }
              

    auto __converted_training = *reinterpret_cast<std::shared_ptr<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::training_t>*>(training);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>(
    new Forest<
              float,
              float,
              uint,
              std::vector<float>,
              std::vector<float>
>(
          max_tree_depth,
          min_samples_at_leaf,
          min_samples_at_node,
          n_trees,
          __converted_deciders,
          __converted_leaf_managers,
          __converted_training
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          void * getForestFromTrees_f_f_uint_fv_fv (

        void * trees,
        void * training
) {
  // From C types conversions.

    std::vector<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::tree_ptr_t> __converted_trees;
    {
      std::vector<void*> carryvec = *reinterpret_cast<std::vector<void*>*>(trees);
      __converted_trees = recover_vec_types<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::tree_ptr_t>(carryvec);
    }
              

    auto __converted_training = *reinterpret_cast<std::shared_ptr<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::training_t>*>(training);
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>(
    new Forest<
              float,
              float,
              uint,
              std::vector<float>,
              std::vector<float>
>(
          __converted_trees,
          __converted_training
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          void * getCombineTrees_f_f_uint_fv_fv (

        void * trees
) {
  // From C types conversions.

    std::vector<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::tree_ptr_t> __converted_trees;
    {
      std::vector<void*> carryvec = *reinterpret_cast<std::vector<void*>*>(trees);
      __converted_trees = recover_vec_types<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::tree_ptr_t>(carryvec);
    }
              

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>(
    new Forest<
              float,
              float,
              uint,
              std::vector<float>,
              std::vector<float>
>(
          __converted_trees
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          void * getForestFromFile_f_f_uint_fv_fv (

        char* filename
) {
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto *libfunc_result = new std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>(
    new Forest<
              float,
              float,
              uint,
              std::vector<float>,
              std::vector<float>
>(
          filename
          ));
#pragma warning( pop )

  void *__converted_return_value = reinterpret_cast<void*>(libfunc_result);
  return __converted_return_value;
}		


          void fitForest_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        mxArray * annotations,
        unsigned int num_threads
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    fertilized::Array<float, 2, 2> __converted_data;
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
      if (_matlab_dtid != mxSINGLE_CLASS) {
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
      float *_dptr = __converted_data.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(data));
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

    fertilized::Array<uint, 2, 2> __converted_annotations;
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
      if (_matlab_dtid != mxUINT32_CLASS) {
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
      uint *_dptr = __converted_annotations.getData();
      uint *_iptr = reinterpret_cast<uint*>(mxGetData(annotations));
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
          num_threads
  );
#pragma warning( pop )

}		


          mxArray * depthsForest_f_f_uint_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> depths(
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
      mxClassID classid = mxUINT64_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      mwIndex _idx [1];
      for (int i = 0; i < 1; ++i) {
        _idx[i] = 0;
      }
      int dimidx;
      size_t *_dptr = libfunc_result.getData();
      size_t *_iptr = reinterpret_cast<size_t*>(mxGetData(__converted_return_value));
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


          void fit_dprovForest_f_f_uint_fv_fv (void *__instance,

        void * fdata_provider,
        void * execution_strategy
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    auto __converted_fdata_provider = *reinterpret_cast<std::shared_ptr<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>::fdprov_t>*>(fdata_provider);
              

    auto __shptr_execution_strategy = *reinterpret_cast<std::shared_ptr<fertilized::Forest<float,float,uint,std::vector<float>,std::vector<float>>::exec_strat_t>*>(execution_strategy);
    auto __converted_execution_strategy = (__shptr_execution_strategy.get());
            

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  __instance_unpacked -> fit_dprov(
          __converted_fdata_provider,
          __converted_execution_strategy
  );
#pragma warning( pop )

}		


          mxArray * predictForest_f_f_uint_fv_fv (void *__instance,

        mxArray * data,
        int num_threads
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    fertilized::Array<float, 2, 2> __converted_data;
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
      if (_matlab_dtid != mxSINGLE_CLASS) {
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
      float *_dptr = __converted_data.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(data));
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


          mxArray * predict_imageForest_f_f_uint_fv_fv (void *__instance,

        mxArray * image,
        size_t step_size,
        int reduce_to_patch_positions,
        float p1,
        float p2
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    fertilized::Array<float, 3, 3> __converted_image;
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
      if (_matlab_dtid != mxSINGLE_CLASS) {
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
      float *_dptr = __converted_image.getData();
      float *_iptr = reinterpret_cast<float*>(mxGetData(image));
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


          size_t get_input_data_dimensionsForest_f_f_uint_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_input_data_dimensions(
  );
#pragma warning( pop )

  return libfunc_result;
}		


          mxArray * compute_feature_importancesForest_f_f_uint_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
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


          mxArray * get_tree_weightsForest_f_f_uint_fv_fv (void *__instance

) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

#pragma warning( push )
#pragma warning( disable : 4800 )
  // Get the libraries' result.
  auto libfunc_result = __instance_unpacked -> get_tree_weights(
  );
#pragma warning( pop )

  // Result conversion.

    mxArray *__converted_return_value;
    {
      // Create array.
      mwSize ndim = 2;
      mwSize shape[ 2 ];
      shape[0] = 1;
      shape[1] = libfunc_result.size();
      mxClassID classid = mxSINGLE_CLASS;
      __converted_return_value = mxCreateNumericArray(ndim, shape, classid, mxREAL);
      // Copy the values.
      float *_dptr = &(libfunc_result[0]);
      float *_iptr = reinterpret_cast<float*>(mxGetData(__converted_return_value));
      for (std::size_t i = 0; i < libfunc_result.size(); ++i) {
        _iptr[i] = _dptr[i];
      }
    }        
  return __converted_return_value;
}		


          int eqForest_f_f_uint_fv_fv (void *__instance,

        void * rhs
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
  // From C types conversions.

    auto __shptr_rhs = *reinterpret_cast<std::shared_ptr<fertilized::Forest<float, float, uint, std::vector<float>, std::vector<float>>>*>(rhs);
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


          void saveForest_f_f_uint_fv_fv (void *__instance,

        char* filename
) {
  // Unpack instance.
  auto __instance_unpacked = *static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(__instance);
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
void delete_Forest_f_f_uint_fv_fv(void *ptr) {
  auto * storage = static_cast<std::shared_ptr<Forest<float,float,uint,std::vector<float>,std::vector<float>>>*>(ptr);
  delete storage;
}
