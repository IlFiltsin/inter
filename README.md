# Simple interpretator

## Syntax of call of function:
`functionName arg1 arg2 ... argN`

where argument can be

- string (with symbols [-][a-z][A-Z][0-9])
- string in quotes without quotes inside ("str")
- call another function in brackets

## How it works

### Register internal functions:
  ```c++
    #include <functor.hpp>

    inter::functor::instance()->connect("name"), [](inter::functor::arg_t ast) {
      // work with ast
      // need to return std::unique_ptr<inter::ast> as result
    });
  ```
In function you can use help functions for convert ast:
  ```c++
  inter::ast_convert::to_num();
  inter::ast_convert::to_str();
  ```
If convert isn't possible both functions return null.

## Example

```bash
$ add 5 7 3
> 15

$ sub -7 "3"
> -10

$ mult (add 5 3) (sub 5 3)
> 16

$ concat "(2 + 2) * 2 = " (mult 2 (add 2 2))
> (2 + 2) * 2 = 8

$ quit
```