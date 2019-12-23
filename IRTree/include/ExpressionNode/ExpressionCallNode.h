//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include "IExpressionNode.h"
#include "ExpressionNameNode.h"

namespace IRTree {
    class ExpressionCallNode : public IExpressionNode {
    public:
        ExpressionCallNode(std::unique_ptr<IExpressionNode> &&method,
                           std::unique_ptr<ExpressionNameNode> &&name) :
                method(std::move(method)),
                name(std::move(name)) {
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> method;
        std::unique_ptr<ExpressionNameNode> name;
        std::vector<std::unique_ptr<IExpressionNode>> arguments;
    };
}
