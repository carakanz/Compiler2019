//
// Created by Zinenko Dmytro on 23.12.2019.
//

#include <BinaryOperationType.h>
#include "WrapperExpressionBinaryOperation.h"

namespace IRTree {
    template <>
    class WrapperExpressionBinaryOperation<BinaryOperationType::AND> : public IWrapper {
    public:
        WrapperExpressionBinaryOperation(std::unique_ptr<IWrapper> &&left, std::unique_ptr<IWrapper> &&right)
                : left_(std::move(left)), right_(std::move(right)) {
        }

        std::unique_ptr<IExpressionNode> to_expression() override {
            // TODO
            assert(false);
        }

        std::unique_ptr<IStatementNode> to_statement() override {
            // TODO
            assert(false);
        }

        std::unique_ptr<IStatementNode> to_conditional(std::unique_ptr<LabelNode>&& true_label,
                                                       std::unique_ptr<LabelNode>&& false_label) override {
            // TODO
            auto label_first_true = std::make_unique<LabelNode>(std::string("first_true"));
            auto first_true_statement = std::make_unique<StatementLabelNode>(
                    std::make_unique<LabelNode>(*label_first_true));

            auto false_label_copy = std::make_unique<LabelNode>(*false_label);
            return std::make_unique<StatementSeqNode>(
                    left_->to_conditional(std::move(label_first_true),
                                          std::move(false_label_copy)),
                    std::move(first_true_statement),
                    right_->to_conditional(std::move(true_label), std::move(false_label))

            );
        }

    private:
        std::unique_ptr<IWrapper> left_;
        std::unique_ptr<IWrapper> right_;
    };
}
