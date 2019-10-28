//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionRoundBracketsNode : public virtual IExpressionNode {
    public:
        explicit ExpressionRoundBracketsNode(std::unique_ptr<IExpressionNode> expression)
                : expression_(std::move(expression)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_ROUND_BRACKETS;
        }

        [[nodiscard]] const IExpressionNode *get_expression() const {
            return expression_.get();
        }

        ~ExpressionRoundBracketsNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> expression_;
    };
}
