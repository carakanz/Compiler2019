//
// Created by Zinenko Dmytro on 27.10.2019.
//
#pragma once

#include <INodeBase.h>
#include <DeclarationNode/DeclarationClassNode.h>
#include <memory>
#include <utility>
#include <vector>

namespace SyntaxTree {
    class GoalNode : public virtual INodeBase {
    public:
        explicit GoalNode(std::unique_ptr<DeclarationClassListNode> classes)
                : classes_(std::move(classes->items_)) {
        }

        [[nodiscard]] NodeType get_type() const override {
            return NodeType::GOAL;
        }

        [[nodiscard]] auto get_first_class() const {
            return classes_.cbegin();
        }

        [[nodiscard]] auto get_last_class() const {
            return classes_.cend();
        }

        ~GoalNode() override = default;

    private:
        std::vector<std::unique_ptr<DeclarationClassNode>> classes_;
    };
}
