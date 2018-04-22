//
// Created by lukec on 19/03/2018.
//

#include "token.h"

using namespace lexer;

Token::Token() = default;

Token::Token(TOKEN name, std::string &value) {
    this->name = name;
    this->value = value;
}