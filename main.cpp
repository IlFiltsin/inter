#include "parser.hpp"
#include "functor.hpp"
#include "ast_convert.hpp"
#include "exception.hpp"
#include <iostream>
#include <numeric>

void reg_fn() {
  auto inst = inter::functor::instance();

  inst->connect("add", [](const std::vector<std::unique_ptr<inter::ast>>& ast) {
    if (ast.empty()) throw inter::runtime_error("Function add must contain at least 1 parameter.");
    int64_t result = 0;
    for (auto &p_ast : ast) {
      auto num_ast = inter::ast_convert::to_num(p_ast);
      if (num_ast) {
        result += num_ast->get();
      } else {
        throw inter::runtime_error("Add: Parameters of add should be possible convert to int");
      }
    }
    return std::make_unique<inter::num>(result);
  });

  inst->connect("sub", [](const std::vector<std::unique_ptr<inter::ast>>& ast) {
    if (ast.empty()) throw inter::runtime_error("Function sub must contain at least 1 parameter.");
    int64_t result = 0;
    for (auto &p_ast : ast) {
      auto num_ast = inter::ast_convert::to_num(p_ast);
      if (num_ast) {
        result -= num_ast->get();
      } else {
        throw inter::runtime_error("Sub: Parameters of add should be possible convert to int");
      }
    }
    return std::make_unique<inter::num>(result);
  });


  inst->connect("mult", [](const std::vector<std::unique_ptr<inter::ast>>& ast) {
    if (ast.empty()) throw inter::runtime_error("Function mult must contain at least 1 parameter.");
    int64_t result = 1;
    for (auto &p_ast : ast) {
      auto num_ast = inter::ast_convert::to_num(p_ast);
      if (num_ast) {
        result *= num_ast->get();
      } else {
        throw inter::runtime_error("Mult: Parameters of add should be possible convert to int");
      }
    }
    return std::make_unique<inter::num>(result);
  });

  inst->connect("concat", [](const std::vector<std::unique_ptr<inter::ast>>& ast) {
    if (ast.empty()) throw inter::runtime_error("Function concat must contain at least 1 parameter.");
    std::string result;
    for (auto &p_ast : ast) {
      auto str_ast = inter::ast_convert::to_str(p_ast);
      if (str_ast) {
        result += str_ast->get();
      } else {
        throw inter::runtime_error("Concat: Parameters of add should be possible convert to str");
      }
    }
    return std::make_unique<inter::str>(result);
  });

  inst->connect("quit", [](const std::vector<std::unique_ptr<inter::ast>>& ast) {
    exit(0);
    return nullptr;
  });

}

void main_loop() {
  while(1) {
    std::cout << "$ ";
    try {
      auto result = inter::ast_convert::to_str(inter::parser::parse_expr()->call())->get();
      std::cout << "> " << result << std::endl;
    } catch(const inter::parser_error &e) {
      std::cout << "\033[1;31m Parser error: "  << e.what() << "\033[0m\n";
    } catch(const inter::runtime_error &e) {
      std::cout << "\033[1;31m Runtime error: " << e.what() << "\033[0m\n";
    }
  };
}

int main() {
  //auto fn = inter::parser::parse_expr();
  reg_fn();
  main_loop();

}