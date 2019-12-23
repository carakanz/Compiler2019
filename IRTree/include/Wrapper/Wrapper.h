//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "IWrapper.h"
#include "cassert"

namespace IRTree {
    template<class NodeType>
    class Wrapper : public IWrapper {
    public:
        explicit Wrapper(std::unique_ptr<NodeType> node) : node_(std::move(node)) {
        }

        std::unique_ptr<IExpressionNode> to_expression() override {
            assert(false);
        }

        std::unique_ptr<IStatementNode> to_statement() override {
            assert(false);
        }

        std::unique_ptr<IStatementNode> to_conditional() override {
            assert(false);
        }

    private:
        std::unique_ptr<NodeType> node_;
    };
}
