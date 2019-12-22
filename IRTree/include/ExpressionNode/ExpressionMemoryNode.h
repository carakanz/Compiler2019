//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionMemoryNode : public IExpressionNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> expression;
    };
}
