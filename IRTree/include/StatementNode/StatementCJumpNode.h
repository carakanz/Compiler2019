//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <LabelNode/LabelNode.h>
#include <ExpressionNode/IExpressionNode.h>
#include <CJumpCondition.h>
#include "IStatementNode.h"

namespace IRTree {

    class StatementCJumpNode : public IStatementNode {
    public:
        StatementCJumpNode(std::unique_ptr<const IExpressionNode>&& left_expression,
                           std::unique_ptr<const IExpressionNode>&& right_expression,
                           std::unique_ptr<const LabelNode>&& positive_label,
                           std::unique_ptr<const LabelNode>&& negative_label)
                           : left_expression(std::move(left_expression)),
                             right_expression(std::move(right_expression)),
                             positive_label(std::move(positive_label)),
                             negative_label(std::move(negative_label))
                           {}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        CJumpCondition condition;
        std::unique_ptr<const IExpressionNode> left_expression;
        std::unique_ptr<const IExpressionNode> right_expression;
        std::unique_ptr<const LabelNode> positive_label;
        std::unique_ptr<const LabelNode> negative_label;
    };
}
