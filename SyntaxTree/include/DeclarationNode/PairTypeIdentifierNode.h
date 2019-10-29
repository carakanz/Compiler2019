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
    using DeclarationVarListNode = ListNode<DeclarationVarNode,
            INodeBase,
            NodeType::DECLARATION_VAR_LIST>;
    using DeclarationMethodArgListNode = ListNode<PairTypeIdentifierNode,
            INodeBase,
            NodeType::DECLARATION_METHOD_ARG_LIST>;

    class PairTypeIdentifierNode : public virtual INodeBase {
    public:
        PairTypeIdentifierNode(std::unique_ptr<ITypeNode> var_type,
                               std::unique_ptr<IdentifierNode> identifier)
                : var_type_(std::move(var_type)),
                  identifier_(std::move(identifier)){
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::PAIR_TYPE_IDENTIFIER;
        }

        [[nodiscard]] auto get_var_type() const {
            return var_type_.get();
        }

        [[nodiscard]] auto get_identifier() const {
            return identifier_.get();
        }

        ~PairTypeIdentifierNode() override = default;

    private:
        std::unique_ptr<ITypeNode> var_type_;
        std::unique_ptr<IdentifierNode> identifier_;
    };
}
