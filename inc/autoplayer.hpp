#pragma once

namespace autoplayer {
  struct frame_type {
    enum { press, release };
  };

  struct frame_t {
    int time;
    int lane;
    int type;

    frame_t(int time, int lane, int type) : time(time), lane(lane), type(type) { }

    bool operator<(const autoplayer::frame_t& other) const {
      return time < other.time;
    }
  };

  void run(sdk::quaver_game& quaver_game, std::vector<autoplayer::frame_t>& frames);
  std::vector<autoplayer::frame_t> generate_frames(sdk::qua& map);

  int get_key_by_lane_index(int key_count, int lane_index);
  void simulate_key(int key_code, int type);

  // You have to change these keycodes based on your settings in game
  static int key_config[11] = {
      0x41, // key_mania_4k1 (A)
      0x53, // key_mania_4k2 (S)
      0x4B, // key_mania_4k3 (K)
      0x4C, // key_mania_4k4 (L)

      0x41, // key_mania_7k1 (A)
      0x53, // key_mania_7k2 (S)
      0x44, // key_mania_7k3 (D)
      0x20, // key_mania_7k4 (SPACE)
      0x4A, // key_mania_7k5 (J)
      0x4B, // key_mania_7k6 (K)
      0x4C  // key_mania_7k7 (L)
  };
} // namespace autoplayer