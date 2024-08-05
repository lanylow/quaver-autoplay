#pragma once

namespace sdk {
  class list {
  public:
    explicit list(uintptr_t pointer) {
      address = *(uintptr_t*)(pointer);
    }

    int size() { 
      return *(int*)(get_array() + 0x8); 
    }

    uintptr_t operator[](int i) {
      return *(uintptr_t*)(get_array() + 0x10 + 0x8 * i);
    }

  private:
    uintptr_t get_array() const {
      return *(uintptr_t*)(address + 0x8);
    }

    uintptr_t address = 0;
  };
} // namespace sdk