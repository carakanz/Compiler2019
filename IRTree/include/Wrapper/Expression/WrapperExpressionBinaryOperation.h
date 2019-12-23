//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "../Wrapper.h"
#include "cassert"

namespace IRTree {
    template<BinaryOperationType operation_type>
    class WrapperExpressionBinaryOperation : public Wrapper<ExpressionBinaryOperationNode> {
    public:
        std::unique_ptr<IExpressionNode> to_expression() override { assert(false); }

        std::unique_ptr<IStatementNode> to_statement() override { assert(false); }

        std::unique_ptr<IStatementNode> to_conditional() override { assert(false); }
    };
}