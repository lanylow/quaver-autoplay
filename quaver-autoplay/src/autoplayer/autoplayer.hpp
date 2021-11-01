#pragma once

namespace autoplayer {
  void run(sdk::quaver_game &quaver_game, replay &rep);
  int get_nearest_frame(replay &rep, double time);
  int get_key_by_lane_index(int key_count, int lane_index);
  void simulate_key(int key_code, int type);
  replay generate_auto_replay(sdk::qua &map);

  static short key_config[11] = {
      0x41, // key_mania_4k1
      0x53, // key_mania_4k2
      0x4B, // key_mania_4k3
      0x4C, // key_mania_4k4

      0x41, // key_mania_7k1
      0x53, // key_mania_7k2
      0x44, // key_mania_7k3
      0x20, // key_mania_7k4
      0x4A, // key_mania_7k5
      0x4B, // key_mania_7k6
      0x4C  // key_mania_7k7
  };
} // namespace autoplayer