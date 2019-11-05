//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionIndexNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_INDEX;
        }
        std::unique_ptr<IExpressionNode> array;
        std::unique_ptr<IExpressionNode> index;
    };
}
