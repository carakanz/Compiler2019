//
// Created by l1onsun on 15.12.19.
//
#include <IVisitor.h>

namespace IRTree {
    class IRTreeTranslator: public IVisitor  {
    public:
        void visit(const TypeIntNode& node);
        void visit(const TypeBooleanNode& node);
        void visit(const TypeArrayNode& node);
        void visit(const TypeUserNode& node);
        void visit(const TypeVoidNode& node);
        void visit(const TypeStringNode& node);
        void visit(const IdentifierNode& node);
        void visit(const ExpressionIdentifierNode& node);
        void visit(const ExpressionBinaryOperationNode& node);
        void visit(const ExpressionIndexNode& node);
        void visit(const ExpressionGetLengthNode& node);
        void visit(const ExpressionMethodCallNode& node);
        void visit(const ExpressionStaticMethodCallNode& node);
        void visit(const ExpressionIntegerLiteralNode& node);
        void visit(const ExpressionBooleanLiteralNode& node);
        void visit(const ExpressionThisNode& node);
        void visit(const ExpressionNewArrayNode& node);
        void visit(const ExpressionNewNode& node);
        void visit(const ExpressionNotOperatorNode& node);
        void visit(const ExpressionRoundBracketsNode& node);
        void visit(const StatementIfNode& node);
        void visit(const ListNode<IStatementNode, IStatementNode>& node);
        void visit(const StatementEmptyNode& node);
        void visit(const StatementWhileNode& node);
        void visit(const StatementPrintlnNode& node);
        void visit(const StatementAssignNode& node);
        void visit(const StatementAssignArrayNode& node);
        void visit(const StatementReturnNode& node);
        void visit(const DeclarationMethodNode& node);
        void visit(const DeclarationClassNode& node);
        void visit(const DeclarationVarNode& node);
        void visit(const ListNode<DeclarationClassNode, INodeBase>& node);
    }
};