//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <IRTree/INodeBase.h>
#include <unordered_map>

namespace IRTree {
    class TempNode : public INodeBase {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::string label;
        static std::unordered_map<std::string, size_t > counters;
    };
}
