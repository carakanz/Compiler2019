//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <IdentifierNode/IdentifierNode.h>
#include <DeclarationNode/PairTypeIdentifierNode.h>
#include <DeclarationNode/DeclarationMethodNode.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    class DeclarationClassNode;
    using DeclarationClassListNode = ListNode<DeclarationClassNode,
            INodeBase,
            NodeType::DECLARATION_CLASS_LIST>;

    class DeclarationClassNode : public virtual INodeBase {
    public:
        DeclarationClassNode(std::unique_ptr<IdentifierNode> identifier,
                             std::unique_ptr<IdentifierNode> base_class_identifier,
                             std::unique_ptr<DeclarationVarListNode> variables,
                             std::unique_ptr<DeclarationMethodListNode> methods)
                : identifier_(std::move(identifier)),
                  base_class_identifier_(std::move(base_class_identifier)),
                  variables_(std::move(variables->items_)),
                  methods_(std::move(methods->items_)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::DECLARATION_CLASS;
        }

        [[nodiscard]] auto get_identifier() const {
            return identifier_.get();
        }

        [[nodiscard]] auto get_base_class_identifier() const {
            return base_class_identifier_.get();
        }

        [[nodiscard]] auto get_first_variable() const {
            return variables_.cbegin();
        }

        [[nodiscard]] auto get_last_variable() const {
            return variables_.cend();
        }

        [[nodiscard]] auto get_first_method() const {
            return methods_.cbegin();
        }

        [[nodiscard]] auto get_last_method() const {
            return methods_.cend();
        }

        ~DeclarationClassNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
        std::unique_ptr<IdentifierNode> base_class_identifier_;
        std::vector<std::unique_ptr<DeclarationVarNode>> variables_;
        std::vector<std::unique_ptr<DeclarationMethodNode>> methods_;
    };
}
