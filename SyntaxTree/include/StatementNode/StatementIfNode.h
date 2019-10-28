//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>
#include <memory>
#include <vector>

namespace SyntaxTree {
    class StatementIfNode : public virtual IStatementNode {
    public:
        StatementIfNode(std::unique_ptr<IExpressionNode> conditional,
                        std::unique_ptr<IStatementNode> then_statement,
                        std::unique_ptr<IStatementNode> else_statement)
                : conditional_(std::move(conditional)),
                  then_statement_(std::move(then_statement)),
                  else_statement_(std::move(else_statement)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_IF;
        }

        [[nodiscard]] auto get_conditional() const {
            return conditional_.get();
        }

        [[nodiscard]] auto get_then() const {
            return then_statement_.get();
        }

        [[nodiscard]] auto get_else() const {
            return else_statement_.get();
        }

        ~StatementIfNode() override = default;

    private:
        std::unique_ptr<IExpressionNode> conditional_;
        std::unique_ptr<IStatementNode> then_statement_;
        std::unique_ptr<IStatementNode> else_statement_;
    };
}
