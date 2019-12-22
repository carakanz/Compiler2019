//
// Created by l1onsun on 23.12.19.
//
#pragma once

#include <memory>
#include <cassert>
#include <ExpressionNode/IExpressionNode.h>
#include <StatementNode/IStatementNode.h>
#include <LabelNode/LabelNode.h>
#include <StatementNode/StatementExpressionNode.h>

namespace IRTree {

    class ISubtreeWrapper {
    public:
        virtual ~ISubtreeWrapper() {};

        virtual const std::unique_ptr<const IExpressionNode>& ToExpression() const { assert(false); };
        virtual const std::unique_ptr<const IStatementNode>& ToStatement() const { assert(false); };
        virtual const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                   const std::unique_ptr<const LabelNode>& negativeLabel) const { assert(false); };
    };

    class ExpressionWrapper : public ISubtreeWrapper {
    public:
        explicit ExpressionWrapper(const std::unique_ptr<const IExpressionNode>& _expression): expression(_expression) {}

        const std::unique_ptr<const IExpressionNode>& ToExpression() const override { return expression; }
        const std::unique_ptr<const IStatementNode>& ToStatement() const override;
        const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                           const std::unique_ptr<const LabelNode>& negativeLabel) const override;

    private:
        const std::unique_ptr<const IExpressionNode>& expression;
    };

    class StatementWrapper : public ISubtreeWrapper {
    public:
        explicit StatementWrapper(const std::unique_ptr<const IStatementNode>& _statement): statement(_statement) {}

        const std::unique_ptr<const IStatementNode>& ToStatement() const override { return statement; }

    private:
        const std::unique_ptr<const IStatementNode>& statement;
    };

    class ConditionalWrapper : public ISubtreeWrapper {
    public:
        virtual ~ConditionalWrapper() {};

        const std::unique_ptr<const IExpressionNode>& ToExpression() const override;
        virtual const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                                   const std::unique_ptr<const LabelNode>& negativeLabel) const override = 0;
    };

    // пока поддерживаем только "меньше <"
    class RelativeConditionalWrapper : public ConditionalWrapper {
    public:
        RelativeConditionalWrapper(const std::unique_ptr<const IExpressionNode>& _leftOperand,
                                   const std::unique_ptr<const IExpressionNode>& _rightOperand);

        const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                           const std::unique_ptr<const LabelNode>& negativeLabel) const override;

    private:
        const std::unique_ptr<const IExpressionNode>& leftOperand;
        const std::unique_ptr<const IExpressionNode>& rightOperand;
    };

    class AndConditionalWrapper : public ConditionalWrapper {
    public:
        AndConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _leftOperand,
                              std::unique_ptr<const ISubtreeWrapper>&& _rightOperand);

        const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                           const std::unique_ptr<const LabelNode>& negativeLabel) const override;

    private:
        std::unique_ptr<const ISubtreeWrapper> leftOperand;
        std::unique_ptr<const ISubtreeWrapper> rightOperand;
    };

    class OrConditionalWrapper : public ConditionalWrapper {
    public:
        OrConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _leftOperand,
                             std::unique_ptr<const ISubtreeWrapper>&& _rightOperand);

        const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                           const std::unique_ptr<const LabelNode>& negativeLabel) const override;

    private:
        std::unique_ptr<const ISubtreeWrapper> leftOperand;
        std::unique_ptr<const ISubtreeWrapper> rightOperand;
    };

    class OppositeConditionalWrapper : public ConditionalWrapper {
    public:
        explicit OppositeConditionalWrapper(std::unique_ptr<const ISubtreeWrapper>&& _wrapper) : internalWrapper(std::move(_wrapper)) {}

        const std::unique_ptr<const IStatementNode>& ToConditional(const std::unique_ptr<const LabelNode>& positiveLabel,
                                                           const std::unique_ptr<const LabelNode>& negativeLabel) const override;

    private:
        std::unique_ptr<const ISubtreeWrapper> internalWrapper;
    };

    //from Make.h
    template <typename T, class... Args>
    inline const std::unique_ptr<const T> makeNode(Args&&... args) {
        return std::make_unique<const T>(std::forward<Args>(args)...);
    }

    template <typename T, class... Args>
    inline const std::unique_ptr<const T> makeWrapper(Args&&... args) {
        return std::make_unique<const T>(std::forward<Args>(args)...);
    }
}
