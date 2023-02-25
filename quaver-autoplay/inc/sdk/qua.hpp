#pragma once

namespace sdk {
  struct qua {
    int game_mode;
    std::string title;
    std::string artist;
    std::string creator;
    std::string difficulty;
    std::vector<sdk::hit_object_data_t> hit_object_data;
  };
} // namespace sdk