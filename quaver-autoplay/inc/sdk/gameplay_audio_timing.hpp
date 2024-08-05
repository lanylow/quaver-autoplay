#pragma once

namespace sdk {
  class gameplay_audio_timing : public sdk::object {
  public:
    explicit gameplay_audio_timing(ptrdiff_t offset) : sdk::object(offset) { }

    double time() { 
      return *(double*)(get_base() + 0x10); 
    }
  };
} // namespace sdk