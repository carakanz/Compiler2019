//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include <fstream>
#include <IRTree/IVisitor.h>
#include "../../../SyntaxTree/Visitors/include/IRTreeGoal.h"

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

        void visit(const ExpressionBinaryOperationNode& node) override ;
        void visit(const ExpressionCallNode& node) override;
        void visit(const ExpressionConstNode& node) override;
        void visit(const ExpressionESeqNode& node) override;
        void visit(const ExpressionLocalNode& node)override;
        void visit(const ExpressionMemoryNode& node)override;
        void visit(const ExpressionNameNode& node)override;
        void visit(const ExpressionTempNode& node)override;
        void visit(const ExpressionTypeNode& node)override;
        void visit(const LabelNode& node)override;
        void visit(const StatementCJumpNode& node)override;
        void visit(const StatementExpressionNode& node)override;
        void visit(const StatementJumpNode& node)override;
        void visit(const StatementLabelNode& node)override;
        void visit(const StatementMoveNode& node)override;
        void visit(const StatementSeqNode& node)override;
        void visit(const TempNode& node)override;

        virtual void visit(const SyntaxTreeVisitor::IRTreeGoal&) = 0;
    private:
        std::ofstream &out_;
    };
}