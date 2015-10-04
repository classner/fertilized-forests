/* Author: Christoph Lassner. */
#pragma once
#ifndef PYFERTILIZED_SERIALIZATION_H_
#define PYFERTILIZED_SERIALIZATION_H_

#ifdef SERIALIZATION_ENABLED
#pragma warning(push, 0)
#include <boost/python.hpp>
#pragma warning(pop)

#include <fertilized/serialization/serialization.h>

namespace py = boost::python;
using namespace fertilized;

namespace pyfertilized {
template <typename T>
struct ParameterlessPickleSuite : py::pickle_suite {
  static py::tuple getinitargs(const T& src) {
    return py::make_tuple();
  }

  static py::object getstate (const T &src) {
    return py::str (serialize(&src, true));
  }

  static void setstate(T &dst, py::object entries) {
    py::str s = py::extract<py::str>(entries)();
    std::string st = py::extract<std::string>(s)();
    std::stringstream is (st);
    deserialize(is, &dst);
  }
};
}  // namespace pyfertilized
#endif  // SERIALIZATION_ENABLED

#endif  // PYFERTILIZED_SERIALIZATION_H_