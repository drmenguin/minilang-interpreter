//
// Created by lukec on 22/04/18.
//

#include <iostream>
#include "parser.h"

using namespace parser;

Parser::Parser(lexer::Lexer* lex) : lex(lex) {
    current_token = lex->next_token();
    next_token    = lex->next_token();
}


void Parser::consume_token() {
    current_token = next_token;
    next_token = lex->next_token();
}


ASTStatementNode* Parser::parse_statement(){

    switch(current_token.type){

        case lexer::TOK_VAR:
            return parse_declaration_statement();

        case lexer::TOK_SET:
            return parse_assignment_statement();

        default:
            std::cout << "Mhux declaration" << std::endl;
    }
}


ASTDeclarationNode * Parser::parse_declaration_statement(){

    // Node attributes
    TYPE type;
    std::string identifier;

    consume_token();
    if(current_token.type != lexer::TOK_IDENTIFIER)
        throw std::runtime_error("Expected variable name on line "
                                 + std::to_string(current_token.line_number) + ".");
    identifier = current_token.value;

    consume_token();
    if(current_token.type != lexer::TOK_COLON)
        throw std::runtime_error("Expected ':' after " + identifier + " on line "
                                 + std::to_string(current_token.line_number) + ".");

    consume_token();
    type = parse_type(identifier);

    consume_token();
    if(current_token.type != lexer::TOK_EQUALS)
        throw std::runtime_error("Expected assignment operator '=' for " + identifier + " on line "
                                 + std::to_string(current_token.line_number) + ".");

    // Parse the right hand side
    ASTExprNode* expr = parse_expression();

    consume_token();
    if(current_token.type != lexer::TOK_SEMICOLON)
        throw std::runtime_error("Expected ';' after assignment of " + identifier + " on line "
                                 + std::to_string(current_token.line_number) + ".");

    // Create ASTExpressionNode to return
    return new ASTDeclarationNode(type, identifier, expr);
}

ASTAssignmentNode* Parser::parse_assignment_statement() {

}

ASTExprNode* Parser::parse_expression(){
    ASTExprNode *simple_expr = parse_simple_expression();

    if(next_token.type == lexer::TOK_RELATIONAL_OP) {
        consume_token();
        return new ASTBinaryExprNode(current_token.value, simple_expr, parse_expression());
    }

    return simple_expr;
}

ASTExprNode* Parser::parse_simple_expression(){

    ASTExprNode *term = parse_term();

    if(next_token.type == lexer::TOK_ADDITIVE_OP) {
        consume_token();
        return new ASTBinaryExprNode(current_token.value, term, parse_simple_expression());
    }

    return term;
}

ASTExprNode* Parser::parse_term() {

    ASTExprNode *factor = parse_factor();

    if(next_token.type == lexer::TOK_MULTIPLICATIVE_OP) {
        consume_token();
        return new ASTBinaryExprNode(current_token.value, factor, parse_term());
    }

    return factor;
}

ASTExprNode* Parser::parse_factor() {
    consume_token();

    switch(current_token.type){

        // Literal Cases
        case lexer::TOK_INT:
            return new ASTLiteralNode<int>(std::stoi(current_token.value));

        case lexer::TOK_REAL:
            return new ASTLiteralNode<float>(std::stof(current_token.value));

        case lexer::TOK_BOOL:
            return new ASTLiteralNode<bool>(current_token.value == "true");

        case lexer::TOK_STRING:
            // Remove \" character from front and end of lexeme
            return new ASTLiteralNode<std::string>(
                    current_token.value.substr(1, current_token.value.size() - 2));

        // Identifier or function call case
        case lexer::TOK_IDENTIFIER:
            if(next_token.type == lexer::TOK_LEFT_BRACKET)
                return parse_function_call();
            else return new ASTIdentifierNode(current_token.value);

        // Subexpression case
        case lexer::TOK_LEFT_BRACKET: {
            ASTExprNode *sub_expr = parse_expression();
            consume_token();
            if (current_token.type != lexer::TOK_RIGHT_BRACKET)
                throw std::runtime_error("Expected ')' after expression on line "
                                         + std::to_string(current_token.line_number) + ".");
            return sub_expr;
        }

        // Unary expression case
        case lexer::TOK_ADDITIVE_OP:
        case lexer::TOK_NOT:
            return new ASTUnaryExprNode(current_token.value, parse_expression());

        default:
            throw std::runtime_error("Expected expression on line "
                                     + std::to_string(current_token.line_number) + ".");

    }

}

ASTFunctionCallNode* Parser::parse_function_call(){
    // current token is the function identifier
    std::string identifier = current_token.value;
    std::vector<ASTExprNode*> *parameters = nullptr;

    consume_token();
    if(current_token.type != lexer::TOK_LEFT_BRACKET)
        throw std::runtime_error("Expected '(' on line "
                                 + std::to_string(current_token.line_number) + ".");

    // If next token is not right bracket, we have parameters
    if(next_token.type != lexer::TOK_RIGHT_BRACKET)
        parameters = parse_actual_params();

    // Ensure right close bracket after fetching parameters
    if(current_token.type != lexer::TOK_RIGHT_BRACKET)
        throw std::runtime_error("Expected ')' on line "
                                 + std::to_string(current_token.line_number)
                                 + " after function parameters.");

    return new ASTFunctionCallNode(identifier, *parameters);
}

std::vector<ASTExprNode*>* Parser::parse_actual_params() {

    auto parameters = new std::vector<ASTExprNode*>;

    parameters->push_back(parse_expression());
    consume_token();

    // If there are more
    while(current_token.type == lexer::TOK_COMMA) {
        parameters->push_back(parse_expression());
        consume_token();
    }

    return parameters;
}

TYPE Parser::parse_type(std::string& identifier){
    switch(current_token.type){
        case lexer::TOK_INT_TYPE:
            return INT;

        case lexer::TOK_REAL_TYPE:
            return REAL;

        case lexer::TOK_BOOL_TYPE:
            return BOOL;

        case lexer ::TOK_STRING:
            return STRING;

        default:
            throw std::runtime_error("Expected type for " + identifier + " after ':' on line "
                                     + std::to_string(current_token.line_number) + ".");
    }
}



