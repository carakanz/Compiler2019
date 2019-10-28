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
    class StatementAssignArrayNode : public virtual IStatementNode {
    public:
        StatementAssignArrayNode(std::unique_ptr<IdentifierNode> identifier,
                                 std::unique_ptr<IExpressionNode> index,
                                 std::unique_ptr<IExpressionNode> expression)
                : identifier_(std::move(identifier)),
                  index_(std::move(index)),
                  expression_(std::move(expression)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::STATEMENT_ASSIGN_ARRAY;
        }

        [[nodiscard]] auto get_identifier() const {
            return identifier_.get();
        }

        [[nodiscard]] auto get_index() const {
            return index_.get();
        }

        [[nodiscard]] auto get_expression() const {
            return expression_.get();
        }

        ~StatementAssignArrayNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
        std::unique_ptr<IExpressionNode> index_;
        std::unique_ptr<IExpressionNode> expression_;
    };
}
