//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <memory>
#include "IStatementNode.h"

namespace IRTree {
    class StatementSeqNode : public IStatementNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IStatementNode> left;
        std::unique_ptr<IStatementNode> right;
    };
}
