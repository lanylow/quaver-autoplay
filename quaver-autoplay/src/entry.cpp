#include "include.hpp"

void autoplayer_thread() {
  AllocConsole();
  freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

  sdk::quaver_game quaver_game(*reinterpret_cast<uintptr_t*>(memory::pattern_scan("48 B9 ?? ?? ?? ?? ?? ?? ?? ?? 33 C0 48 89 01 48 B9 ?? ?? ?? ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 89 45 F8") + 2));

  while (true) {
    if (quaver_game.gameplay_screen->is_loaded()) {
      sdk::qua map = quaver_game.gameplay_screen->current_map();
      std::printf("Playing %s - %s [%s] by %s\n", map.artist.c_str(), map.title.c_str(), map.difficulty.c_str(), map.creator.c_str());

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

bool __stdcall DllMain(void* instance, int reason, void* reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}