/***********************************************************************
FILE CTIMER.H CONTAINS SIMPLE TIMER IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (25.12.2019) BY ARTUR K. 
***********************************************************************/

#ifndef UH_TIMER_HPP__
#define UH_TIMER_HPP__

#include "TimeTypes.hpp"

// C++
#include <cstdint>

namespace UH
{

/**
 * @class CTimer
 * @brief Based on std::chrono::high_resolution_clock clock.
 * 
 * @note Conversion units:
 * 1s = 1000ms 		(milli-seconds)
 * 1s = 1000000us 	(micro-seconds)
 * 1s = 1e+9ns		(nano-seconds)
 */
class CTimer
{
public:
	/// Default ctor, starts the timer.
	CTimer();

	/// Explicit call to start the timer.
	void start();

	/// Resets the timer ( calls start() internally )
	void reset();

	/// Returns elapsed time from the "start() call or timer object construction" in seconds.
	[[nodiscard]] double elapsedTimeS() const;

	/// Returns elapsed time from the "start() call or timer object construction" in milliseconds.
	[[nodiscard]] std::int64_t elapsedTimeMs() const;

	/// Returns elapsed time from the "start() call or timer object construction" in microseconds.
	[[nodiscard]] std::int64_t elapsedTimeUs() const;

	/// Returns elapsed time from the "start() call or timer object construction" in nanoseconds.
	[[nodiscard]] std::int64_t elapsedTimeNs() const;

private:
	Clock m_clock; //!< high_resolution_clock
	TimePointNs m_startTP; //!< Starting time stamp
};
} //namespace UH
#endif //UH_TIMER_HPP__
