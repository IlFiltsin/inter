#pragma once

#include <string>

namespace inter {
  class runtime_error {
    public:
      runtime_error(const std::string &msg_) noexcept;
      std::string what() const noexcept;
    private:
      std::string msg;
  };
  class parser_error {
    public:
      parser_error(const std::string &msg_) noexcept;
      std::string what() const noexcept;
    private:
      std::string msg;
  };
}
