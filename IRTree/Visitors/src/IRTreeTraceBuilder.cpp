//
// Created by carak on 02.06.2020.
//

#include <IRTreeTraceBuilder.h>

namespace IRTreeVisitor {

    IRTree::ProgramInBlock IRTreeTraceBuilder::run() {
        IRTree::ProgramInBlock result;
        for (auto &block_class : program_) {
            for (auto &block_method : block_class.second) {
                current_method_ = &block_method.second;
                result[block_class.first][block_method.first] = build_method();
            }
        }
        return result;
    }

    IRTree::MethodInBlock IRTreeTraceBuilder::build_method() {
        IRTree::MethodInBlock result;
        for (auto block = current_method_->begin();
             block != current_method_->end();
             ++block) {
            auto &next_block = *(block + 1);
            result.push_back(std::move(*block));

            if (block + 1 == current_method_->end()) {
                continue;
            }

            auto &current_block = result.back();
            current_block.back()->accept(*this);
            next_block.front()->accept(*this);

            assert(!label.empty());
            assert(!positive_label.empty());

            if (label == negative_label) {
                continue;
            } else if (!negative_label.empty()) {
                IRTree::IStatementNode &statement_node = *current_block.back();
                auto &cjump_node = dynamic_cast<IRTree::StatementCJumpNode &>(statement_node);
                if (label == positive_label) {
                    std::swap(cjump_node.negative_label, cjump_node.negative_label);
                    std::swap(cjump_node.left_expression, cjump_node.right_expression);
                } else {
                    assert(false);
                    IRTree::Block new_block;
                    auto new_label = std::make_unique<IRTree::StatementLabelNode>(
                            std::make_unique<IRTree::LabelNode>("temp"));
                    auto new_jump = std::make_unique<IRTree::StatementJumpNode>(
                            std::move(cjump_node.negative_label));
                    cjump_node.negative_label = std::make_unique<IRTree::LabelNode>(*new_label->label);
                    new_block.push_back(std::move(new_label));
                    new_block.push_back(std::move(new_jump));
                    result.push_back(std::move(new_block));
                }
            } else if (negative_label.empty() && label == positive_label) {
                current_block.pop_back();
            }
        }
        return result;
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionBinaryOperationNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionCallNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionConstNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionESeqNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionLocalNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionMemoryNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionNameNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::ExpressionTempNode &/*node*/) {
        assert(false);;
    }

    void IRTreeTraceBuilder::visit(const IRTree::LabelNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::StatementCJumpNode &node) {
        positive_label = node.positive_label->label;
        negative_label = node.negative_label->label;
    }

    void IRTreeTraceBuilder::visit(const IRTree::StatementExpressionNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::StatementJumpNode &node) {
        positive_label = node.label->label;
        negative_label = "";
    }

    void IRTreeTraceBuilder::visit(const IRTree::StatementLabelNode &node) {
        label = node.label->label;
    }

    void IRTreeTraceBuilder::visit(const IRTree::StatementMoveNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::StatementSeqNode &/*node*/) {
        assert(false);
    }

    void IRTreeTraceBuilder::visit(const IRTree::TempNode &/*node*/) {
        assert(false);
    }


}