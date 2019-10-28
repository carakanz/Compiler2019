//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"
#include <IdentifierNode/IdentifierNode.h>
#include <memory>

namespace SyntaxTree {
    class TypeUserNode : public virtual ITypeNode {
        explicit TypeUserNode(std::unique_ptr<IdentifierNode> identifier)
                : identifier_(std::move(identifier)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::TYPE_USER;
        }

        [[nodiscard]] const IdentifierNode *get_identifier() const {
            return identifier_.get();
        }

        ~TypeUserNode() override = default;

    private:
        std::unique_ptr<IdentifierNode> identifier_;
    };
}
