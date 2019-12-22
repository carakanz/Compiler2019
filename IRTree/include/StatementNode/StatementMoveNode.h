//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include <ExpressionNode/IExpressionNode.h>
#include "IStatementNode.h"

namespace IRTree {
    class StatementMoveNode : public IStatementNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> source;
        std::unique_ptr<IExpressionNode> destination;
    };
}
