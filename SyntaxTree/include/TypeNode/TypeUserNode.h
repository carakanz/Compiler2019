//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class TypeUserNode : public ITypeNode {
    public:
        TypeUserNode() = default;

        explicit TypeUserNode(std::unique_ptr<IdentifierNode> identifier_)
                : identifier(std::move(identifier_)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::TYPE_USER;
        }

        std::unique_ptr<IdentifierNode> identifier;
    };
}
