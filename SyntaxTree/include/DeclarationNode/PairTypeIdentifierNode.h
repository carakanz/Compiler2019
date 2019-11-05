//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <IdentifierNode/IdentifierNode.h>
#include <TypeNode/ITypeNode.h>
#include <TemplateNode/CloneNode.h>
#include <TemplateNode/ListNode.h>
#include <memory>

namespace SyntaxTree {
    class PairTypeIdentifierNode;

    using DeclarationVarNode = CloneNode<PairTypeIdentifierNode, NodeType::DECLARATION_VAR>;

    class PairTypeIdentifierNode : public INodeBase {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::PAIR_TYPE_IDENTIFIER;
        }
        std::unique_ptr<ITypeNode> var_type;
        std::unique_ptr<IdentifierNode> identifier;
    };
}
