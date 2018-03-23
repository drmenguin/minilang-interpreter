//
// Created by lukec on 19/03/2018.
//

#ifndef PROJECT_TOKEN_H
#define PROJECT_TOKEN_H

#include <string>

namespace lexer {

    enum TOKEN {
        TOK_Number,
        TOK_ArithmeticOP,
        TOK_EOF
    };

    class Token {

    public:
        Token(TOKEN, std::string&);
        TOKEN name;
        std::string value;
    };
};


#endif //PROJECT_TOKEN_H
