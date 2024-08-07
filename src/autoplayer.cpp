#include "include.hpp"

void autoplayer::run(sdk::quaver_game& quaver_game, std::vector<autoplayer::frame_t>& frames) {
  auto key_count = std::max_element(frames.begin(), frames.end(), [](auto lhs, auto rhs) {
    return lhs.lane < rhs.lane;
  })->lane;

  auto index = 0ull;

  while (quaver_game.gameplay_screen->is_loaded() && index < frames.size()) {
    auto current_time = quaver_game.gameplay_screen->gameplay_audio_timing->time();

    while (index < frames.size() && frames[index].time <= current_time) {
      auto key = autoplayer::get_key_by_lane_index(key_count, frames[index].lane);
      auto press = frames[index].type == frame_type::press;

      autoplayer::simulate_key(key, press ? 0 : KEYEVENTF_KEYUP);

      index++;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  for (auto i = 0; i < key_count; i++)
    autoplayer::simulate_key(autoplayer::get_key_by_lane_index(key_count, i), KEYEVENTF_KEYUP);
}

std::vector<autoplayer::frame_t> autoplayer::generate_frames(sdk::qua& map) {
  if (map.hit_object_data.empty())
    return { };

  std::vector<autoplayer::frame_t> frames;
  frames.reserve(map.hit_object_data.size() * 2);

  for (auto& object : map.hit_object_data) {
    if (!object.is_long_note())
      object.end_time = object.start_time + 30;

    frames.emplace_back(object.start_time, object.key_lane, frame_type::press);
    frames.emplace_back(object.end_time, object.key_lane, frame_type::release);
  }

  std::sort(frames.begin(), frames.end());

  return frames;
}

int autoplayer::get_key_by_lane_index(int key_count, int lane_index) {
  if (key_count == 4)
    return key_config[--lane_index];
  else if (key_count == 7)
    return key_config[--lane_index + 4];
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