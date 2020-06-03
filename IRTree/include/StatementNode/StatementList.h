 //
// Created by Admin on 02.06.2020.
//

#include <StatementNode/IStatementNode.h>
#include <IRTree/IVisitor.h>

#ifndef COMPILER2019_STATEMENTLIST_H
#define COMPILER2019_STATEMENTLIST_H

namespace IRTree {
    class StatementList
    {
    public:
        StatementList() = default;

        explicit StatementList( const IRTree::IStatementNode* statement )
        {
            add( statement );
        }

        void add( const IRTree::IStatementNode* statement )
        {
            statements.emplace_back( statement );
        }

        void add( std::unique_ptr<const IRTree::IStatementNode> statement )
        {
            statements.emplace_back( std::move( statement ) );
        }

        void accept( IVisitor& visitor ) const {
            visitor.visit(*this);
        }

    private:
        std::vector<std::unique_ptr<const IRTree::IStatementNode>> statements;
    };
}

#endif //COMPILER2019_STATEMENTLIST_H
