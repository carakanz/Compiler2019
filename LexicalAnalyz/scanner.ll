%{
    #include <LexicalAnalyz.h>
%}
%option noyywrap
%option c++
%option yyclass="LexicalAnalyz"

SPACE        [ \t\r\f\v]+;
END_OF_LINE  (\n)+
DIGIT        [0-9]
ALPHA        [A-Za-z]
INT_VALUE    {DIGIT}+
REAL_VALUE   ({DIGIT}+"."{DIGIT}*)|({DIGIT}*"."{DIGIT}+)
STRING_VALUE "\""[^"\""]*"\""
CHAR_VALUE   "'"[^"'"]"'"
ID           ({ALPHA}|_)({ALPHA}|_|{DIGIT})*
%%

"//"[^\n]* { return Process(Token::T_COMMENT); }
{SPACE}    { Space(); }
" "    { Space(); }
"\t"    { Space(); }
{END_OF_LINE} { EndOfLine(); }

"class"    { return Process(Token::T_CLASS); }
"this"     { return Process(Token::T_THIS); }
"("        { return Process(Token::T_LEFT_BRACKET); }
")"        { return Process(Token::T_RIGHT_BRACKET); }
"{"        { return Process(Token::T_LEFT_BRACE); }
"}"        { return Process(Token::T_RIGHT_BRACE); }
"["        { return Process(Token::T_LEFT_SQUARE_BRACKET); }
"]"        { return Process(Token::T_RIGHT_SQUARE_BRACKET); }
"public"   { return Process(Token::T_PUBLIC_MODIFIER); }
"private"  { return Process(Token::T_PRIVATE_MODIFIER); }
"static"   { return Process(Token::T_STATIC_MODIFIER); }
"return"   { return Process(Token::T_RETURN); }
"int"|"boolean"|"String"|"void" { return Process(Token::T_STANDARD_TYPE); }
"new"      { return Process(Token::T_NEW); }
"while"    { return Process(Token::T_WHILE); }
"if"       { return Process(Token::T_IF); }
"else"     { return Process(Token::T_ELSE); }
"System.out.println" { return Process(Token::T_PRINT_LN); }
"true"|"false" { return Process(Token::T_BOOL_VALUE); }
{INT_VALUE}  { return Process(Token::T_INT_VALUE); }
{REAL_VALUE}   { return Process(Token::T_REAL_VALUE); }
{CHAR_VALUE}   { return Process(Token::T_CHAR_VALUE); }
"."{ID}    { return Process(Token::T_METHOD); }
{ID}       { return Process(Token::T_IDENTIFIER); }
";"        { return Process(Token::T_SEMICOLON); }
","        { return Process(Token::T_COMMA); }
"="        { return Process(Token::T_ASSIGN_OPERATION); }
"&&"|"||"  { return Process(Token::T_BOOL_OPERATION); }
"!"   { return Process(Token::T_NOT_OPERATION); }
"+"|"-"|"*"|"/" { return Process(Token::T_ARITHMETIC_OPERATION); }
"<"|">"|"=="|"<="|">="|"!=" { return Process(Token::T_COMPARE_OPERATION); }

<<EOF>>    { return Process(Token::T_EOF); }
.          { return Process(Token::T_UNKNOWN); }
%%


