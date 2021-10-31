#pragma once

namespace sdk {
  class string {
  public:
    string(unsigned long long pointer) {
      auto address = *(unsigned long long *)(pointer);
      len = *(int *)(address + 0x8);
      buf = (const wchar_t *)(address + 0xC);
    }

    int size() { return len; }

    std::wstring wstr() { return std::wstring(buf, len); }

    std::string str() { return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(wstr()); }

  private:
    int len;
    const wchar_t *buf;
  };
} // namespace sdk