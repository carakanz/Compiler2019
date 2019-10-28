//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionIndexNode : public virtual IExpressionNode {
    public:
        ExpressionIndexNode(std::unique_ptr<IExpressionNode> array,
                            std::unique_ptr<IExpressionNode> index)
                : array_(std::move(array)),
                  index_(std::move(index)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_INDEX;
        }

        [[nodiscard]] const IExpressionNode* get_left() const {
            return array_.get();
        }

        [[nodiscard]] const IExpressionNode* get_right() const {
            return index_.get();
        }

        ~ExpressionIndexNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> array_;
        std::unique_ptr<IExpressionNode> index_;
    };
}
