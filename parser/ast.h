//
// Created by lukec on 22/04/18.
//

#ifndef MINILANG_AST_H
#define MINILANG_AST_H

#include <string>
#include <vector>

namespace parser {

    // Types
    enum TYPE {INT, REAL, BOOL, STRING};

    class ASTNode {

    };

    class ASTExprNode : public ASTNode {

    };

    class ASTStatementNode : public ASTNode {

    };

    class ASTBinaryExprNode : public ASTExprNode {

        public:
            ASTBinaryExprNode(std::string&, ASTExprNode*, ASTExprNode*);
            std::string op;
            ASTExprNode *left;
            ASTExprNode *right;
    };

    template <class T>
    class ASTLiteralNode : public ASTExprNode {
        public:
            ASTLiteralNode(T val) : val(val) {};
            T val;
    };

    class ASTFunctionCallNode : public ASTExprNode {
        public:
            ASTFunctionCallNode(std::string&, std::vector<ASTExprNode*>);
            std::string identifier;
            std::vector<ASTExprNode*> parameters;
    };

    class ASTIdentifierNode : public ASTExprNode {
        public:
            explicit ASTIdentifierNode(std::string&);
            std::string identifier;
    };

    class ASTUnaryExprNode : public ASTExprNode {
        public:
            ASTUnaryExprNode(std::string&, ASTExprNode*);
            std::string unary_op;
            ASTExprNode* expr;
    };

    class ASTDeclarationNode : public ASTStatementNode {
        public:
            ASTDeclarationNode(TYPE, std::string&, ASTExprNode*);
            TYPE type;
            std::string identifier;
            ASTExprNode *expr;
    };

    class ASTAssignmentNode : public ASTStatementNode {
        public:
            ASTAssignmentNode(std::string&, ASTExprNode*);
            std::string identifier;
            ASTExprNode *expr;
    };



}


#endif //MINILANG_AST_H
