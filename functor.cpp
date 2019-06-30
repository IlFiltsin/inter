#include "functor.hpp"

namespace inter {
  functor::functor() {}
  functor* functor::instance() {
    static functor obj;
    return &obj;
  }

  void functor::connect(const std::string &str, functor::function fn) {
    fn_map[str] = fn;
  }
  std::unique_ptr<ast> functor::call(const std::string &name, const std::vector<std::unique_ptr<ast>>& args) {
    if (fn_map.count(name) != 0) {
      return fn_map[name](args);
    }
    return nullptr;
  }
}
