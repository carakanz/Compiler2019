//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <TemplateNode/ListNode.h>

namespace SyntaxTree {
    class IStatementNode : public INodeBase {};

    using StatementListNode = ListNode<IStatementNode, IStatementNode>;

    class StatementEmptyNode : public IStatementNode {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }
    };
}
