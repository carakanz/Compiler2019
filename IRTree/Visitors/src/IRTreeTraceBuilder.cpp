//
// Created by carak on 02.06.2020.
//

#include <IRTreeTraceBuilder.h>

namespace IRTreeVisitor {

    IRTree::ProgramInBlock TraceBuilder::run() {
        IRTree::ProgramInBlock result;
        for (auto &block_class : program_) {
            for (auto &block_method : block_class.second) {
                current_method_ = &block_method.second;
                result[block_class.first][block_method.first] = build_method();
            }
        }
        return IRTree::ProgramInBlock();
    }

    IRTree::MethodInBlock TraceBuilder::build_method() {
        IRTree::MethodInBlock result;
        for (auto block = current_method_->begin();
             block != current_method_->end();
             ++block) {
            auto& next_block = *(block + 1);
            result.push_back(std::move(*block));
            auto& current_block = result.back();

            current_block.back()->accept(*this);
            next_block.front()->accept(*this);

            assert(!label.empty());
            assert(!positive_label.empty());

            if (label == negative_label) {
                continue;
            } else if (!negative_label.empty()) {
                IRTree::IStatementNode& statement_node = *current_block.back();
                auto& cjump_node = dynamic_cast<IRTree::StatementCJumpNode&>(statement_node);
                if (label != positive_label) {
                    std::swap(cjump_node.negative_label, cjump_node.negative_label);
                    std::swap(cjump_node.left_expression, cjump_node.right_expression);
                } else {
                    assert(false);
                    IRTree::Block new_block;
                    IRTree::LabelNode new_label("temp");
                    IRTree::StatementJumpNode new_jump(std::move(cjump_node.negative_label));
                    cjump_node.negative_label->label = new_label.label;
                }
            } else if (negative_label.empty() && label == positive_label) {
                current_block.pop_back();
            }
        }
        return result;
    }

    void TraceBuilder::visit(const IRTree::ExpressionBinaryOperationNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionCallNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionConstNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionESeqNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionLocalNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionMemoryNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionNameNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::ExpressionTempNode &/*node*/) {
        assert(false);;
    }

    void TraceBuilder::visit(const IRTree::LabelNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::StatementCJumpNode &node) {
        positive_label = node.positive_label->label;
        negative_label = node.negative_label->label;
    }

    void TraceBuilder::visit(const IRTree::StatementExpressionNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::StatementJumpNode &node) {
        positive_label = node.label->label;
        negative_label = "";
    }

    void TraceBuilder::visit(const IRTree::StatementLabelNode &node) {
        label = node.label->label;
    }

    void TraceBuilder::visit(const IRTree::StatementMoveNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::StatementSeqNode &/*node*/) {
        assert(false);
    }

    void TraceBuilder::visit(const IRTree::TempNode &/*node*/) {
        assert(false);
    }


}