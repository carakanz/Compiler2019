//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include "IExpressionNode.h"
#include "ExpressionNameNode.h"

namespace IRTree {
    class ExpressionCallNode : public IExpressionNode {
    public:
        ExpressionCallNode(std::unique_ptr<IExpressionNode> &&method) :
                method(std::move(method)) {
        }

        ExpressionCallNode(
                std::unique_ptr<IExpressionNode> &&method,
                std::vector<std::unique_ptr<IExpressionNode>> & arguments) :
                method(std::move(method)), arguments(std::move(arguments)) {
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> method;
        std::vector<std::unique_ptr<IExpressionNode>> arguments;
    };
}
