#pragma once

namespace sdk {
  class gameplay_screen : public sdk::object {
  public:
    explicit gameplay_screen(ptrdiff_t offset) : sdk::object(offset) {
      set_children({ 
        gameplay_audio_timing = new sdk::gameplay_audio_timing(0x48) 
      }); 
    }

    bool is_loaded() override {
      auto loaded = single_component_loaded();
      for (auto& child : children)
        loaded &= child->is_loaded();
      loaded &= *(int*)(get_base() + 0xF0) == quaver_screen_type::gameplay;
      return loaded;
    }

    sdk::qua current_map() {
      auto address = *(uintptr_t*)(get_base() + 0x58);
      return sdk::qua(address);
    }

    sdk::gameplay_audio_timing* gameplay_audio_timing;
  };
} // namespace sdk