#include "engine/include/timer.h"

#include "app/include/debug.h"
namespace ho_renderer {

Timer::Timer() = default;
Timer ::~Timer() = default;

void Timer::SetStartTime() { start_time_ = std::chrono::steady_clock::now(); }
void Timer::SetLatestFrameStartTime() {
  latest_frame_start_time_ = std::chrono::steady_clock::now();
}
void Timer::SetTemporaryStartTime() {
  temporary_start_time_ = std::chrono::steady_clock::now();
}

long long Timer::GetMilliElapsedTime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now() - start_time_)
      .count();
}

long long Timer::GetMilliDeltaTime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now() - latest_frame_start_time_)
      .count();
}
long long Timer::ClampMilliDeltaTime(long long min, long long max) {
  long long delta_time;
  while ((delta_time = GetMilliDeltaTime()) < min);
  if (delta_time > max) {
    return max;
  }
  return delta_time;
}

long long Timer::GetMilliTemporaryElapsedTime() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now() - temporary_start_time_)
      .count();
}
}  // namespace ho_renderer