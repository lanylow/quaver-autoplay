#pragma once

namespace sdk {
  class qua {
  public:
    explicit qua(uintptr_t pointer) {
      game_mode = *(int*)(pointer + 0xAC);
      title = sdk::string(pointer + 0x20).str();
      artist = sdk::string(pointer + 0x28).str();
      creator = sdk::string(pointer + 0x40).str();
      difficulty = sdk::string(pointer + 0x48).str();

      sdk::list<sdk::qua::hit_object_info_t*> hit_object_list(pointer + 0x90);

      for (int i = 0; i < hit_object_list.size(); i++) {
        auto obj = hit_object_list[i];
        hit_object_data.push_back({ obj->start_time, obj->end_time, obj->key_lane });
      }
    }

    int game_mode;
    std::string title;
    std::string artist;
    std::string creator;
    std::string difficulty;
    std::vector<sdk::hit_object_data_t> hit_object_data;

  private:
    struct hit_object_info_t {
      uint8_t pad_00[0x10];
      int start_time;
      int key_lane;
      int end_time;
    };
  };
} // namespace sdk