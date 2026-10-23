%{
#define YY_NO_UNPUT
#include "yacc.tab.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/* prototypes to avoid implicit-declaration warnings */
int yylex(void);
void yyerror(char *s);
%}

%option yylineno
%x COMMENT


%%
"BEGIN"          { return begin; }
"END"            { return end; }
[I][F]           { return IF; }
[F][O][R]       { return FOR; }
[C][O][N][S][T] { return CONST; }
[I][N][T]       { return INT; }
[F][L][O][A][T] { return FLOAT; }
[B][O][O][L]   { return BOOL; }
[E][L][S][E]   { return ELSE; }


"true"              { yylval.num = 1.0; return bool_literal; }
"false"             { yylval.num = 0.0; return bool_literal; }

[A-Za-z_][A-Za-z0-9_]*   {
			int len = strlen(yytext);
			if (len > 10) {
				fprintf(stderr, "line %d: identifier too long '%s'\n", yylineno, yytext);
				exit(1);
			}
			if (yytext[len-1] == '_') {
				fprintf(stderr, "line %d: identifier must not end with '_' '%s'\n", yylineno, yytext);
				exit(1);
			}
			if (strstr(yytext, "__") != NULL) {
				fprintf(stderr, "line %d: identifier must not contain consecutive '_' '%s'\n", yylineno, yytext);
				exit(1);
			}
			yylval.id = strdup(yytext);
			return identifier;
}

"//".*            { /* single-line comment; newline handled by newline rule */ }
"/*"                   { BEGIN(COMMENT); }
<COMMENT>"*/"          { BEGIN(INITIAL); }

<COMMENT>.              { /* skip other comment chars */ }

[0-9]+\.[0-9]+      { double v = atof(yytext); yylval.num = v; return float_number; }
[0-9]+               { double v = atof(yytext); yylval.num = v; return int_number; }



"=="    { return EQ; }
"!="    { return NE; }
"<="    { return LE; }
">="    { return GE; }
"<"     { return LT; }
">"     { return GT; }

"="     { return ASSIGN; }
";"     { return SEMI; }
","     { return COMMA; }
"("     { return LP; }
")"     { return RP; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MUL; }
"/"     { return DIV; }




[ \t\n]         ;






.                { fprintf(stderr, "line %d: unexpected character '%s'\n", yylineno, yytext); yyerror("unexpected character");
                    				exit(1); }




%%

int yywrap(void){return 1;}
