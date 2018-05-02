/**
 * @file lexer.h
 * Contains all initialisations
 */
#ifndef MINILANG_LEXER_H
#define MINILANG_LEXER_H


#include <string>
#include <vector>
#include "token.h"

namespace lexer {

    /**
     * @enum List of possible transition types
     */
    enum TRANSITION_TYPE {
        DIGIT           =  0,
        PERIOD          =  1,
        ADDITIVE_OP     =  2,
        ASTERISK        =  3,
        EXCL_MARK       =  4,
        ORDER_REL       =  5,
        EQUALS          =  6,
        UNDERSCORE      =  7,
        FORWARDSLASH    =  8,
        BACKSLASH       =  9,
        QUOTATION_MARK  = 10,
        PUNCTUATION     = 11,
        NEWLINE         = 12,
        ENDOFFILE       = 13,
        LETTER          = 14,
        PRINTABLE       = 15,
        OTHER           = 16
    };

    class Lexer {

        public:
            /**
             * Constructor for Lexer class with the input program string as a
             * parameter. This constructor generates
             *
             * @param program An
             */
            Lexer(std::string&);
            Token next_token();
            ~Lexer();


        private:
            const unsigned int e = 23;
                                /* S0  S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 S17 S18 S19 S20 S21 S22 Se */
            const bool is_final[24] = {   0,  1,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  0,  0,  1,  0,  1,  0,  0,  0,  1,  1,  1, 0};

            const unsigned int transitions[17][23] = {
                                     /* S0  S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 S17 S18 S19 S20 S21 S22 */
                /* DIGIT          */ {   1,  1,  3,  3,  e,  e,  e,  e,  e,  e, 10,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* PERIOD         */ {   2,  3,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* ADDITIVE_OP    */ {   4,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* ASTERISK       */ {   5,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 13, 12, 15,  e, 15,  e, 17, 17, 17,  e,  e,  e},
                /* EXCL_MARK      */ {   6,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* ORDER_REL      */ {   7,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* EQUALS         */ {   8,  e,  e,  e,  e,  e,  9,  9,  9,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* UNDERSCORE     */ {  10,  e,  e,  e,  e,  e,  e,  e,  e,  e, 10,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* FORWARDSLASH   */ {  11,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 12, 13,  e, 16,  e, 17, 17, 17,  e,  e,  e},
                /* BACKSLASH      */ {   e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 18, 18, 18,  e,  e,  e},
                /* QUOTATION_MARK */ {  17,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 20, 19, 20,  e,  e,  e},
                /* PUNCTUATION    */ {  21,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* NEWLINE        */ {   e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 14, 13,  e, 13,  e,  e,  e,  e,  e,  e,  e},
                /* ENDOFFILE      */ {  22,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e},
                /* LETTER         */ {  10,  e,  e,  e,  e,  e,  e,  e,  e,  e, 10,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* PRINTABLE      */ {   e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e, 12, 13,  e, 13,  e, 17, 17, 17,  e,  e,  e},
                /* OTHER          */ {   e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e,  e}
            };


            unsigned int current_token = 0;
            std::vector<Token> tokens;

            /**
             *
             * @return hi
             */
            int transition_delta(int, char);

            Token next_token(std::string&, unsigned int&);

            int get_line_number(std::string&, unsigned int);
    };

};


#endif //MINILANG_LEXER_H
