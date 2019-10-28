//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionBooleanLiteralNode : public virtual IExpressionNode {
    public:
        explicit ExpressionBooleanLiteralNode(bool value)
                : value_(value) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_BOOLEAN_LITERAL;
        }

        [[nodiscard]] bool get_value() const {
            return value_;
        }

        ~ExpressionBooleanLiteralNode() override = default;

    private:
        bool value_;
    };
}
