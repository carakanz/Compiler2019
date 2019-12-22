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

IRTree::AndConditionalWrapper::AndConditionalWrapper(std::unique_ptr<const ISubtreeWrapper> &&_leftOperand,
                                                     std::unique_ptr<const ISubtreeWrapper> &&_rightOperand)
                                                     :   leftOperand(std::move(_leftOperand)),
                                                     rightOperand(std::move(_rightOperand))
                                                     {}


IRTree::OrConditionalWrapper::OrConditionalWrapper(std::unique_ptr<const ISubtreeWrapper> &&_leftOperand,
                                                   std::unique_ptr<const ISubtreeWrapper> &&_rightOperand)
                                                   :   leftOperand(std::move(_leftOperand)),
                                                   rightOperand(std::move(_rightOperand))
                                                   {}


//const std::unique_ptr<const StatementExpressionNode> IRTree::ExpressionWrapper::ToStatement() const {
//    //return makeNode<StatementExpressionNode>(expression);
//}
