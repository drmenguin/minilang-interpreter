#include <iostream>
#include <fstream>

#include "lexer/lexer.h"
#include "parser/parser.h"
#include "visitor/xml_visitor.h"
#include "visitor/semantic_analysis.h"
#include "visitor/interpreter.h"

int main() {

    // Read file
    std::ifstream file;
    file.open("../program.txt");

    // If file not read
    if(!file) {
        std::cout << "Unable to read program.txt" << std::endl;
        std::exit(1);   // terminate with error
    }

    //Tokens
    std::string tokens[32] = {
            "TOK_INT",
            "TOK_REAL",
            "TOK_ADDITIVE_OP",
            "TOK_MULTIPLICATIVE_OP",
            "TOK_RELATIONAL_OP",
            "TOK_EQUALS",
            "TOK_VAR",
            "TOK_SET",
            "TOK_DEF",
            "TOK_RETURN",
            "TOK_IF",
            "TOK_ELSE",
            "TOK_WHILE",
            "TOK_PRINT",
            "TOK_INT_TYPE",
            "TOK_REAL_TYPE",
            "TOK_BOOL_TYPE",
            "TOK_STRING_TYPE",
            "TOK_BOOL",
            "TOK_NOT",
            "TOK_IDENTIFIER",
            "TOK_COMMENT",
            "TOK_STRING",
            "TOK_LEFT_CURLY",
            "TOK_RIGHT_CURLY",
            "TOK_LEFT_BRACKET",
            "TOK_RIGHT_BRACKET",
            "TOK_COMMA",
            "TOK_SEMICOLON",
            "TOK_COLON",
            "TOK_EOF",
            "TOK_ERROR"
    };

    // Convert whole program to std::string
    std::string line, program;
    while(std::getline(file, line))
        program.append(line + "\n");

    // Print program
    // std::cout << "The program string: \n \"" + program + "\"" << std::endl;

    // Try lexer
    lexer::Lexer lexer(program);
//    lexer::Token t;
//
//    // Lexemes
//    std::cout << "Lexemes:" << std::endl;
//
//    while (t.type != lexer::TOK_EOF) {
//        t = lexer.next_token();
//        std::cout << tokens[t.type] + ": " + t.value << std::endl;
//    }

    // Parse
    parser::Parser parser(&lexer);
    parser::ASTProgramNode* prog = parser.parse_program();


    // XML generation
    visitor::XMLVisitor xml_generator;
    xml_generator.visit(prog);

    // Semantic Analysis
    visitor::SemanticAnalyser semantic_analyser;
    semantic_analyser.visit(prog);

    // Interpreter
    visitor::Interpreter interpreter;
    interpreter.visit(prog);

    // Close file
    file.close();
    return 0;
}