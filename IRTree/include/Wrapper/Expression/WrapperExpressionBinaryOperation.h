//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "../Wrapper.h"
#include "cassert"

namespace IRTree {
    template<BinaryOperationType operation_type>
    class WrapperExpressionBinaryOperation : public IWrapper {
    public:
        WrapperExpressionBinaryOperation(std::unique_ptr<IWrapper> &&left, std::unique_ptr<IWrapper> &&right)
                : left_(std::move(left)), right_(std::move(right)) {
        }

        std::unique_ptr<IExpressionNode> to_expression() override {
            return std::make_unique<ExpressionBinaryOperationNode>(operation_type,
                                                                   left_->to_expression(),
                                                                   right_->to_expression());
        }

        std::unique_ptr<IStatementNode> to_statement() override {
            return std::make_unique<StatementSeqNode>(left_->to_statement(),
                                                      right_->to_statement());
        }

        std::unique_ptr<IStatementNode> to_conditional(std::unique_ptr<LabelNode>& true_label,
                                                       std::unique_ptr<LabelNode>& false_label) override {
            switch (operation_type) {
                case BinaryOperationType::EQUIVALENT:
                    return std::make_unique<StatementCJumpNode>(CJumpCondition::EQUIVALENT,
                                                                left_->to_expression(),
                                                                right_->to_expression(),
                                                                std::move(true_label),
                                                                std::move(false_label));
                case BinaryOperationType::NOT_EQUIVALENT:
                    return std::make_unique<StatementCJumpNode>(CJumpCondition::NOT_EQUIVALENT,
                                                                left_->to_expression(),
                                                                right_->to_expression(),
                                                                std::move(true_label),
                                                                std::move(false_label));
                case BinaryOperationType::LESS:
                    return std::make_unique<StatementCJumpNode>(CJumpCondition::LESS,
                                                                left_->to_expression(),
                                                                right_->to_expression(),
                                                                std::move(true_label),
                                                                std::move(false_label));
                case BinaryOperationType::LESS_OR_EQUIVALENT:
                    return std::make_unique<StatementCJumpNode>(CJumpCondition::LESS_OR_EQUIVALENT,
                                                                left_->to_expression(),
                                                                right_->to_expression(),
                                                                std::move(true_label),
                                                                std::move(false_label));
                case BinaryOperationType::MORE:
                    return std::make_unique<StatementCJumpNode>(CJumpCondition::LESS_OR_EQUIVALENT,
                                                                left_->to_expression(),
                                                                right_->to_expression(),
                                                                std::move(false_label),
                                                                std::move(true_label));
                case BinaryOperationType::MORE_OR_EQUIVALENT:
                    return std::make_unique<StatementCJumpNode>(CJumpCondition::LESS,
                                                                left_->to_expression(),
                                                                right_->to_expression(),
                                                                std::move(false_label),
                                                                std::move(true_label));
                default:
                    assert(false);
            }
        }

    private:
        std::unique_ptr<IWrapper> left_;
        std::unique_ptr<IWrapper> right_;
    };
}
