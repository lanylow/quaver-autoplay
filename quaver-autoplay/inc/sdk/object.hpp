#pragma once

#include <utility>

namespace sdk {
  class object {
  public:
    explicit object(ptrdiff_t offset) : base_pointer(0), offset(offset) { }

    object(uintptr_t base_pointer, ptrdiff_t offset) : base_pointer(base_pointer), offset(offset) { }

    void set_children(std::vector<sdk::object*> objects) {
      children = std::move(objects);
      for (auto& child : children)
        child->parent = this;
    }

    auto get_children() { 
      return children; 
    }

    uintptr_t get_base() const { // NOLINT(*-no-recursion)
      if (base_pointer)
        return *(uintptr_t*)(base_pointer);
      if (parent->single_component_loaded())
        return *(uintptr_t*)(parent->get_base() + offset);
      return 0;
    }

    bool single_component_loaded() const { // NOLINT(*-no-recursion)
      auto valid = true;
      if (parent)
        valid &= parent->single_component_loaded();
      else
        valid &= get_base() != 0;
      return valid;
    }

    virtual bool is_loaded() { // NOLINT(*-no-recursion)
      auto loaded = single_component_loaded();
      for (auto& child : children)
        loaded &= child->is_loaded();
      return loaded;
    }

    sdk::object* parent = nullptr;

  protected:
    std::vector<sdk::object*> children{ };
    uintptr_t base_pointer;
    ptrdiff_t offset;
  };
} // namespace sdk