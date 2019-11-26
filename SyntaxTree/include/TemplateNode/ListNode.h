//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    template<class Source, class Interface>
    class ListNode : public Interface {
    public:
        explicit ListNode(std::unique_ptr<Source> source) {
            items.push_back(std::move(source));
        }

        void accept(IVisitor& visitor) const override {
            return visitor.visit(*this);
        }

        std::vector<std::unique_ptr<Source>> items;
    };
}
