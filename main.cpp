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
    std::cout << program << std::endl;

    // Try lexer
    lexer::Lexer lexer;
    std::cout << lexer.next_token(program).value << std::endl;
    std::cout << lexer.next_token(program, 3).value << std::endl;

    // Close file
    file.close();
    return 0;
}