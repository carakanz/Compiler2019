//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include "IRTree/IRTreeWrappers.h"


namespace IRTree {

    AndConditionalWrapper::AndConditionalWrapper(std::unique_ptr<IWrapper> &&_leftOperand,
                                                         std::unique_ptr<IWrapper> &&_rightOperand)
            : leftOperand_(std::move(_leftOperand)),
              rightOperand_(std::move(_rightOperand)) {}


    OrConditionalWrapper::OrConditionalWrapper(std::unique_ptr<IWrapper> &&_leftOperand,
                                                       std::unique_ptr<IWrapper> &&_rightOperand)
            : leftOperand_(std::move(_leftOperand)),
              rightOperand_(std::move(_rightOperand)) {}


    std::unique_ptr<const IStatementNode> ExpressionWrapper::to_statement() {
        return std::make_unique<StatementExpressionNode>(std::move(expression_));
    }

    std::unique_ptr<const IStatementNode>
    ExpressionWrapper::to_conditional(std::unique_ptr<const LabelNode> &positiveLabel,
                                      std::unique_ptr<const LabelNode> &negativeLabel) {
        StatementCJumpNode(std::move(expression_),
                std::make_unique<ExpressionConstNode>(1),
                           std::move(positiveLabel),
                           std::move(negativeLabel));
    }


    std::unique_ptr<const IExpressionNode> ConditionalWrapper::to_expression() {
        std::unique_ptr<const LabelNode> positiveLabel= std::make_unique<LabelNode>(std::string("Label_true_"));
        std::unique_ptr<const LabelNode> negativeLabel= std::make_unique<LabelNode>(std::string("Label_false_"));
        std::unique_ptr<const IExpressionNode> tempExpression = std::make_unique<ExpressionTempNode>(
                std::make_unique<TempNode>("Label_temp_"));

        return std::make_unique<ExpressionESeqNode>(
            std::make_unique<StatementSeqNode>(
                std::make_unique<StatementMoveNode>(std::move(tempExpression), std::make_unique<ExpressionConstNode>(1)),
                std::make_unique<StatementSeqNode>(
                        std::move(to_conditional(positiveLabel, negativeLabel)),
                        std::make_unique<StatementSeqNode>(
                                std::make_unique<StatementLabelNode>(std::move(negativeLabel)),
                                        std::make_unique<StatementSeqNode>(
                                                std::make_unique<StatementMoveNode>(std::move(tempExpression), std::make_unique<ExpressionConstNode>(0)),
                                                std::make_unique<StatementLabelNode>(std::move(positiveLabel))
                                        )
                        )
                )
            ),
            std::move(tempExpression)
        );
    }

    std::unique_ptr<const IStatementNode>
    RelativeConditionalWrapper::to_conditional(std::unique_ptr<const LabelNode> &positiveLabel,
                                               std::unique_ptr<const LabelNode> &negativeLabel) {
        return std::make_unique<StatementCJumpNode>(std::move(leftOperand_),
                std::move(rightOperand_),
                std::move(positiveLabel),
                std::move(negativeLabel));
    }

    std::unique_ptr<const IStatementNode>
    AndConditionalWrapper::to_conditional(std::unique_ptr<const LabelNode> &positiveLabel,
                                          std::unique_ptr<const LabelNode> &negativeLabel) {
        std::unique_ptr<const LabelNode> midLabel = std::make_unique<LabelNode>(std::string("Lable_mid_"));
        return std::make_unique<StatementSeqNode>(
                    leftOperand_->to_conditional(midLabel, negativeLabel),
                    std::make_unique<StatementSeqNode>(
                            std::make_unique<StatementLabelNode>(std::move(midLabel)),
                            rightOperand_->to_conditional(midLabel, negativeLabel)
                    )
                );
    }

    std::unique_ptr<const IStatementNode>
    OrConditionalWrapper::to_conditional(std::unique_ptr<const LabelNode> &positiveLabel,
                                         std::unique_ptr<const LabelNode> &negativeLabel) {
        std::unique_ptr<const LabelNode> midLabel = std::make_unique<LabelNode>(std::string("Lable_mid_"));
        return std::make_unique<StatementSeqNode>(
                leftOperand_->to_conditional(positiveLabel, midLabel),
                std::make_unique<StatementSeqNode>(
                        std::make_unique<StatementLabelNode>(std::move(midLabel)),
                        rightOperand_->to_conditional(midLabel, negativeLabel)
                )
        );
    }

    std::unique_ptr<const IStatementNode>
    OppositeConditionalWrapper::to_conditional(std::unique_ptr<const LabelNode> &positiveLabel,
                                               std::unique_ptr<const LabelNode> &negativeLabel) {
        //return internalWrapper->ToConditional(negativeLabel, positiveLabel);
        return internalWrapper_->to_conditional(negativeLabel, positiveLabel);
    }
}