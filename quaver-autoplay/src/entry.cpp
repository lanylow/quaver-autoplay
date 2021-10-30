#include "include.hpp"

void autoplayer_thread() {
  AllocConsole();
  freopen_s((FILE **)(stdout), "CONOUT$", "w", stdout);

  sdk::quaver_game quaver_game(
      *(unsigned long long *)(memory::pattern_scan("48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8B 12 48 8B 92 ?? ?? ?? ?? 4C 8B 81 ?? ?? ?? ?? 4C 8D 89") + 2));

  while (true) {
    if (quaver_game.gameplay_screen->is_loaded()) {
      printf("time: %d\n", (int)quaver_game.gameplay_screen->gameplay_audio_timing->time());
      std::this_thread::yield();
    }
  }
}

bool __stdcall DllMain(void *instance, int reason, void *reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}