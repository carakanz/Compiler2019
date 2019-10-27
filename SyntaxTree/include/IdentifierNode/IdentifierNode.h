//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>

namespace SyntaxTree {
    class IdentifierNode : public virtual INodeBase {
    public:
        NodeType get_type() const override {
            return NodeType::IDENTIFIER_NODE;
        }
        ~IdentifierNode() override = default;
    };
}
