#pragma once

#include <map>
#include <functional>
#include <vector>
#include <string>
#include <memory>

namespace inter {

  class ast;
  
  class functor {
    public:
      using arg_t = const std::vector<std::unique_ptr<ast>>&;
      using fn_t = std::function<std::unique_ptr<ast>(arg_t)>;
      static functor* instance();

      void connect(const std::string &name, fn_t fn);
      std::unique_ptr<ast> call(const std::string &name, arg_t args);

      functor(const functor&) = delete;
      functor& operator=(const functor&) = delete;

    private:
      functor();
      std::map<std::string, fn_t> fn_map;
  };
  

}