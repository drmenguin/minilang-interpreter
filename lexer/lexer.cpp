//
// Created by lukec on 05/03/2018.
//

#include <stack>
#include <stdexcept>
#include <iostream>
#include "lexer.h"

using namespace lexer;


Lexer::Lexer(std::string& program) {
    unsigned int current_index = 0;

    // Tokenise the program
    while(current_index <= program.length())
        tokens.push_back(next_token(program, current_index));
}


Token Lexer::next_token() {
    if(current_token < tokens.size())
        return tokens[current_token++];
    else{
        std::string error = "Final token surpassed.";
        return Token(TOK_ERR, error);
    }
}


int Lexer::transition_delta(int q, char alpha) {

    /* Check which transition type we have, and then refer to the
     * transition table.
     */
    switch(alpha){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return transitions[DIGIT][q];

        case '.':
            return transitions[PERIOD][q];

        case '+':
        case '-':
            return transitions[ADDITIVE_OP][q];

        case '*':
            return transitions[ASTERISK][q];

        case '!':
            return transitions[EXCL_MARK][q];

        case '>':
        case '<':
            return transitions[ORDER_REL][q];

        case '=':
            return transitions[EQUALS][q];

        case '_':
            return transitions[UNDERSCORE][q];

        case '/':
            return transitions[FORWARDSLASH][q];

        case '\\':
            return transitions[BACKSLASH][q];

        case '\"':
            return transitions[QUOTATION_MARK][q];

        case ':':
        case ';':
        case ',':
        case '(':
        case ')':
        case '{':
        case '}':
            return transitions[PUNCTUATION][q];

        case '\n':
            return transitions[NEWLINE][q];

        case EOF:
            return transitions[ENDOFFILE][q];

        default:
            auto ascii = (int) alpha;

            // If alpha is in [A-Z] or [a-z]
            if (((0x41 <= ascii) && (ascii <= 0x5A)) ||
                ((0x61 <= ascii) && (ascii <= 0x7A)))
                return transitions[LETTER][q];

            // Else if Printable
            if ((0x20 <= ascii) && (ascii <= 0x7E))
                return transitions[PRINTABLE][q];

            // If other
            return transitions[OTHER][q];
    }


}

Token Lexer::next_token(std::string &program, unsigned int &current_index) {

    // Setup stack and lexeme
    int current_state = 0;
    std::stack<int> state_stack;
    char current_symbol;
    std::string lexeme;

    // Push 'BAD' state on the stack
    state_stack.push(-1);

    // Ignore whitespaces or newlines in front of lexeme
    while(program[current_index] == ' ' || program[current_index] == '\n')
        current_index++;

    // Check if EOF
    if(current_index == program.length()){
        lexeme = (char) EOF;
        current_index++;
        return Token(TOK_EOF, lexeme);
    }

    // While current state is not error state
    while(current_state != e){
        current_symbol = program[current_index];
        lexeme += current_symbol;

        // If current state is final, remove previously recorded final states
        if (is_final[current_state])
            while(!state_stack.empty())
                state_stack.pop();

        // and push current one on the stack
        state_stack.push(current_state);

        // Go to next state using delta function in DFA
        current_state = transition_delta(current_state, current_symbol);

        // Update current index for next iteration
        current_index++;
    }

    // Rollback loop
    while(!is_final[current_state] && current_state != -1){
        current_state = state_stack.top();
        state_stack.pop();
        lexeme.pop_back();
        current_index--;
    }


    if(is_final[current_state])
        return Token(TOK_Number, lexeme);

    else throw std::runtime_error("Syntax error on line " + std::to_string(get_line_number(program, current_index)) + ".");
}

int Lexer::get_line_number(std::string &program, unsigned int index) {
    int line = 1;
    for(int i = 0; i < index; i++)
        if(program[i] == '\n')
            line ++;
    return line;
}


Lexer::~Lexer() = default;