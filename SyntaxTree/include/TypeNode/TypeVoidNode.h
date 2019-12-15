//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"

namespace SyntaxTree {
    class TypeVoidNode : public ITypeNode {
    public:
        void accept(IVisitor& visitor) const override {
            return visitor.visit(*this);
        }

        [[nodiscard]] std::string get_name() const override {
            return "void";
        };
    };
}
