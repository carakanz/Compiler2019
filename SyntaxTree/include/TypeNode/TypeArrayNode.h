//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"
#include <memory>

namespace SyntaxTree {
    class TypeArrayNode : public virtual ITypeNode {
    public:
        explicit TypeArrayNode(std::unique_ptr<ITypeNode> type)
                : type_(std::move(type)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::TYPE_ARRAY;
        }

        [[nodiscard]] const ITypeNode *get_array_type() const {
            return type_.get();
        }

        ~TypeArrayNode() override = default;

    private:
        std::unique_ptr<ITypeNode> type_;
    };
}
