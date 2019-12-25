/***********************************************************************
FILE CTIMER.H CONTAINS SIMPLE TIMER IMPLEMENTATION

FILE UTMOST REVIEW DONE ON (25.12.2019) BY ARTUR K. 
***********************************************************************/

#ifndef UH_TIMER_H
#define UH_TIMER_H

#include <chrono>

namespace UH
{
	typedef long long int										int64;
	typedef std::chrono::high_resolution_clock					Clock;
	typedef std::chrono::time_point<std::chrono::steady_clock>	TimePoint;

	//-----------------------------------------------------------------------
	//TIMER
	//
	//Based on std::chrono high resolution clock.
	//-----------------------------------------------------------------------

	class CTimer
	{
	public:
		CTimer();

		void start() { m_startTP = m_clock.now(); }
		void reset() { this->start(); }

		//Returns elapsed time in seconds.
		double getElapsedTimeS();

		//Returns elapsed time in milliseconds.
		int64 getElapsedTimeMs();

		//Returns elapsed time in microseconds.
		int64 getElapsedTimeUs();
	
		//Returns elapsed time in nanoseconds.
		int64 getElapsedTimeNs();
	private:
		Clock m_clock;
		TimePoint m_startTP;
		TimePoint m_endTP;
	};
} //namespace UH
#endif //UH_TIMER_H
