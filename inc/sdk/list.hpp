#pragma once

namespace sdk {
  template <typename item_type>
  class list {
  public:
    explicit list(uintptr_t pointer) {
      address = *(uintptr_t*)(pointer);
    }

    int size() { 
      return *(int*)(address + 0x10);
    }

    item_type operator[](int i) {
      return *(item_type*)(get_array() + 0x10 + sizeof(item_type) * i);
    }

  private:
    uintptr_t get_array() const {
      return *(uintptr_t*)(address + 0x8);
    }

    uintptr_t address = 0;
  };
} // namespace sdk