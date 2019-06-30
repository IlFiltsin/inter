#pragma once

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace inter {

  class ast {
    public:
      virtual ~ast();
  };

  class num : public ast {
    public:
      num(int64_t value_) noexcept;
      int64_t get() const noexcept;
    private:
      int64_t value;
  };

  class str : public ast {
    public:
      str(const std::string &value_) noexcept;
      std::string get() const noexcept;
    private:
      std::string value; 
  };

  class fn : public ast {
    public:
      fn(const std::string &name_, std::vector<std::unique_ptr<ast>> args_ = {}) noexcept;
      void add_arg(std::unique_ptr<ast> arg) noexcept;

      std::unique_ptr<ast> call() const;
    private:
      std::string name;
      mutable std::vector<std::unique_ptr<ast>> args;
  };
}