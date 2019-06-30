#pragma once

#include <memory>

namespace inter {

  class ast;
  class num;
  class str;

  namespace ast_convert {
    std::unique_ptr<num> to_num(const std::unique_ptr<ast>& p);
    std::unique_ptr<str> to_str(const std::unique_ptr<ast>& p);
  }
}
