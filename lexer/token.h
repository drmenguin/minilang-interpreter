//
// Created by lukec on 19/03/2018.
//

#ifndef MINILANG_TOKEN_H
#define MINILANG_TOKEN_H

#include <string>

namespace lexer {

    enum TOKEN {
        TOK_INT,
        TOK_REAL,
        TOK_ADDITIVE_OP,
        TOK_MULTIPLICATIVE_OP,
        TOK_RELATIONAL_OP,
        TOK_EQUALS,
        TOK_VAR,
        TOK_SET,
        TOK_DEF,
        TOK_RETURN,
        TOK_IF,
        TOK_ELSE,
        TOK_WHILE,
        TOK_PRINT,
        TOK_INT_TYPE,
        TOK_REAL_TYPE,
        TOK_BOOL_TYPE,
        TOK_STRING_TYPE,
        TOK_BOOL,
        TOK_NOT,
        TOK_IDENTIFIER,
        TOK_COMMENT,
        TOK_STRING,
        TOK_LEFT_CURLY,
        TOK_RIGHT_CURLY,
        TOK_LEFT_BRACKET,
        TOK_RIGHT_BRACKET,
        TOK_COMMA,
        TOK_SEMICOLON,
        TOK_COLON,
        TOK_EOF,
        TOK_ERROR
    };

    class Token {

        public:
            Token();
            Token(int, std::string, int line_number = 0);
            TOKEN type;
            std::string value;
            int line_number;

        private:
            TOKEN determine_token_type(int, std::string&);
    };
};


#endif //MINILANG_TOKEN_H
