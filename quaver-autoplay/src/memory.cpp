#include <include.hpp>

uintptr_t memory::pattern_scan(const char* pattern, size_t len) {
  MEMORY_BASIC_INFORMATION mbi;
  auto address = 0ull;

  while (VirtualQuery((void*)(address), &mbi, sizeof(mbi))) {
    address = (uintptr_t)(mbi.BaseAddress) + mbi.RegionSize;

    if (mbi.State != MEM_COMMIT || mbi.Protect != PAGE_EXECUTE_READWRITE)
      continue;

    auto start = (uintptr_t)(mbi.BaseAddress);
    auto buffer = (const char*)(start);

    for (auto i = 0; i < mbi.RegionSize; i++) {
      auto found = true;

      for (auto j = 0; j < len && found; j++)
        if (pattern[j] != 0x00 && buffer[i + j] != pattern[j])
          found = false;

      if (found)
        return start + i;
    }
  }

  return 0;
}