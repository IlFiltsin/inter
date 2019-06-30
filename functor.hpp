#pragma once

#include "ast.hpp"
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

namespace inter {
  
  class functor {
    public:
      using function = std::function<std::unique_ptr<ast>(const std::vector<std::unique_ptr<ast>>&)>;
      static functor* instance();

      void connect(const std::string &name, function fn);
      std::unique_ptr<ast> call(const std::string &name, const std::vector<std::unique_ptr<ast>>& args);

      functor(const functor&) = delete;
      functor& operator=(const functor&) = delete;

    private:
      functor();
      std::map<std::string, function> fn_map;
  };
  

}