//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <TemplateNode/ListNode.h>
#include <TemplateNode/CloneNode.h>

namespace SyntaxTree {
    class IStatementNode;

    using StatementListNode = ListNode<IStatementNode,
            IStatementNode,
            NodeType::STATEMENT_LIST>;

    using StatementEmptyNode = CloneNode<IStatementNode,
            NodeType::STATEMENT_EMPTY>;

    class IStatementNode : public INodeBase {};
}
