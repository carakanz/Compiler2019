//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include "ITypeNode.h"

namespace SyntaxTree {
    class TypeIntNode : public virtual ITypeNode {
        NodeType get_type() const override {
            return NodeType::TYPE_INT;
        }

        ~TypeIntNode() override = default;
    };
}
