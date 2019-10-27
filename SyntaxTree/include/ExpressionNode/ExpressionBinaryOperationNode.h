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
                                      IExpressionNode* left,
                                      IExpressionNode* right)
                : operation_type_(operation_type), left_(left), right_(right) {
        }

        NodeType get_type() const override {
            return NodeType::EXPRESSION_BINARY_OPERATION;
        }

        const IExpressionNode* get_left() const {
            return left_.get();
        }

        const IExpressionNode* get_right() const {
            return right_.get();
        }

        BinaryOperationType get_operation_type() const {
            return operation_type_;
        }

        ~ExpressionBinaryOperationNode() override = default;

    private:
        BinaryOperationType operation_type_;
        std::unique_ptr<IExpressionNode> left_;
        std::unique_ptr<IExpressionNode> right_;
    };
}
