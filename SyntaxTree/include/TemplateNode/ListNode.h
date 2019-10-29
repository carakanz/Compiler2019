//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    template<class Source, class Interface, NodeType type>
    class ListNode : public virtual Interface {
    public:
        ListNode(std::unique_ptr<ListNode> original,
                 std::unique_ptr<Source> new_item)
                : items_(std::move(original->items_)) {
            items_.push_back(std::move(new_item));
        }

        ListNode(std::unique_ptr<Source> first_item,
                 std::unique_ptr<Source> second_item)
                : items_({std::move(first_item), std::move(second_item)}) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return type;
        }

        ~ListNode() override = default;

        std::vector<std::unique_ptr<Source>> items_;
    };
}
