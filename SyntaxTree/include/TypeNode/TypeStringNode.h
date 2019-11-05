//
// Created by Zinenko Dmytro on 05.11.2019.
//

#ifndef COMPILER2019_TYPESTRINGNODE_H
#define COMPILER2019_TYPESTRINGNODE_H

#endif //COMPILER2019_TYPESTRINGNODE_H
//
// Created by Zinenko Dmytro on 27.10.2019.
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
