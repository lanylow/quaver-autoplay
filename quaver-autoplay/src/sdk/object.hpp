#pragma once

namespace sdk {
  class object {
  public:
    object(unsigned long long offset) : base_pointer(0), offset(offset) {}

    object(unsigned long long base_pointer, unsigned long long offset) : base_pointer(base_pointer), offset(offset) {}

    object* parent = nullptr;

    void set_childs(std::vector<object*> objects) {
      childs = objects;
      for (object* child : childs)
        child->parent = this;
    }

    auto get_childs() { return childs; }

    unsigned long long get_base() {
      if (base_pointer)
        return *(unsigned long long*)(base_pointer);
      if (parent->single_component_loaded())
        return *(unsigned long long*)(parent->get_base() + offset);
      return 0;
    }

    bool single_component_loaded() {
      auto valid = true;
      if (parent)
        valid &= parent->single_component_loaded();
      else
        valid &= get_base() != 0;
      return valid;
    }

    virtual bool is_loaded() {
      bool loaded = single_component_loaded();
      for (object* child : childs)
        loaded &= child->is_loaded();
      return loaded;
    }

  protected:
    std::vector<object*> childs{};
    unsigned long long base_pointer;
    unsigned long long offset;
  };
} // namespace sdk