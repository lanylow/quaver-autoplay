#pragma once

namespace sdk {
  class gameplay_screen : public object {
  public:
    sdk::gameplay_audio_timing *gameplay_audio_timing;

    virtual bool is_loaded() override {
      bool loaded = single_component_loaded();
      for (object *child : childs)
        loaded &= child->is_loaded();
      loaded &= *(int *)(get_base() + 0xF0) == quaver_screen_type::gameplay;
      return loaded;
    }

    gameplay_screen(unsigned long long offset) : object(offset) { set_childs({gameplay_audio_timing = new sdk::gameplay_audio_timing(0x48)}); }
  };
} // namespace sdk