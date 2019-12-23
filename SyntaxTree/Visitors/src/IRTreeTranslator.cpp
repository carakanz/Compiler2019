//
// Created by l1onsun on 15.12.19.
//

#include <SymbolTableBuilder.h>
#include <IRTree/Nodes.h>
#include <IRTreeTranslator.h>
#include <Wrapper/Wrapper.h>
#include <Wrapper/Expression/WrapperExpressionBinaryOperation.h>
#include <Consts.h>

namespace SyntaxTreeVisitor {

    void IRTreeTranslator::visit(const SyntaxTree::TypeIntNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeArrayNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeBooleanNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeUserNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeVoidNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::TypeStringNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::IdentifierNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionIdentifierNode &node)
    {
        const auto method_var_info = current_method_->var_info.find(node.identifier->name);
        if (method_var_info != current_method_->var_info.cend()) {
            auto wrapper = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>();
            //TODO
            last_wrapper_ = std::move(wrapper);
            return;
        }
        const auto method_arg_info = current_method_->arg_info.find(node.identifier->name);
        if (method_arg_info != current_method_->arg_info.cend()) {
            auto wrapper = std::make_unique<IRTree::Wrapper<IRTree::ExpressionTempNode>>();
            //TODO
            last_wrapper_ = std::move(wrapper);
            return;
        }
        const auto class_var_info = current_class_->var_info.find(node.identifier->name);
        if (class_var_info != current_class_->var_info.cend()) {
            auto wrapper = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>();
            //TODO
            last_wrapper_ = std::move(wrapper);
            return;
        }
        assert(false);
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
        node.object->accept(*this);
        auto object_wrapper = std::move(last_wrapper_);

        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                object_wrapper->to_expression(),
                std::make_unique<IRTree::ExpressionNameNode(std::make_unique<IRTree::LabelNode(node.method->name))>);
        for(const auto& argument : node.arguments) {
            argument->accept(*this);
            result->arguments.push_back(last_wrapper_->to_expression());
        }
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionCallNode>>(result);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionStaticMethodCallNode &node) {
        auto result = std::make_unique<IRTree::ExpressionCallNode>(
                std::make_unique<IRTree::ExpressionTypeNode>(node.class_id->name));
        for (const auto &argument : node.arguments) {
            argument->accept(*this);
            result->arguments.push_back(last_wrapper_->to_expression());
        }
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionCallNode>>(result);
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionIntegerLiteralNode &node) {
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionConstNode>>(
                std::make_unique<IRTree::ExpressionConstNode>(node.value));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionBooleanLiteralNode &node) {
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionConstNode>>(
                std::make_unique<IRTree::ExpressionConstNode>(node.value));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionThisNode &node) {
        last_wrapper_ = std::make_unique<IRTree::Wrapper<IRTree::ExpressionLocalNode>>(
                std::make_unique<IRTree::ExpressionLocalNode>(true, "this"));
    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionNewArrayNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionNewNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionNotOperatorNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::ExpressionRoundBracketsNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementIfNode &node) {

    }

    void IRTreeTranslator::visit(
            const SyntaxTree::ListNode<SyntaxTree::IStatementNode, SyntaxTree::IStatementNode> &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementEmptyNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementWhileNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementPrintlnNode &node) {
        std::cout << "SyntaxTree::StatementPrintlnNode" << std::endl;
        node.expression->accept(*this);

//    const auto printOperandWrapper = std::move(currentWrapper);
//    std::vector<std::shared_ptr<const IIrtExpression>> arguments;
//    arguments.push_back(printOperandWrapper->ToExpression());
//
//    currentWrapper = makeWrapper<StatementWrapper>(
//            makeNode<IrtExpressionStatement>(
//                    makeNode<IrtCallExpression>(
//                            makeNode<IrtNameExpression>(makeNode<IrtLabel>(L"print")),
//                            makeNode<IrtExpressionList>(std::move(arguments))
//                    )
//            )
//    );
    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementAssignNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementAssignArrayNode &node) {

    }

    void IRTreeTranslator::visit(const SyntaxTree::StatementReturnNode &node) {

    }V

    void IRTreeTranslator::visit(const SyntaxTree::DeclarationMethodNode &node) {
        for (const auto &statement : node.statements) {
            buildStatement(statement);
        }

        // ... node.variables

    }

    void IRTreeTranslator::visit(const SyntaxTree::DeclarationClassNode &node) {
        goal->add_class(node.identifier->name);
        for (const auto &method : node.methods) {
            method->accept(*this);

            std::string method_signature = SymbolTree::SymbolTableBuilder::build_method_signature(*method);
            goal->add_method(node.identifier->name, method_signature, last_wrapper_->to_statement());
        }

    }

    void IRTreeTranslator::visit(const SyntaxTree::DeclarationVarNode &node) {

    }

    void IRTreeTranslator::visit( // GoalNode
            const SyntaxTree::ListNode<SyntaxTree::DeclarationClassNode, SyntaxTree::INodeBase> &node) {

        //yea it's govnokod
        //handle main class first
        for (const auto &item : node.items) {
            if (item->identifier->name == mainClass->name) {
                current_class = getClassFromName(item->identifier->name);
                item->accept(*this);
            }
        }

        //then handle others
        for (const auto &item : node.items) {
            if (item->identifier->name != mainClass->name) {
                current_class = getClassFromName(item->identifier->name);
                item->accept(*this);
            }
        }

    }

    void IRTreeTranslator::buildStatement(const std::unique_ptr<SyntaxTree::IStatementNode> &statement) {
        std::cout << "here now" << std::endl;
        statement->accept(*this);
        //...
    }

}