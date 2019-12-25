//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <memory>
#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>

namespace IRTree {
    class StatementExpressionNode : public IStatementNode {
    public:
        explicit StatementExpressionNode(std::unique_ptr<IExpressionNode> &&expression)
                : expression(std::move(expression)) {
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> expression;
    };
}
