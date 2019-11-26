//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <string>
#include <iostream>
#include "Position.h"
#include <IVisitor.h>

namespace SyntaxTree {
    class INodeBase {
    public:
        virtual void accept(IVisitor& visitor) const = 0;

        Position position{};
        virtual ~INodeBase() = default;
    };
}
