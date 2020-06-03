//
// Created by Admin on 03.06.2020.
//

#include <IRTreeESeqCanonizator.h>
#include <iostream>

namespace IRTreeVisitor{

    IRTree::ExpressionESeqNode * ESeqCast(IRTree::IExpressionNode* node) {
        return dynamic_cast<IRTree::ExpressionESeqNode*>( node );
    }

    std::unique_ptr<IRTree::IExpressionNode> IRTreeESeqCanonizator::canonizeExpSubtree(
            std::unique_ptr<IRTree::IExpressionNode> exp ) const
    {
        IRTreeESeqCanonizator visitor;
        exp->accept( visitor );
        return std::move(visitor.prevExp);
    }

    std::unique_ptr<IRTree::IStatementNode> IRTreeESeqCanonizator::canonizeStmSubtree(
            std::unique_ptr<IRTree::IStatementNode> stm ) const
    {
        IRTreeESeqCanonizator visitor;
        stm->accept( visitor );
        return std::move(visitor.prevStm);
    }

    bool IRTreeESeqCanonizator::areCommuting( IRTree::IStatementNode* stm, IRTree::IExpressionNode* exp )
    {
        assert( stm != nullptr && exp != nullptr );
        auto expStm = dynamic_cast<IRTree::StatementExpressionNode *>( stm );
        bool isStmEmpty = expStm != nullptr &&
                          dynamic_cast<IRTree::ExpressionConstNode *>( expStm->expression.get() ) != nullptr;
        return isStmEmpty ||
               dynamic_cast<IRTree::ExpressionConstNode *>( exp ) != nullptr ||
               dynamic_cast<IRTree::ExpressionNameNode *>( exp ) != nullptr;
    }

    void IRTreeESeqCanonizator::visit( const IRTree::ExpressionConstNode& n )
    {
        updateLastExp(n);
    }

    void IRTreeESeqCanonizator::visit( const IRTree::ExpressionNameNode& n )
    {
        updateLastExp(n);
    }

    void IRTreeESeqCanonizator::visit( const IRTree::ExpressionTempNode& n )
    {
        static int numEntries = 0;
        std::cout << numEntries << std::endl;
        updateLastExp(n);
        numEntries++;
    }

    void IRTreeESeqCanonizator::visit(const IRTree::ExpressionLocalNode& n)
    {
        //std::cout << "ExpLocal\n";
        updateLastExp(n);
    }

    void IRTreeESeqCanonizator::visit(const IRTree::TempNode &node) {
        assert(false); // should be processed later
        node.accept(*this);
    }

    void IRTreeESeqCanonizator::visit(const IRTree::LabelNode &node) {
        assert(false); // should be processed later
        node.accept(*this);
    }

    void IRTreeESeqCanonizator::visit( const IRTree::ExpressionBinaryOperationNode& n )
    {
        n.left->accept(*this);
        auto canonLeft = std::move( prevExp );

        n.right->accept(*this);
        auto canonRight = std::move( prevExp );

        auto eseqLeft = ESeqCast( canonLeft.get() );
        auto eseqRight = ESeqCast( canonRight.get() );

        std::unique_ptr<IRTree::IExpressionNode> resultExp = nullptr;
        if( eseqLeft ) {
            resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                    std::move(eseqLeft->statement),
                    std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                            n.operation_type,
                            std::move(eseqLeft->expression),
                            std::move( canonRight ) ) ) ;

            if( eseqRight ) {
                resultExp = canonizeExpSubtree( std::move(resultExp ));
            }
        } else if( eseqRight ) {
            if( areCommuting( eseqRight->statement.get(), canonLeft.get() ) ) {
                resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                        std::move(eseqRight->statement),
                        std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                                n.operation_type,
                                std::move( canonLeft ),
                                std::move(eseqRight->expression) ) );
            } else {
                resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                        std::make_unique<IRTree::StatementMoveNode>(
                                std::move( canonLeft ),
                                std::make_unique<IRTree::ExpressionTempNode>(
                                        std::make_unique<IRTree::TempNode>( "auxiliary", true ) ) ),
                        std::make_unique<IRTree::ExpressionESeqNode>(
                                std::move(eseqRight->statement),
                                std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                                        n.operation_type,
                                        std::make_unique<IRTree::ExpressionTempNode>(
                                                std::make_unique<IRTree::TempNode>( "auxiliary", false ) ) ,
                                        std::move(eseqRight->expression) ) ) );
                resultExp = canonizeExpSubtree( std::move( resultExp ) );
            }
        } else {
            resultExp = std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                    n.operation_type,
                    std::move(canonLeft),
                    std::move(canonRight) );
        }

        updateLastExp(std::move(resultExp));
    }

    void IRTreeESeqCanonizator::visit(const IRTree::ExpressionMemoryNode & n )
    {
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonAddr = std::move( prevExp );

        auto eseqAddr = ESeqCast( canonAddr.get() );
        std::unique_ptr<IRTree::IExpressionNode> resultExp = nullptr;
        if( eseqAddr ) {
            resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                    std::move(eseqAddr->statement),
                    std::make_unique<IRTree::ExpressionMemoryNode>( std::move(eseqAddr->expression) ) );
        } else {
            resultExp = std::make_unique<IRTree::ExpressionMemoryNode>( std::move(canonAddr) ) ;
        }
        updateLastExp(std::move(resultExp));
    }

    void IRTreeESeqCanonizator::visit( const IRTree::ExpressionCallNode& n )
    {
        n.method->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonFunc = std::move( prevExp );

        std::vector<std::unique_ptr<IRTree::IExpressionNode>> canonArgList;
        for(const auto& arg : n.arguments) {
            arg->accept(*this);
            canonArgList.emplace_back(std::move(prevExp));
        }

        std::vector<std::unique_ptr<IRTree::IStatementNode>> newStms;

        std::vector<std::unique_ptr<IRTree::IExpressionNode>> newArgs;

        for( auto& canonArg : canonArgList ) {
            auto eseqArg = ESeqCast( canonArg.get() );
            if( eseqArg ) {
                newStms.emplace_back( std::move(eseqArg->statement) );
            }

            newArgs.emplace_back( std::make_unique<IRTree::ExpressionTempNode>(
                    std::make_unique<IRTree::TempNode>("auxiliary", true) ) );

            std::unique_ptr<IRTree::IExpressionNode> moveSrcExp;
            if( eseqArg ) {
                moveSrcExp = std::move(eseqArg->expression);
            } else {
                moveSrcExp = std::move(canonArg);
            }
            std::unique_ptr<const IRTree::IStatementNode> moveStm = std::make_unique<IRTree::StatementMoveNode>(
                    std::move( moveSrcExp ),
                    std::make_unique<IRTree::ExpressionTempNode>(
                            std::make_unique<IRTree::TempNode>("auxiliary", false)));
            newStms.emplace_back(std::move(moveSrcExp));
        }

        std::unique_ptr<IRTree::IExpressionNode> resultExp = nullptr;
        if( !newStms.empty() ) {
            std::unique_ptr<const IRTree::IStatementNode> suffStm = std::move( newStms.back() );
            newStms.pop_back();
            for( int i = int(newStms.size()) - 1; i >= 0 ; i-- ) {
                suffStm = std::make_unique<IRTree::StatementSeqNode>(
                        std::move( newStms[i] ) ,
                        std::move( suffStm ));
            }

            resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                    std::move( suffStm ),
                    std::make_unique<IRTree::ExpressionCallNode>(
                            std::move( canonFunc ),
                            std::move( newArgs ) ) );
        } else {
            resultExp = std::make_unique<IRTree::ExpressionCallNode>(
                    std::move( canonFunc ),
                    std::move( canonArgList ) );
        }

        updateLastExp( std::move( resultExp ) );

    }

    void IRTreeESeqCanonizator::visit( const IRTree::ExpressionESeqNode& n )
    {
        n.statement->accept( *this );
        std::unique_ptr<IRTree::IStatementNode> canonStm = std::move( prevStm );
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonExp = std::move( prevExp );

        auto eseqExp = ESeqCast( canonExp.get() );
        std::unique_ptr<IRTree::IExpressionNode> resultExp;
        if( eseqExp ) {
            resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                    std::make_unique<IRTree::StatementSeqNode>(
                            std::move( canonStm ),
                            std::move(eseqExp->statement) ),
                    std::move(eseqExp->expression) );
        } else {
            resultExp = std::make_unique<IRTree::ExpressionESeqNode>(
                    std::move( canonStm ),
                    std::move( canonExp ) );
        }

        updateLastExp( std::move( resultExp ) );

    }

    void IRTreeESeqCanonizator::visit( const IRTree::StatementExpressionNode& n )
    {
        n.expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonExp = std::move( prevExp );

        auto eseqExp = ESeqCast( canonExp.get() );
        std::unique_ptr<IRTree::IStatementNode> resultStm  = nullptr;
        if( eseqExp ) {
            resultStm = std::make_unique<IRTree::StatementSeqNode>(
                    std::move(eseqExp->statement),
                    std::make_unique<IRTree::StatementExpressionNode>( std::move(eseqExp->expression) ) );
        } else {
            resultStm = std::make_unique<IRTree::StatementExpressionNode>( std::move( canonExp ) );
        }

        updateLastStm( std::move( resultStm ) );

    }

    void IRTreeESeqCanonizator::visit( const IRTree::StatementCJumpNode & n )
    {

        auto& nc_n = const_cast<IRTree::StatementCJumpNode &>(n);
        n.left_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonLeft = std::move( prevExp );

        n.right_expression->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonRight = std::move( prevExp );

        auto eseqLeft = ESeqCast( canonLeft.get() );
        auto eseqRight = ESeqCast( canonRight.get() );

        std::unique_ptr<IRTree::IStatementNode> resultStm = nullptr;

        if( eseqLeft ) {
            resultStm = std::make_unique<IRTree::StatementCJumpNode>(
                    nc_n.condition,
                    std::move(eseqLeft->expression),
                    std::move( canonRight ),
                    std::move(nc_n.positive_label),
                    std::move(nc_n.negative_label) );
            if( eseqRight ) {
                resultStm = canonizeStmSubtree( std::move( resultStm ) );
            }

            resultStm = std::make_unique<IRTree::StatementSeqNode>(
                    std::move(eseqLeft->statement),
                    std::move( resultStm ) );
        } else if( eseqRight ) {
            if( areCommuting( eseqRight->statement.get(), canonLeft.get() ) ) {
                resultStm = std::make_unique<IRTree::StatementSeqNode>(
                        std::move(eseqRight->statement),
                        std::make_unique<IRTree::StatementCJumpNode>(
                                nc_n.condition,
                                std::move( canonLeft ),
                                std::move(eseqRight->expression),
                                std::move(nc_n.positive_label),
                                std::move(nc_n.negative_label) ) );
            } else {
                resultStm = std::make_unique<IRTree::StatementSeqNode>(
                        std::make_unique<IRTree::StatementMoveNode>(
                                std::move( canonLeft ),
                                std::make_unique<IRTree::ExpressionTempNode>(
                                        std::make_unique<IRTree::TempNode>( "auxiliary", true ))),
                        std::make_unique<IRTree::StatementSeqNode>(
                                std::move(eseqRight->statement),
                                std::make_unique<IRTree::StatementCJumpNode>(
                                        nc_n.condition,
                                        std::make_unique<IRTree::ExpressionTempNode>(
                                                std::make_unique<IRTree::TempNode>( "auxiliary", false )),
                                        std::move(eseqRight->expression),
                                        std::move(nc_n.positive_label),
                                        std::move(nc_n.negative_label)) ) );
            }
        } else {
            resultStm = std::make_unique<IRTree::StatementCJumpNode>(
                    nc_n.condition,
                    std::move( canonLeft ),
                    std::move( canonRight ),
                    std::move(nc_n.positive_label),
                    std::move(nc_n.negative_label) );
        }

        updateLastStm( std::move( resultStm ) );

    }

    void IRTreeESeqCanonizator::visit( const IRTree::StatementJumpNode& n )
    {
        updateLastStm( n );
    }

    void IRTreeESeqCanonizator::visit( const IRTree::StatementLabelNode& n )
    {
        updateLastStm( n );
    }

    void IRTreeESeqCanonizator::visit( const IRTree::StatementMoveNode & n )
    {
        n.destination->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonDest = std::move( prevExp );

        n.source->accept( *this );
        std::unique_ptr<IRTree::IExpressionNode> canonSrc = std::move( prevExp );

        auto eseqDest = ESeqCast( canonDest.get() );
        auto eseqSrc = ESeqCast( canonSrc.get() );

        std::unique_ptr<IRTree::IStatementNode> resultStm = nullptr;
        if( eseqDest ) {
            resultStm = std::make_unique<IRTree::StatementMoveNode>(
                    std::move(canonSrc),
                    std::move(eseqDest->expression) );
            if( eseqSrc ) {
                resultStm = canonizeStmSubtree( std::move( resultStm ) );
            }
            resultStm = std::make_unique<IRTree::StatementSeqNode>(
                    std::move(eseqDest->statement),
                    std::move( resultStm ) );
        } else if( eseqSrc ) {
            if( areCommuting( eseqSrc->statement.get(), canonDest.get() ) ) {
                resultStm = std::make_unique<IRTree::StatementSeqNode>(
                        std::move(eseqSrc->statement),
                        std::make_unique<IRTree::StatementMoveNode>(
                                std::move(eseqSrc->expression),
                                std::move( canonDest ) ) );
            } else {
                resultStm = std::make_unique<IRTree::StatementSeqNode>(
                        std::make_unique<IRTree::StatementSeqNode>(
                                std::move(eseqSrc->statement),
                                std::make_unique<IRTree::StatementMoveNode>(
                                        std::move(eseqSrc->expression),
                                        std::make_unique<IRTree::ExpressionTempNode>(
                                                std::make_unique<IRTree::TempNode>("auxiliary", true) ) ) ),
                        std::make_unique<IRTree::StatementMoveNode>(
                                std::make_unique<IRTree::ExpressionTempNode>(
                                        std::make_unique<IRTree::TempNode>("auxiliary", false) ),
                                std::move( canonDest ) ) );
            }
        } else {
            resultStm = std::make_unique<IRTree::StatementMoveNode>(
                            std::move( canonSrc) ,
                            std::move( canonDest ) );
        }

        updateLastStm( std::move( resultStm ) );

    }

    void IRTreeESeqCanonizator::visit( const IRTree::StatementSeqNode& n )
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

    void IRTreeESeqCanonizator::visit(const SyntaxTreeVisitor::IRTreeGoal &goal) {
        for (const auto &class_info : goal.wrappers) {
            for (const auto &method_info : class_info.second) {
                method_info.second->accept(*this);
                const_cast<std::unique_ptr<IRTree::IStatementNode> &>(method_info.second) = std::move(prevStm);
            }
        }
    }

    void IRTreeESeqCanonizator::updateLastExp(const IRTree::ExpressionNameNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionNameNode &>(node);
        assert(nc_node.label.get() != nullptr);
        prevExp = std::make_unique<IRTree::ExpressionNameNode>(std::move(nc_node.label));
    }

    void IRTreeESeqCanonizator::updateLastExp(const IRTree::ExpressionTempNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionTempNode &>(node);
        assert(nc_node.temp.get() != nullptr);
        prevExp = std::make_unique<IRTree::ExpressionTempNode>(std::move(nc_node.temp));
    }

    void IRTreeESeqCanonizator::updateLastExp(const IRTree::ExpressionConstNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionConstNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionConstNode>(nc_node.value);
    }

    void IRTreeESeqCanonizator::updateLastExp(const IRTree::ExpressionLocalNode &node) {
        auto& nc_node = const_cast<IRTree::ExpressionLocalNode &>(node);
        prevExp = std::make_unique<IRTree::ExpressionLocalNode>(nc_node.is_class_var, nc_node.name);
    }

    void IRTreeESeqCanonizator::updateLastStm(const IRTree::StatementJumpNode &node) {
        auto& nc_node = const_cast<IRTree::StatementJumpNode &>(node);
        prevStm = std::make_unique<IRTree::StatementJumpNode>(std::move(nc_node.label));
    }

    void IRTreeESeqCanonizator::updateLastStm(const IRTree::StatementLabelNode &node) {
        auto& nc_node = const_cast<IRTree::StatementLabelNode &>(node);
        prevStm = std::make_unique<IRTree::StatementLabelNode>(std::move(nc_node.label));
    }

}

