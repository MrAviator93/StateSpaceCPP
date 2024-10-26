#include "timer.hpp"

namespace UH
{

CTimer::CTimer()
	: m_startTP( m_clock.now() )
{ }

void CTimer::start()
{
	m_startTP = m_clock.now();
}

void CTimer::reset()
{
	start();
}

double CTimer::elapsedTimeS() const
{
	return static_cast< double >( elapsedTimeUs() ) / 1'000'000.0;
}

std::int64_t CTimer::elapsedTimeMs() const
{
	return std::chrono::duration_cast< Milliseconds >( m_clock.now() - m_startTP ).count();
}

std::int64_t CTimer::elapsedTimeUs() const
{
	return std::chrono::duration_cast< Microseconds >( m_clock.now() - m_startTP ).count();
	// return std::chrono::time_point_cast< std::chrono::microseconds >( m_endTP ).time_since_epoch().count;
}

std::int64_t CTimer::elapsedTimeNs() const
{
	return std::chrono::duration_cast< Nanoseconds >( m_clock.now() - m_startTP ).count();
}

} // namespace UH
