//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementPrintlnNode : public IStatementNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_PRINTLN;
        }

        std::unique_ptr<IExpressionNode> expression;
    };
}
