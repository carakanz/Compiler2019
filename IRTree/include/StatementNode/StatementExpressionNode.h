//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <memory>
#include "IStatementNode.h"
#include <ExpressionNode/IExpressionNode.h>

namespace IRTree {
    class StatementExpressionNode : public IStatementNode {
    public:
        StatementExpressionNode(const std::unique_ptr<const SyntaxTree::IExpressionNode> uniquePtr) {
            //autocreation
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<SyntaxTree::IExpressionNode> expression;
    };
}
