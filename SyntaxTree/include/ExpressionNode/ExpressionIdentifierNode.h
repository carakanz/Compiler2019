//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "IExpressionNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class ExpressionIdentifierNode : public IExpressionNode {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IdentifierNode> identifier;
    };
}
