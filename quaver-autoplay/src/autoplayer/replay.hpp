#pragma once

namespace autoplayer {
  struct replay_autoplay_frame_type {
    enum { press, release };
  };

  struct replay_key_press_state {
    enum { k1 = 1 << 0, k2 = 1 << 1, k3 = 1 << 2, k4 = 1 << 3, k5 = 1 << 4, k6 = 1 << 5, k7 = 1 << 6, k8 = 1 << 7, k9 = 1 << 8 };

    static auto key_press_state_to_lanes(int keys) {
      std::vector<int> lanes;
      if (keys & k1)
        lanes.push_back(0);
      if (keys & k2)
        lanes.push_back(1);
      if (keys & k3)
        lanes.push_back(2);
      if (keys & k4)
        lanes.push_back(3);
      if (keys & k5)
        lanes.push_back(4);
      if (keys & k6)
        lanes.push_back(5);
      if (keys & k7)
        lanes.push_back(6);
      if (keys & k8)
        lanes.push_back(7);
      if (keys & k9)
        lanes.push_back(8);
      return lanes;
    }

    static auto key_lane_to_press_state(int lane) { return (int)(1 << (lane - 1)); }
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