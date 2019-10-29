//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <TemplateNode/ListNode.h>

namespace SyntaxTree {
    class IStatementNode;
    using StatementListNode = ListNode<IStatementNode, IStatementNode, STATEMENT_LIST>;

    class IStatementNode : public virtual INodeBase {
    public:
        ~IStatementNode() override = default;
    };
}
