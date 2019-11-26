//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <IdentifierNode/IdentifierNode.h>
#include <TypeNode/ITypeNode.h>
#include <TemplateNode/ListNode.h>
#include <memory>

namespace SyntaxTree {
    class DeclarationVarNode : public INodeBase {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<ITypeNode> var_type;
        std::unique_ptr<IdentifierNode> identifier;
    };
}
