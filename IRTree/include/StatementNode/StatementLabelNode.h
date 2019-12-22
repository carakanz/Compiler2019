//
// Created by Zinenko Dmytro on 22.12.2019.
//

#include <LabelNode/LabelNode.h>
#include "IStatementNode.h"

namespace IRTree {
    class StatementLabelNode : public IStatementNode {
    public:
        void accept(IVisitor &visitor) const override {
            visitor.visit(*this);
        }

        std::unique_ptr<LabelNode> label;
    };
}
