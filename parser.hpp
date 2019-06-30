#pragma once

#include <memory>

namespace inter {

  class ast;
  class fn;

  namespace parser { 
    std::unique_ptr<fn> parse_expr();
    std::unique_ptr<fn> parse_fn();
    std::unique_ptr<fn> parse_inline_fn();
    std::unique_ptr<ast> parse_arg();
  };

}