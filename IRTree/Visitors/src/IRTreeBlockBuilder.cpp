//
// Created by carak on 02.06.2020.
//

#include "IRTreeBlockBuilder.h"

namespace IRTreeVisitor {
    IRTree::ProgramInBlock IRTreeBlockBuilder::build(IRTree::ProgramInLine &&tree) {
        IRTreeBlockBuilder builder(std::move(tree));
        return builder.run();
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionBinaryOperationNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionCallNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionConstNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionESeqNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionLocalNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionMemoryNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionNameNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::ExpressionTempNode &/*node*/) {
        assert(false);;
    }

    void IRTreeBlockBuilder::visit(const IRTree::LabelNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::StatementCJumpNode &/*node*/) {
        current_ = NodeType::JUMP;
    }

    void IRTreeBlockBuilder::visit(const IRTree::StatementExpressionNode &/*node*/) {
        current_ = NodeType::OTHER;
    }

    void IRTreeBlockBuilder::visit(const IRTree::StatementJumpNode &/*node*/) {
        current_ = NodeType::JUMP;
    }

    void IRTreeBlockBuilder::visit(const IRTree::StatementLabelNode &node) {
        label_ = node.label.get();
        current_ = NodeType::LABEL;
    }

    void IRTreeBlockBuilder::visit(const IRTree::StatementMoveNode &/*node*/) {
        current_ = NodeType::OTHER;
    }

    void IRTreeBlockBuilder::visit(const IRTree::StatementSeqNode &/*node*/) {
        assert(false);
    }

    void IRTreeBlockBuilder::visit(const IRTree::TempNode &/*node*/) {
        assert(false);
    }

    IRTree::ProgramInBlock IRTreeBlockBuilder::run() {
        IRTree::ProgramInBlock result;
        for (auto& line_class : tree_) {
            for (auto& line_method : line_class.second) {
                std::unique_ptr<IRTree::StatementLabelNode> prolog_end_label =
                        std::make_unique<IRTree::StatementLabelNode>(
                        std::make_unique<IRTree::LabelNode>("prolog"));
                current_block_.push_back(std::move(prolog_end_label));
                for (auto& statement : line_method.second) {
                    statement->accept(*this);
                    if (current_ == NodeType::LABEL || previous_ == NodeType::JUMP) {
                        if (!current_block_.empty())  {
                            if (previous_ != NodeType::JUMP) {
                                std::unique_ptr<IRTree::StatementJumpNode> jump_node =
                                        std::make_unique<IRTree::StatementJumpNode>(
                                        std::make_unique<IRTree::LabelNode>(*label_));
                                current_block_.push_back(std::move(jump_node));
                            }
                            result[line_class.first][line_method.first]
                                    .push_back(std::move(current_block_));
                            current_block_.clear();
                            if (current_ != NodeType::LABEL) {
                                std::unique_ptr<IRTree::StatementLabelNode> label_node =
                                        std::make_unique<IRTree::StatementLabelNode>(
                                                std::make_unique<IRTree::LabelNode>("temp_label"));
                                current_block_.push_back(std::move(label_node));
                            }
                        }
                    }
                    current_block_.push_back(std::move(statement));
                    previous_ = current_;
                }
                if (!current_block_.empty())  {
                    if (previous_ != NodeType::JUMP) {
                        std::unique_ptr<IRTree::StatementJumpNode> jumpNode = std::make_unique<IRTree::StatementJumpNode>(
                                std::make_unique<IRTree::LabelNode>("epilog"));
                        current_block_.push_back(std::move(jumpNode));
                    }
                    result[line_class.first][line_method.first]
                            .push_back(std::move(current_block_));
                    current_block_.clear();
                }
            }
        }
        return result;
    }
}