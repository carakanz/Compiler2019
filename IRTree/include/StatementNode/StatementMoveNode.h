//
// Created by Zinenko Dmytro on 22.12.2019.
//
#pragma once

#include <ExpressionNode/IExpressionNode.h>
#include <jpeglib.h>
#include "IStatementNode.h"

namespace IRTree {
    class StatementMoveNode : public IStatementNode {
    public:
        StatementMoveNode(std::unique_ptr<const IExpressionNode>&& source,
                          std::unique_ptr<const ExpressionConstNode>&& destination)
                          : source(std::move(source)),
                            destination(std::move(destination))
                            {}

        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<const IExpressionNode> source;
        std::unique_ptr<const IExpressionNode> destination;
    };
}
