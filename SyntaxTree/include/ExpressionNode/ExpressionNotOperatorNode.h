//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionNotOperatorNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_NOT_OPERATION;
        }
        std::unique_ptr<IExpressionNode> expression;
    };
}
