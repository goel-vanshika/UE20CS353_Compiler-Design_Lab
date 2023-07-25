%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    void yyerror(const char*);
    int yylex();
    extern int yylineno;
    extern char* yytext;
%}
%token T_INT T_CHAR T_DOUBLE T_WHILE T_INC T_DEC T_OROR T_ANDAND T_EQCOMP T_NOTEQUAL T_GREATEREQ T_LESSEREQ T_NUM T_ID T_FLOAT T_IF T_ELSE T_STRLITERAL T_DO T_INCLUDE T_HEADER T_MAIN T_FOR

%start START

%%
START : PROG {printf("Valid syntax\n"); YYACCEPT;}

PROG : T_INCLUDE '<' T_HEADER '>' PROG
       |MAIN PROG
       |DECLR ';' PROG
       | ASSGN ';' PROG
       | error ';' PROG
       |
       ;

DECLR : TYPE LISTVAR
        ;

LISTVAR : LISTVAR ',' T_ID
          | T_ID
          ;

TYPE : T_INT
       | T_FLOAT
       | T_DOUBLE 
       | T_CHAR
       ;

ASSGN : T_ID '=' EXPR
        ;
    
EXPR : EXPR REL_OP E
       | E
       ;

REL_OP : T_LESSEREQ
         | T_GREATEREQ
         | '<'
         | '>'
         | T_EQCOMP
         | T_NOTEQUAL
         ;

E : E '+' T
    | E '-' T
    | T
    ;

T : T '*' F
    | T '/' F
    | F
    ;

F : '(' EXPR ')'
     | T_ID
     | T_NUM
     ;
    
MAIN : TYPE T_MAIN '(' EMPTY_LISTVAR ')' '{' STMT '}' ;

EMPTY_LISTVAR : LISTVAR
                |
                ;

STMT : SINGLE_STMT STMT
       | BLOCK STMT
       ;

SINGLE_STMT : DECLR ';'
       | ASSGN ';'
       | T_IF COND STMT
       | T_IF COND STMT T_ELSE STMT 
       | WHILE_L
       | error ';'
       ;

BLOCK : '{' STMT '}';

WHILE_L : T_WHILE '(' STMT ')' WHILE_2

COND : EXPR
       | ASSGN 
       ;

WHILE_2 : '{' STMT '}'
           | 
           ;

%%

void yyerror (char const *s)
{
	printf("Error: %s, line number: %d, token: %s\n",s,yylineno+1,yytext);
}

int main()
{
	yyparse();
	return 0;
}
