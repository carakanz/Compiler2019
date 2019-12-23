//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include "IRTree/IRTreeWrappers.h"

IRTree::RelativeConditionalWrapper::RelativeConditionalWrapper(
        const std::unique_ptr<const IExpressionNode> &_leftOperand,
        const std::unique_ptr<const IExpressionNode> &_rightOperand)
        :   leftOperand(_leftOperand),
        rightOperand(_rightOperand)
        {}

IRTree::AndConditionalWrapper::AndConditionalWrapper(std::unique_ptr<const IWrapper> &&_leftOperand,
                                                     std::unique_ptr<const IWrapper> &&_rightOperand)
                                                     :   leftOperand_(std::move(_leftOperand)),
                                                     rightOperand_(std::move(_rightOperand))
                                                     {}


IRTree::OrConditionalWrapper::OrConditionalWrapper(std::unique_ptr<const IWrapper> &&_leftOperand,
                                                   std::unique_ptr<const IWrapper> &&_rightOperand)
                                                   :   leftOperand_(std::move(_leftOperand)),
                                                   rightOperand_(std::move(_rightOperand))
                                                   {}


//const std::unique_ptr<const IRTree::IStatementNode> &IRTree::ExpressionWrapper::to_statement() const {
//    return std::move(expression_);
//}
