//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <LabelNode/LabelNode.h>
#include "IStatementNode.h"

namespace IRTree {
    class StatementLabelNode : public IStatementNode {
    public:
        StatementLabelNode(std::unique_ptr<const LabelNode>&& label) : label(std::move(label)){}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<const LabelNode> label;
    };
}
