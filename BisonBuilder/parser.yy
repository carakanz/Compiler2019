%require "3.4.2"
%language "c++"

%%

result:
  list  { std::cout << $1 << '\n'; }
;


%type <std::vector<std::string>> list;

list:
  %empty     { /* Generates an empty string list */ }
| list item  { $$ = $1; $$.push_back ($2); }
;


%define api.value.type variant



%code
{
  // Print a list of strings.
  auto
  operator<< (std::ostream& o, const std::vector<std::string>& ss)
    -> std::ostream&
  {
    o << '{';
    const char *sep = "";

    for (const auto& s: ss)
      {
        o << sep << s;
        sep = ", ";
      }

    return o << '}';
  }
}

%type <std::string> item;
%token <std::string> TEXT;
%token <int> NUMBER;

item:
  TEXT
| NUMBER  { $$ = std::to_string ($1); }
;

