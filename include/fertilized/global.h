/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_GLOBAL_H_
#define FERTILIZED_GLOBAL_H_

#include "fertilized/version.h"

#ifdef PYTHON_ENABLED
// This inclusion must be done before certain system header to avoid nasty
// redefines. It must be the boost version, because otherwise under Windows
// usually the debug build breaks because of the not provided python27_d.lib.
#include <boost/python/detail/wrap_python.hpp>
// Fix a boost Python pointer issue with older versions of Boost and clang.
// Does not happen on the apple clang builds.
#if (BOOST_VERSION < 105300 || defined BOOST_NO_CXX11_SMART_PTR) && !defined(__APPLE__) && defined(__clang__)
#include <memory>
namespace boost {
  template<class T> const T* get_pointer(std::shared_ptr<T> const& p) {
    return p.get();
  }

  template<class T> T* get_pointer(std::shared_ptr<T>& p)  {
    return p.get();
  }
} // namespace boost
#endif  // BOOST_VERSION < 105300 || defined BOOST_NO_CXX11_SMART_PTR
#endif  // PYTHON_ENABLED

//#define DISABLE_DYNAMIC

#if ! (defined NDEBUG) && defined(_MSC_VER)
// Solve a MSVC specific name clash between WinDef.h and <algorithm> :(
// See http://www.suodenjoki.dk/us/archive/2010/min-max.htm.
#define NOMINMAX
#include <Windows.h>
#endif

#include <string>

// If wanted, you can enable serialization by setting the compiler define
// SERIALIZATION_ENABLED. This adds a dependency to the boost serialization
// project.

// Use 64-bit aligned memory for faster computations.
#define mmalloc(size) mkl_malloc(size, 64)
#define ffree(space) mkl_free(space)

// The library version (as used for boost serialization) Must be <=255.
#define FERTILIZED_VERSION_COUNT 1

// A define that makes it easier to find forbidden calls to pure virtual
// functions in debugging mode.
#if defined(NDEBUG) || !defined(_MSC_VER)
  #define VIRTUAL(type) =0
  #define VIRTUAL_VOID =0
  #define VIRTUAL_PTR =0
#else
  #define VIRTUAL(type) { DebugBreak(); return type();}
  #define VIRTUAL_VOID { DebugBreak(); }
  #define VIRTUAL_PTR { DebugBreak(); return nullptr; }
#endif

/**
 * A macro to disallow the copy constructor and operator= functions
 * This should be used in the private: declarations for a class
 * see http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml.
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

/// @cond
// Declare the ndarray namespace for later use.
namespace ndarray { }
namespace boost { namespace python {} }
/// @endcond

namespace fertilized {
#ifdef PYTHON_ENABLED
  namespace py = boost::python;
#endif

  using namespace ndarray;

  // This library's exception type.
  class Fertilized_Exception: public std::exception {
   public:
    explicit Fertilized_Exception(const std::string &what)
      : whatstr(what) {}

    virtual const char* what() const throw() {
      return whatstr.c_str();
    };

    virtual ~Fertilized_Exception() throw() {};

   private:
    const std::string whatstr;
  };
}  // namespace fertilized

// The following compiles ONLY exclusively as
// data.template getSize<1>() with gcc, and
// data.getSize<1>() with MSVC. :(
#ifdef _MSC_VER
#define TPLMETH
#else
#define TPLMETH template
#endif

#if defined RUNTIME_CHECKS && defined _MSC_VER
#define FASSERT(condition)                                                    \
  if (!(condition))                                                           \
    DebugBreak();
#else
#define FASSERT(condition)
#endif

// Library exports.
#if !defined(_MSC_VER)
#define DllExport
#elif __BUILD_FERTILIZED_LIBRARY
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#ifdef __BUILD_FERTILIZED_LIBRARY
#define TemplateExport template class
#define TemplateFuncExport template
#define ExportVar
#else
#define TemplateExport extern template class
#define TemplateFuncExport extern template
#define ExportVar extern
#endif

#endif  // FERTILIZED_GLOBAL_H_
