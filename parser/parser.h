//
// Created by lukec on 22/04/18.
//

#ifndef MINILANG_PARSER_H
#define MINILANG_PARSER_H


#include "ast.h"
#include "../lexer/lexer.h"

namespace parser {

    class Parser {

        public:
            Parser(lexer::Lexer*);

        //private:
            lexer::Lexer* lex;
            lexer::Token current_token;
            lexer::Token next_token;

            void consume_token();

            ASTStatementNode* parse_statement();
            ASTDeclarationNode* parse_declaration_statement();
            ASTAssignmentNode* parse_assignment_statement();
            ASTExprNode* parse_expression();
            ASTExprNode* parse_simple_expression();
            ASTExprNode* parse_term();
            ASTExprNode* parse_factor();
            ASTFunctionCallNode* parse_function_call();
            std::vector<ASTExprNode*> *parse_actual_params();

            TYPE parse_type(std::string&);

    };

}

#endif //MINILANG_PARSER_H
