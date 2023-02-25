#include "../include.hpp"

autoplayer::replay autoplayer::generate_auto_replay(sdk::qua &map) {
  std::vector<replay_autoplay_frame> non_combined;

  for (auto &object : map.hit_object_data) {
    non_combined.push_back({(int)(object.start_time), replay_autoplay_frame_type::press, replay_key_press_state::key_lane_to_press_state(object.key_lane), object});

    if (object.is_long_note())
      non_combined.push_back({(int)(object.end_time - 1), replay_autoplay_frame_type::release, replay_key_press_state::key_lane_to_press_state(object.key_lane), object});
    else
      non_combined.push_back({(int)(object.start_time + 30), replay_autoplay_frame_type::release, replay_key_press_state::key_lane_to_press_state(object.key_lane), object});
  }

  std::sort(non_combined.begin(), non_combined.end(), [](replay_autoplay_frame lhs, replay_autoplay_frame rhs) { return lhs.time < rhs.time; });

  replay rep;
  rep.game_mode = map.game_mode;
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

void autoplayer::run(sdk::quaver_game &quaver_game, replay &rep) {
  auto last_time = quaver_game.gameplay_screen->gameplay_audio_timing->time();
  int key_count = rep.game_mode == sdk::game_mode::keys4 ? 4 : 7;

  std::vector<int> replay_keys;
  for (auto i = 0; i < key_count; i++)
    replay_keys.push_back(i);

  int index = get_nearest_frame(rep, quaver_game.gameplay_screen->gameplay_audio_timing->time());
  while (quaver_game.gameplay_screen->is_loaded() && index < rep.frames.size()) {
    auto current_time = quaver_game.gameplay_screen->gameplay_audio_timing->time();
    if (abs(current_time - last_time) >= 50)
      break;

    last_time = current_time;
    if (current_time >= rep.frames[index].time) {
      auto key_state = replay_key_press_state::key_press_state_to_lanes(rep.frames[index].keys);
      for (auto &i : replay_keys) {
        int key = get_key_by_lane_index(key_count, i);
        if (std::count(key_state.begin(), key_state.end(), i))
          simulate_key(key, 0);
        else
          simulate_key(key, KEYEVENTF_KEYUP);
      }

      index++;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  for (auto i = 0; i < key_count; i++)
    simulate_key(get_key_by_lane_index(key_count, i), KEYEVENTF_KEYUP);
}

int autoplayer::get_nearest_frame(replay &rep, double time) {
  for (int i = (int)rep.frames.size() - 1; i >= 0; i--)
    if (rep.frames[i].time <= time)
      return i;
  return 0;
}

int autoplayer::get_key_by_lane_index(int key_count, int lane_index) {
  if (key_count == 4)
    return key_config[lane_index];
  else if (key_count == 7)
    return key_config[lane_index + 4];
  else
    return 0x20;
}

void autoplayer::simulate_key(int key_code, int type) {
  INPUT input;
  input.type = INPUT_KEYBOARD;
  input.ki.wScan = MapVirtualKeyA(key_code, 0);
  input.ki.time = 0;
  input.ki.dwExtraInfo = 0;
  input.ki.wVk = key_code;
  input.ki.dwFlags = type | KEYEVENTF_SCANCODE;
  SendInput(1, &input, sizeof(INPUT));
}