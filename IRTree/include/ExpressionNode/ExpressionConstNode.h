//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionConstNode : public IExpressionNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        const int value{};
    };
}
