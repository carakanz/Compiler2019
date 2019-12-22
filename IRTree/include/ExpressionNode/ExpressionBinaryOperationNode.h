//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <BinaryOperationType.h>

namespace IRTree {
    class ExpressionBinaryOperationNode : public IExpressionNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        BinaryOperationType operation_type;
        std::unique_ptr<IExpressionNode> left;
        std::unique_ptr<IExpressionNode> right;
    };
}
