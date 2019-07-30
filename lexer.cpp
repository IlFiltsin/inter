#include "lexer.hpp"

#include <cctype>
#include <iostream>

namespace inter {
  lexer::lexer() noexcept : last_token(token::eol), last_char(' ') {}
  lexer* lexer::instance() noexcept {
    static lexer obj;
    return &obj;
  }
  lexer::token lexer::next_token() noexcept {

    last_value.clear();

    while(last_char != '\n' && std::isspace(last_char)) {
      last_char = getchar();
    };

    if (std::isalnum(last_char) || last_char == '-') {
      bool is_num = isdigit(last_char);
      last_value = last_char;
      while (1) {
        last_char = getchar();
        if (!std::isalnum(last_char) && last_char != '-') break;
        if (!std::isdigit(last_char)) is_num = false;
        last_value += last_char;
      }
      last_token = is_num ? token::num : token::str;
      return last_token;
    }

    if (last_char == '"') {
      while(1) {
        last_char = getchar();
        if (last_char == '"' || last_char == '\n') break;
        last_value += last_char;
      }
      if (last_char == '\n') {
        last_token = token::undefined;
      } else {
        last_char = getchar();
        last_token = token::str;
      }
      return last_token;
    }

    if (last_char == '\n') {
      last_char = ' ';
      last_token = token::eol;
    }
    else {

      if (last_char == '(') last_token = token::lbracket;
      else if (last_char == ')') last_token = token::rbracket;
      else last_token = token::undefined;

      last_char = getchar();
    }

    return last_token;

  }
  lexer::token lexer::current_token() noexcept {return last_token;}
  std::string lexer::get_value() const noexcept {return last_value;}
}