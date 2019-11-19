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
    #include<Token.h>

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


%token <Token<void>> T_EOF 0
%token <Token<void>> T_CLASS
%token <Token<void>> T_EXTEND
%token <Token<void>> T_THIS
%token <Token<void>> T_LEFT_BRACKET
%token <Token<void>> T_RIGHT_BRACKET
%token <Token<void>> T_LEFT_BRACE
%token <Token<void>> T_RIGHT_BRACE
%token <Token<void>> T_LEFT_SQUARE_BRACKET
%token <Token<void>> T_RIGHT_SQUARE_BRACKET
%token <Token<DeclarationMethodNode::PrivacyModifier>> T_PRIVACY_MODIFIER
%token <Token<void>> T_STATIC_MODIFIER
%token <Token<void>> T_RETURN
%token <Token<void>> T_INT
%token <Token<void>> T_BOOLEAN
%token <Token<void>> T_STRING
%token <Token<void>> T_VOID
%token <Token<void>> T_NEW
%token <Token<void>> T_LENGTH
%token <Token<void>> T_WHILE
%token <Token<void>> T_IF
%token <Token<void>> T_ELSE
%token <Token<void>> T_PRINT_LN
%token <Token<bool>> T_BOOL_VALUE
%token <Token<int>> T_INT_VALUE
%token <Token<void>> T_DOT
%token <Token<std::string>> T_IDENTIFIER
%token <Token<void>> T_SEMICOLON
%token <Token<void>> T_COMMA
%token <Token<void>> T_ASSIGN_OPERATION
%token <Token<ExpressionBinaryOperationNode::BinaryOperationType>> T_MUL_OPERATION
%token <Token<ExpressionBinaryOperationNode::BinaryOperationType>> T_ADD_OPERATION
%token <Token<ExpressionBinaryOperationNode::BinaryOperationType>> T_COMPARE_OPERATION
%token <Token<ExpressionBinaryOperationNode::BinaryOperationType>> T_EQUIVALENT_OPERATION
%token <Token<ExpressionBinaryOperationNode::BinaryOperationType>> T_AND_OPERATION
%token <Token<ExpressionBinaryOperationNode::BinaryOperationType>> T_OR_OPERATION
%token <Token<void>> T_NOT_OPERATION
%token <Token<void>> T_UNKNOWN

%type Goal
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

%nonassoc T_IF
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
    : Goal DeclarationClass {
        scanner.root->items.push_back(std::move($2));
    }
    | DeclarationClass {
        scanner.root = std::make_unique<GoalNode>(std::move($1));
    }

DeclarationClassBegin
    : T_CLASS Identifier T_EXTEND Identifier T_LEFT_BRACE {
        $$ = std::make_unique<DeclarationClassNode>();
        $$->position = $1.position;
        $$->identifier = std::move($2);
        $$->base_class_identifier = std::move($4);
    }
    | T_CLASS Identifier T_LEFT_BRACE {
        $$ = std::make_unique<DeclarationClassNode>();
        $$->position = $1.position;
        $$->identifier = std::move($2);
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
        $$ = std::move($1);
    }

DeclarationVar
    : PairTypeIdentifier T_SEMICOLON {
        $$ = std::make_unique<DeclarationVarNode>();
        $$->position = $1->position;
        $$->var_type = std::move($1->var_type);
        $$->identifier = std::move($1->identifier);
    }

PairTypeIdentifier
    : Type Identifier {
        $$ = std::make_unique<PairTypeIdentifierNode>();
        $$->position = $1->position;
        $$->var_type = std::move($1);
        $$->identifier = std::move($2);
    }
    | Identifier Identifier {
        $$ = std::make_unique<PairTypeIdentifierNode>();
        $$->position = $1->position;
        $$->var_type = std::make_unique<TypeUserNode>(std::move($1));
        $$->identifier = std::move($2);
    }

DeclarationMethodBegin
    : T_PRIVACY_MODIFIER T_STATIC_MODIFIER Type Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->position = $1.position;
        $$->privacy_modifier = $1.info;
        $$->is_static = true;
        $$->return_type = std::move($3);
        $$->identifier = std::move($4);
    }
    | T_PRIVACY_MODIFIER Type Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->position = $1.position;
        $$->privacy_modifier = $1.info;
        $$->is_static = false;
        $$->return_type = std::move($2);
        $$->identifier = std::move($3);
    }
    | T_PRIVACY_MODIFIER T_STATIC_MODIFIER Identifier Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->position = $1.position;
        $$->privacy_modifier = $1.info;
        $$->is_static = true;
        $$->return_type = std::make_unique<TypeUserNode>(std::move($3));
        $$->identifier = std::move($4);
    }
    | T_PRIVACY_MODIFIER Identifier Identifier T_LEFT_BRACKET {
        $$ = std::make_unique<DeclarationMethodNode>();
        $$->position = $1.position;
        $$->privacy_modifier = $1.info;
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
        $$->position = $1.position;
    }
    | T_BOOLEAN {
        $$ = std::make_unique<TypeBooleanNode>();
        $$->position = $1.position;
    }
    | T_VOID {
        $$ = std::make_unique<TypeVoidNode>();
        $$->position = $1.position;
    }
    | T_STRING {
        $$ = std::make_unique<TypeStringNode>();
        $$->position = $1.position;
    }
    | Type T_LEFT_SQUARE_BRACKET T_RIGHT_SQUARE_BRACKET {
        auto position = $1->position;
        $$ = std::make_unique<TypeArrayNode>(std::move($1));
        $$->position = position;
    }
    | Identifier T_LEFT_SQUARE_BRACKET T_RIGHT_SQUARE_BRACKET {
        auto position = $1->position;
        auto type = std::make_unique<TypeArrayNode>(std::make_unique<TypeUserNode>(std::move($1)));
        type->position = type->type->position = position;
        $$ = std::move(type);
    }

OpenStatement
    : T_LEFT_BRACE Statement {
        $$ = std::make_unique<StatementListNode>(std::move($2));
        $$->position = $1.position;
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
        $$->position = $1.position;
    }
    | T_IF T_LEFT_BRACKET Expression T_RIGHT_BRACKET Statement T_ELSE Statement {
        auto statement = std::make_unique<StatementIfNode>();
        statement->conditional = std::move($3);
        statement->then_statement = std::move($5);
        statement->else_statement = std::move($7);
        $$ = std::move(statement);
        $$->position = $1.position;
    }
    | T_WHILE T_LEFT_BRACKET Expression T_RIGHT_BRACKET Statement {
        auto statement = std::make_unique<StatementWhileNode>();
        statement->conditional = std::move($3);
        statement->then_statement = std::move($5);
        $$ = std::move(statement);
        $$->position = $1.position;
    }
    | T_PRINT_LN T_LEFT_BRACKET Expression T_RIGHT_BRACKET T_SEMICOLON {
        auto statement = std::make_unique<StatementPrintlnNode>();
        statement->expression = std::move($3);
        $$ = std::move(statement);
        $$->position = $1.position;
    }
    | Identifier T_ASSIGN_OPERATION Expression T_SEMICOLON {
        auto statement = std::make_unique<StatementAssignNode>();
        statement->position = $1->position;
        statement->identifier = std::move($1);
        statement->expression = std::move($3);
        $$ = std::move(statement);
    }
    | Identifier T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET T_ASSIGN_OPERATION Expression T_SEMICOLON {
        auto statement = std::make_unique<StatementAssignArrayNode>();
        statement->position = $1->position;
        statement->identifier = std::move($1);
        statement->index = std::move($3);
        statement->expression = std::move($6);
        $$ = std::move(statement);
    }
    | T_RETURN Expression T_SEMICOLON {
        auto statement = std::make_unique<StatementReturnNode>();
        statement->expression = std::move($2);
        $$ = std::move(statement);
        $$->position = $1.position;
    }

Expression
    : Expression T_MUL_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->position = $1->position;
        expression->left = std::move($1);
        expression->operation_type = $2.info;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_ADD_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->position = $1->position;
        expression->left = std::move($1);
        expression->operation_type = $2.info;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_COMPARE_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->position = $1->position;
        expression->left = std::move($1);
        expression->operation_type = $2.info;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_EQUIVALENT_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->position = $1->position;
        expression->left = std::move($1);
        expression->operation_type = $2.info;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_AND_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->position = $1->position;
        expression->left = std::move($1);
        expression->operation_type = $2.info;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_OR_OPERATION Expression {
        auto expression = std::make_unique<ExpressionBinaryOperationNode>();
        expression->position = $1->position;
        expression->left = std::move($1);
        expression->operation_type = $2.info;
        expression->left = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET {
        auto expression = std::make_unique<ExpressionIndexNode>();
        expression->position = $1->position;
        expression->array = std::move($1);
        expression->index = std::move($3);
        $$ = std::move(expression);
    }
    | Expression T_LENGTH {
        auto expression = std::make_unique<ExpressionGetLengthNode>();
        expression->position = $1->position;
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
        expression->value = $1.info;
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_BOOL_VALUE {
        auto expression = std::make_unique<ExpressionIntegerLiteralNode>();
        expression->value = $1.info;
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_THIS {
        $$ = std::make_unique<ExpressionThisNode>();
        $$->position = $1.position;
    }
    | T_NEW Identifier T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET {
        auto expression = std::make_unique<ExpressionNewArrayNode>();
        auto user_type = std::make_unique<TypeUserNode>();
        user_type->identifier = std::move($2);
        expression->type = std::move(user_type);
        expression->size = std::move($4);
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_NEW Identifier T_LEFT_BRACKET T_RIGHT_BRACKET {
        auto expression = std::make_unique<ExpressionNewNode>();
        auto user_type = std::make_unique<TypeUserNode>();
        user_type->identifier = std::move($2);
        expression->type = std::move(user_type);
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_NEW Type T_LEFT_SQUARE_BRACKET Expression T_RIGHT_SQUARE_BRACKET {
        auto expression = std::make_unique<ExpressionNewArrayNode>();
        expression->type = std::move($2);
        expression->size = std::move($4);
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_NEW Type T_LEFT_BRACKET T_RIGHT_BRACKET {
        auto expression = std::make_unique<ExpressionNewNode>();
        expression->type = std::move($2);
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_NOT_OPERATION Expression {
        auto expression = std::make_unique<ExpressionNotOperatorNode>();
        expression->expression = std::move($2);
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | T_LEFT_BRACKET Expression T_RIGHT_BRACKET {
        auto expression = std::make_unique<ExpressionRoundBracketsNode>();
        expression->expression = std::move($2);
        $$ = std::move(expression);
        $$->position = $1.position;
    }
    | Identifier {
        auto expression = std::make_unique<ExpressionIdentifierNode>();
        expression->position = $1->position;
        expression->identifier = std::move($1);
        $$ = std::move(expression);
    }

ExpressionMethodCallBegin
    : Expression T_DOT Identifier T_LEFT_BRACKET {
        auto expression = std::make_unique<ExpressionMethodCallNode>();
        expression->position = $1->position;
        expression->object = std::move($1);
        expression->method = std::move($3);
        $$ = std::move(expression);
    }

ExpressionMethodCallArgs
    : ExpressionMethodCallBegin Expression {
        $$ = std::move($1);
        $$->arguments.push_back(std::move($2));
    }
    | ExpressionMethodCallArgs T_COMMA Expression {
        $$ = std::move($1);
        $$->arguments.push_back(std::move($3));
    }

Identifier
    : T_IDENTIFIER {
        $$ = std::make_unique<IdentifierNode>();
        $$->position = $1.position;
        $$->name = $1.info;
    }
%%

void BisonParser::Parser::error (const std::string& m) {
    std::cout << "Parser error: " << m << std::endl;
}
