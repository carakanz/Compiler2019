//
// Created by Zinenko Dmytro on 19.11.2019.
//

#pragma once

namespace SyntaxTree {
    template<class Source, class Interface>
    class ListNode;

    class IStatementNode;
    class INodeBase;
    class TypeIntNode;
    class TypeBooleanNode;
    class TypeArrayNode;
    class TypeUserNode;
    class TypeVoidNode;
    class TypeStringNode;
    class IdentifierNode;
    class ExpressionIdentifierNode;
    class ExpressionBinaryOperationNode;
    class ExpressionIndexNode;
    class ExpressionGetLengthNode;
    class ExpressionMethodCallNode;
    class ExpressionStaticMethodCallNode;
    class ExpressionIntegerLiteralNode;
    class ExpressionBooleanLiteralNode;
    class ExpressionThisNode;
    class ExpressionNewArrayNode;
    class ExpressionNewNode;
    class ExpressionNotOperatorNode;
    class ExpressionRoundBracketsNode;
    class StatementEmptyNode;
    class StatementIfNode;
    class StatementWhileNode;
    class StatementPrintlnNode;
    class StatementAssignNode;
    class StatementAssignArrayNode;
    class StatementReturnNode;
    class DeclarationMethodNode;
    class DeclarationClassNode;
    class DeclarationVarNode;

    class IVisitor {
    public:
        virtual void visit(const TypeIntNode& node) = 0;
        virtual void visit(const TypeBooleanNode& node) = 0;
        virtual void visit(const TypeArrayNode& node) = 0;
        virtual void visit(const TypeUserNode& node) = 0;
        virtual void visit(const TypeVoidNode& node) = 0;
        virtual void visit(const TypeStringNode& node) = 0;
        virtual void visit(const IdentifierNode& node) = 0;
        virtual void visit(const ExpressionIdentifierNode& node) = 0;
        virtual void visit(const ExpressionBinaryOperationNode& node) = 0;
        virtual void visit(const ExpressionIndexNode& node) = 0;
        virtual void visit(const ExpressionGetLengthNode& node) = 0;
        virtual void visit(const ExpressionMethodCallNode& node) = 0;
        virtual void visit(const ExpressionStaticMethodCallNode& node) = 0;
        virtual void visit(const ExpressionIntegerLiteralNode& node) = 0;
        virtual void visit(const ExpressionBooleanLiteralNode& node) = 0;
        virtual void visit(const ExpressionThisNode& node) = 0;
        virtual void visit(const ExpressionNewArrayNode& node) = 0;
        virtual void visit(const ExpressionNewNode& node) = 0;
        virtual void visit(const ExpressionNotOperatorNode& node) = 0;
        virtual void visit(const ExpressionRoundBracketsNode& node) = 0;
        virtual void visit(const StatementIfNode& node) = 0;
        virtual void visit(const ListNode<IStatementNode, IStatementNode>& node) = 0;
        virtual void visit(const StatementEmptyNode& node) = 0;
        virtual void visit(const StatementWhileNode& node) = 0;
        virtual void visit(const StatementPrintlnNode& node) = 0;
        virtual void visit(const StatementAssignNode& node) = 0;
        virtual void visit(const StatementAssignArrayNode& node) = 0;
        virtual void visit(const StatementReturnNode& node) = 0;
        virtual void visit(const DeclarationMethodNode& node) = 0;
        virtual void visit(const DeclarationClassNode& node) = 0;
        virtual void visit(const DeclarationVarNode& node) = 0;
        virtual void visit(const ListNode<DeclarationClassNode, INodeBase>& node) = 0;

        virtual ~IVisitor() = default;
    };
}
