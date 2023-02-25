#pragma once

namespace sdk {
  class gameplay_screen : public object {
  public:
    sdk::gameplay_audio_timing* gameplay_audio_timing;

    virtual bool is_loaded() override {
      bool loaded = single_component_loaded();
      for (object* child : childs)
        loaded &= child->is_loaded();
      loaded &= *(int*)(get_base() + 0xF0) == quaver_screen_type::gameplay;
      return loaded;
    }

    auto current_map() {
      unsigned long long address = *(unsigned long long*)(get_base() + 0x58);

      /*unsigned long long slider_velocities = *(unsigned long long *)(address + 0x80);
      *(unsigned long long *)(slider_velocities + 0x10) = 0;
      *(float *)(address + 0xA8) = 32.f;*/

      qua map;
      map.game_mode = *(int*)(address + 0xA4);
      map.title = string(address + 0x20).str();
      map.artist = string(address + 0x28).str();
      map.creator = string(address + 0x40).str();
      map.difficulty = string(address + 0x48).str();

      list hit_object_list(address + 0x88);

      for (int i = 0; i < hit_object_list.size(); i++) {
        map.hit_object_data.push_back({
            *(int*)(hit_object_list[i] + 0x10),
            *(int*)(hit_object_list[i] + 0x18),
            *(int*)(hit_object_list[i] + 0x14),
          });
      }

      return map;
    }

    gameplay_screen(unsigned long long offset) : object(offset) { set_childs({ gameplay_audio_timing = new sdk::gameplay_audio_timing(0x48) }); }
  };
} // namespace sdk