//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <IdentifierNode/IdentifierNode.h>
#include <DeclarationNode/DeclarationVarNode.h>
#include <DeclarationNode/DeclarationMethodNode.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    class DeclarationClassNode : public INodeBase {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IdentifierNode> identifier;
        std::unique_ptr<IdentifierNode> base_class_identifier;
        std::vector<std::unique_ptr<DeclarationVarNode>> variables;
        std::vector<std::unique_ptr<DeclarationMethodNode>> methods;
    };
}
