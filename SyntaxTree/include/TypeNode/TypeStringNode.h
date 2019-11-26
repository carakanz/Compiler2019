//
// Created by Zinenko Dmytro on 05.11.2019.
//
#pragma once

#include "ITypeNode.h"

namespace SyntaxTree {
    class TypeStringNode : public ITypeNode {
    public:
        void accept(IVisitor& visitor) const override {
            return visitor.visit(*this);
        }
    };
}
