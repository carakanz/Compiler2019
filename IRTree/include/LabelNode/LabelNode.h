//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <IRTree/INodeBase.h>
#include <unordered_map>
#include <utility>

namespace IRTree {
    class LabelNode : public INodeBase {
    public:
        explicit LabelNode(const std::string& label_) {
            label = label_ + "@" + std::to_string(++counters);
        }

        LabelNode(LabelNode& copy) {
            label = copy.label;
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::string label;
        static uint32_t counters;
    };
}
