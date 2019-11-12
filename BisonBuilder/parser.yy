%require "3.4.2"
%language "c++"

%define api.parser.class { Parser }
%define api.namespace { BisonParser }
%define api.token.constructor
%define api.value.type variant

%code requires{
    #pragma once

    #include<memory>
    #include<string>
    #include<TreeNodes.h>

    using namespace SyntaxTree;

namespace BisonBuilder {
    class Builder;
    }
}

%parse-param { BisonBuilder::Builder &scanner }

%code {
    #include "Builder.h"

    #undef yylex
    #define yylex scanner.get_next_token
}


%token T_EOF
%token T_CLASS
%token T_EXTEND
%token T_THIS
%token T_LEFT_BRACKET
%token T_RIGHT_BRACKET
%token T_LEFT_BRACE
%token T_RIGHT_BRACE
%token T_LEFT_SQUARE_BRACKET
%token T_RIGHT_SQUARE_BRACKET
%token <DeclarationMethodNode::PrivacyModifier> T_PRIVACY_MODIFIER
%token T_STATIC_MODIFIER
%token T_RETURN
%token T_INT
%token T_BOOLEAN
%token T_STRING
%token T_VOID
%token T_NEW
%token T_LENGTH
%token T_WHILE
%token T_IF
%token T_ELSE
%token T_PRINT_LN
%token <bool> T_BOOL_VALUE
%token <int> T_INT_VALUE
%token T_DOT
%token <std::string> T_IDENTIFIER
%token T_SEMICOLON
%token T_COMMA
%token T_ASSIGN_OPERATION
%token <ExpressionBinaryOperationNode::BinaryOperationType> T_MUL_OPERATION
%token <ExpressionBinaryOperationNode::BinaryOperationType> T_ADD_OPERATION
%token <ExpressionBinaryOperationNode::BinaryOperationType> T_COMPARE_OPERATION
%token <ExpressionBinaryOperationNode::BinaryOperationType> T_EQUIVALENT_OPERATION
%token <ExpressionBinaryOperationNode::BinaryOperationType> T_AND_OPERATION
%token <ExpressionBinaryOperationNode::BinaryOperationType> T_OR_OPERATION
%token T_NOT_OPERATION
%token T_UNKNOWN

%type Goal
%type <std::unique_ptr<GoalNode>> GoalBegin
%type <std::unique_ptr<DeclarationClassNode>> DeclarationClassBegin
%type <std::unique_ptr<DeclarationClassNode>> DeclarationClass
%type <std::unique_ptr<DeclarationVarNode>> DeclarationVar
%type <std::unique_ptr<PairTypeIdentifierNode>> PairTypeIdentifier
%type <std::unique_ptr<DeclarationMethodNode>> DeclarationMethodBegin
%type <std::unique_ptr<DeclarationMethodNode>> DeclarationMethodArgs
%type <std::unique_ptr<DeclarationMethodNode>> DeclarationMethodNameEnd
%type <std::unique_ptr<DeclarationMethodNode>> DeclarationMethodBody
%type <std::unique_ptr<DeclarationMethodNode>> DeclarationMethod
%type <std::unique_ptr<ITypeNode>> Type
%type <std::unique_ptr<StatementListNode>> OpenStatement
%type <std::unique_ptr<IStatementNode>> Statement
%type <std::unique_ptr<IExpressionNode>> Expression
%type <std::unique_ptr<ExpressionMethodCallNode>> ExpressionMethodCallBegin
%type <std::unique_ptr<ExpressionMethodCallNode>> ExpressionMethodCallArgs
%type <std::unique_ptr<IdentifierNode>> Identifier

%right T_NOT_OPERATION

%nonassoc T_ELSE

%left T_OR_OPERATION
%left T_AND_OPERATION
%left T_COMPARE_OPERATION
%left T_EQUIVALENT_OPERATION
%left T_ADD_OPERATION
%left T_MUL_OPERATION

%left T_DOT T_LENGTH T_LEFT_SQUARE_BRACKET

%%

Goal
    : GoalBegin T_EOF {
        std::cout << "Goal: T_EOF" << std::endl;
        scanner.root_ = std::move($1);
    }

GoalBegin
    : GoalBegin DeclarationClass {
        std::cout << "GoalBegin: Goal DeclarationClass" << std::endl;
        $$ = std::move($1);
        $$->items.push_back(std::move($2));
    }
    | DeclarationClass {
        std::cout << "GoalBegin: DeclarationClass" << std::endl;
        $$ = std::make_unique<GoalNode>(std::move($1));
    }

DeclarationClassBegin
    : T_CLASS Identifier T_EXTEND Identifier T_LEFT_BRACE {
        std::cout << "DeclarationClassBegin: T_CLASS Identifier T_EXTEND Identifier T_LEFT_BRACKET" << std::endl;
        $$ = std::make_unique<DeclarationClassNode>();
        $$->identifier = std::move($2);
        $$->base_class_identifier = std::move($4);
    }
    | T_CLASS Identifier T_LEFT_BRACE {
        std::cout << "DeclarationClassBegin: T_CLASS Identifier T_LEFT_BRACKET" << std::endl;
        //$$ = std::make_unique<DeclarationClassNode>();
        //$$->identifier = std::move($2);
    }
    | DeclarationClassBegin DeclarationVar {
        $$ = std::move($1);
        $$->variables.push_back(std::move($2));
    }
    | DeclarationClassBegin DeclarationMethod {
        $$ = std::move($1);
        $$->methods.push_back(std::move($2));
    }

DeclarationClass
    : DeclarationClassBegin T_RIGHT_BRACE {
        std::cout << "DeclarationClass: DeclarationClassBegin T_RIGHT_BRACE" << std::endl;
        $$ = std::move($1);
    }

DeclarationVar
    : PairTypeIdentifier T_SEMICOLON {
        $$ = std::make_unique<DeclarationVarNode>();
        $$->var_type = std::move($1->var_type);
        $$->identifier = std::move($1->identifier);
    }

PairTypeIdentifier
    : Type Identifier {
        $$ = std::make_unique<PairTypeIdentifierNode>();
        $$->var_type = std::move($1);
        $$->identifier = std::move($2);
    }
    | Identifier Identifier {
        $$ = std::make_unique<PairTypeIdentifierNode>();
        $$->var_type = std::make_unique<TypeUserNode>(std::move($1));
        $$->identifier = std::move($2);
    }

DeclarationMethodBegin
    : T_PRIVACY_MODIFIER T_STATIC_MODIFIER Type Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->privacy_modifier = $1;
        $$->is_static = true;
        $$->return_type = std::move($3);
        $$->identifier = std::move($4);
    }
    | T_PRIVACY_MODIFIER Type Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->privacy_modifier = $1;
        $$->is_static = false;
        $$->return_type = std::move($2);
        $$->identifier = std::move($3);
    }
    | T_PRIVACY_MODIFIER T_STATIC_MODIFIER Identifier Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->privacy_modifier = $1;
        $$->is_static = true;
        $$->return_type = std::make_unique<TypeUserNode>(std::move($3));
        $$->identifier = std::move($4);
    }
    | T_PRIVACY_MODIFIER Identifier Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->privacy_modifier = $1;
        $$->is_static = false;
        $$->return_type = std::make_unique<TypeUserNode>(std::move($2));
        $$->identifier = std::move($3);
    }

DeclarationMethodArgs
    : DeclarationMethodBegin PairTypeIdentifier {
        $$ = std::move($1);
        $$->arguments.push_back(std::move($2));
    }
    | DeclarationMethodArgs T_COMMA PairTypeIdentifier {
        $$ = std::move($1);
        $$->arguments.push_back(std::move($3));
    }

DeclarationMethodNameEnd
    : DeclarationMethodBegin T_RIGHT_BRACKET T_LEFT_BRACE {
        $$ = std::move($1);
    }
    | DeclarationMethodArgs T_RIGHT_BRACKET T_LEFT_BRACE {
        $$ = std::move($1);
    }
    | DeclarationMethodNameEnd DeclarationVar {
        $$ = std::move($1);
        $$->variables.push_back(std::move($2));
    }

DeclarationMethodBody
    : DeclarationMethodNameEnd Statement {
        $$ = std::move($1);
        $$->statements.push_back(std::move($2));
    }
    | DeclarationMethodBody Statement {
        $$ = std::move($1);
        $$->statements.push_back(std::move($2));
    }

DeclarationMethod
    : DeclarationMethodBody T_RIGHT_BRACE {
        $$ = std::move($1);
    }

Type
    : T_INT {
        $$ = std::make_unique<TypeIntNode>();
    }
    | T_BOOLEAN {
        $$ = std::make_unique<TypeBooleanNode>();
    }
    | T_VOID {
        $$ = std::make_unique<TypeVoidNode>();
    }
    | T_STRING {
            $$ = std::make_unique<TypeVoidNode>();
    }
    | Type T_LEFT_SQUARE_BRACKET T_RIGHT_SQUARE_BRACKET {
        $$ = std::make_unique<TypeArrayNode>(std::move($1));
    }
    | Identifier T_LEFT_SQUARE_BRACKET T_RIGHT_SQUARE_BRACKET {
        $$ = std::make_unique<TypeArrayNode>(std::make_unique<TypeUserNode>(std::move($1)));
    }

OpenStatement
    : T_LEFT_BRACE Statement {
        $$ = std::make_unique<StatementListNode>(std::move($2));
    }
    | OpenStatement Statement {
        $$ = std::move($1);
        $$->items.push_back(std::move($2));
    }

Statement
    : OpenStatement T_RIGHT_BRACE {
        $$ = std::move($1);
    }
    | T_LEFT_BRACE T_RIGHT_BRACE {
        $$ = std::make_unique<StatementEmptyNode>();
    }
    | T_IF T_LEFT_BRACKET Expression T_RIGHT_BRACKET Statement T_ELSE Statement {
        auto statement = std::make_unique<StatementIfNode>();
        statement->conditional = std::move($3);
        statement->then_statement = std::move($5);
        statement->else_statement = std::move($7);
        $$ = std::move(statement);
    }
    | T_IF T_LEFT_BRACKET Expression T_RIGHT_BRACKET Statement {
        auto statement = std::make_unique<StatementIfNode>();
        statement->conditional = std::move($3);
        statement->then_statement = std::move($5);
        statement->else_statement = std::make_unique<StatementEmptyNode>();
        $$ = std::move(statement);
    }
    | T_WHILE T_LEFT_BRACKET Expression T_RIGHT_BRACKET Statement {
        auto statement = std::make_unique<StatementWhileNode>();
        statement->conditional = std::move($3);
        statement->then_statement = std::move($5);
        $$ = std::move(statement);
    }
    | T_PRINT_LN T_LEFT_BRACKET Expression T_RIGHT_BRACKET T_SEMICOLON {
        auto statement = std::make_unique<StatementPrintlnNode>();
        statement->expression = std::move($3);
        $$ = std::move(statement);
    }
    | Identifier T_ASSIGN_OPERATION Expression T_SEMICOLON {
        auto statement = std::make_unique<StatementAssignNode>();
        statement->identifier = std::move($1);
        statement->expression = std::move($3);
        $$ = std::move(statement);
    }
    | Identifier T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET T_ASSIGN_OPERATION Expression T_SEMICOLON {
        auto statement = std::make_unique<StatementAssignArrayNode>();
        statement->identifier = std::move($1);
        statement->index = std::move($3);
        statement->expression = std::move($6);
        $$ = std::move(statement);
    }
    | T_RETURN Expression T_SEMICOLON {
        auto statement = std::make_unique<StatementReturnNode>();
        statement->expression = std::move($2);
        $$ = std::move(statement);
    }

Expression
    : Expression T_MUL_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->left = std::move($1);
        expression->operation_type = $2;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_ADD_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->left = std::move($1);
        expression->operation_type = $2;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_COMPARE_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->left = std::move($1);
        expression->operation_type = $2;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_EQUIVALENT_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->left = std::move($1);
        expression->operation_type = $2;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_AND_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->left = std::move($1);
        expression->operation_type = $2;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_OR_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->left = std::move($1);
        expression->operation_type = $2;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET {
        auto expression = std::make_unique<ExpressionIndexNode>();
        expression->array = std::move($1);
        expression->index = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_LENGTH {
        auto expression = std::make_unique<ExpressionGetLengthNode>();
        expression->array = std::move($1);
        $$ = std::move(expression);
    }
    | ExpressionMethodCallBegin T_RIGHT_BRACKET {
        $$ = std::move($1);
    }
    | ExpressionMethodCallArgs T_RIGHT_BRACKET {
        $$ = std::move($1);
    }
    | T_INT_VALUE {
        auto expression = std::make_unique<ExpressionIntegerLiteralNode>();
        expression->value = $1;
        $$ = std::move(expression);
    }
    | T_BOOL_VALUE {
        auto expression = std::make_unique<ExpressionIntegerLiteralNode>();
        expression->value = $1;
        $$ = std::move(expression);
    }
    | T_THIS {
        $$ = std::make_unique<ExpressionThisNode>();
    }
    | T_NEW Identifier T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET {
        auto expression = std::make_unique<ExpressionNewArrayNode>();
        expression->identifier = std::move($2);
        expression->size = std::move($4);
        $$ = std::move(expression);
    }
    | T_NEW Identifier T_LEFT_BRACKET T_RIGHT_BRACKET {
        auto expression = std::make_unique<ExpressionNewNode>();
        expression->identifier = std::move($2);
        $$ = std::move(expression);
    }
    | T_NOT_OPERATION Expression {
        auto expression = std::make_unique<ExpressionNotOperatorNode>();
        expression->expression = std::move($2);
        $$ = std::move(expression);
    }
    | T_LEFT_BRACKET Expression T_RIGHT_BRACKET {
        auto expression = std::make_unique<ExpressionRoundBracketsNode>();
        expression->expression = std::move($2);
        $$ = std::move(expression);
    }
    | Identifier {
        auto expression = std::make_unique<ExpressionIdentifierNode>();
        expression->identifier = std::move($1);
        $$ = std::move(expression);
    }

ExpressionMethodCallBegin
    : Expression T_DOT Identifier T_LEFT_BRACKET {
        auto expression = std::make_unique<ExpressionMethodCallNode>();
        expression->object = std::move($1);
        expression->method = std::move($3);
        $$ = std::move(expression);
    }

ExpressionMethodCallArgs
    : ExpressionMethodCallBegin Expression {
        auto expression = std::make_unique<ExpressionMethodCallNode>();
        expression->arguments.push_back(std::move($2));
        $$ = std::move(expression);
    }
    | ExpressionMethodCallArgs T_COMMA Expression {
        auto expression = std::make_unique<ExpressionMethodCallNode>();
        expression->arguments.push_back(std::move($3));
        $$ = std::move(expression);
    }

Identifier
    : T_IDENTIFIER {
        $$ = std::make_unique<IdentifierNode>();
        $$->name = $1;
    }
%%

void BisonParser::Parser::error (const std::string& m) {
    std::cout << "Parser error: " << m << std::endl;
}
