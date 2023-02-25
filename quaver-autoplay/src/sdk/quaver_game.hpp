#pragma once

namespace sdk {
  class quaver_game : public object {
  public:
    sdk::gameplay_screen* gameplay_screen;

    quaver_game(unsigned long long base_pointer) : object(base_pointer, 0) { set_childs({ gameplay_screen = new sdk::gameplay_screen(0x128) }); }
  };
} // namespace sdk