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
        StatementSeqNode(std::vector<std::unique_ptr<IStatementNode>> &&nodes) {
            assert(nodes.size() > 1);
            right = std::move(nodes.back());
            if (nodes.size() == 2) {
                left = std::move(nodes[0]);
            } else {
                nodes.pop_back();
                left = std::make_unique<StatementSeqNode>(std::move(nodes));
            }
        }

        template <class Left, class Right>
        StatementSeqNode(Left &&left_,
                         Right && right_)
                : left(std::move(left_)),
                  right(std::move(right_)) {
            assert(left != nullptr);
            assert(right != nullptr);
        }

        template <class Left, class... Right>
        StatementSeqNode(Left &&left_,
                         Right &&... right_)
                : left(std::move(left_)),
                  right(std::make_unique<StatementSeqNode>(std::forward<Right>(right_)...)) {
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
