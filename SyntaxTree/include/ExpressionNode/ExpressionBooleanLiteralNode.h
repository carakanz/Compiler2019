//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionBooleanLiteralNode : public IExpressionNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_BOOLEAN_LITERAL;
        }

        bool value = true;
    };
}
