#ifndef TIMER_HPP
#define TIMER_HPP
#pragma once
#include <chrono>
namespace timer
{
using clock = std::chrono::steady_clock;
using time = std::chrono::time_point<clock>;
using timeFrame = std::chrono::milliseconds;
inline time now() { return timer::clock::now(); }
inline bool isTimeRemaining(const std::chrono::time_point<clock> start, const int duration) { return std::chrono::duration_cast<timeFrame>(now() - start).count() < duration; }
} // namespace timer
#endif // !TIMER_HPP