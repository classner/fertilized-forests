/* Author: Christoph Lassner. */
#pragma  once
#ifndef UTILITY_TIMEIT_H_
#define UTILITY_TIMEIT_H_

#include <chrono>
#include <algorithm>
#include <limits>

namespace Utility {
  /**
   * \brief Functor to time.
   *
   * Must return an int dependent on the function's result.
   * It may be a meaningless value, but must be returned to avoid compiler
   * optimization of a side-effect-less statement in a loop.
   * (also see http://stackoverflow.com/questions/1152333/force-compiler-to-not-optimize-side-effect-less-statements).
   */
  struct ITimefunc {
    virtual ~ITimefunc() {}
    virtual int operator()() = 0;
  };

  // The limit of 5000 is a conservative limit based on the list on
  // http://www.boost.org/doc/libs/1_54_0/libs/timer/doc/cpu_timers.html.
  const std::chrono::nanoseconds MIN_CPU_RESOLUTION(5000);

  /**
   * \brief IPython style timeit measurement interface.
   * 
   * It automagically takes most important things into account for getting
   * a good timing estimate. Considered as very important are:
   * (1) Do a measurement of time of an event that is at least 100 times
   *     longer than the CPU time resolution. The method determines if the
   *     function to measure has a shorter execution time and will execute
   *     it in batches that are long enough, dividing the measured time by
   *     batch size. The CPU resolution is hard-coded as 5000ns, which is
   *     a conservative value based on
   *     http://www.boost.org/doc/libs/1_54_0/libs/timer/doc/cpu_timers.html.
   *     It can be changed in the source.
   * (2) Run multiple times. The function is run at least 3 times 
   *     (adjustable) and an average is taken. The amount of executions is
   *     chosen such that it is close to take in total one second (adjustable)
   *     or at least the specified minimum amount of times.
   * (3) Run on release builds. This must be taken into account by the user.
   * 
   * Because of compiler optimizations side-effect-less statements are
   * removed from loops. This is why the functor should return an int value
   * that is somehow derived from the functions result, but can
   * be absolutely meaningless. It is used internally to increment a dummy
   * counter during execution to ensure that the function is called properly.
   *
   * \param U Duration unit of the return value, e.g. std::chrono::milliseconds.
   * \param function The function to measure.
   * \param return_min Whether to return the best or the mean value of observed
   *          function executions (maybe still an average of batch executions)
   * \param number_of_seconds_to_approximate The target duration it shall take
   *          for all iterations of the functions to execute to make the
   *          measurement. The second unit here gives a lower bound, which
   *          is reasonable, since this duration should be quite a little
   *          larger than the function execution time (otherwise it is always
   *          just executed min_number_of_repetitions times. If for a specific
   *          applications smaller timeslots are necessary, adjust the code
   *          accordingly.
   */
  template <typename U>
  float timeit(ITimefunc *function, const bool &return_min=false,
               const unsigned int &min_number_of_repetitions=3,
               const unsigned int &number_of_seconds_to_approximate=2) {
    namespace cr = std::chrono;
    // Get now.
    auto measure_start = cr::high_resolution_clock::now();
    int dummy_count = (*function)();
    // Get the elapsed time for one function call, just to get an impression
    // of the function's complexity.
    auto diff = cr::high_resolution_clock::now() - measure_start;
    auto elapsed_for_one = cr::duration_cast<cr::nanoseconds>(diff);

    // Determine how often the time should be measured. The given value
    // is the minimum number of iterations that will be done.
    auto num_iterations = static_cast<cr::high_resolution_clock::rep>(
                                                min_number_of_repetitions);
    // This is actually more than one second, but has been determined to
    // result in much more accurate values.
    cr::seconds time_to_approximate(number_of_seconds_to_approximate);

    // If the tested function can be executed too quickly for the timer
    // resolution, the results are not representative. Avoid this by
    // doing batch execution.
    // Determine the batch size to be big enough to have a batch fill at least
    // 100 * the minimum cpu resolution.
    unsigned int batch_iterations = 1;
    // It can happen that during the first measurement the CPU was very busy
    // and it took very long. In this case, the measurement could have taken
    // more than 100 * MIN_CPU_RESOLUTION, though the function needs in
    // reality less than 1 * MIN_CPU_RESOLUTION. In this case, this while
    // loop will not do anything and all measurements later on can be zero.
    // To avoid this, if one batch measurement is zero, the algorithm jumps
    // back to this place, to readjust the batch size.
START_BATCH_MEASURE:
    while (elapsed_for_one < 100 * MIN_CPU_RESOLUTION) {
      batch_iterations *= 2;
      measure_start = cr::high_resolution_clock::now();
      for (unsigned int i = 0; i < batch_iterations; ++i) {
        dummy_count += (*function)();
      }
      elapsed_for_one = cr::duration_cast<cr::nanoseconds>(
                            cr::high_resolution_clock::now() - measure_start);
    }
    // Now elapsed_for_one contains the measurement length for one batch
    // execution of batch_iterations.
    // Determine how often the function batches should be executed in powers
    // of ten to approximate the execution length.
    num_iterations = static_cast<cr::high_resolution_clock::rep>(
      pow(10, floor(log10(static_cast<double>(
      std::max(num_iterations, time_to_approximate / elapsed_for_one))))));

    // Use Donald Knuth's running mean algorithm or determine the min.
    float m = (return_min ? std::numeric_limits<float>::max() : 0.f);
    for (unsigned int i = 0; i < num_iterations; ++i) {
      measure_start = cr::high_resolution_clock::now();
      // Execute one batch.
      for (unsigned int j = 0; j < batch_iterations; ++j)
        dummy_count += (*function)();
      diff = cr::high_resolution_clock::now() - measure_start;
      float current_timing = 
        static_cast<float>(cr::duration_cast<U>(diff).count()) /
            static_cast<float>(batch_iterations);
      // This is a clear indication that the batch size is far too small and
      // has been determined as a result of a very bad measurement. Adjust
      // the batch size and restart measuring.
      if (diff < MIN_CPU_RESOLUTION) {
        elapsed_for_one = cr::nanoseconds::zero();
        goto START_BATCH_MEASURE;
      }
      // Determine the required average or min value.
      if (return_min) {
        m = std::min(m, current_timing);
      } else {
        m += (current_timing - m) / (static_cast<float>(i) + 1.f);
      }
    }
    return m;
  };
};  // namespace utility

#endif  // UTILITY_TIMEIT_H_
