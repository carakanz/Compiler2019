//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionIntegerLiteralNode : public virtual IExpressionNode {
    public:
        explicit ExpressionIntegerLiteralNode(int value)
                : value_(value) {
        }

        NodeType get_type() const override {
            return NodeType::EXPRESSION_INTEGER_LITERAL;
        }

        int get_value() const {
            return value_;
        }

        ~ExpressionIntegerLiteralNode() override = default;

    private:
        int value_;
    };
}
