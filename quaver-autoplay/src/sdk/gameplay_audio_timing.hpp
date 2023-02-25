#pragma once

namespace sdk {
  class gameplay_audio_timing : public object {
  public:
    gameplay_audio_timing(unsigned long long offset) : object(offset) {}

    double time() { return *(double*)(get_base() + 0x10); }
  };
} // namespace sdk