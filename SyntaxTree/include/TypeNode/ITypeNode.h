//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>

namespace SyntaxTree {
    class ITypeNode : public INodeBase {
    public:
        [[nodiscard]] virtual std::string get_name() const = 0;
    };
}
