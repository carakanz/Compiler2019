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
        LabelNode(std::string&& label_) {
            if (counters.find(label_) == counters.end() ) {
                counters[label_] = 0;
            }
            label = label_ + std::to_string(counters[label_]++);
        }

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::string label;
        static std::unordered_map<std::string, size_t> counters;
    };
}
