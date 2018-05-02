//
// Created by lukec on 30/04/18.
//

#ifndef MINILANG_SEMANTIC_ANALYSIS_H
#define MINILANG_SEMANTIC_ANALYSIS_H

#include <map>
#include <vector>
#include "../parser/ast.h"

namespace visitor {

    class Scope {
    public:
        bool already_declared(std::string, std::vector<parser::TYPE>*);
        void declare(std::string, parser::TYPE, std::vector<parser::TYPE>* = nullptr);

    private:
        std::map<std::pair<std::string, std::vector<parser::TYPE>*>,
                parser::TYPE> symbol_table;
    };
}

#endif //MINILANG_SEMANTIC_ANALYSIS_H
