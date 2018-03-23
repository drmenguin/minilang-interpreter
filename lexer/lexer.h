//
// Created by lukec on 05/03/2018.
//

#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H


#include <string>
#include "token.h"

namespace lexer {

    enum CLASSIFICATION {
        DIGIT  = 0,
        PERIOD = 1,
        OTHER  = 2,
    };

    class Lexer {

    public:
        Lexer();
        Token next_token(std::string&, int = 0);

    private:
        int e = 4;
        bool is_final[5] = {0, 1, 0, 1, 0};
        int transitions[3][5] = {
                       /* S0  S1  S2  S3  Se
          /* DIGIT  */ {   1,  1,  3,  3,  e},
          /* PERIOD */ {   2,  3,  e,  e,  e},
          /* OTHER  */ {   e,  e,  e,  e,  e}
        };

        int transition_delta(int, char);

    };

};


#endif //PROJECT_LEXER_H
