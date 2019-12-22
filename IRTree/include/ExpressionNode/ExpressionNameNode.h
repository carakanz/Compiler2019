//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include <LabelNode/LabelNode.h>
#include "IExpressionNode.h"

namespace IRTree {
    class ExpressionNameNode : public IExpressionNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<LabelNode> label;
    };
}
