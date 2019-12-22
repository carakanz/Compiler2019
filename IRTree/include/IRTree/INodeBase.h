//
// Created by l1onsun on 21.12.19.
//
#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <IRTree/IVisitor.h>

namespace IRTree {
    class INodeBase {
    public:
        virtual ~INodeBase() = default;
        virtual void accept(IVisitor& visitor) const = 0;
    };

}