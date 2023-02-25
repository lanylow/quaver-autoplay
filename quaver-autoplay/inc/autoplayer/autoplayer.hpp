#pragma once

namespace autoplayer {
  void run(sdk::quaver_game& quaver_game, autoplayer::replay& rep);
  int get_nearest_frame(autoplayer::replay& rep, double time);
  int get_key_by_lane_index(int key_count, int lane_index);
  void simulate_key(int key_code, int type);
  autoplayer::replay generate_auto_replay(sdk::qua& map);

  // You have to change these keycodes based on your settings in game
  static short key_config[11] = {
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