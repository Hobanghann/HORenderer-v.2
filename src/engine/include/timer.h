#ifndef _HORENDERER_ENGINE_TIMER_H_
#define _HORENDERER_ENGINE_TIMER_H_

#include <chrono>

namespace ho_renderer {
class Timer {
 public:
  Timer();
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  ~Timer();

  void SetStartTime();
  void SetLatestFrameStartTime();
  void SetTemporaryStartTime();

  long long GetMilliElapsedTime();
  long long GetMilliDeltaTime();
  long long ClampMilliDeltaTime(long long min, long long max);
  long long GetMilliTemporaryElapsedTime();

 private:
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>
      start_time_;
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>
      latest_frame_start_time_;
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds>
      temporary_start_time_;
};
}  // namespace ho_renderer
#endif  // _HORENDERER_ENGINE_TIMER_H_