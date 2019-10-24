%{
    #include <FlexAnalyzerBuilder.h>
%}
%option noyywrap
%option c++
%option yyclass="FlexAnalyzerBuilder"

SPACE        [ \t\r\f\v];
END_OF_LINE  (\n)
DIGIT        [0-9]
ALPHA        [A-Za-z]
INT_VALUE    {DIGIT}+
REAL_VALUE   ({DIGIT}+"."{DIGIT}*)|({DIGIT}*"."{DIGIT}+)
STRING_VALUE "\""[^"\""]*"\""
CHAR_VALUE   "'"[^"'"]"'"
ID           ({ALPHA}|_)({ALPHA}|_|{DIGIT})*
%%

"//"[^\n]* { return (Token::T_COMMENT); }
{SPACE}    { space(); }
" "    { space(); }
"\t"    { space(); }
{END_OF_LINE} { end_of_line(); }

"class"    { return Token::T_CLASS; }
"this"     { return Token::T_THIS; }
"("        { return Token::T_LEFT_BRACKET; }
")"        { return Token::T_RIGHT_BRACKET; }
"{"        { return Token::T_LEFT_BRACE; }
"}"        { return Token::T_RIGHT_BRACE; }
"["        { return Token::T_LEFT_SQUARE_BRACKET; }
"]"        { return Token::T_RIGHT_SQUARE_BRACKET; }
"public"   { return Token::T_PUBLIC_MODIFIER; }
"private"  { return Token::T_PRIVATE_MODIFIER; }
"static"   { return Token::T_STATIC_MODIFIER; }
"return"   { return Token::T_RETURN; }
"int"|"boolean"|"String"|"void" { return Token::T_STANDARD_TYPE; }
"new"      { return Token::T_NEW; }
"while"    { return Token::T_WHILE; }
"if"       { return Token::T_IF; }
"else"     { return Token::T_ELSE; }
"System.out.println" { return Token::T_PRINT_LN; }
"true"|"false" { return Token::T_BOOL_VALUE; }
{INT_VALUE}    { return Token::T_INT_VALUE; }
{REAL_VALUE}   { return Token::T_REAL_VALUE; }
{CHAR_VALUE}   { return Token::T_CHAR_VALUE; }
"."{ID}    { return Token::T_METHOD; }
{ID}       { return Token::T_IDENTIFIER; }
";"        { return Token::T_SEMICOLON; }
","        { return Token::T_COMMA; }
"="        { return Token::T_ASSIGN_OPERATION; }
"&&"|"||"  { return Token::T_BOOL_OPERATION; }
"!"        { return Token::T_NOT_OPERATION; }
"+"|"-"|"*"|"/" { return Token::T_ARITHMETIC_OPERATION; }
"<"|">"|"=="|"<="|">="|"!=" { return Token::T_COMPARE_OPERATION; }

<<EOF>>    { return Token::T_EOF; }
.          { return Token::T_UNKNOWN; }
%%


