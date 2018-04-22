//
// Created by lukec on 19/03/2018.
//

#ifndef MINILANG_TOKEN_H
#define MINILANG_TOKEN_H

#include <string>

namespace lexer {

    enum TOKEN {
        TOK_Number,
        TOK_ERR,
        TOK_EOF
    };

    class Token {

    public:
        Token();

        Token(TOKEN, std::string&);
        TOKEN name;
        std::string value;
    };
};


#endif //MINILANG_TOKEN_H
