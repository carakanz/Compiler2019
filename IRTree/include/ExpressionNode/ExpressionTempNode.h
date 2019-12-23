//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <TempNode/TempNode.h>
#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionTempNode : public IExpressionNode {
    public:
        ExpressionTempNode(std::unique_ptr<TempNode>&& temp): temp(std::move(temp)){}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<TempNode> temp;
    };
}
