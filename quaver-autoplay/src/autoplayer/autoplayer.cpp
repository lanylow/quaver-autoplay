#include "../include.hpp"

autoplayer::replay autoplayer::generate_auto_replay(sdk::qua &map) {
  std::vector<replay_autoplay_frame> non_combined;

  for (auto &object : map.hit_object_data) {
    non_combined.push_back({object.start_time, replay_autoplay_frame_type::press, replay_key_press_state::key_lane_to_press_state(object.key_lane), object});

    if (object.is_long_note())
      non_combined.push_back(
          {object.end_time - 1, replay_autoplay_frame_type::release, replay_key_press_state::key_lane_to_press_state(object.key_lane), object});
    else
      non_combined.push_back(
          {object.start_time + 30, replay_autoplay_frame_type::release, replay_key_press_state::key_lane_to_press_state(object.key_lane), object});
  }

  std::sort(non_combined.begin(), non_combined.end(), [](replay_autoplay_frame lhs, replay_autoplay_frame rhs) { return lhs.time < rhs.time; });

  replay rep;
  rep.frames.push_back({-10000, 0});

  std::map<int, std::vector<replay_autoplay_frame>> start_time_group;
  for (auto &frame : non_combined)
    start_time_group[frame.time].push_back(frame);

  int state = 0;
  for (auto &item : start_time_group) {
    for (auto &frame : item.second) {
      switch (frame.type) {
      case replay_autoplay_frame_type::press: {
        state |= replay_key_press_state::key_lane_to_press_state(frame.object.key_lane);
      } break;
      case replay_autoplay_frame_type::release: {
        state -= replay_key_press_state::key_lane_to_press_state(frame.object.key_lane);
      } break;
      }
    }
    rep.frames.push_back({item.first, state});
  }

  return rep;
}