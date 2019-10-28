//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementPrintlnNode : public virtual IStatementNode {
    public:
        explicit StatementPrintlnNode(std::unique_ptr<IExpressionNode> expression)
                : expression_(std::move(expression)){
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_PRINTLN;
        }

        [[nodiscard]] auto get_expression() const {
            return expression_.get();
        }

        ~StatementPrintlnNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> expression_;
    };
}
