//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionBinaryOperationNode : public virtual IExpressionNode {
    public:
        enum BinaryOperationType {
            ADD,
            SUB,
            MUL,
            DIV,
            MOD,
            OR,
            AND,
            EQUIVALENT,
            NOT_EQUIVALENT,
            LESS,
            LESS_OR_EQUIVALENT,
            MORE,
            MORE_OR_EQUIVALENT
        };

        ExpressionBinaryOperationNode(BinaryOperationType operation_type,
                                      std::unique_ptr<IExpressionNode> left,
                                      std::unique_ptr<IExpressionNode> right)
                : operation_type_(operation_type),
                left_(std::move(left)),
                right_(std::move(right)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::EXPRESSION_BINARY_OPERATION;
        }

        [[nodiscard]] const IExpressionNode* get_left() const {
            return left_.get();
        }

        [[nodiscard]] const IExpressionNode* get_right() const {
            return right_.get();
        }

        [[nodiscard]] BinaryOperationType get_operation_type() const {
            return operation_type_;
        }

        ~ExpressionBinaryOperationNode() override = default;

    private:
        BinaryOperationType operation_type_;
        std::unique_ptr<IExpressionNode> left_;
        std::unique_ptr<IExpressionNode> right_;
    };
}
