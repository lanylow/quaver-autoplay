#pragma once

namespace sdk {
  class gameplay_screen : public sdk::object {
  public:
    gameplay_screen(unsigned long long offset) : sdk::object(offset) { 
      set_children({ 
        gameplay_audio_timing = new sdk::gameplay_audio_timing(0x48) 
      }); 
    }

    virtual bool is_loaded() override {
      auto loaded = single_component_loaded();
      for (auto& child : children)
        loaded &= child->is_loaded();
      loaded &= *(int*)(get_base() + 0xF0) == quaver_screen_type::gameplay;
      return loaded;
    }

    auto current_map() {
      auto address = *(unsigned long long*)(get_base() + 0x58);

      /*
      unsigned long long slider_velocities = *(unsigned long long *)(address + 0x80);
      *(unsigned long long *)(slider_velocities + 0x10) = 0;
      *(float *)(address + 0xA8) = 32.f;
      */

      sdk::qua map;
      map.game_mode = *(int*)(address + 0xA4);
      map.title = sdk::string(address + 0x20).str();
      map.artist = sdk::string(address + 0x28).str();
      map.creator = sdk::string(address + 0x40).str();
      map.difficulty = sdk::string(address + 0x48).str();

      sdk::list hit_object_list(address + 0x88);

      for (int i = 0; i < hit_object_list.size(); i++) {
        map.hit_object_data.push_back({
          *(int*)(hit_object_list[i] + 0x10),
          *(int*)(hit_object_list[i] + 0x18),
          *(int*)(hit_object_list[i] + 0x14),
        });
      }

      return map;
    }

    sdk::gameplay_audio_timing* gameplay_audio_timing;
  };
} // namespace sdk