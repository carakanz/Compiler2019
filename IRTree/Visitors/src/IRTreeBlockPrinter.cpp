//
// Created by l1onsun on 23.12.19.
//
#include "IRTreeBlockPrinter.h"


namespace IRTreeVisitor {

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionBinaryOperationNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionCallNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionConstNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionESeqNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionLocalNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionMemoryNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionNameNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::ExpressionTempNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::LabelNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockPrinter::visit(const IRTree::StatementCJumpNode &node) {
        out_ << "[label=\"StatementCJumpNode: "
             << static_cast<int>(node.condition)
             << " ? " << node.positive_label->label
             << " : " << node.negative_label->label
             << "\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::StatementExpressionNode &/*node*/) {
        out_ << "[label=\"StatementExpressionNode\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::StatementJumpNode &node) {
        out_ << "[label=\"StatementJumpNode: " << node.label->label << "\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::StatementLabelNode &node) {
        out_ << "[label=\"StatementLabelNode: " << node.label->label << "\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::StatementMoveNode &/*node*/) {
        out_ << "[label=\"StatementMoveNode\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::StatementSeqNode &/*node*/) {
        out_ << "[label=\"StatementSeqNode\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::TempNode &/*node*/) {
        out_ << "[label=\"TempNode\" shape=box]";
    }

    void IRTreeBlockPrinter::visit(const IRTree::ProgramInBlock &goal) {
        std::string program_name = "\"Program\"";
        out_ << "\"" << &goal << "\"" << " [label=" << program_name << " shape=box]\n";
        for (auto& block_class : goal) {
            std::string class_name = "\"Class: " + block_class.first + "\"";
            out_ << "\"" << &block_class << "\"" << " [label=" << class_name << "shape=box]\n";
            out_ << "\"" << &goal << "\"" << " -> " << "\"" << &block_class << "\"" << "\n";
            for (auto &block_method : block_class.second) {
                std::string method_name = "\"Method: " + block_method.first + "\"";
                out_ << "\"" << &block_method << "\"" << " [label=" << method_name << "shape=box]\n";
                out_ << "\"" << &block_class << "\"" << " -> " << "\"" << &block_method << "\"" << "\n";
                const void* last_link = &block_method;
                for (auto &block : block_method.second) {
                    out_ << "subgraph cluster_" << &block << "{\n";
                    out_ << "node [shape=\"box\", style=\"filled\", fillcolor=\"green\", fontcolor=\"black\", fontsize=\"9\"]\n";
                    out_ << "\"" << &block << "\"" << " [label=" << "\"block start\"" << "shape=box]\n";
                    const void* last_statement = &block;
                    for (const auto &statement : block) {
                        out_ << "\"" << &statement << "\" ";
                        statement->accept(*this);
                        out_ << "\n";
                        out_ << "\"" << last_statement << "\"" << " -> " << "\"" << &statement << "\"" << "\n";
                        last_statement = &statement;
                    }
                    out_ <<  "}\n";
                    out_ << "\"" << last_link << "\"" << " -> " << "\"" << &block << "\"" << "\n";
                    last_link = &block;
                }
            }
        }
    }
}
