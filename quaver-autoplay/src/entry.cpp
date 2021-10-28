#include "include.hpp"

void autoplayer_thread() {}

bool __stdcall DllMain(void *instance, int reason, void *reserved) {
  if (reason == DLL_PROCESS_ATTACH)
    std::thread(autoplayer_thread).detach();
  return true;
}