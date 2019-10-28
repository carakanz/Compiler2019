//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementWhileNode : public virtual IStatementNode {
    public:
        StatementWhileNode(std::unique_ptr<IExpressionNode> conditional,
                           std::unique_ptr<IStatementNode> then_statement)
                : conditional_(std::move(conditional)),
                  then_statement_(std::move(then_statement)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_WHILE;
        }

        // get begin iterator
        [[nodiscard]] auto get_conditional() const {
            return conditional_.get();
        }

        // get end iterator
        [[nodiscard]] auto get_then_statement() const {
            return then_statement_.get();
        }

        ~StatementWhileNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> conditional_;
        std::unique_ptr<IStatementNode> then_statement_;
    };
}
