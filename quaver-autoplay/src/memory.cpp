#include "include.hpp"

auto parse_pattern(const char* pattern) {
  std::vector<int> b = {};

  char* s = (char*)pattern;
  char* e = (char*)pattern + strlen(pattern);

  for (char* c = s; c < e; ++c) {
    if (*c == '?') {
      ++c;
      if (*c == '?')
        ++c;
      b.push_back(-1);
    }
    else {
      b.push_back(strtoul(c, &c, 16));
    }
  }

  return b;
}

auto get_next_region(unsigned long long& address) {
  std::pair<unsigned long long, unsigned long long> b;
  MEMORY_BASIC_INFORMATION m = {};
  unsigned long long a = 0;

  if (address)
    a = address;

  do {
    VirtualQuery((void*)(a), &m, sizeof(m));
    b = std::make_pair((unsigned long long)(m.BaseAddress), m.RegionSize);
    a = b.first + b.second;
  } while (m.State != MEM_COMMIT || m.Protect != PAGE_EXECUTE_READWRITE);

  return b;
}

unsigned long long memory::pattern_scan(const char* pattern) {
  auto p = parse_pattern(pattern);
  unsigned long long s = 0;
  unsigned long long e = 0;
  unsigned char* r;
  bool f = true;

  do {
    auto ri = get_next_region(e);

    s = ri.first;
    e = ri.first + ri.second;
    r = (unsigned char*)s;

    for (auto i = 0; i < ri.second; i++) {
      f = true;

      for (auto j = 0; j < p.size() && f; j++)
        if (p[j] != -1)
          if (r[i + j] != p[j])
            f = false;

      if (f)
        return s + i;
    }
  } while (!f);

  return 0;
}