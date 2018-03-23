//
// Created by lukec on 05/03/2018.
//

#include <stack>
#include <stdexcept>
#include "lexer.h"

using namespace lexer;

Lexer::Lexer() {
}

int Lexer::transition_delta(int q, char alpha) {

    switch(alpha){

        // The DIGIT case
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

        // The PERIOD case
        case '.':
            return transitions[PERIOD][q];

        // The OTHER case
        default:
            return transitions[OTHER][q];
    }


}

Token Lexer::next_token(std::string &program, int current_index) {

    int current_state = 0;
    std::stack<int> state_stack;
    char current_symbol;
    std::string lexeme;

    state_stack.push(-1);

    while(current_state != e){
        current_symbol = program[current_index];
        lexeme += current_symbol;

        if (is_final[current_state])
            while(!state_stack.empty())
                state_stack.pop();

        state_stack.push(current_state);

        current_state = transition_delta(current_state, current_symbol);

        current_index++;
    }

    while(!is_final[current_state] && current_state != -1){
        current_state = state_stack.top();
        state_stack.pop();
        lexeme.pop_back();
    }

    if(is_final[current_state])
        return Token(TOK_Number, lexeme);

    else throw std::invalid_argument("Invalid token.");
}
