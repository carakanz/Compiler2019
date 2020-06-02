//
// Created by Admin on 02.06.2020.
//

#include <IRTree/IVisitor.h>
#include <IRTree/Nodes.h>
#include <IRTree/IRTreeGoal.h>
#include <IRTreeCanonizator.h>
//#include "../../include/ExpressionNode/IExpressionNode.h"
#include <ExpressionNode/ExpressionList.h>
#include <StatementNode/StatementList.h>

#ifndef COMPILER2019_IRTREECALLCANONIZATOR_H
#define COMPILER2019_IRTREECALLCANONIZATOR_H

namespace IRTreeVisitor {
    class IRTreeCallCanonizator : IRTreeVisitor::IRTreeCanonizator {

    public:
        explicit IRTreeCallCanonizator() = default;

        void visit(const IRTree::ExpressionBinaryOperationNode &node) override;

        void visit(const IRTree::ExpressionCallNode &node) override;

        void visit(const IRTree::ExpressionConstNode &node) override;

        void visit(const IRTree::ExpressionESeqNode &node) override;

        void visit(const IRTree::ExpressionLocalNode &node) override;

        void visit(const IRTree::ExpressionMemoryNode &node) override;

        void visit(const IRTree::ExpressionNameNode &node) override;

        void visit(const IRTree::ExpressionTempNode &node) override;

        void visit(const IRTree::LabelNode &node) override;

        void visit(const IRTree::StatementCJumpNode &node) override;

        void visit(const IRTree::StatementExpressionNode &node) override;

        void visit(const IRTree::StatementJumpNode &node) override;

        void visit(const IRTree::StatementLabelNode &node) override;

        void visit(const IRTree::StatementMoveNode &node) override;

        void visit(const IRTree::StatementSeqNode &node) override;

        void visit(const IRTree::TempNode &node) override;

        void visit(const SyntaxTreeVisitor::IRTreeGoal &goal);


    };
}

#endif //COMPILER2019_IRTREECALLCANONIZATOR_H
