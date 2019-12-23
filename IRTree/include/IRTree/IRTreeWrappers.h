////
//// Created by l1onsun on 23.12.19.
////
//#pragma once
//
//#include <memory>
//#include <cassert>
//#include <ExpressionNode/IExpressionNode.h>
//#include <ExpressionNode/ExpressionConstNode.h>
//#include <ExpressionNode/ExpressionTempNode.h>
//#include <ExpressionNode/ExpressionESeqNode.h>
//#include <StatementNode/IStatementNode.h>
//#include <StatementNode/StatementCJumpNode.h>
//#include <StatementNode/StatementMoveNode.h>
//#include <StatementNode/StatementLabelNode.h>
//#include <StatementNode/StatementSeqNode.h>
//#include <LabelNode/LabelNode.h>
//#include <StatementNode/StatementExpressionNode.h>
//#include <TempNode/TempNode.h>
//
//
//namespace IRTree {
//
//    class IWrapper {
//    public:
//        virtual ~IWrapper() {};
//
//        virtual std::unique_ptr<const IExpressionNode> to_expression() { assert(false); };
//        virtual std::unique_ptr<const IStatementNode> to_statement() { assert(false); };
//        virtual std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                            std::unique_ptr<const LabelNode>& negativeLabel) { assert(false); };
//    };
//
//    class ExpressionWrapper : public IWrapper {
//    public:
//        explicit ExpressionWrapper(std::unique_ptr<const IExpressionNode>&& expression): expression_(std::move(expression)) {}
//
//        std::unique_ptr<const IExpressionNode> to_expression() override { return std::move(expression_); }
//        std::unique_ptr<const IStatementNode> to_statement() override;
//        std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                    std::unique_ptr<const LabelNode>& negativeLabel) override;
//
//    private:
//        std::unique_ptr<const IExpressionNode> expression_;
//    };
//
//    class StatementWrapper : public IWrapper {
//    public:
//        explicit StatementWrapper(std::unique_ptr<const IStatementNode>&& statement): statement_(std::move(statement)) {}
//
//        std::unique_ptr<const IStatementNode> to_statement() override { return std::move(statement_); }
//
//    private:
//        std::unique_ptr<const IStatementNode> statement_;
//    };
//
//    class ConditionalWrapper : public IWrapper {
//    public:
//        virtual ~ConditionalWrapper() {};
//
//        std::unique_ptr<const IExpressionNode> to_expression() override;
//        virtual std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                            std::unique_ptr<const LabelNode>& negativeLabel) override = 0;
//    };
//
//    // пока поддерживаем только "меньше <"
//    class RelativeConditionalWrapper : public ConditionalWrapper {
//    public:
//        RelativeConditionalWrapper(std::unique_ptr<const IExpressionNode>&& leftOperand,
//                                   std::unique_ptr<const IExpressionNode>&& rightOperand)
//                                   : leftOperand_(std::move(leftOperand)),
//                                   rightOperand_(std::move(rightOperand))
//                                   {}
//
//        std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                    std::unique_ptr<const LabelNode>& negativeLabel) override;
//
//    private:
//        std::unique_ptr<const IExpressionNode> leftOperand_;
//        std::unique_ptr<const IExpressionNode> rightOperand_;
//    };
//
//    class AndConditionalWrapper : public ConditionalWrapper {
//    public:
//        AndConditionalWrapper(std::unique_ptr<IWrapper>&& leftOperand,
//                              std::unique_ptr<IWrapper>&& rightOperand);
//
//        std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                    std::unique_ptr<const LabelNode>& negativeLabel) override;
//
//    private:
//        std::unique_ptr<IWrapper> leftOperand_;
//        std::unique_ptr<IWrapper> rightOperand_;
//    };
//
//    class OrConditionalWrapper : public ConditionalWrapper {
//    public:
//        OrConditionalWrapper(std::unique_ptr<IWrapper>&& leftOperand,
//                             std::unique_ptr<IWrapper>&& rightOperand);
//
//        std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                    std::unique_ptr<const LabelNode>& negativeLabel) override;
//
//    private:
//        std::unique_ptr<IWrapper> leftOperand_;
//        std::unique_ptr<IWrapper> rightOperand_;
//    };
//
//    class OppositeConditionalWrapper : public ConditionalWrapper {
//    public:
//        explicit OppositeConditionalWrapper(std::unique_ptr<IWrapper>&& wrapper) : internalWrapper_(std::move(wrapper)) {}
//
//        std::unique_ptr<const IStatementNode> to_conditional(std::unique_ptr<const LabelNode>& positiveLabel,
//                                                                    std::unique_ptr<const LabelNode>& negativeLabel) override;
//
//    private:
//        std::unique_ptr<IWrapper> internalWrapper_;
//    };
//
//    //from Make.h
////    template <typename T, class... Args>
////    inline const std::unique_ptr<const T> makeNode(Args&&... args) {
////        return std::make_unique<const T>(std::forward<Args>(args)...);
////    }
////
////    template <typename T, class... Args>
////    inline const std::unique_ptr<const T> makeWrapper(Args&&... args) {
////        return std::make_unique<const T>(std::forward<Args>(args)...);
////    }
//}
