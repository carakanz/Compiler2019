//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include "../StatementNode/IStatementNode.h"
#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionESeqNode : public IExpressionNode {
    public:
        ExpressionESeqNode(std::unique_ptr<const IStatementNode> statement,
                           std::unique_ptr<const IExpressionNode> expression)
                           : statement(std::move(statement)),
                             expression(std::move(expression))
                           {}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<const IStatementNode> statement;
        std::unique_ptr<const IExpressionNode> expression;
    };
}
