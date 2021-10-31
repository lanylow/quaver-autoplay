#pragma once

namespace sdk {
  struct hit_object_data_t {
    int start_time;
    int end_time;
    int key_lane;
    bool is_long_note() { return end_time > 0; }
  };
} // namespace sdk