//
// Created by lukec on 22/04/18.
//

#include "ast.h"
#include <utility>

using namespace parser;


ASTDeclarationNode::ASTDeclarationNode(TYPE type, std::string& identifier, ASTExprNode* expr) :
    type(type),
    identifier(identifier),
    expr(expr)
{}

ASTIdentifierNode::ASTIdentifierNode(std::string &identifier) :
        identifier(identifier)
{}

ASTUnaryExprNode::ASTUnaryExprNode(std::string &unary_op, ASTExprNode *expr) :
    unary_op(unary_op),
    expr(expr)
{}

ASTFunctionCallNode::ASTFunctionCallNode(std::string &identifier, std::vector<ASTExprNode*> parameters) :
    identifier(identifier),
    parameters(std::move(parameters))
{}

ASTBinaryExprNode::ASTBinaryExprNode(std::string &op, ASTExprNode *left, ASTExprNode *right) :
    op(op),
    left(left),
    right(right)
{}

ASTAssignmentNode::ASTAssignmentNode(std::string &identifier, ASTExprNode * expr) :
    identifier(identifier),
    expr(expr)
{}
