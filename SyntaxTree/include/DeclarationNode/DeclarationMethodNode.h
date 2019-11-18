//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <TypeNode/ITypeNode.h>
#include <IdentifierNode/IdentifierNode.h>
#include <DeclarationNode/PairTypeIdentifierNode.h>
#include <StatementNode/IStatementNode.h>
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    class DeclarationMethodNode : public INodeBase {
    public:
        enum PrivacyModifier {
            PUBLIC,
            PRIVATE
        };

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::DECLARATION_METHOD;
        }
        PrivacyModifier privacy_modifier;
        bool is_static = true;
        std::unique_ptr<ITypeNode> return_type;
        std::unique_ptr<IdentifierNode> identifier;
        std::vector<std::unique_ptr<PairTypeIdentifierNode>> arguments;
        std::vector<std::unique_ptr<DeclarationVarNode>> variables;
        std::vector<std::unique_ptr<IStatementNode>> statements;
    };
}
