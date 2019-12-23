//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <LabelNode/LabelNode.h>

#include <utility>
#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionLocalNode : public IExpressionNode {
    public:
        ExpressionLocalNode(bool is_class_var,
                            std::string name) :
                is_class_var(is_class_var),
                name(std::move(name)) {
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        bool is_class_var;
        std::string name;
    };
}
