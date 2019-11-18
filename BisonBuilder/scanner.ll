%{
    #include <Builder.h>
    using namespace BisonBuilder;
    #undef YY_DECL
    #define YY_DECL BisonParser::Parser::symbol_type BisonBuilder::Builder::get_next_token()

    #define yyterminate() BisonParser::Parser::make_T_EOF();
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

"class"    { return process(Token::T_CLASS); }
"extends"  { return process(Token::T_EXTEND); }
"this"     { return process(Token::T_THIS); }
"("        { return process(Token::T_LEFT_BRACKET); }
")"        { return process(Token::T_RIGHT_BRACKET); }
"{"        { return process(Token::T_LEFT_BRACE); }
"}"        { return process(Token::T_RIGHT_BRACE); }
"["        { return process(Token::T_LEFT_SQUARE_BRACKET); }
"]"        { return process(Token::T_RIGHT_SQUARE_BRACKET); }
"public"|"private"   { return process(Token::T_PRIVACY_MODIFIER); }
"static"   { return process(Token::T_STATIC_MODIFIER); }
"return"   { return process(Token::T_RETURN); }
"int"      { return process(Token::T_INT); }
"boolean"  { return process(Token::T_BOOLEAN); }
"String"   { return process(Token::T_STRING); }
"void"     { return process(Token::T_VOID); }
"new"      { return process(Token::T_NEW); }
".length"  { return process(Token::T_LENGTH); }
"while"    { return process(Token::T_WHILE); }
"if"       { return process(Token::T_IF); }
"else"     { return process(Token::T_ELSE); }
"System.out.println" { return process(Token::T_PRINT_LN); }
"true"|"false" { return process(Token::T_BOOL_VALUE); }
{INT_VALUE}    { return process(Token::T_INT_VALUE); }
"."        { return process(Token::T_DOT); }
{ID}       { return process(Token::T_IDENTIFIER); }
";"        { return process(Token::T_SEMICOLON); }
","        { return process(Token::T_COMMA); }
"="        { return process(Token::T_ASSIGN_OPERATION); }
"*"|"/"|"%"  { return process(Token::T_MUL_OPERATION); }
"+"|"-"  { return process(Token::T_ADD_OPERATION); }
"<"|">"|"<="|">="  { return process(Token::T_COMPARE_OPERATION); }
"=="|"!="  { return process(Token::T_EQUIVALENT_OPERATION); }
"&&"       { return process(Token::T_AND_OPERATION); }
"||"       { return process(Token::T_OR_OPERATION); }
"!"        { return process(Token::T_NOT_OPERATION); }

<<EOF>>    { return yyterminate(); }
.          { return process(Token::T_UNKNOWN); }
%%