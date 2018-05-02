//
// Created by lukec on 30/04/18.
//

#include "semantic_analysis.h"

using namespace visitor;

bool Scope::already_declared(std::string identifier, std::vector<parser::TYPE> *signature) {
    return !(symbol_table.find(std::make_pair(std::move(identifier), signature)) == symbol_table.end());
}

void Scope::declare(std::string identifier, parser::TYPE type, std::vector<parser::TYPE> *signature) {
    symbol_table[std::make_pair(std::move(identifier), signature)] = type;
}
