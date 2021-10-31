#include "include.hpp"

void autoplayer_thread() {
  AllocConsole();
  freopen_s((FILE **)(stdout), "CONOUT$", "w", stdout);

  sdk::quaver_game quaver_game(
      *(unsigned long long *)(memory::pattern_scan("48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8B 12 48 8B 92 ?? ?? ?? ?? 4C 8B 81 ?? ?? ?? ?? 4C 8D 89") + 2));

  while (true) {
    if (quaver_game.gameplay_screen->is_loaded()) {
      sdk::qua_t map = quaver_game.gameplay_screen->current_map();
      printf("%s - %s [%s] by %s\n", map.artist.c_str(), map.title.c_str(), map.difficulty.c_str(), map.creator.c_str());
      for (auto &object : map.hit_object_data)
        printf("start_time: %d, end_time: %d, key_lane: %d\n", object.start_time, object.end_time, object.key_lane);
      break;
    }
  }
}

bool __stdcall DllMain(void *instance, int reason, void *reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}