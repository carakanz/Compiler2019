//
// Created by l1onsun on 23.12.19.
//
#include "IRTreePrinter.h"


namespace IRTreeVisitor {

    void IRTreeVisitor::visit(const IRTree::ExpressionBinaryOperationNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionBinaryOperationNode: " << static_cast<int>(node.operation_type) << "\" shape=box]\n";
        node.left->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.left.get() << "\"" << "\n";
        node.right->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.right.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionCallNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionCallNode\" shape=box]\n";
        node.method->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.method.get() << "\"" << "\n";
        for (const auto& arg : node.arguments) {
            arg->accept(*this);
            out_ << "\"" << &node << "\"" << " -> " << "\"" << arg.get() << "\"" << "\n";
        }
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionConstNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionConstNode: " << node.value << "\" shape=box]\n";
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionESeqNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionESeqNode\" shape=box]\n";
        node.expression->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
        node.statement->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.statement.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionLocalNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionLocalNode: " << node.name << "\" shape=box]\n";
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionMemoryNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionMemoryNode\" shape=box]\n";
        node.expression->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionNameNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionNameNode\" shape=box]\n";
        node.label->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.label.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::ExpressionTempNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"ExpressionTempNode\" shape=box]\n";
        node.temp->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.temp.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::LabelNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"LabelNode: " << node.label  << "\" shape=box]\n";
    }

    void IRTreeVisitor::visit(const IRTree::StatementCJumpNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementCJumpNode: " << static_cast<int>(node.condition)
             << "\" shape=box]\n";
        node.left_expression->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.left_expression.get() << "\"" << "\n";
        node.right_expression->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.right_expression.get() << "\"" << "\n";
        node.negative_label->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.negative_label.get() << "\"" << "\n";
        node.positive_label->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.positive_label.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::StatementExpressionNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementExpressionNode\" shape=box]\n";
        node.expression->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.expression.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::StatementJumpNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementJumpNode\" shape=box]\n";
        node.label->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.label.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::StatementLabelNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementLabelNode\" shape=box]\n";
        node.label->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.label.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::StatementMoveNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementMoveNode\" shape=box]\n";
        node.source->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.source.get() << "\"" << "\n";
        node.destination->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.destination.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::StatementSeqNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"StatementSeqNode\" shape=box]\n";
        node.left->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.left.get() << "\"" << "\n";
        node.right->accept(*this);
        out_ << "\"" << &node << "\"" << " -> " << "\"" << node.right.get() << "\"" << "\n";
    }

    void IRTreeVisitor::visit(const IRTree::TempNode &node) {
        out_ << "\"" << &node << "\"" << " [label=\"TempNode: " << node.label << "\" shape=box]\n";
    }

    void IRTreeVisitor::visit(const SyntaxTreeVisitor::IRTreeGoal &goal) {
        for (const auto& class_info : goal.wrappers) {
            for (const auto& method_info : class_info.second) {
                method_info.second->accept(*this);
            }
        }
    }
    
    void IRTreeVisitor::visit_linear(const SyntaxTreeVisitor::IRTreeGoal &goal) {
    	for (const auto& class_info : goal.linear_wrappers) {
            for (const auto& method_info : class_info.second) {
                for (const auto& statement : method_info.second) {
					statement->accept(*this);
                }
            }
        }
    }
}
