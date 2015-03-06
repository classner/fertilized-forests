/* Author: ... */
#ifndef FERTILIZED_OBJECT_TEMPLATE_H
#define FERTILIZED_OBJECT_TEMPLATE_H

// Concerning the filename:
// the filename MUST be exactly the lower-case object name, e.g.,
// for an object called ObjectTemplate, it must reside in objecttemplate.h,
// it its an object called Object_Template, it must reside in object_template.h!

// Include, to get all library dependent global definitions, etc.
// Depending on where you put the object header file, you have to
// adjust the relative path to 'global.h'.
#include "./global.h"

// Only pull in the dependency if necessary.
#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#endif

// C and C++ includes, e.g.,
#include <vector>
// The basic library types. If you need forward declarations for the header
// only library layout, include "./fertilized_fwd.h". This file is auto-
// generated and kept up-to-date with all library types.
#include "./types.h"
// Library includes.
#include "./data_providers/unchangedfdataprovider.h"
// If your objects should be serializable:
#include "./serialization/serialization.h"
// If your object works with the array class:
#include "./ndarray.h"

namespace fertilized {
  /**
   * Object template.
   *
   * After having described the object, add a section like the following
   * to specify in which interfaces the object should be available, and, if it
   * is templated, which instantiations of the object. The instantiations are
   * ;-separated lists of the C++ types to use.
   *
   * To start and end this section, use exactly -----. End the lists with a dot
   * and add an empty line after the last list. This is not due to our parser,
   * but due to doxygen. It is required to get a meaningful rendering for the
   * documentation.
   *
   * Use exactly the library template names `input_dtype`, `feature_dtype`,
   * `annotation_dtype`, `leaf_return_dtype`, `forest_dtype` for your
   * objects as necessary (you may omit unnecessary ones). If your class is 
   * templated differently, only one possible
   * template instantiation can be used for the interfaces. In that case, you
   * have to specify this with a parser list "Soil type always:". You can find
   * an example for this in impurities/shannonentropy.h.
   *
   * The specification of the "Serialization generation:" is important if you
   * want to serialize your object and remain compatible to older versions
   * of the library. Specify the number as the version number of the library
   * in hundreds format (e.g., 1.00 as 100) plus one
   * (e.g., if the current library version is 1.01, use 102). Your self-
   * compiled library version with the additional object will be backwards
   * compatible with all lower library versions. Increase the library version in
   * the file 'global.h' to the same value!
   *
   * IMPORTANT: you HAVE to adjust the `Serializaton generation:` version number
   * and the library version in 'global.h' to serialize your object and
   * maintain backwards compatibility!
   *
   * -----
   * Available in:
   * - C++
   * - Python
   * - Matlab
   * .
   * Instantiations:
   * - int; int; uint; std::vector<float>; std::vector<float>
   * - float; float; uint; std::vector<float>; std::vector<float>
   * .
   * Serialization generation: 100
   *
   * -----
   */
  template <typename input_dtype, typename feature_dtype, typename annotation_dtype, typename leaf_return_dtype, typename forest_return_dtype>
  class ObjectTemplate {
   public:
    /**
     * For every method, including the constructor, you can specify a
     * list of interfaces in which the method should be exported. Add the
     * description of the parameters after the specification (this is again
     * just to get nice doxygen results). Parameter conversion code for method
     * arguments is generated automatically for
     * - all plain C++ types,
     * - vectors of these types,
     * - 'Array's,
     * - vectors of 'Array's,
     * - library objects,
     * - vectors of library objects.
     *
     * Return types may be
     * - all plain C++ types,
     * - vectors of these types,
     * - 'Array's,
     * - library objects (not available for Matlab!),
     * - vectors of library objects (not available for Matlab!).
     *
     * Remember to run `scons --generate-interfaces` to update all language
     * interfaces after a change to your class specification. This also requires
     * compilation.
     *
     * -----
     * Available in:
     * - C++
     * - Python
     * - Matlab
     * .
     *
     * -----
     *
     * \param example_param uint > 0
     *    An example parameter to illustrate the documentation.
     */
    ObjectTemplate(const uint &example_param)
      : example_property(example_param) {};

    // Keep the serialization encapsulated.
#ifdef SERIALIZATION_ENABLED
    // Give boost serialization access to all object properties.
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const uint file_version) {
      // If the object inherits from another object, add
      // ar & boost::serialization::base_object<TheBaseClass>(*this);
      // Serialize all relevant properties.
      ar & example_property;
    }
#endif

   protected:
    // All classes MUST have a parameterless constructor that is at least
    // 'protected' (not private) for deserialization purposes.
    ObjectTemplate() {}

   private:
    // If uncommented, forbids copying.
    DISALLOW_COPY_AND_ASSIGN(ObjectTemplate);

    unsigned int example_property;
  };
};  // namespace fertilized
#endif // FERTILIZED_OBJECT_TEMPLATE_H
