//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"
#include <memory>

namespace SyntaxTree {
    class TypeArrayNode : public virtual ITypeNode {
    public:
        explicit TypeArrayNode(ITypeNode *type)
                : type_(type) {
        }

        NodeType get_type() const override {
            return NodeType::TYPE_ARRAY;
        }

        const ITypeNode *get_array_type() const {
            return type_.get();
        }

        ~TypeArrayNode() override = default;

    private:
        std::unique_ptr<ITypeNode> type_;
    };
}
