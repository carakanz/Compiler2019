//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <string>

namespace SyntaxTree {
    class IdentifierNode : public INodeBase {
    public:
        void accept(IVisitor& visitor) const override {
            visitor.visit(*this);
        }

        std::string name;
    };
}
