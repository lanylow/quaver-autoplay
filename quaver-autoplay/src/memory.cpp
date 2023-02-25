#include <include.hpp>

auto parse_pattern(const char* pattern) {
  std::vector<int> bytes = { };

  auto start = (char*)(pattern);
  auto end = (char*)(pattern) + strlen(pattern);

  for (auto curr = start; curr < end; ++curr) {
    if (*curr == '?') {
      ++curr;
      if (*curr == '?')
        ++curr;
      bytes.push_back(-1);
    }
    else {
      bytes.push_back(std::strtoul(curr, &curr, 16));
    }
  }

  return bytes;
}

auto get_next_region(unsigned long long& address) {
  std::pair<unsigned long long, unsigned long long> region_info;
  MEMORY_BASIC_INFORMATION memory_info = {};
  auto query_address = 0ull;

  if (address)
    query_address = address;

  do {
    VirtualQuery((void*)(query_address), &memory_info, sizeof(memory_info));
    region_info = std::make_pair((unsigned long long)(memory_info.BaseAddress), memory_info.RegionSize);
    query_address = region_info.first + region_info.second;
  } while (memory_info.State != MEM_COMMIT || memory_info.Protect != PAGE_EXECUTE_READWRITE);

  return region_info;
}

unsigned long long memory::pattern_scan(const char* pattern) {
  auto bytes = parse_pattern(pattern);
  auto start = 0ull;
  auto end = 0ull;
  auto found = true;

  do {
    auto region_info = get_next_region(end);
    start = region_info.first;
    end = region_info.first + region_info.second;

    auto buffer = (unsigned char*)start;

    for (auto i = 0; i < region_info.second; i++) {
      found = true;

      for (auto j = 0; j < bytes.size() && found; j++)
        if (bytes[j] != -1)
          if (buffer[i + j] != bytes[j])
            found = false;

      if (found)
        return start + i;
    }
  } while (!found);

  return 0;
}