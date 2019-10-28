//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionGetLengthNode : public virtual IExpressionNode {
    public:
        explicit ExpressionGetLengthNode(std::unique_ptr<IExpressionNode> array)
                : array_(std::move(array)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_GET_LENGHT;
        }

        [[nodiscard]] const IExpressionNode *get_array() const {
            return array_.get();
        }

        ~ExpressionGetLengthNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> array_;
    };
}
