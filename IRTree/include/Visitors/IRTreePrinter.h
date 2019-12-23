//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include <fstream>
#include <IRTree/IVisitor.h>
#include "../../../SyntaxTree/Visitors/include/IRTreeGoal.h"

class ExpressionBinaryOperationNode;
class ExpressionCallNode;
class ExpressionConstNode;
class ExpressionESeqNode;
class ExpressionLocalNode;
class ExpressionMemoryNode;
class ExpressionNameNode;
class ExpressionTempNode;
class ExpressionTypeNode;
class LabelNode;
class StatementCJumpNode;
class StatementExpressionNode;
class StatementJumpNode;
class StatementLabelNode;
class StatementMoveNode;
class StatementSeqNode;
class TempNode;

namespace IRTreeVisitor {
    class IRTreeVisitor : IRTree::IVisitor {
    public:
        explicit IRTreeVisitor(std::ofstream &out) : out_(out) {}

        void print_start(std::string name) {
            size_t dot = name.find('.');
            while (dot != std::string::npos) {
                name.erase(name.find('.'));
                dot = name.find('.');
            }
            out_ << "digraph " << name << " {" << "\n";
        };

        void print_end() {
            out_ << "}" << std::endl;
        };

        virtual void visit(const ExpressionBinaryOperationNode& node) = 0;
        virtual void visit(const ExpressionCallNode& node) = 0;
        virtual void visit(const ExpressionConstNode& node) = 0;
        virtual void visit(const ExpressionESeqNode& node) = 0;
        virtual void visit(const ExpressionLocalNode& node) = 0;
        virtual void visit(const ExpressionMemoryNode& node) = 0;
        virtual void visit(const ExpressionNameNode& node) = 0;
        virtual void visit(const ExpressionTempNode& node) = 0;
        virtual void visit(const ExpressionTypeNode& node) = 0;
        virtual void visit(const LabelNode& node) = 0;
        virtual void visit(const StatementCJumpNode& node) = 0;
        virtual void visit(const StatementExpressionNode& node) = 0;
        virtual void visit(const StatementJumpNode& node) = 0;
        virtual void visit(const StatementLabelNode& node) = 0;
        virtual void visit(const StatementMoveNode& node) = 0;
        virtual void visit(const StatementSeqNode& node) = 0;
        virtual void visit(const TempNode& node) = 0;

        virtual void visit(const SyntaxTreeVisitor::IRTreeGoal&) = 0;
    private:
        std::ofstream &out_;
    };
}