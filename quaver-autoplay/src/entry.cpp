#include "include.hpp"

void autoplayer_thread() {
  AllocConsole();
  freopen_s((FILE **)(stdout), "CONOUT$", "w", stdout);

  auto quaver_game_pointer = memory::pattern_scan("48 BA ?? ?? ?? ?? ?? ?? ?? ?? 48 8B 12 48 8B 92 ?? ?? ?? ?? 4C 8B 81 ?? ?? ?? ?? 4C 8D 89") + 2;
}

bool __stdcall DllMain(void *instance, int reason, void *reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}