//
// Created by Zinenko Dmytro on 25.12.2019.
//
#pragma once

#include <memory>
#include "../IWrapper.h"
#include "cassert"

namespace IRTree {
    class WrapperOperationNot : public IWrapper {
    public:
        explicit WrapperOperationNot(std::shared_ptr<IWrapper>&& wrapper) : wrapper_(wrapper) {
        }
        std::unique_ptr<IExpressionNode> to_expression() override {
            assert(false);
        };

        std::unique_ptr<IStatementNode> to_statement() override {
            return wrapper_->to_statement();
        }

        std::unique_ptr<IStatementNode> to_conditional(std::unique_ptr<LabelNode> &&true_label,
                                                       std::unique_ptr<LabelNode> &&false_label) override {
            return wrapper_->to_conditional(std::move(false_label), std::move(true_label));
        }

    private:
        std::shared_ptr<IWrapper> wrapper_;
    };
}