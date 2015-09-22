/* Author: Christoph Lassner. */
#pragma once
#ifndef FERTILIZED_FEATURES_IFEATURESELECTIONGENERATOR_H_
#define FERTILIZED_FEATURES_IFEATURESELECTIONGENERATOR_H_

#ifdef SERIALIZATION_ENABLED
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#endif

#include <unordered_set>
#include <random>
#include <vector>
#include <algorithm>

#include "../global.h"
#include "../types.h"
#include "../data_providers/idataprovider.h"
#include "../util/sampling.h"

namespace fertilized {
  /** Utility class used by the \ref IFeatureSelectionGenerator s. */
  class IFeatureSelectionGenerator {
  public:
    virtual ~IFeatureSelectionGenerator() {}

    virtual bool available() const VIRTUAL(bool);

    virtual size_t max_count() const VIRTUAL(size_t);

    virtual std::vector<size_t> get_next() VIRTUAL(std::vector<size_t>);

  protected:
    IFeatureSelectionGenerator() {}

  private:
    DISALLOW_COPY_AND_ASSIGN(IFeatureSelectionGenerator);
  };
}  // namespace fertilized
#endif  // FERTILIZED_FEATURES_IFEATURESELECTIONGENERATOR_H_
