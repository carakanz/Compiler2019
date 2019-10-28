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
    class StatementAssignNode : public virtual IStatementNode {
    public:
        StatementAssignNode(std::unique_ptr<IdentifierNode> identifier,
                            std::unique_ptr<IExpressionNode> expression)
                : identifier_(std::move(identifier)),
                  expression_(std::move(expression)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_ASSIGN;
        }

        [[nodiscard]] auto get_identifier() const {
            return identifier_.get();
        }

        [[nodiscard]] auto get_expression() const {
            return expression_.get();
        }

        ~StatementAssignNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
        std::unique_ptr<IExpressionNode> expression_;
    };
}
