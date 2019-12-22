//
// Created by Zinenko Dmytro on 29.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include "../ExpressionNode/IExpressionNode.h"
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementReturnNode : public IStatementNode {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> expression;
    };
}
