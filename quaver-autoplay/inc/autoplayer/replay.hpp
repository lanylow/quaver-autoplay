#pragma once

namespace autoplayer {
  struct replay_autoplay_frame_type {
    enum { press, release };
  };

  struct replay_key_press_state {
    enum { k1 = 1 << 0, k2 = 1 << 1, k3 = 1 << 2, k4 = 1 << 3, k5 = 1 << 4, k6 = 1 << 5, k7 = 1 << 6, k8 = 1 << 7, k9 = 1 << 8 };

    static std::vector<int> key_press_state_to_lanes(int keys);
    static int key_lane_to_press_state(int lane);
  };

  struct replay_autoplay_frame {
    int time;
    int type;
    int keys;
    sdk::hit_object_data_t object;
  };

  struct replay_frame {
    int time;
    int keys;
  };

  struct replay {
    int game_mode;
    std::vector<replay_frame> frames;
  };
} // namespace autoplayer