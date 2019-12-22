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
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        CJumpCondition condition;
        std::unique_ptr<IExpressionNode> left_expression;
        std::unique_ptr<IExpressionNode> right_expression;
        std::unique_ptr<LabelNode> positive_label;
        std::unique_ptr<LabelNode> negative_label;
    };
}
