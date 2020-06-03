//
// Created by Admin on 03.06.2020.
//

#include <IRTreeFinalLinearisator.h>
#include <iostream>
#include <assert.h>

namespace IRTreeVisitor{

    void IRTreeFinalLinearisator::visit(const IRTree::ExpressionConstNode& n )
    {
        ++stackDepthCounter.back();
        updateLastExp(n);
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::ExpressionNameNode& n )
    {
        ++stackDepthCounter.back();
        updateLastExp(n);
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::ExpressionTempNode& n )
    {
        ++stackDepthCounter.back();
        updateLastExp(n);
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit(const IRTree::ExpressionLocalNode& n)
    {
        ++stackDepthCounter.back();
        //std::cout << "ExpLocal\n";
        updateLastExp(n);
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit(const IRTree::TempNode &node) {
        assert(false); // should be processed later
        node.accept(*this);
    }

    void IRTreeFinalLinearisator::visit(const IRTree::LabelNode &node) {
        assert(false); // should be processed later
        node.accept(*this);
    }

    void IRTreeFinalLinearisator::visit( const IRTree::ExpressionBinaryOperationNode& n )
    {
        ++stackDepthCounter.back();

        n.left->accept(*this);
        std::unique_ptr<IRTree::IExpressionNode> nLeft = std::move( prevExp );

        n.right->accept(*this);
        auto nRight = std::move( prevExp );

        updateLastExp(std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                n.operation_type, std::move(nLeft), std::move(nRight)));

        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::ExpressionMemoryNode& n )
    {
        ++stackDepthCounter.back();
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> addressExp = std::move( prevExp );

        updateLastExp(std::move(addressExp));

        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::ExpressionCallNode & n )
    {
        ++stackDepthCounter.back();

        n.method->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> functionExp = std::move( prevExp );
        //std::cout << "after method accept\n";

        std::vector<std::unique_ptr<IRTree::IExpressionNode>> argumentList;
        for(const auto& arg : n.arguments) {
            arg->accept(*this);
            argumentList.emplace_back(std::move(prevExp));
        }

        updateLastExp(std::make_unique<IRTree::ExpressionCallNode>(
                std::move( functionExp ),
                argumentList));

        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::ExpressionESeqNode& n )
    {
        assert( false );
    }

    void IRTreeFinalLinearisator::visit( const IRTree::StatementExpressionNode& n )
    {
        ++stackDepthCounter.back();

        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> exp = std::move( prevExp );

        saveCreatedStm( std::make_unique<IRTree::StatementExpressionNode>( std::move( exp ) ) );
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::StatementCJumpNode& n )
    {
        ++stackDepthCounter.back();

        auto& nc_n = const_cast<IRTree::StatementCJumpNode &>(n);
        n.left_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> nLeft = std::move( prevExp );

        n.right_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> nRight = std::move( prevExp );

        saveCreatedStm(
                std::make_unique<IRTree::StatementCJumpNode>(
                        nc_n.condition,
                        std::move(nLeft),
                        std::move(nRight),
                        std::move(nc_n.positive_label),
                        std::move(nc_n.negative_label)
                )
        );
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::StatementJumpNode& n )
    {
        ++stackDepthCounter.back();
        updateLastStm(n);
        saveCreatedStm(std::move(prevStm));
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::StatementLabelNode& n )
    {
        ++stackDepthCounter.back();
        updateLastStm(n);
        saveCreatedStm(std::move(prevStm));
        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::StatementMoveNode& n )
    {
        ++stackDepthCounter.back();

        n.destination->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> destination = std::move( prevExp );

        n.source->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> source = std::move( prevExp );

        saveCreatedStm(
                std::make_unique<IRTree::StatementMoveNode>(
                        std::move(source),
                        std::move(destination)
                )
        );

        --stackDepthCounter.back();
    }

    void IRTreeFinalLinearisator::visit( const IRTree::StatementSeqNode& n )
    {
        if(! stackDepthCounter.empty()) {
            ++stackDepthCounter.back();
            assert(stackDepthCounter.back() == 1); // the ancestor of Seq must be only Seq
        }
        stackDepthCounter.push_back( 0 );

        n.left->accept( *this );
        assert(stackDepthCounter.back() == 0);
        n.right->accept( *this );
        assert(stackDepthCounter.back() == 0);
        stackDepthCounter.pop_back();

        --stackDepthCounter.back();
    }


    void IRTreeFinalLinearisator::saveCreatedStm( std::unique_ptr<IRTree::IStatementNode> result )
    {
        if( stackDepthCounter.back() == 1 ) {
            stackOfSeqChildren.emplace_back( std::move( result ) );
        } else {
            updateLastStm( std::move( result ) );
        }
    }

    void IRTreeFinalLinearisator::visit(const IRTree::IRTreeGoal &goal) {

        auto& nc_goal = const_cast<IRTree::IRTreeGoal &>(goal);
        nc_goal.reset_linear_wrappers();

        for (const auto &class_info : goal.wrappers) {
            for (const auto &method_info : class_info.second) {
                method_info.second->accept(*this);
                nc_goal.linear_wrappers[class_info.first][method_info.first] = std::move(stackOfSeqChildren);
            }
        }
    }

    void IRTreeFinalLinearisator::updateLastExp(const IRTree::ExpressionNameNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionNameNode &>(node);
        assert(nc_node.label.get() != nullptr);
        prevExp = std::make_unique<IRTree::ExpressionNameNode>(std::move(nc_node.label));
    }

    void IRTreeFinalLinearisator::updateLastExp(const IRTree::ExpressionTempNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionTempNode &>(node);
        assert(nc_node.temp.get() != nullptr);
        prevExp = std::make_unique<IRTree::ExpressionTempNode>(std::move(nc_node.temp));
    }

    void IRTreeFinalLinearisator::updateLastExp(const IRTree::ExpressionConstNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionConstNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionConstNode>(nc_node.value);
    }

    void IRTreeFinalLinearisator::updateLastExp(const IRTree::ExpressionLocalNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionLocalNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionLocalNode>(nc_node.is_class_var, nc_node.name);
    }

    void IRTreeFinalLinearisator::updateLastStm(const IRTree::StatementJumpNode &node) {
        auto& nc_node = const_cast<IRTree::StatementJumpNode &>(node);
        prevStm = std::make_unique<IRTree::StatementJumpNode>(std::move(nc_node.label));
    }

    void IRTreeFinalLinearisator::updateLastStm(const IRTree::StatementLabelNode &node) {
        auto& nc_node = const_cast<IRTree::StatementLabelNode &>(node);
        prevStm = std::make_unique<IRTree::StatementLabelNode>(std::move(nc_node.label));
    }

}