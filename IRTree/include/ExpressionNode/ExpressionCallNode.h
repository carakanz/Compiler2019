//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionCallNode : public IExpressionNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<IExpressionNode> method;
        std::vector<std::unique_ptr<IExpressionNode>> arguments;
    };
}
