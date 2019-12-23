//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "../Wrapper.h"
#include "cassert"

namespace IRTree {
    template<BinaryOperationType operation_type>
    class WrapperExpressionBinaryOperation : public IWrapper {
    public:
        WrapperExpressionBinaryOperation(std::unique_ptr<IWrapper> &&left, std::unique_ptr<IWrapper> &&right)
                : left_(std::move(left)), right_(std::move(right)) {
        }

        std::unique_ptr<IExpressionNode> to_expression() override { assert(false); }

        std::unique_ptr<IStatementNode> to_statement() override { assert(false); }

        std::unique_ptr<IStatementNode> to_conditional() override { assert(false); }

    private:
        std::unique_ptr<IWrapper> left_;
        std::unique_ptr<IWrapper> right_;
    };
}
