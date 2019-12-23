//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionMemoryNode : public IExpressionNode {
    public:
        explicit ExpressionMemoryNode(std::unique_ptr<IExpressionNode> &&expression) :
                expression(std::move(expression)) {
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> expression;
    };
}
