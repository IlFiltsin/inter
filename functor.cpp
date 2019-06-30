#include "functor.hpp"
#include "ast.hpp"

namespace inter {
  functor::functor() {}
  functor* functor::instance() {
    static functor obj;
    return &obj;
  }

  void functor::connect(const std::string &str, fn_t fn) {
    fn_map[str] = fn;
  }
  std::unique_ptr<ast> functor::call(const std::string &name, arg_t args) {
    if (fn_map.count(name) != 0) {
      return fn_map[name](args);
    }
    return nullptr;
  }
}
