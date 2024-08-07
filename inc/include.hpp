#include <windows.h>
#include <thread>
#include <cstdint>
#include <vector>
#include <string>
#include <codecvt>
#include <algorithm>
#include <map>
#include <random>

#include "sdk/object.hpp"
#include "sdk/list.hpp"
#include "sdk/string.hpp"
#include "sdk/hit_object_data.hpp"
#include "sdk/qua.hpp"
#include "sdk/quaver_screen_type.hpp"
#include "sdk/gameplay_audio_timing.hpp"
#include "sdk/gameplay_screen.hpp"
#include "sdk/quaver_game.hpp"

#include "autoplayer.hpp"

#include "memory.hpp"

using namespace std::chrono_literals;