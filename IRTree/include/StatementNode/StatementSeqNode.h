//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <memory>
#include "IStatementNode.h"
#include <cassert>

namespace IRTree {
    class StatementSeqNode : public IStatementNode {
    public:
        StatementSeqNode(std::unique_ptr<IStatementNode> &&left_,
                         std::unique_ptr<IStatementNode> &&right_)
                : left(std::move(left_)),
                  right(std::move(right_)) {
            assert(left != nullptr);
            assert(right != nullptr);
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IStatementNode> left;
        std::unique_ptr<IStatementNode> right;
    };
}
