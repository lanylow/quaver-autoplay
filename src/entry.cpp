#include <include.hpp>

[[noreturn]] void autoplayer_thread() {
  AllocConsole();
  freopen_s((FILE**)(stdout), "conout$", "w", stdout);

  auto ptr = *(uintptr_t*)(memory::pattern_scan("\x48\x89\x4D\x10\x48\xBA\x00\x00\x00\x00\x00\x00\x00\x00\x48\x83\x3A\x00\x74\x41", 20) + 6);
  sdk::quaver_game quaver_game(ptr);

  while (true) {
    while (!quaver_game.gameplay_screen->is_loaded())
      std::this_thread::sleep_for(100ms);

    auto map = quaver_game.gameplay_screen->current_map();
    std::printf("Playing %s - %s [%s] by %s\n", map.artist.c_str(), map.title.c_str(), map.difficulty.c_str(), map.creator.c_str());

    auto rep = autoplayer::generate_frames(map);
    while (quaver_game.gameplay_screen->is_loaded())
      autoplayer::run(quaver_game, rep);
  }
}

bool __stdcall DllMain(void* instance, int reason, void* reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}