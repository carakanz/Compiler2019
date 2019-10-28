//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class ExpressionNewNode : public virtual IExpressionNode {
    public:
        explicit ExpressionNewNode(std::unique_ptr<IdentifierNode> identifier)
                : identifier_(std::move(identifier)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_NEW;
        }

        [[nodiscard]] const IdentifierNode *get_identifier() const {
            return identifier_.get();
        }

        ~ExpressionNewNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
    };
}
