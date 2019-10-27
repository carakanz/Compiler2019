//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionNotOperatorNode : public virtual IExpressionNode {
    public:
        explicit ExpressionNotOperatorNode(IExpressionNode* right)
                : right_(right) {
        }

        NodeType get_type() const override {
            return NodeType::EXPRESSION_NOT_OPERATION;
        }

        const IExpressionNode *get_right() const {
            return right_.get();
        }

        ~ExpressionNotOperatorNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> right_;
    };
}
