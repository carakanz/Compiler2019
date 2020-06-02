//
// Created by Admin on 02.06.2020.
//

#include <IRTreeCallCanonizator.h>
#include <TempNode/TempNode.h>

namespace IRTreeVisitor{

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionConstNode& n )
    {
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionNameNode& n )
    {
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionTempNode& n )
    {
        updateLastExp(n);
    }

    void IRTreeCallCanonizator::visit(const IRTree::ExpressionLocalNode& n)
    {
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
        n.left->accept(*this);
        std::unique_ptr<IRTree::IExpressionNode> nLeft = std::move( prevExp );

        n.right->accept(*this);
        auto nRight = std::move( prevExp );

        updateLastExp(std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                n.operation_type, std::move(nLeft), std::move(nRight)));
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionMemoryNode& n )
    {
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> addressExp = std::move( prevExp );

        updateLastExp(
                std::make_unique<IRTree::IExpressionNode>( addressExp.release() )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionCallNode& n )
    {
        n.method->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> functionExp = std::move( prevExp );

        std::vector<std::unique_ptr<IRTree::IExpressionNode>> argumentList;
        for(const auto& arg : n.arguments) {
            arg->accept(*this);
            argumentList.emplace_back(std::move(prevExp));
        }

        IRTree::TempNode temp("auxiliary");
        IRTree::TempNode temp_repl = temp;
        auto res = IRTree::ExpressionTempNode(std::unique_ptr<IRTree::TempNode>(&temp));
        updateLastExp(
                std::make_unique<IRTree::ExpressionESeqNode>(
                        std::make_unique<IRTree::StatementMoveNode>(
                                std::make_unique<IRTree::ExpressionTempNode>(
                                        std::unique_ptr<IRTree::TempNode>(&temp) ),
                                std::make_unique<IRTree::ExpressionCallNode>(
                                        std::move( functionExp ),
                                        argumentList
                                )
                        ),
                        std::make_unique<IRTree::ExpressionTempNode>(
                                std::unique_ptr<IRTree::TempNode>(&temp_repl))
                ) );
    }

    void IRTreeCallCanonizator::visit( const IRTree::ExpressionESeqNode& n )
    {
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
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> exp = std::move( prevExp );

        updateLastStm(
                std::make_unique<IRTree::StatementExpressionNode>( std::move(exp) )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementCJumpNode& n )
    {
        n.left_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> nLeft = std::move( prevExp );

        n.right_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> nRight = std::move( prevExp );

        updateLastStm(
                std::make_unique<IRTree::StatementCJumpNode>(
                        n.condition,
                        std::move(nLeft),
                        std::move(nRight),
                        std::move(n.positive_label),
                        std::move(n.negative_label)
                )
        );
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementJumpNode& n )
    {
        updateLastStm(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementLabelNode& n )
    {
        updateLastStm(n);
    }

    void IRTreeCallCanonizator::visit( const IRTree::StatementMoveNode& n )
    {
        n.destination->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> destination = std::move( prevExp );

        n.destination->accept( *this );
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
}

