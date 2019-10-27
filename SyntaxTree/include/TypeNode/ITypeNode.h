//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>

namespace SyntaxTree {
    class ITypeNode : public virtual INodeBase {
    public:
        ~ITypeNode() override = default;
    };
}
