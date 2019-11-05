//
// Created by Zinenko Dmytro on 29.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementReturnNode : public IStatementNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_RETURN;
        }

        std::unique_ptr<IExpressionNode> expression;
    };
}
