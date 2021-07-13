#pragma once
#ifndef _TIMER_HPP_
#define _TIMER_HPP_

/////////////////////////////////////////////////
//////////////////// Headers ////////////////////
/////////////////////////////////////////////////

#include <chrono>

namespace EngineSupport
{
	class Timer
	{
	protected:
		using clock_t = std::chrono::high_resolution_clock;
		using second_t = std::chrono::duration<double, std::ratio<1>>;

		std::chrono::time_point<clock_t> m_beg;
	public:
		Timer() : m_beg{ clock_t::now() }
		{
		}
		void reset() noexcept { m_beg = clock_t::now(); }
		virtual double elapse() const noexcept { return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count(); }
	};
}

#endif // _TIMER_HPP_