//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <string>

namespace SyntaxTree {
    class IdentifierNode : public INodeBase {
    public:
        [[nodiscard]] NodeType get_type() const override {
            return NodeType::IDENTIFIER_NODE;
        }
        std::string name;
    };
}
