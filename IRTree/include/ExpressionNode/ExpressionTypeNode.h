//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <LabelNode/LabelNode.h>

#include <utility>
#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionTypeNode : public IExpressionNode {
    public:
        explicit ExpressionTypeNode(std::string class_name) : class_name(std::move(class_name)) {
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::string class_name;
    };
}
