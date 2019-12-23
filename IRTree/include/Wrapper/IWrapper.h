//
// Created by Zinenko Dmytro on 23.12.2019.
//
#pragma once

#include <memory>
#include "../IRTree/Nodes.h"

namespace IRTree {
    class IWrapper  {
    public:
        virtual ~IWrapper() = default;
        virtual std::unique_ptr<IExpressionNode> to_expression() = 0;
        virtual std::unique_ptr<IStatementNode> to_statement() = 0;
        virtual std::unique_ptr<IStatementNode> to_conditional(std::unique_ptr<LabelNode>& true_label,
                                                               std::unique_ptr<LabelNode>& false_label) = 0;
    };
}