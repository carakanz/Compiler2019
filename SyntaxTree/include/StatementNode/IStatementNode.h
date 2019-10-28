//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>

namespace SyntaxTree {
    class IStatementNode : public virtual INodeBase {
    public:
        ~IStatementNode() override = default;
    };
}
