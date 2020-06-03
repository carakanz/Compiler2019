//
// Created by Admin on 02.06.2020.
//

#include <IRTree/IVisitor.h>
#include <ExpressionNode/IExpressionNode.h>

#ifndef COMPILER2019_EXPRESSIONLIST_H
#define COMPILER2019_EXPRESSIONLIST_H

namespace IRTree {
    class ExpressionList {
    public:
        ExpressionList() = default;

        explicit ExpressionList( const IRTree::IExpressionNode* expression )
        {
            add( expression );
        }

        void add( const IRTree::IExpressionNode* expression )
        {
            expressions.emplace_back( expression );
        }

        void add( std::unique_ptr<const IRTree::IExpressionNode> expression )
        {
            expressions.emplace_back( std::move( expression ) );
        }

        void accept( IVisitor &visitor) const {
            visitor.visit(*this);
        }

        std::vector<std::unique_ptr<const IRTree::IExpressionNode>> expressions;

    };
}
#endif //COMPILER2019_EXPRESSIONLIST_H
