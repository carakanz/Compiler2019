//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionRoundBracketsNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_ROUND_BRACKETS;
        }
        std::unique_ptr<IExpressionNode> expression;
    };
}
