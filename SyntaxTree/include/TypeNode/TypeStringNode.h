//
// Created by Zinenko Dmytro on 05.11.2019.
//
#pragma once

#include "ITypeNode.h"

namespace SyntaxTree {
    class TypeStringNode : public ITypeNode {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::TYPE_STRING;
        }
    };
}
