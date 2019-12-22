//
// Created by l1onsun on 21.12.19.
//
#pragma once


#include <BinaryOperationType.h>
#include <CJumpCondition.h>

namespace IRTree {

    class ExpressionBinaryOperationNode;
    class ExpressionCallNode;
    class ExpressionConstNode;
    class ExpressionESeqNode;
    class ExpressionMemoryNode;
    class ExpressionNameNode;
    class ExpressionTempNode;
    class LabelNode;
    class StatementCJumpNode;
    class StatementExpressionNode;
    class StatementJumpNode;
    class StatementLabelNode;
    class StatementMoveNode;
    class StatementSeqNode;
    class TempNode;

    class IVisitor {
    public:
        virtual void visit(const ExpressionBinaryOperationNode& node) = 0;
        virtual void visit(const ExpressionCallNode& node) = 0;
        virtual void visit(const ExpressionConstNode& node) = 0;
        virtual void visit(const ExpressionESeqNode& node) = 0;
        virtual void visit(const ExpressionMemoryNode& node) = 0;
        virtual void visit(const ExpressionNameNode& node) = 0;
        virtual void visit(const ExpressionTempNode& node) = 0;
        virtual void visit(const LabelNode& node) = 0;
        virtual void visit(const StatementCJumpNode& node) = 0;
        virtual void visit(const StatementExpressionNode& node) = 0;
        virtual void visit(const StatementJumpNode& node) = 0;
        virtual void visit(const StatementLabelNode& node) = 0;
        virtual void visit(const StatementMoveNode& node) = 0;
        virtual void visit(const StatementSeqNode& node) = 0;
        virtual void visit(const TempNode& node) = 0;
        virtual ~IVisitor() = default;
    };
}