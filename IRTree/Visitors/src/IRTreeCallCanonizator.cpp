//
// Created by Admin on 02.06.2020.
//

#include <IRTreeCallCanonizator.h>
#include <TempNode/TempNode.h>
#include <assert.h>
#include <iostream>

namespace IRTreeVisitor{

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionConstNode& n )
    {
	//std::cout << "ExpConst\n";
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionNameNode& n )
    {
	//std::cout << "ExpName\n";
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionTempNode& n )
    {
	//std::cout << "ExpTemp\n";
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit(const IRTree::ExpressionLocalNode& n)
    {
	//std::cout << "ExpLocal\n";
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit(const IRTree::TempNode &node) {
        assert(false); // should be processed later
        node.accept(*this);
    }

    void IRTreeCallCanonizator::visit(const IRTree::LabelNode &node) {
        assert(false); // should be processed later
        node.accept(*this);
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionBinaryOperationNode& n )
    {
	//std::cout << "ExpBinary\n";
        n.left->accept(*this);
        std::unique_ptr<IRTree::IExpressionNode> nLeft = std::move( prevExp );

        n.right->accept(*this);
        auto nRight = std::move( prevExp );

        updateLastExp(std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                n.operation_type, std::move(nLeft), std::move(nRight)));
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionMemoryNode& n )
    {
	//std::cout << "ExpMemory\n";
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> addressExp = std::move( prevExp );

        updateLastExp(
                std::move(addressExp)
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionCallNode& n )
    {
	//std::cout << "ExpCall\n";
	//std::cout << "before method accept\n";
        n.method->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> functionExp = std::move( prevExp );
	//std::cout << "after method accept\n";

        std::vector<std::unique_ptr<IRTree::IExpressionNode>> argumentList;
        for(const auto& arg : n.arguments) {
            arg->accept(*this);
            argumentList.emplace_back(std::move(prevExp));
        }
	//std::cout << "after arguments accept\n";

	assert(functionExp.get() != nullptr);

        updateLastExp(
                std::make_unique<IRTree::ExpressionESeqNode>(
                        std::make_unique<IRTree::StatementMoveNode>(
                                std::make_unique<IRTree::ExpressionTempNode>(
                                        std::move(std::make_unique<IRTree::TempNode>("auxiliary", true) )),
                                std::make_unique<IRTree::ExpressionCallNode>(
                                        std::move( functionExp ),
                                        argumentList
                                )
                        ),
                        std::make_unique<IRTree::ExpressionTempNode>(
                                std::move(std::make_unique<IRTree::TempNode>("auxiliary", false)))
                ) );
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionESeqNode& n )
    {
	//std::cout << "ExpESeq\n";
        n.statement->accept( *this );
        n.expression->accept( *this );

        updateLastExp(
                std::make_unique<IRTree::ExpressionESeqNode>(
                        std::move(prevStm),
                        std::move(prevExp)
                )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementExpressionNode& n )
    {
	//std::cout << "StExp\n";
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> exp = std::move( prevExp );

        updateLastStm(
                std::make_unique<IRTree::StatementExpressionNode>( std::move(exp) )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementCJumpNode& n )
    {
	//std::cout << "StCJump\n";
	auto& nc_n = const_cast<IRTree::StatementCJumpNode &>(n);
        n.left_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> nLeft = std::move( prevExp );

        n.right_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> nRight = std::move( prevExp );

        updateLastStm(
                std::make_unique<IRTree::StatementCJumpNode>(
                        nc_n.condition,
                        std::move(nLeft),
                        std::move(nRight),
                        std::move(nc_n.positive_label),
                        std::move(nc_n.negative_label)
                )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementJumpNode& n )
    {
	//std::cout << "StJump\n";
        updateLastStm(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementLabelNode& n )
    {
	//std::cout << "StLabel\n";
        updateLastStm(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementMoveNode& n )
    {
	//std::cout << "StMove\n";
        n.destination->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> destination = std::move( prevExp );

        n.source->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> source = std::move( prevExp );

        updateLastStm(
                std::make_unique<IRTree::StatementMoveNode>(
                        std::move(source),
                        std::move(destination)
                )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementSeqNode& n )
    {
	//std::cout << "StSeq\n";
        n.left->accept( *this );
        std::unique_ptr<IRTree::IStatementNode> nLeft = std::move( prevStm );

        n.right->accept( *this );
        std::unique_ptr<IRTree::IStatementNode> nRight = std::move( prevStm );

        updateLastStm(
                std::make_unique<IRTree::StatementSeqNode>(
                        std::move(nLeft),
                        std::move(nRight)
                )
        );
    }

    void IRTreeCallCanonizator::visit(const SyntaxTreeVisitor::IRTreeGoal &goal) {
        for (const auto &class_info : goal.wrappers) {
            for (const auto &method_info : class_info.second) {
                method_info.second->accept(*this);
                const_cast<std::unique_ptr<IRTree::IStatementNode> &>(method_info.second) = std::move(prevStm);
            }
        }
    }

    void IRTreeCallCanonizator::updateLastExp(const IRTree::ExpressionNameNode &node) {
	/*if(node.label.get() == nullptr) {
	    std::cout << "node label is empty!\n";
	} else {
	    std::cout << "node label is ok\n";
	}*/
        auto& nc_node = const_cast<IRTree::ExpressionNameNode &>(node);
	assert(nc_node.label.get() != nullptr);
        prevExp = std::make_unique<IRTree::ExpressionNameNode>(std::move(nc_node.label));
	//assert(nc_node.label.get() == nullptr);
	//assert(dynamic_cast<IRTree::ExpressionNameNode*>(prevExp.get())->label.get() == nullptr);
    }

    void IRTreeCallCanonizator::updateLastExp(const IRTree::ExpressionTempNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionTempNode &>(node);
	assert(nc_node.temp.get() != nullptr);
        prevExp = std::make_unique<IRTree::ExpressionTempNode>(std::move(nc_node.temp));
	//assert(dynamic_cast<IRTree::ExpressionTempNode*>(prevExp.get())->temp.get() != nullptr);
    }

    void IRTreeCallCanonizator::updateLastExp(const IRTree::ExpressionConstNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionConstNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionConstNode>(nc_node.value);
    }

    void IRTreeCallCanonizator::updateLastExp(const IRTree::ExpressionLocalNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionLocalNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionLocalNode>(nc_node.is_class_var, nc_node.name);
    }

    void IRTreeCallCanonizator::updateLastStm(const IRTree::StatementJumpNode &node) {
        auto& nc_node = const_cast<IRTree::StatementJumpNode &>(node);
        prevStm = std::make_unique<IRTree::StatementJumpNode>(std::move(nc_node.label));
    }

    void IRTreeCallCanonizator::updateLastStm(const IRTree::StatementLabelNode &node) {
        auto& nc_node = const_cast<IRTree::StatementLabelNode &>(node);
        prevStm = std::make_unique<IRTree::StatementLabelNode>(std::move(nc_node.label));
    }
}

