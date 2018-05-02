//
// Created by lukec on 22/04/18.
//

#ifndef MINILANG_AST_H
#define MINILANG_AST_H

#include <string>
#include <vector>
#include "../visitor/visitor.h"

namespace parser {

    // Types
    enum TYPE {INT, REAL, BOOL, STRING};


    // Abstract Nodes
    class ASTNode {
        public:
            virtual void accept(visitor::Visitor*) = 0;
    };

    class ASTStatementNode : public ASTNode {
        public:
            void accept(visitor::Visitor*) override = 0;
    };

    class ASTExprNode : public ASTNode {
    public:
        void accept(visitor::Visitor*) override = 0;
    };

    // Statement Nodes
    class ASTProgramNode : public ASTNode {
    public:
        explicit ASTProgramNode(std::vector<ASTStatementNode*>);
        std::vector<ASTStatementNode*> statements;
        void accept(visitor::Visitor*) override;
    };

    class ASTDeclarationNode : public ASTStatementNode {
    public:
        ASTDeclarationNode(TYPE, std::string, ASTExprNode*);
        TYPE type;
        std::string identifier;
        ASTExprNode *expr;
        void accept(visitor::Visitor*) override;
    };

    class ASTAssignmentNode : public ASTStatementNode {
    public:
        ASTAssignmentNode(std::string, ASTExprNode*);
        std::string identifier;
        ASTExprNode *expr;
        void accept(visitor::Visitor*) override;
    };

    class ASTPrintNode : public ASTStatementNode {
    public:
        explicit ASTPrintNode(ASTExprNode*);
        ASTExprNode *expr;
        void accept(visitor::Visitor*) override;
    };

    class ASTReturnNode : public ASTStatementNode {
    public:
        explicit ASTReturnNode(ASTExprNode*);
        ASTExprNode *expr;
        void accept(visitor::Visitor*) override;
    };

    class ASTBlockNode : public ASTStatementNode {
    public:
        explicit ASTBlockNode(std::vector<ASTStatementNode*>);
        std::vector<ASTStatementNode*> statements;
        void accept(visitor::Visitor*) override;
    };

    class ASTIfNode : public ASTStatementNode {
    public:
        ASTIfNode(ASTExprNode*, ASTBlockNode*, ASTBlockNode* = nullptr);
        ASTExprNode *condition;
        ASTBlockNode *if_block;
        ASTBlockNode *else_block;
        void accept(visitor::Visitor*) override;
    };

    class ASTWhileNode : public ASTStatementNode {
    public:
        ASTWhileNode(ASTExprNode*, ASTBlockNode*);
        ASTExprNode *condition;
        ASTBlockNode *block;
        void accept(visitor::Visitor*) override;
    };

    class ASTFunctionDefinitionNode : public ASTStatementNode {
    public:
        ASTFunctionDefinitionNode(std::string, std::vector<std::pair<std::string, TYPE>>,
                                  TYPE, ASTBlockNode*);
        std::string identifier;
        std::vector<std::pair<std::string, TYPE>> parameters;
        std::vector<TYPE> signature;
        TYPE type;
        ASTBlockNode* block;
        void accept(visitor::Visitor*) override;
    };

    // Expression Nodes
    template <typename T>
    class ASTLiteralNode : public ASTExprNode {
        public:
            explicit ASTLiteralNode(T val) : val(val) {};
            T val;
            void accept(visitor::Visitor*) override;
    };

    class ASTBinaryExprNode : public ASTExprNode {

    public:
        ASTBinaryExprNode(std::string, ASTExprNode*, ASTExprNode*);
        std::string op;
        ASTExprNode *left;
        ASTExprNode *right;
        void accept(visitor::Visitor*) override;
    };

    class ASTIdentifierNode : public ASTExprNode {
        public:
            explicit ASTIdentifierNode(std::string);
            std::string identifier;
            void accept(visitor::Visitor*) override;
    };

    class ASTUnaryExprNode : public ASTExprNode {
        public:
            ASTUnaryExprNode(std::string, ASTExprNode*);
            std::string unary_op;
            ASTExprNode *expr;
            void accept(visitor::Visitor*) override;
    };

    class ASTFunctionCallNode : public ASTExprNode {
    public:
        ASTFunctionCallNode(std::string, std::vector<ASTExprNode*>);
        std::string identifier;
        std::vector<ASTExprNode*> parameters;
        void accept(visitor::Visitor*) override;
    };
}


#endif //MINILANG_AST_H
