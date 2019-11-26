//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"

namespace SyntaxTree {
    class TypeIntNode : public ITypeNode {
    public:
        void accept(IVisitor& visitor) const override {
            return visitor.visit(*this);
        }
    };
}
