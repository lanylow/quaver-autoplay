#include <include.hpp>

std::vector<int> autoplayer::replay_key_press_state::to_lanes(int keys) {
  std::vector<int> lanes;

  for (auto i = 1, j = 0; i <= k9; i *= 2, j++)
    if (keys & i)
      lanes.push_back(j);

  return lanes;
}

int autoplayer::replay_key_press_state::from_lane(int lane) {
  return (int)(1 << (lane - 1));
}