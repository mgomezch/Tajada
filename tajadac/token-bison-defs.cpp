#include <iostream>

#include "tokens.hpp"

#define TOKEN_BISON_DEFS(tag, description, regex) "\%token " #tag "\n"

int main() { std::cout << TOKEN_DATA(TOKEN_BISON_DEFS) << std::endl; }
