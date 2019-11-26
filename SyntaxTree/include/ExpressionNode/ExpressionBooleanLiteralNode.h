//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <memory>

namespace SyntaxTree {
    class ExpressionBooleanLiteralNode : public IExpressionNode {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        bool value = true;
    };
}
