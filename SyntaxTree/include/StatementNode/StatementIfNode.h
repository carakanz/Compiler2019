//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementIfNode : public IStatementNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_IF;
        }

        std::unique_ptr<IExpressionNode> conditional;
        std::unique_ptr<IStatementNode> then_statement;
        std::unique_ptr<IStatementNode> else_statement;
    };
}
