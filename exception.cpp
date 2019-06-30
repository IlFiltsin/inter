#include "exception.hpp"

namespace inter {
  parser_error::parser_error(const std::string &msg_) noexcept : msg(msg_) {}
  std::string parser_error::what() const noexcept {return msg;}
  runtime_error::runtime_error(const std::string &msg_) noexcept : msg(msg_) {}
  std::string runtime_error::what() const noexcept {return msg;}
}