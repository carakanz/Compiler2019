//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementAssignArrayNode : public IStatementNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_ASSIGN_ARRAY;
        }

        std::unique_ptr<IdentifierNode> identifier;
        std::unique_ptr<IExpressionNode> index;
        std::unique_ptr<IExpressionNode> expression;
    };
}
