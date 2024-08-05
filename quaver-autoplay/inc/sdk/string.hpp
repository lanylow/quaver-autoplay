#pragma once

namespace sdk {
  class string {
  public:
    explicit string(uintptr_t pointer) {
      auto address = *(uintptr_t*)(pointer);
      len = *(int*)(address + 0x8);
      buf = (const wchar_t*)(address + 0xC);
    }

    size_t size() const {
      return len; 
    }

    std::wstring wstr() { 
      return { buf, len };
    }

    std::string str() { 
      return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t>{}.to_bytes(wstr()); 
    }

  private:
    size_t len;
    const wchar_t* buf;
  };
} // namespace sdk