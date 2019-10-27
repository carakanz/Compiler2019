//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class ExpressionIdentifierNode : public virtual IExpressionNode {
    public:
        explicit ExpressionIdentifierNode(const IdentifierNode *identifier)
                : identifier_(std::make_unique<IdentifierNode>(identifier)) {
        }

        NodeType get_type() const override {
            return NodeType::EXPRESSION_IDENTIFIER;
        }

        const IdentifierNode* get_identifier() const {
            return identifier_.get();
        }

        ~ExpressionIdentifierNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
    };
ъ
