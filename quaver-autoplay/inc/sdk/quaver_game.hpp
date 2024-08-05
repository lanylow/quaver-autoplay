#pragma once

namespace sdk {
  class quaver_game : public sdk::object {
  public:
    explicit quaver_game(uintptr_t base_pointer) : sdk::object(base_pointer, 0) {
      set_children({
        gameplay_screen = new sdk::gameplay_screen(0x128) 
      }); 
    }

    sdk::gameplay_screen* gameplay_screen;
  };
} // namespace sdk