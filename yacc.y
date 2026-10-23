%{
void yyerror (char *s);
int yylex(void);
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
extern int yylineno;
/* Simplified symbol table (variable-only) is implemented below */
/* Simplified symbol table: only variables (identifiers) stored */
typedef enum {T_UNKNOWN, T_INT, T_FLOAT, T_BOOL} TypeKind;
typedef struct VarSym {
  char *name;
  double value;
  TypeKind type;
  int is_const; /* 1 if constant */
  int has_value; /* 1 if initialized */
  struct VarSym *next;
} VarSym;

static VarSym *varsym_head = NULL;

void symtab_init(void) { varsym_head = NULL; }

static VarSym *varsym_lookup(const char *name) {
  VarSym *p = varsym_head;
  while (p) {
    if (strcmp(p->name, name) == 0) return p;
    p = p->next;
  }
  return NULL;
}

/* insert variable; return 1 if inserted, 0 if already exists */
int symtab_insert_var(const char *name, TypeKind type, int is_const, double value, int has_value) {
  if (varsym_lookup(name)) return 0;
  VarSym *s = (VarSym*)malloc(sizeof(VarSym));
  s->name = strdup(name);
  s->type = type;
  s->is_const = is_const;
  s->value = value;
  s->has_value = has_value;
  s->next = varsym_head;
  varsym_head = s;
  return 1;
}

/* set variable value; returns 1 on success, 0 on failure (const or missing) */
int symtab_set_value(const char *name, double value) {
  VarSym *s = varsym_lookup(name);
  if (!s) return 0;
  if (s->is_const) return 0;
  s->value = value;
  s->has_value = 1;
  return 1;
}

/* set variable as constant (called for CONST declarations) */
void symtab_mark_const(const char *name, double value) {
  VarSym *s = varsym_lookup(name);
  if (s) { s->is_const = 1; s->value = value; s->has_value = 1; }
}

void symtab_print(void) {
  VarSym *p;
  /* count entries */
  int total = 0;
  for (p = varsym_head; p; p = p->next) total++;
  if (total == 0) return;
  printf("\nSymbols table:\n\n");

  printf("%-4s %-20s %-10s %-10s %s\t\tEntity\n", "#","Name","Value","Type","Const");
  printf("%s\n","-----------------------------------------------------------------------");
  int idx = 1;
  for (p = varsym_head; p; p = p->next) {
    const char *t = "-";
    char value_str[64];
    if (p->type == T_INT) t = "int";
    else if (p->type == T_FLOAT) t = "float";
    else if (p->type == T_BOOL) t = "bool";

    if (!p->has_value) {
      snprintf(value_str, sizeof(value_str), "NaN");
    } else if (p->type == T_FLOAT) {
      snprintf(value_str, sizeof(value_str), "%.2f", p->value);
    } else if (p->type == T_INT) {
      snprintf(value_str, sizeof(value_str), "%.0f", p->value);
    } else if (p->type == T_BOOL) {
      snprintf(value_str, sizeof(value_str), "%s", (p->value != 0.0) ? "true" : "false");
    } else {
      snprintf(value_str, sizeof(value_str), "%-g", p->value);
    }

    printf("%-4d %-20s %-10s %-10s %s \t\t\tidentifier\n", idx, p->name, value_str, t, p->is_const ? "yes" : "no");
    idx++;
  }
}
/* current declaration type used by VarDecl actions */
static TypeKind current_decl_type = T_UNKNOWN;
/* whether current declaration is CONST */
static int current_decl_is_const = 0;
%}

%code requires {
typedef struct { double val; int etype; } ExprVal;
}

/* semantic value types */
%union {
  double num;
  ExprVal expr;
  char *id;
  int itype; /* for TypeKind values */
}

/* tokens */
%token <id> identifier
%token <num> int_number float_number bool_literal
%token begin end IF FOR CONST INT FLOAT BOOL ELSE
%token EQ NE LE GE LT GT ASSIGN SEMI COMMA LP RP LBRACE RBRACE PLUS MINUS MUL DIV

%type <itype> Type
%type <expr> Expression

%nonassoc LOWER_THAN_ELSE
%left PLUS MINUS
%left MUL DIV
%right ASSIGN



%%
code    :   
            Declaration
            begin    
            Program   
            end       
        ;     

Declaration :

            | Declaration DeclarationStatement   
            ;
          

DeclarationStatement:
      Type { current_decl_type = $1; current_decl_is_const = 0; } VarList SEMI { current_decl_type = T_UNKNOWN; current_decl_is_const = 0; }
    | CONST Type { current_decl_type = $2; current_decl_is_const = 1; } VarList SEMI { current_decl_type = T_UNKNOWN; current_decl_is_const = 0; }
    ;

Type:
      INT   { $$ = T_INT; }
    | FLOAT { $$ = T_FLOAT; }
    | BOOL  { $$ = T_BOOL; }
    ;


/* A VarDecl is an identifier optionally initialized with an expression */
VarDecl:
      identifier { if (!symtab_insert_var($1, current_decl_type, current_decl_is_const, 0, 0)) { fprintf(stderr, "line %d: double declaration of '%s'\n", yylineno, $1); } }
    | identifier ASSIGN Expression {
        /* type compatibility for initializer */
        int ok = 1;
        if ($3.etype == T_UNKNOWN) ok = 0;
        if (current_decl_type == T_INT && $3.etype == T_FLOAT) {
          fprintf(stderr, "line %d: cannot initialize int '%s' with float\n", yylineno, $1); ok = 0;
        }
        if (current_decl_type == T_BOOL && $3.etype != T_BOOL) {
          fprintf(stderr, "line %d: cannot initialize bool '%s' with non-bool\n", yylineno, $1); ok = 0;
        }
        if (ok) {
          if (!symtab_insert_var($1, current_decl_type, current_decl_is_const, $3.val, 1)) { fprintf(stderr, "line %d: double declaration of '%s'\n", yylineno, $1); }
        } else {
          if (!symtab_insert_var($1, current_decl_type, current_decl_is_const, 0, 0)) { fprintf(stderr, "line %d: double declaration of '%s'\n", yylineno, $1); }
        }
      }
    ;

VarList:
      VarDecl
    | VarList COMMA VarDecl
    ;


/* ConstList removed: use VarList with current_decl_is_const flag instead */

Program:
      /* empty */
    | Program Statement
    ;

Statement:
      MatchedStatement
    | UnmatchedStatement
    ;

CompoundStatement:
      LBRACE Program RBRACE
    ;

Affectation:
      identifier ASSIGN Expression { 
        VarSym *s = varsym_lookup($1);
        if (!s) {
          fprintf(stderr, "line %d: undeclared variable '%s'\n", yylineno, $1);
        } else if (s->is_const) {
          fprintf(stderr, "line %d: cannot assign to constant '%s'\n", yylineno, $1);
        } else {
          /* type compatibility checks */
          if (s->type == T_INT && $3.etype == T_FLOAT) {
            fprintf(stderr, "line %d: cannot assign float to int variable '%s'\n", yylineno, $1);
          } else if (s->type == T_BOOL && $3.etype != T_BOOL) {
            fprintf(stderr, "line %d: cannot assign non-bool to bool variable '%s'\n", yylineno, $1);
          } else {
            /* allow int->float (promotion) */
            s->value = $3.val;
            s->has_value = 1;
          }
        }
      }
    ;


Expression:
  int_number    { ExprVal e; e.val = $1; e.etype = T_INT; $$ = e; }
  | float_number  { ExprVal e; e.val = $1; e.etype = T_FLOAT; $$ = e; }
  | bool_literal  { ExprVal e; e.val = $1; e.etype = T_BOOL; $$ = e; }
  | identifier    { VarSym *s = varsym_lookup($1); ExprVal e; if (!s) { fprintf(stderr, "line %d: undeclared variable '%s'\n", yylineno, $1); e.val = 0; e.etype = T_UNKNOWN; } else { if (!s->has_value) { fprintf(stderr, "line %d: variable '%s' used before initialization\n", yylineno, $1); } e.val = s->value; e.etype = s->type; } $$ = e; }
  | Expression PLUS Expression  {
      ExprVal e; if ($1.etype==T_BOOL || $3.etype==T_BOOL) { fprintf(stderr, "line %d: type error in '+' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; }
        else { e.val = $1.val + $3.val; e.etype = ($1.etype==T_FLOAT || $3.etype==T_FLOAT) ? T_FLOAT : T_INT; } $$ = e; }
  | Expression MINUS Expression { ExprVal e; if ($1.etype==T_BOOL || $3.etype==T_BOOL) { fprintf(stderr, "line %d: type error in '-' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else { e.val = $1.val - $3.val; e.etype = ($1.etype==T_FLOAT || $3.etype==T_FLOAT) ? T_FLOAT : T_INT; } $$ = e; }
  | Expression MUL Expression   { ExprVal e; if ($1.etype==T_BOOL || $3.etype==T_BOOL) { fprintf(stderr, "line %d: type error in '*' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else { e.val = $1.val * $3.val; e.etype = ($1.etype==T_FLOAT || $3.etype==T_FLOAT) ? T_FLOAT : T_INT; } $$ = e; }
  | Expression DIV Expression   { ExprVal e; if ($1.etype==T_BOOL || $3.etype==T_BOOL) { fprintf(stderr, "line %d: type error in '/' with bool\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else if ($3.val == 0) { fprintf(stderr, "line %d: division by zero\n", yylineno); e.val = 0; e.etype = T_UNKNOWN; } else { e.val = $1.val / $3.val; e.etype = T_FLOAT; } $$ = e; }
  | LP Expression RP            { $$ = $2; }
    ;

/* Eliminate dangling-else by splitting matched / unmatched statements */
MatchedStatement:
      IF LP Condition RP MatchedStatement ELSE MatchedStatement
    | ForStatement
    | CompoundStatement
    | Affectation SEMI
    | Expression SEMI
    ;

UnmatchedStatement:
      IF LP Condition RP Statement %prec LOWER_THAN_ELSE
    | IF LP Condition RP MatchedStatement ELSE UnmatchedStatement
    ;

Condition:
      Expression RelOp Expression
    ;

RelOp:
      LT | GT | EQ | NE | LE | GE
    ;


ForStatement:
      FOR LP Affectation SEMI Condition SEMI Affectation RP MatchedStatement
    ;





%%

int main(void){
  symtab_init();
  int r = yyparse ();
  symtab_print();
  return r;
}
void yyerror (char *s) { fprintf(stderr, "line %d: %s\n", yylineno, s); }

