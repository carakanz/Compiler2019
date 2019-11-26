//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"
#include <memory>

namespace SyntaxTree {
    class TypeArrayNode : public ITypeNode {
    public:
        TypeArrayNode() = default;

        explicit TypeArrayNode(std::unique_ptr<ITypeNode> type_)
                : type(std::move(type_)) {
        }

        void accept(IVisitor& visitor) const override {
            return visitor.visit(*this);
        }

        std::unique_ptr<ITypeNode> type;
    };
}
