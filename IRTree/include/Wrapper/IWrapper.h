//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "../StatementNode/IStatementNode.h"
#include "../ExpressionNode/IExpressionNode.h"

namespace IRTree {
    class IWrapper  {
    public:
        virtual ~IWrapper() = delete;
        virtual std::unique_ptr<IExpressionNode> to_expression() = 0;
        virtual std::unique_ptr<IStatementNode> to_statement() = 0;
        virtual std::unique_ptr<IStatementNode> to_conditional() = 0;
    };
}