%{
#include<stdio.h>
#include<math.h>
#include<string>
#include"GraphGenerator.h"
extern FILE* yyin;
int yylex();
void yyerror(const char *);
using namespace std;
int yydebug = 1;
%}
%expect 1

%code requires{
#include"splast.h"
extern SPLAST::ProgramASTN* ASTRoot;
}

%union{
	char char_val;
	int int_val;
	double double_val;
	bool bool_val;
	const char* string_val;
	SPLVarType vartype;
	SPLProcType proctype;
	SPLFuncType functype;
	SPLAST::ASTNode* astnode;
	SPLAST::ProgramASTN* programASTN;
	SPLAST::ProgramHeadASTN* programheadASTN;
	SPLAST::NameASTN* nameASTN;
	SPLAST::RoutineASTN* routineASTN;
	SPLAST::RoutineHeadASTN* routineheadASTN;
	SPLAST::ConstPartASTN* constpartASTN;
	SPLAST::TypePartASTN* typepartASTN;
	SPLAST::VarPartASTN* varpartASTN;
	SPLAST::RoutinePartASTN* routinepartASTN;
	SPLAST::ConstExprASTN* constexprASTN;
	SPLAST::ConstValueASTN* constvalueASTN;
	SPLAST::TypeDefASTN* typedefASTN;
	SPLAST::TypeDeclASTN* typedeclASTN;
	SPLAST::FieldListASTN* fieldlistASTN;
	SPLAST::FieldDeclASTN* fielddeclASTN;
	SPLAST::NameListASTN* namelistASTN;
	SPLAST::VarDeclASTN* vardeclASTN;
	SPLAST::FuncDeclASTN* funcdeclASTN;
	SPLAST::ProcDeclASTN* procdeclASTN;
	SPLAST::ParaASTN* paraASTN;
	SPLAST::ParaTypeListASTN* paratypelistASTN;
	SPLAST::StmtListASTN* stmtlistASTN;
	SPLAST::StmtASTN* stmtASTN;
	SPLAST::AssignStmtASTN* assignstmtASTN;
	SPLAST::ProcStmtASTN* procstmtASTN;
	SPLAST::IfStmtASTN* ifstmtASTN;
	SPLAST::RepeatStmtASTN* repeatstmtASTN;
	SPLAST::WhileStmtASTN* whilestmtASTN;
	SPLAST::ForStmtASTN* forstmtASTN;
	SPLAST::CaseStmtASTN* casestmtASTN;
	SPLAST::GotoStmtASTN* gotostmtASTN;
	SPLAST::ExprASTN* exprASTN;
	SPLAST::ExprListASTN* exprlistASTN;
	SPLAST::FactorASTN* factorASTN;
	SPLAST::ElseASTN* elseASTN;
	SPLAST::CaseExprASTN* caseexprASTN;
	SPLAST::SExprASTN* sexprASTN;
	SPLAST::TermASTN* termASTN;
}

%start program
%token AND ARRAY KEY_BEGIN CASE CONST KEY_DIV DO DOWNTO ELSE END FOR FUNCTION GOTO IF MOD NOT OF OR
%token PACKED PROCEDURE PROGRAM RECORD REPEAT THEN TO TYPE UNTIL VAR WHILE FALSE MAXINT TRUE
%token ABS CHR ODD ORD PRED SQR SQRT SUCC WRITE WRITELN BOOLEAN CHAR INTEGER REAL READ 
%token LP RP LB RB DOTDOT DOT COMMA MUL DIV UNEQUAL PLUS MINUS GE GT LE LT EQUAL ASSIGN SEMI COLON
%token D_VAL I_VAL C_VAL NAME
%type<int_val> I_VAL const_int_value
%type<bool_val> const_bool_value direction
%type<char_val> C_VAL const_char_value
%type<double_val> D_VAL const_double_value
%type<string_val> NAME
%type<vartype> SYS_TYPE
%type<proctype> SYS_PROC
%type<programASTN> program
%type<programheadASTN> program_head
%type<nameASTN> ID
%type<routineASTN> routine sub_routine
%type<routineheadASTN> routine_head
%type<constpartASTN> const_part const_expr_list
%type<constexprASTN> const_expr
%type<constvalueASTN> const_value
%type<typepartASTN> type_part type_decl_list
%type<typedefASTN> type_definition
%type<typedeclASTN> type_decl simple_type_decl array_type_decl record_type_decl
%type<fieldlistASTN> field_decl_list
%type<fielddeclASTN> field_decl
%type<namelistASTN> name_list
%type<varpartASTN> var_part var_decl_list
%type<vardeclASTN> var_decl
%type<routinepartASTN> routine_part
%type<funcdeclASTN> function_decl
%type<procdeclASTN> procedure_decl
%type<paraASTN> parameters para_decl_list
%type<paratypelistASTN> para_type_list
%type<stmtlistASTN> routine_body compound_stmt stmt_list
%type<stmtASTN> stmt non_label_stmt
%type<assignstmtASTN> assign_stmt
%type<procstmtASTN> proc_stmt
%type<ifstmtASTN> if_stmt
%type<elseASTN> else_clause
%type<repeatstmtASTN> repeat_stmt
%type<whilestmtASTN> while_stmt
%type<forstmtASTN> for_stmt
%type<casestmtASTN> case_stmt case_expr_list
%type<caseexprASTN> case_expr
%type<gotostmtASTN> goto_stmt
%type<exprlistASTN> expression_list
%type<exprASTN> expression
%type<sexprASTN> expr
%type<termASTN> term
%type<factorASTN> factor
%type<functype> SYS_FUNCT
%%

program : program_head routine DOT { $$ = new SPLAST::ProgramASTN($1, $2); ASTRoot = $$;}
;

program_head : PROGRAM ID SEMI { $$ = new SPLAST::ProgramHeadASTN($2);}
;

ID : NAME { $$ = new SPLAST::NameASTN($1);}
;

routine : routine_head routine_body { $$ = new SPLAST::RoutineASTN($1, $2); }
;

sub_routine : routine_head routine_body { $$ = new SPLAST::RoutineASTN($1, $2); }
;

routine_head : const_part type_part var_part routine_part { $$ = new SPLAST::RoutineHeadASTN($1, $2, $3, $4); }
;

const_part : CONST const_expr_list { $$ = new SPLAST::ConstPartASTN($2); }
| { $$ = new SPLAST::ConstPartASTN(); }
;

const_expr_list : const_expr_list const_expr { $$ = new SPLAST::ConstPartASTN($1, $2); }
| const_expr { $$ = new SPLAST::ConstPartASTN($1); }
;

const_expr :  NAME EQUAL const_value SEMI { $$ = new SPLAST::ConstExprASTN($1, $3); }

const_value : const_int_value { $$ = new SPLAST::ConstValueASTN($1); }
| const_double_value { $$ = new SPLAST::ConstValueASTN($1); }
| const_char_value { $$ = new SPLAST::ConstValueASTN($1); }
| const_bool_value { $$ = new SPLAST::ConstValueASTN($1); }
;

const_int_value : I_VAL { $$ = $1; }
| MAXINT { $$ = 32767; }
;

const_double_value : D_VAL { $$ = $1; }
;

const_char_value : C_VAL { $$ = $1; }
;

const_bool_value : TRUE { $$ = true; }
| FALSE { $$ = false; }
;

type_part : TYPE type_decl_list { $$ = new SPLAST::TypePartASTN($2); }
| { $$ = new SPLAST::TypePartASTN(); }
;

type_decl_list : type_decl_list type_definition { $$ = new SPLAST::TypePartASTN($1, $2); }
| type_definition { $$ = new SPLAST::TypePartASTN($1); }
;

type_definition : NAME EQUAL type_decl SEMI { $$ = new SPLAST::TypeDefASTN($1, $3); }
;

type_decl : simple_type_decl { $$ = new SPLAST::TypeDeclASTN($1); }
| array_type_decl { $$ = new SPLAST::TypeDeclASTN($1); }
| record_type_decl { $$ = new SPLAST::TypeDeclASTN($1); }
;

simple_type_decl : SYS_TYPE { $$ = new SPLAST::TypeDeclASTN($1); }
| NAME { $$ = new SPLAST::TypeDeclASTN($1); }
| LP name_list RP { $$ = new SPLAST::TypeDeclASTN($2); }
| const_value DOTDOT const_value { $$ = new SPLAST::TypeDeclASTN($1, $3); }
| MINUS const_value DOTDOT const_value { $$ = new SPLAST::TypeDeclASTN($2->Minus(), $4); delete $2; }
| MINUS const_value DOTDOT MINUS const_value { $$ = new SPLAST::TypeDeclASTN($2->Minus(), $5->Minus()); delete $2; delete $5;}
| NAME DOTDOT NAME { $$ = new SPLAST::TypeDeclASTN($1, $3);}
;

SYS_TYPE : BOOLEAN { $$ = _BOOL; }
| CHAR { $$ = _CHAR; }
| INTEGER { $$ = _INT; }
| REAL { $$ = _DOUBLE; }
;

array_type_decl : ARRAY LB simple_type_decl RB OF type_decl { $$ = new SPLAST::TypeDeclASTN($3, $6); }
;

record_type_decl : RECORD field_decl_list END { $$ = new SPLAST::TypeDeclASTN($2); }
;

field_decl_list : field_decl_list field_decl { $$ = new SPLAST::FieldListASTN($1, $2); }
| field_decl { $$ = new SPLAST::FieldListASTN($1); }
;

field_decl : name_list COLON type_decl SEMI { $$ = new SPLAST::FieldDeclASTN($1, $3); }
;

name_list : name_list COMMA ID { $$ = new SPLAST::NameListASTN($1, $3); }
| ID { $$ = new SPLAST::NameListASTN($1); }
;

var_part : VAR var_decl_list { $$ = new SPLAST::VarPartASTN($2); }
| { $$ = new SPLAST::VarPartASTN(); }
;

var_decl_list : var_decl_list var_decl { $$ = new SPLAST::VarPartASTN($1, $2); }
| var_decl { $$ = new SPLAST::VarPartASTN($1); }
;

var_decl : name_list COLON type_decl SEMI { $$ = new SPLAST::VarDeclASTN($1, $3); }
;

routine_part : routine_part function_decl { $$ = new SPLAST::RoutinePartASTN($1, $2); }
| routine_part procedure_decl { $$ = new SPLAST::RoutinePartASTN($1, $2); }
| { $$ = new SPLAST::RoutinePartASTN(); }
;

function_decl : FUNCTION NAME parameters COLON simple_type_decl SEMI sub_routine SEMI { $$ = new SPLAST::FuncDeclASTN($2, $3, $5, $7); }
;

procedure_decl : PROCEDURE NAME parameters SEMI sub_routine SEMI { $$ = new SPLAST::ProcDeclASTN($2, $3, $5); }
;

parameters : LP para_decl_list RP { $$ = new SPLAST::ParaASTN($2); }
| { $$ = new SPLAST::ParaASTN(); } 
;

para_decl_list : para_decl_list SEMI para_type_list { $$ = new SPLAST::ParaASTN($1, $3); }
| para_type_list { $$ = new SPLAST::ParaASTN($1); }
;

para_type_list : VAR name_list COLON simple_type_decl { $$ = new SPLAST::ParaTypeListASTN($2, $4, true); }
| name_list COLON simple_type_decl { $$ = new SPLAST::ParaTypeListASTN($1, $3, false); }
;

routine_body : compound_stmt { $$ = new SPLAST::StmtListASTN($1); }
;

compound_stmt : KEY_BEGIN stmt_list END { $$ = new SPLAST::StmtListASTN($2); }
;

stmt_list : stmt_list stmt SEMI { $$ = new SPLAST::StmtListASTN($1, $2); }
| { $$ = new SPLAST::StmtListASTN(); }
;

stmt : I_VAL COLON non_label_stmt { $$ = new SPLAST::StmtASTN($3, $1);}
| non_label_stmt { $$ = new SPLAST::StmtASTN($1); }
;

non_label_stmt : assign_stmt { $$ = new SPLAST::StmtASTN($1); }
| proc_stmt { $$ = new SPLAST::StmtASTN($1); }
| compound_stmt { $$ = new SPLAST::StmtASTN($1); }
| if_stmt { $$ = new SPLAST::StmtASTN($1); }
| repeat_stmt { $$ = new SPLAST::StmtASTN($1); }
| while_stmt { $$ = new SPLAST::StmtASTN($1); }
| for_stmt { $$ = new SPLAST::StmtASTN($1); }
| case_stmt { $$ = new SPLAST::StmtASTN($1); }
| goto_stmt { $$ = new SPLAST::StmtASTN($1); }
;

assign_stmt : ID ASSIGN expression { $$ = new SPLAST::AssignStmtASTN($1, $3); }
| ID LB expression RB ASSIGN expression { $$ = new SPLAST::AssignStmtASTN($1, $3, $6); }
| ID DOT ID ASSIGN expression { $$ = new SPLAST::AssignStmtASTN($1, $3, $5); }
;

proc_stmt : ID { $$ = new SPLAST::ProcStmtASTN($1); }
| ID LP expression_list RP { $$ = new SPLAST::ProcStmtASTN($1, $3); }
| SYS_PROC LP expression_list RP { $$ = new SPLAST::ProcStmtASTN($1, $3); }
| READ LP factor RP { $$ = new SPLAST::ProcStmtASTN($3); }
;

SYS_PROC : WRITE { $$ = _WRITE; }
| WRITELN { $$ = _WRITELN; }
;

if_stmt : IF expression THEN stmt else_clause { $$ = new SPLAST::IfStmtASTN($2, $4, $5); }
;

else_clause : ELSE stmt { $$ = new SPLAST::ElseASTN($2); }
| { $$ = new SPLAST::ElseASTN(); }
;

repeat_stmt : REPEAT stmt_list UNTIL expression { $$ = new SPLAST::RepeatStmtASTN($2, $4); }
;

while_stmt : WHILE expression DO stmt { $$ = new SPLAST::WhileStmtASTN($2, $4); }
;

for_stmt : FOR ID ASSIGN expression direction expression DO stmt { $$ = new SPLAST::ForStmtASTN($2, $4, $6, $8, $5);}
;

direction : TO { $$ = POS; }
| DOWNTO { $$ = NEG; }
;

case_stmt : CASE expression OF case_expr_list END { $$ = new SPLAST::CaseStmtASTN($2, $4); }
;

case_expr_list : case_expr_list case_expr { $$ = new SPLAST::CaseStmtASTN($1, $2); }
| case_expr { $$ = new SPLAST::CaseStmtASTN($1); }
;

case_expr : const_value COLON stmt SEMI { $$ = new SPLAST::CaseExprASTN($1, $3); }
| ID COLON stmt SEMI { $$ = new SPLAST::CaseExprASTN($1, $3); }
;

goto_stmt : GOTO I_VAL { $$ = new SPLAST::GotoStmtASTN($2); }
;

expression_list : expression_list COMMA expression { $$ = new SPLAST::ExprListASTN($1, $3); }
| expression { $$ = new SPLAST::ExprListASTN($1); }
;

expression : expression GE expr { $$ = new SPLAST::ExprASTN($1, _GE, $3); }
| expression GT expr { $$ = new SPLAST::ExprASTN($1, _GT, $3); }
| expression LE expr { $$ = new SPLAST::ExprASTN($1, _LE, $3); }
| expression LT expr { $$ = new SPLAST::ExprASTN($1, _LT, $3); }
| expression EQUAL expr { $$ = new SPLAST::ExprASTN($1, _EQUAL, $3); }
| expression UNEQUAL expr { $$ = new SPLAST::ExprASTN($1, _UNEQUAL, $3); }
| expr { $$ = new SPLAST::ExprASTN($1); }
;

expr : expr PLUS term { $$ = new SPLAST::SExprASTN($1, _PLUS, $3); }
| expr MINUS term { $$ = new SPLAST::SExprASTN($1, _MINUS, $3); }
| expr OR term { $$ = new SPLAST::SExprASTN($1, _OR, $3); }
| term { $$ = new SPLAST::SExprASTN($1); }
;

term : term MUL factor { $$ = new SPLAST::TermASTN($1, _MUL, $3); }
| term DIV factor { $$ = new SPLAST::TermASTN($1, _DIV, $3); }
| term KEY_DIV factor { $$ = new SPLAST::TermASTN($1, _INTDIV, $3); }
| term MOD factor { $$ = new SPLAST::TermASTN($1, _MOD, $3); }
| term AND factor { $$ = new SPLAST::TermASTN($1, _AND, $3); }
| factor { $$ = new SPLAST::TermASTN($1); }
;

factor : NAME { $$ = new SPLAST::FactorASTN($1); }
| NAME LP expression_list RP { $$ = new SPLAST::FactorASTN($1, $3); }
| SYS_FUNCT { $$ = new SPLAST::FactorASTN($1); }
| SYS_FUNCT LP expression_list RP { $$ = new SPLAST::FactorASTN($1, $3); }
| const_value { $$ = new SPLAST::FactorASTN($1); }
| LP expression RP { $$ = new SPLAST::FactorASTN($2); }
| NOT factor { $$ = new SPLAST::FactorASTN($2, _NOT); }
| MINUS factor { $$ = new SPLAST::FactorASTN($2, _NEG); }
| ID LB expression RB { $$ = new SPLAST::FactorASTN($1, $3); }
| ID DOT ID { $$ = new SPLAST::FactorASTN($1, $3); }
;

SYS_FUNCT : ABS { $$ = _ABS; }
| CHR { $$ = _CHR; }
| ODD { $$ = _ODD; }
| ORD { $$ = _ORD; }
| PRED { $$ = _PRED; }
| SQR { $$ = _SQR; }
| SQRT { $$ = _SQRT; }
| SUCC { $$ = _SUCC; }
;


%%
int main(int argc, char **argv)
{
	if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }
	yyparse();
	printf("Successfully Parsed ! ASTRoot = %p\n", ASTRoot);
	Visitor visitor;
	visitor.VisitProgramASTN(ASTRoot);
	return 0;
}
void yyerror(const char * msg)
{
	printf("Error encountered: %s \n", msg);
}