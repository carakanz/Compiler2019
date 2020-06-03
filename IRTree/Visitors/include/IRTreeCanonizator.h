//
// Created by Admin on 02.06.2020.
//

#include "../include/IRTree/IVisitor.h"
#include "../include/IRTree/Nodes.h"
#include "IRTree/IRTreeGoal.h"

#ifndef COMPILER2019_IRTREECANONIZATOR_H
#define COMPILER2019_IRTREECANONIZATOR_H

namespace IRTreeVisitor {
    class IRTreeCanonizator : public IRTree::IVisitor {
    public:
        void updateLastExp(const IRTree::ExpressionConstNode &node);
        void updateLastExp(const IRTree::ExpressionTempNode &node);
        void updateLastExp(const IRTree::ExpressionNameNode & node);
        void updateLastExp(const IRTree::ExpressionLocalNode &node);

        void updateLastExp( std::unique_ptr<IRTree::IExpressionNode> newLastExp ){
            prevExp = std::move( newLastExp );
        }


        void updateLastStm(const IRTree::StatementJumpNode& node);
        void updateLastStm(const IRTree::StatementLabelNode &node);

        void updateLastStm(std::unique_ptr<IRTree::IStatementNode> newLastStm) {
            prevStm = std::move(newLastStm );
        }

        std::unique_ptr<IRTree::IExpressionNode> prevExp;
        std::unique_ptr<IRTree::IStatementNode> prevStm;
    };
}

#endif //COMPILER2019_IRTREECANONIZATOR_H
