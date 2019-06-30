#include "ast_convert.hpp"
#include "ast.hpp"

namespace inter {
  std::unique_ptr<num> ast_convert::to_num(const std::unique_ptr<ast>& p) {
    auto num_obj = dynamic_cast<num*>(p.get());
    if (num_obj) {
      return std::make_unique<num>(num_obj->get());
    }
    auto str_obj = dynamic_cast<str*>(p.get());
    if (str_obj) {
      std::string value = str_obj->get();

      if (value.empty()) return nullptr;

      for (auto it = value.cbegin(); it < value.cend(); ++it) {
        if ((*it != '-' && it != value.cbegin()) && !isdigit(*it)) return nullptr;
      }

      return std::make_unique<num>(std::stoll(value));

    }
    return nullptr;
  }
  std::unique_ptr<str> ast_convert::to_str(const std::unique_ptr<ast>& p) {
    auto num_obj = dynamic_cast<num*>(p.get());
    if (num_obj) {
      return std::make_unique<str>(std::to_string(num_obj->get()));
    }
    auto str_obj = dynamic_cast<str*>(p.get());
    if (str_obj) {
      return std::make_unique<str>(str_obj->get());
    }
    return nullptr;
  }
}
