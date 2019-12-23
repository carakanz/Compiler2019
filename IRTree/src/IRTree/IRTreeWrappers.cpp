//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include "IRTree/IRTreeWrappers.h"


namespace IRTree {

    RelativeConditionalWrapper::RelativeConditionalWrapper(
            const std::unique_ptr<const IExpressionNode> &_leftOperand,
            const std::unique_ptr<const IExpressionNode> &_rightOperand)
            : leftOperand(_leftOperand),
              rightOperand(_rightOperand) {}

    AndConditionalWrapper::AndConditionalWrapper(std::unique_ptr<const IWrapper> &&_leftOperand,
                                                         std::unique_ptr<const IWrapper> &&_rightOperand)
            : leftOperand_(std::move(_leftOperand)),
              rightOperand_(std::move(_rightOperand)) {}


    OrConditionalWrapper::OrConditionalWrapper(std::unique_ptr<const IWrapper> &&_leftOperand,
                                                       std::unique_ptr<const IWrapper> &&_rightOperand)
            : leftOperand_(std::move(_leftOperand)),
              rightOperand_(std::move(_rightOperand)) {}


    std::unique_ptr<const IStatementNode> ExpressionWrapper::to_statement() {
        //return makeNode<StatementExpressionNode>(expression_);
        return std::make_unique<StatementExpressionNode>(expression_);
    }

    std::unique_ptr<const IStatementNode>
    ExpressionWrapper::to_conditional(std::unique_ptr<const LabelNode> &positiveLabel,
                                      std::unique_ptr<const LabelNode> &negativeLabel) {
        auto x = std::make_unique<ExpressionConstNode>(1);
        StatementCJumpNode(std::move(expression_),
                std::make_unique<ExpressionConstNode>(1),
                           std::move(positiveLabel),
                           std::move(negativeLabel));
//        return std::make_unique<StatementCJumpNode>(expression_,
//                std::make_unique<ExpressionConstNode>(1),
//                        positiveLabel,
//                        negativeLabel);
    }


}