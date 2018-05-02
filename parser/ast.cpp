//
// Created by lukec on 22/04/18.
//

#include "ast.h"
#include <utility>

using namespace parser;

// Program Node
ASTProgramNode::ASTProgramNode(std::vector<ASTStatementNode*> statements) :
        statements(std::move(statements))
{}


// Statement Nodes
ASTDeclarationNode::ASTDeclarationNode(TYPE type, std::string identifier, ASTExprNode *expr) :
    type(type),
    identifier(std::move(identifier)),
    expr(expr)
{}

ASTAssignmentNode::ASTAssignmentNode(std::string identifier, ASTExprNode *expr) :
        identifier(std::move(identifier)),
        expr(expr)
{}

ASTPrintNode::ASTPrintNode(ASTExprNode *expr) :
        expr(expr)
{}

ASTReturnNode::ASTReturnNode(ASTExprNode *expr) :
        expr(expr)
{}

ASTBlockNode::ASTBlockNode(std::vector<ASTStatementNode*> statements) :
        statements(std::move(statements))
{}

ASTIfNode::ASTIfNode(ASTExprNode* condition, ASTBlockNode *if_block, ASTBlockNode *else_block) :
        condition(condition),
        if_block(if_block),
        else_block(else_block)
{}

ASTWhileNode::ASTWhileNode(ASTExprNode *condition, ASTBlockNode *block) :
        condition(condition),
        block(block)
{}

ASTFunctionDefinitionNode::ASTFunctionDefinitionNode(std::string identifier,
                                                     std::vector<std::pair<std::string, TYPE>> parameters,
                                                     TYPE type, ASTBlockNode* block) :
        identifier(std::move(identifier)),
        parameters(std::move(parameters)),
        type(type),
        block(block)
{
    this->signature = std::vector<TYPE>();
    for(auto param : parameters)
        signature.push_back(param.second);
}


// Expression Nodes
ASTBinaryExprNode::ASTBinaryExprNode(std::string op, ASTExprNode *left, ASTExprNode *right) :
        op(std::move(op)),
        left(left),
        right(right)
{}

ASTIdentifierNode::ASTIdentifierNode(std::string identifier) :
        identifier(std::move(identifier))
{}

ASTUnaryExprNode::ASTUnaryExprNode(std::string unary_op, ASTExprNode *expr) :
    unary_op(std::move(unary_op)),
    expr(expr)
{}

ASTFunctionCallNode::ASTFunctionCallNode(std::string identifier, std::vector<ASTExprNode*> parameters) :
    identifier(std::move(identifier)),
    parameters(std::move(parameters))
{}


// Accept functions for visitors
void ASTBinaryExprNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

namespace parser {

    template<>
    void ASTLiteralNode<int>::accept(visitor::Visitor *v) {
        v->visit(this);
    }

    template<>
    void ASTLiteralNode<float>::accept(visitor::Visitor *v) {
        v->visit(this);
    }

    template<>
    void ASTLiteralNode<bool>::accept(visitor::Visitor *v) {
        v->visit(this);
    }

    template<>
    void ASTLiteralNode<std::string>::accept(visitor::Visitor *v) {
        v->visit(this);
    }
}

void ASTFunctionCallNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTIdentifierNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTUnaryExprNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTDeclarationNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTAssignmentNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTPrintNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTReturnNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTBlockNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTIfNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTWhileNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTFunctionDefinitionNode::accept(visitor::Visitor *v){
    v -> visit(this);
}

void ASTProgramNode::accept(visitor::Visitor *v){
    v -> visit(this);
}