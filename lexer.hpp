#pragma once

#include <string>

namespace inter { 

  class lexer {
    public:

      enum class token {
        eol, // end of line
        num,
        str,
        lbracket, // (
        rbracket, // )
        undefined
      };

  
      static lexer* instance() noexcept;

      token next_token() noexcept;
      token current_token() noexcept;

      std::string get_value() const noexcept;

      lexer(const lexer&) = delete;
      lexer& operator=(const lexer&) = delete;

    private:
      lexer() noexcept;
      char last_char;
      std::string last_value;
      token last_token;
  };

}