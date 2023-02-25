#pragma once

namespace sdk {
  class list {
  public:
    list(unsigned long long pointer) { address = *(unsigned long long*)(pointer); }

    int size() { return *(int*)(get_array() + 0x8); }

    unsigned long long operator[](int i) { return *(unsigned long long*)(get_array() + 0x10 + 0x8 * i); }

  private:
    unsigned long long get_array() { return *(unsigned long long*)(address + 0x8); }

    unsigned long long address = 0;
  };
} // namespace sdk