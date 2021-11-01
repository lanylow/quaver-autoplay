#include "include.hpp"

void autoplayer_thread() {
  AllocConsole();
  freopen_s((FILE **)(stdout), "CONOUT$", "w", stdout);

  sdk::quaver_game quaver_game(
      *(unsigned long long *)(memory::pattern_scan("48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8B 12 48 8B 92 ?? ?? ?? ?? 4C 8B 81 ?? ?? ?? ?? 4C 8D 89") + 2));

  while (true) {
    if (quaver_game.gameplay_screen->is_loaded()) {
      sdk::qua map = quaver_game.gameplay_screen->current_map();
      printf("Playing %s - %s [%s] by %s\n", map.artist.c_str(), map.title.c_str(), map.difficulty.c_str(), map.creator.c_str());

      autoplayer::replay rep = autoplayer::generate_auto_replay(map);   
      while (quaver_game.gameplay_screen->is_loaded())
        autoplayer::run(quaver_game, rep);
    }
    else {
      while (!quaver_game.gameplay_screen->is_loaded())
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }
}

bool __stdcall DllMain(void *instance, int reason, void *reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}