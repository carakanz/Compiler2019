//
// Created by l1onsun on 15.12.19.
//

#include <SymbolTableBuilder.h>
#include <IRTree/Nodes.h>
#include <IRTreeTranslator.h>
#include <Wrapper/Wrapper.h>
#include <Wrapper/Expression/WrapperExpressionBinaryOperation.h>
#include <Wrapper/Expression/WrapperExpressionAnd.h>
#include <Wrapper/Expression/WrapperExpressionNot.h>
#include <Consts.h>

namespace SyntaxTreeVisitor {

    void IRTreeTranslator::visit(const SyntaxTree::TypeIntNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeArrayNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeBooleanNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeUserNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeVoidNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeStringNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::IdentifierNode &node) {
        const auto method_var_info = current_method_->var_info.find(node.name);
        if (method_var_info != current_method_->var_info.cend()) {
            last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>(false,
                                                                                           method_var_info->second.name);
            return;
        }
        const auto method_arg_info = current_method_->arg_info.find(node.name);
        if (method_arg_info != current_method_->arg_info.cend()) {
            last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>(false,
                                                                                           method_arg_info->second.name);
            return;
        }
        const auto class_var_info = current_class_->var_info.find(node.name);
        if (class_var_info != current_class_->var_info.cend()) {
            last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>(false,
                                                                                           class_var_info->second.name);
            return;
        }
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionIdentifierNode &node) {
        node.identifier->accept(*this);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionBinaryOperationNode &node) {
        node.left->accept(*this);
        auto left_wrapper = std::move(last_wrapper_);
        node.right->accept(*this);
        auto right_wrapper = std::move(last_wrapper_);
        switch (node.operation_type) {
            case BinaryOperationType::ADD:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::ADD>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::SUB:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::SUB>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::MUL:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::MUL>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::DIV:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::DIV>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::MOD:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::MOD>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::OR:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::OR>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::AND:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::AND>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::EQUIVALENT:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::EQUIVALENT>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::NOT_EQUIVALENT:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::NOT_EQUIVALENT>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::LESS:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::LESS>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::LESS_OR_EQUIVALENT:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::LESS_OR_EQUIVALENT>>(
                        std::move(left_wrapper),
                        std::move(right_wrapper)
                );
                break;
            case BinaryOperationType::MORE:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::LESS_OR_EQUIVALENT>>(
                        std::move(right_wrapper),
                        std::move(left_wrapper)
                );
                break;
            case BinaryOperationType::MORE_OR_EQUIVALENT:
                last_wrapper_ = std::make_unique<IRTree::WrapperExpressionBinaryOperation<BinaryOperationType::LESS>>(
                        std::move(right_wrapper),
                        std::move(left_wrapper)
                );
                break;
        }
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionIndexNode &node) {
        node.array->accept(*this);
        auto array_wrapper = std::move(last_wrapper_);
        node.index->accept(*this);
        auto index_wrapper = std::move(last_wrapper_);

        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionMemoryNode>>(
                std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                        BinaryOperationType::ADD,
                        array_wrapper->to_expression(),
                        std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                                BinaryOperationType::ADD,
                                std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                                        BinaryOperationType::MUL,
                                        index_wrapper->to_expression(),
                                        std::make_unique<IRTree::ExpressionConstNode>(size_of_ptr)
                                ),
                                std::make_unique<IRTree::ExpressionConstNode>(size_of_ptr)
                        )
                )
        );
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionGetLengthNode &node) {
        node.array->accept(*this);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionMethodCallNode &node) {
        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                std::make_unique<IRTree::ExpressionNameNode>(
                        std::make_unique<IRTree::LabelNode>(node.method->name)
                )
        );

        node.object->accept(*this);
        result->arguments.push_back(last_wrapper_->to_expression());

        for (const auto &argument : node.arguments) {
            argument->accept(*this);
            result->arguments.push_back(last_wrapper_->to_expression());
        }

        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionCallNode>>(std::move(result));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {
        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                std::make_unique<IRTree::ExpressionNameNode>(
                        std::make_unique<IRTree::LabelNode>(node.method->name)
                )
        );

        for (const auto &argument : node.arguments) {
            argument->accept(*this);
            result->arguments.push_back(last_wrapper_->to_expression());
        }
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionCallNode>>(std::move(result));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionConstNode>>(node.value);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionConstNode>>(node.value);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionThisNode &/*node*/) {
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>(
                std::make_unique<IRTree::ExpressionLocalNode>(true, "this"));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionNewArrayNode &node) {
        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                std::make_unique<IRTree::ExpressionNameNode>(
                        std::make_unique<IRTree::LabelNode>(std::string("new[]"))
                )
        );
        node.size->accept(*this);
        result->arguments.push_back(std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                BinaryOperationType::MUL,
                last_wrapper_->to_expression(),
                std::make_unique<IRTree::ExpressionConstNode>(1))
        );
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionCallNode>>(std::move(result));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionNewNode &/*node*/) {
        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                std::make_unique<IRTree::ExpressionNameNode>(
                        std::make_unique<IRTree::LabelNode>(std::string("new"))
                )
        );

        //Todo
        result->arguments.push_back(std::make_unique<IRTree::ExpressionConstNode>(1));


        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionCallNode>>(std::move(result));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {
        node.expression->accept(*this);
        last_wrapper_ = std::make_unique<IRTree::WrapperOperationNot>(std::move(last_wrapper_));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {
        node.expression->accept(*this);
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementIfNode &node) {
        node.conditional->accept(*this);
        const auto conditional_wrapper = std::move(last_wrapper_);
        node.then_statement->accept(*this);
        const auto then_statement_wrapper = std::move(last_wrapper_);
        node.else_statement->accept(*this);
        const auto else_statement_wrapper = std::move(last_wrapper_);

        auto label_if_true = std::make_unique<IRTree::LabelNode>(std::string("if_true"));
        auto label_if_false = std::make_unique<IRTree::LabelNode>(std::string("if_false"));
        auto label_if_end = std::make_unique<IRTree::LabelNode>(std::string("if_end"));

        auto true_statement_label = std::make_unique<IRTree::StatementLabelNode>(
                std::make_unique<IRTree::LabelNode>(*label_if_true));
        auto false_statement_label = std::make_unique<IRTree::StatementLabelNode>(
                std::make_unique<IRTree::LabelNode>(*label_if_false));
        auto end_label = std::make_unique<IRTree::StatementLabelNode>(
                std::make_unique<IRTree::LabelNode>(*label_if_end));

        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementSeqNode>>(
                conditional_wrapper->to_conditional(std::move(label_if_true), std::move(label_if_false)),
                std::move(true_statement_label),
                then_statement_wrapper->to_statement(),
                std::make_unique<IRTree::StatementJumpNode>(std::move(label_if_end)),
                std::move(false_statement_label),
                else_statement_wrapper->to_statement(),
                std::move(end_label)
        );
    }

    void IRTreeTranslator::visit(
            const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {
        assert(!node.items.empty());
        if (node.items.size() == 1) {
            node.items[0]->accept(*this);
            return;
        }
        std::vector<std::unique_ptr<IRTree::IStatementNode>> statements;
        for (const auto &statement : node.items) {
            statement->accept(*this);
            statements.push_back(last_wrapper_->to_statement());
        }
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementSeqNode>>(std::move(statements));
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementEmptyNode &/*node*/) {
        // TODO
        assert(false);
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementWhileNode &node) {
        node.conditional->accept(*this);
        auto conditional_wrapper = std::move(last_wrapper_);
        node.then_statement->accept(*this);
        auto then_statement_wrapper = std::move(last_wrapper_);

        auto label_conditional = std::make_unique<IRTree::LabelNode>(std::string("while_conditional"));
        auto label_true = std::make_unique<IRTree::LabelNode>(std::string("while_true"));
        auto label_end = std::make_unique<IRTree::LabelNode>(std::string("while_end"));

        auto conditional_statement_label = std::make_unique<IRTree::StatementLabelNode>(
                std::make_unique<IRTree::LabelNode>(*label_conditional));
        auto true_statement_label = std::make_unique<IRTree::StatementLabelNode>(
                std::make_unique<IRTree::LabelNode>(*label_true));
        auto end_label = std::make_unique<IRTree::StatementLabelNode>(
                std::make_unique<IRTree::LabelNode>(*label_end));

        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementSeqNode>>(
                std::make_unique<IRTree::StatementJumpNode>(std::move(label_conditional)),
                std::move(true_statement_label),
                then_statement_wrapper->to_statement(),
                std::move(conditional_statement_label),
                conditional_wrapper->to_conditional(std::move(label_true), std::move(label_end)),
                std::move(end_label)
        );
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementPrintlnNode &node) {
        node.expression->accept(*this);

        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                std::make_unique<IRTree::ExpressionNameNode>(
                        std::make_unique<IRTree::LabelNode>(std::string("System.out.println"))
                )
        );

        const std::unique_ptr<IRTree::IWrapper> print_wrapper = std::move(last_wrapper_);
        result->arguments.push_back(print_wrapper->to_expression());

        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementExpressionNode> >(
                std::make_unique<IRTree::StatementExpressionNode>(
                        std::move(result)
                )
        );
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementAssignNode &node) {
        node.expression->accept(*this);
        auto expression_wrapper = std::move(last_wrapper_);
        node.identifier->accept(*this);
        auto identifier_wrapper = std::move(last_wrapper_);
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementMoveNode>>(
                std::make_unique<IRTree::StatementMoveNode>(
                        std::make_unique<IRTree::ExpressionMemoryNode>(
                                identifier_wrapper->to_expression()),
                        expression_wrapper->to_expression()));
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementAssignArrayNode &node) {
        node.expression->accept(*this);
        auto expression_wrapper = std::move(last_wrapper_);
        node.identifier->accept(*this);
        auto identifier_wrapper = std::move(last_wrapper_);
        node.index->accept(*this);
        auto index_wrapper = std::move(last_wrapper_);

        auto expression_memory_node = std::make_unique<IRTree::ExpressionMemoryNode>(
                std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                        BinaryOperationType::ADD,
                        identifier_wrapper->to_expression(),
                        std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                                BinaryOperationType::ADD,
                                std::make_unique<IRTree::ExpressionBinaryOperationNode>(
                                        BinaryOperationType::MUL,
                                        index_wrapper->to_expression(),
                                        std::make_unique<IRTree::ExpressionConstNode>(size_of_ptr)
                                ),
                                std::make_unique<IRTree::ExpressionConstNode>(size_of_ptr)
                        )
                )
        );

        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementMoveNode>>(
                std::make_unique<IRTree::StatementMoveNode>(
                        std::move(expression_memory_node),
                        expression_wrapper->to_expression()
                )
        );
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementReturnNode &node) {
        node.expression->accept(*this);
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::StatementMoveNode>>(
                std::make_unique<IRTree::StatementMoveNode>(
                        std::make_unique<IRTree::ExpressionTempNode>(
                                std::make_unique<IRTree::TempNode>(return_expression)),
                        last_wrapper_->to_expression()
                )
        );
    }

    void IRTreeTranslator::visit(const SyntaxTree::DeclarationMethodNode &node) {
        std::unique_ptr<IRTree::IWrapper> result_wrapper = nullptr;
        for (const auto &statement : node.statements) {
            buildStatement(statement, result_wrapper);
        }
        last_wrapper_ = std::move(result_wrapper);

    }

    void IRTreeTranslator::visit(const SyntaxTree::DeclarationClassNode &node) {
        for (const auto &method : node.methods) {
            std::string method_signature = SymbolTree::SymbolTableBuilder::build_method_signature(*method);
            current_method_ = &current_class_->method_info.find(method_signature)->second;
            method->accept(*this);

            goal->add_method(node.identifier->name, method_signature, last_wrapper_->to_statement());
        }

    }

    void IRTreeTranslator::visit(const SyntaxTree::DeclarationVarNode &/*node*/) {
        assert(false);
    }

    void IRTreeTranslator::visit( // GoalNode
            const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {
        goal = std::make_unique<IRTreeGoal>();

        for (const auto &item : node.items) {
            goal->add_class(item->identifier->name);
            current_class_ = &symbol_tree_.classes_info.find(item->identifier->name)->second;
            item->accept(*this);
        }


    }

    void IRTreeTranslator::buildStatement(const std::unique_ptr<SyntaxTree::IStatementNode> &statement,
                                          std::unique_ptr<IRTree::IWrapper>& result_wrapper) {
        statement->accept(*this);
        if (result_wrapper) {
            result_wrapper = std::make_unique<IRTree::Wrapper<IRTree::StatementSeqNode> >( //need StatementWrapper
                    std::make_unique<IRTree::StatementSeqNode> (
                                result_wrapper->to_statement(),
                                last_wrapper_->to_statement()
                    )
            );
        }
        else {
            result_wrapper = std::move(last_wrapper_);
        }
    }

}
