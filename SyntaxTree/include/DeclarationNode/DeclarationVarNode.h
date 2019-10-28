//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <IdentifierNode/IdentifierNode.h>
#include <TypeNode/ITypeNode.h>
#include <memory>

namespace SyntaxTree {
    class DeclarationVarNode : public virtual INodeBase {
    public:
        DeclarationVarNode(std::unique_ptr<ITypeNode> var_type,
                           std::unique_ptr<IdentifierNode> identifier)
                : var_type_(std::move(var_type)),
                  identifier_(std::move(identifier)){
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::DECLARATION_VAR;
        }

        [[nodiscard]] auto get_var_type() const {
            return var_type_.get();
        }

        [[nodiscard]] auto get_identifier() const {
            return identifier_.get();
        }

        ~DeclarationVarNode() override = default;

    private:
        std::unique_ptr<ITypeNode> var_type_;
        std::unique_ptr<IdentifierNode> identifier_;
    };
}
