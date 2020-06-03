    //
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <IRTree/INodeBase.h>
#include <unordered_map>

namespace IRTree {
    class TempNode : public INodeBase {
    public:
        explicit TempNode(const std::string& label_) {
            static uint32_t counters;
            label = label_ + "@" + std::to_string(++counters);
        }

	TempNode(const std::string& label_, bool forward_counter) {
	    static uint32_t counters;
	    if(forward_counter) {
		label = label_ + "@" + std::to_string(++counters);
	    } else {
		label = label_ + "@" + std::to_string(counters);
	    }
	}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        TempNode(const TempNode& other) : label(other.label) {};

        std::string label;
    };
}
