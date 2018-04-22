#include <iostream>
#include <fstream>

#include "lexer/lexer.h"

int main() {

    // Read file
    std::ifstream file;
    file.open("../program.txt");

    // If file not read
    if(!file) {
        std::cout << "Unable to read program.txt" << std::endl;
        std::exit(1);   // terminate with error
    }

    // Convert whole program to std::string
    std::string line, program;
    while(std::getline(file, line))
        program.append(line + "\n");

    // Print program
    std::cout << "The program string: \n \"" + program + "\"" << std::endl;

    // Try lexer
    lexer::Lexer lexer(program);
    lexer::Token t;

    // Lexemes
    std::cout << "Lexemes:" << std::endl;

    while (t.name != lexer::TOK_EOF) {
        t = lexer.next_token();
        std::cout << "'" + t.value + "'" << std::endl;
    }

    // Close file
    file.close();
    return 0;
}