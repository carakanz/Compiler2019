%{
    #include <Builder.h>
    using namespace BisonBuilder;
    #undef YY_DECL
    #define YY_DECL BisonParser::Parser::symbol_type BisonBuilder::Builder::get_next_token()

    #define yyterminate() BisonParser::Parser::make_T_EOF(Token<void>(new_position));
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Builder"

SPACE        [ \t\r\f\v]
END_OF_LINE  (\n)
DIGIT        [0-9]
ALPHA        [A-Za-z]
INT_VALUE    {DIGIT}+
REAL_VALUE   ({DIGIT}+"."{DIGIT}*)|({DIGIT}*"."{DIGIT}+)
STRING_VALUE "\""[^"\""]*"\""
CHAR_VALUE   "'"[^"'"]"'"
ID           ({ALPHA}|_)({ALPHA}|_|{DIGIT})*
%%

"//"[^\n]* { new_position.column += std::string(YYText()).size(); }
{SPACE}    { ++new_position.column; }
{END_OF_LINE} { ++new_position.line; new_position.column = 0; }

"class"    { return process(FlexToken::T_CLASS); }
"extends"  { return process(FlexToken::T_EXTEND); }
"this"     { return process(FlexToken::T_THIS); }
"("        { return process(FlexToken::T_LEFT_BRACKET); }
")"        { return process(FlexToken::T_RIGHT_BRACKET); }
"{"        { return process(FlexToken::T_LEFT_BRACE); }
"}"        { return process(FlexToken::T_RIGHT_BRACE); }
"["        { return process(FlexToken::T_LEFT_SQUARE_BRACKET); }
"]"        { return process(FlexToken::T_RIGHT_SQUARE_BRACKET); }
"public"|"private"   { return process(FlexToken::T_PRIVACY_MODIFIER); }
"static"   { return process(FlexToken::T_STATIC_MODIFIER); }
"return"   { return process(FlexToken::T_RETURN); }
"int"      { return process(FlexToken::T_INT); }
"boolean"  { return process(FlexToken::T_BOOLEAN); }
"String"   { return process(FlexToken::T_STRING); }
"void"     { return process(FlexToken::T_VOID); }
"new"      { return process(FlexToken::T_NEW); }
".length"  { return process(FlexToken::T_LENGTH); }
"while"    { return process(FlexToken::T_WHILE); }
"if"       { return process(FlexToken::T_IF); }
"else"     { return process(FlexToken::T_ELSE); }
"System.out.println" { return process(FlexToken::T_PRINT_LN); }
"true"|"false" { return process(FlexToken::T_BOOL_VALUE); }
{INT_VALUE}    { return process(FlexToken::T_INT_VALUE); }
"."        { return process(FlexToken::T_DOT); }
{ID}       { return process(FlexToken::T_IDENTIFIER); }
";"        { return process(FlexToken::T_SEMICOLON); }
","        { return process(FlexToken::T_COMMA); }
"="        { return process(FlexToken::T_ASSIGN_OPERATION); }
"*"|"/"|"%"  { return process(FlexToken::T_MUL_OPERATION); }
"+"|"-"  { return process(FlexToken::T_ADD_OPERATION); }
"<"|">"|"<="|">="  { return process(FlexToken::T_COMPARE_OPERATION); }
"=="|"!="  { return process(FlexToken::T_EQUIVALENT_OPERATION); }
"&&"       { return process(FlexToken::T_AND_OPERATION); }
"||"       { return process(FlexToken::T_OR_OPERATION); }
"!"        { return process(FlexToken::T_NOT_OPERATION); }

<<EOF>>    { return yyterminate(); }
.          { return process(FlexToken::T_UNKNOWN); }
%%