/* Author: Christoph Lassner. */
#pragma once
#ifndef PYFERTILIZED_UTIL_H_
#define PYFERTILIZED_UTIL_H_

#include <type_traits>
#include <vector>
#include <set>

#pragma warning(push, 0)
#include <fertilized/ndarray/bp/auto.h>
#pragma warning(pop)

#include "./global.h"

namespace pyfertilized {
static std::set<std::string> REGISTERED_TOP_VEC_TYPES;
static std::set<std::string> REGISTERED_FROP_VEC_TYPES;

/**
 * \brief Python sequence to and from std::vector converter.
 *
 * Extended and corrected implementation from
 * http://bazaar.launchpad.net/~yade-dev/yade/trunk/view/head:/py/wrapper/customConverters.cpp#L127.
 */
template <typename containedType>
struct custom_vector_from_seq {
  custom_vector_from_seq() {
    // Duplicate converter registry is not allowed, hence only register 
    // converters if they have not been registered before.
    if (REGISTERED_TOP_VEC_TYPES.find(typeid(containedType).name()) ==
                                      REGISTERED_TOP_VEC_TYPES.end()) {
      // Insert converter from C++ to Python.
      py::converter::registry::insert(
        (boost::python::converter::to_python_function_t)&std_vector_to_py_list,
        py::type_id<std::vector<containedType>>());
      REGISTERED_TOP_VEC_TYPES.insert(typeid(containedType).name());
    }
    if (REGISTERED_FROP_VEC_TYPES.find(typeid(containedType).name()) ==
                                       REGISTERED_FROP_VEC_TYPES.end()) {
      // Insert converter from Python to C++.
      py::converter::registry::push_back(&convertible,
                                         &construct,
                                         py::type_id<std::vector<containedType>>());
      REGISTERED_FROP_VEC_TYPES.insert(typeid(containedType).name());
    }
  }

  static PyObject* std_vector_to_py_list(const std::vector<containedType>& v) {
    py::object ret_list(py::handle<>(PyList_New(v.size())));
    for (std::size_t index = 0; index < v.size(); ++index) {
      py::object tmpobj(v[index]);
      // PyList_SetItem steals a reference.
      if (PyList_SetItem(ret_list.ptr(), index, py::incref(tmpobj.ptr()))) {
        PyErr_SetString(PyExc_ValueError, "Could not create Python list!");
        py::throw_error_already_set();
      };
    }
    // The py::object is destroyed, but the reference returned to Python,
    // so make sure that the object lives.
    return py::incref(ret_list.ptr());
  }

  static void* convertible(PyObject* obj_ptr){
    // The second condition is important, for some reason otherwise there were
    // attempted conversions of Body to list which failed afterwards.
    if(!PySequence_Check(obj_ptr) || !PyObject_HasAttrString(obj_ptr,"__len__")) return 0;
    return obj_ptr;
  }

  static void construct(PyObject* obj_ptr, py::converter::rvalue_from_python_stage1_data* data){
     // Initialize storage.
     void* storage=((py::converter::rvalue_from_python_storage<std::vector<containedType> >*)(data))->storage.bytes;
     new (storage) std::vector<containedType>();
     std::vector<containedType>* v = (std::vector<containedType>*)(storage);
     // Get the sequence size.
     Py_ssize_t l = PySequence_Size(obj_ptr);
     if (l < 0) {
       abort();
     }
     //std::cerr<<"l="<<l<<"; "<<typeid(containedType).name()<<std::endl;
     v -> reserve(static_cast<std::size_t>(l));
     for(Py_ssize_t i = 0; i < l; ++i) {
       py::object tmp_obj(py::handle<>(PySequence_GetItem(obj_ptr, i)));
       py::extract<containedType> extractor(tmp_obj.ptr());
       if (extractor.check()) {
         v -> push_back(extractor());
       } else {
         PyErr_SetString(PyExc_ValueError, ("Object at sequence position " +
           std::to_string(i) + " can not be converted to target type " +
           typeid(containedType).name() + "!").c_str());
         py::throw_error_already_set();
       }
     }
     data->convertible=storage;
  }
};

template <typename T>
bool ne_from_eq(const T &self, const T &other) {
  return !(self == other);
};

}  // namespace pyfertilized
#endif  // PYFERTILIZED_UTIL_H_