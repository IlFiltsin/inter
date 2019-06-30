#include "parser.hpp"
#include "lexer.hpp"
#include "exception.hpp"

namespace inter {
  std::unique_ptr<fn> parser::parse_expr() {
    auto result = parse_fn();
    if (lexer::instance()->current_token() == lexer::token::rbracket) {
      throw parser_error("Expected (");
    }
    return result;
  }
  std::unique_ptr<fn> parser::parse_fn() {

    lexer *inst = lexer::instance();

    inst->next_token();
    std::string func_name = inst->get_value();

    auto fn_ast = std::make_unique<fn>(func_name);

    std::unique_ptr<ast> arg;

    while(1) {
      arg = parse_arg();
      if (arg == nullptr) break;

      fn_ast->add_arg(std::move(arg));
    }

    return fn_ast;
  }
  std::unique_ptr<fn> parser::parse_inline_fn() {
    auto result = parse_fn();
    if (lexer::instance()->current_token() != lexer::token::rbracket) {
      throw parser_error("Expected )");
    }
    return result;
  }
  std::unique_ptr<ast> parser::parse_arg() {
    lexer *inst = lexer::instance();

    lexer::token token = inst->next_token();

    if (token == lexer::token::str) {
      return std::make_unique<str>(inst->get_value());
    }

    if (token == lexer::token::num) {
      return std::make_unique<num>(std::stoll(inst->get_value()));
    }

    if (token == lexer::token::lbracket) {
      return parse_inline_fn();
    }

    if (token == lexer::token::undefined) {
      throw parser_error("Undefined value \"" + inst->get_value());
    }

    return nullptr; // eol, rbracket
  }
}
