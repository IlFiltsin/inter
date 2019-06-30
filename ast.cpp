#include "ast.hpp"
#include "lexer.hpp"
#include "functor.hpp"
#include "exception.hpp"

namespace inter {
  ast::~ast() {}
  num::num(int64_t value_) noexcept : value(value_) {}
  int64_t inter::num::get() const noexcept {return value;}

  str::str(const std::string &value_) noexcept : value(value_) {};
  std::string str::get() const noexcept {return value;};

  fn::fn(const std::string &name_, std::vector<std::unique_ptr<ast>> args_) noexcept:
         name(name_), args(std::move(args_)) {}

  void fn::add_arg(std::unique_ptr<ast> arg) noexcept {
    args.emplace_back(std::move(arg));
  }
  std::unique_ptr<ast> fn::call() const {
    for (auto &v : args) {
      auto fn_ast = dynamic_cast<fn*>(v.get());
      if (fn_ast != nullptr) {
        v = std::move(fn_ast->call());
      }
    }
    auto result = functor::instance()->call(name, args);
    if (result == nullptr) throw runtime_error("Function " + name + " does not exist.");
    return result;
  }
}