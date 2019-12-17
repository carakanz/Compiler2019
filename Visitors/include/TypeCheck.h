//
// Created by carak on 17.12.2019.
//

#include <SymbolTree.h>
#include <Nodes.h>

namespace Visitor {

    class TypeCheck : SyntaxTree::IVisitor  {
    public:
        bool can_assigned(const std::string& src, const std::string& dst) const {
            // DOTO
            return src == dst;
        }

        std::string is_array(const std::string& type_name) const {
            return (type_name.size() > 2 &&
                    type_name[type_name.size() - 1] == ']' &&
                    type_name[type_name.size() - 2] == '[') ?
                   type_name.substr(type_name.size() - 2) :
                   "";
        }

        void visit(const SyntaxTree::TypeIntNode &node) override;

        void visit(const SyntaxTree::TypeBooleanNode &node) override;

        void visit(const SyntaxTree::TypeArrayNode &node) override;

        void visit(const SyntaxTree::TypeUserNode &node) override;

        void visit(const SyntaxTree::TypeVoidNode &node) override;

        void visit(const SyntaxTree::TypeStringNode &node) override;

        void visit(const SyntaxTree::IdentifierNode &node) override;

        void visit(const SyntaxTree::ExpressionIdentifierNode &node) override;

        void visit(const SyntaxTree::ExpressionBinaryOperationNode &node) override;

        void visit(const SyntaxTree::ExpressionIndexNode &node) override;

        void visit(const SyntaxTree::ExpressionGetLengthNode &node) override;

        void visit(const SyntaxTree::ExpressionMethodCallNode &node) override;

        void visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) override;

        void visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) override;

        void visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) override;

        void visit(const SyntaxTree::ExpressionThisNode &node) override;

        void visit(const SyntaxTree::ExpressionNewArrayNode &node) override;

        void visit(const SyntaxTree::ExpressionNewNode &node) override;

        void visit(const SyntaxTree::ExpressionNotOperatorNode &node) override;

        void visit(const SyntaxTree::ExpressionRoundBracketsNode &node) override;

        void visit(const SyntaxTree::StatementIfNode &node) override;

        void visit(const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) override;

        void visit(const SyntaxTree::StatementEmptyNode &node) override;

        void visit(const SyntaxTree::StatementWhileNode &node) override;

        void visit(const SyntaxTree::StatementPrintlnNode &node) override;

        void visit(const SyntaxTree::StatementAssignNode &node) override;

        void visit(const SyntaxTree::StatementAssignArrayNode &node) override;

        void visit(const SyntaxTree::StatementReturnNode &node) override;

        void visit(const SyntaxTree::DeclarationMethodNode &node) override;

        void visit(const SyntaxTree::DeclarationClassNode &node) override;

        void visit(const SyntaxTree::DeclarationVarNode &node) override;

        void visit(const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) override;

    private:
        const SyntaxTree::DeclarationClassNode* current_class_;
        const SyntaxTree::DeclarationMethodNode* current_method_;
        const SymbolTree::SymbolTree symbol_tree_;
        std::string last_return_type_;
    };

}