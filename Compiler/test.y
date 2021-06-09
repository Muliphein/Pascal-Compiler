%{
#include<stdio.h>
#include<math.h>
#include<string>
#include "GraphGenerator.h"
#include "ASTTransfer.h"
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
%token TOKEN_AND TOKEN_ARRAY TOKEN_KEY_BEGIN TOKEN_CASE TOKEN_CONST TOKEN_KEY_DIV TOKEN_DO TOKEN_DOWNTO TOKEN_ELSE TOKEN_END TOKEN_FOR TOKEN_FUNCTION TOKEN_GOTO TOKEN_IF TOKEN_MOD TOKEN_NOT TOKEN_OF TOKEN_OR
%token TOKEN_PACKED TOKEN_PROCEDURE TOKEN_PROGRAM TOKEN_RECORD TOKEN_REPEAT TOKEN_THEN TOKEN_TO TOKEN_TYPE TOKEN_UNTIL TOKEN_VAR TOKEN_WHILE TOKEN_FALSE TOKEN_MAXINT TOKEN_TRUE
%token TOKEN_ABS TOKEN_CHR TOKEN_ODD TOKEN_ORD TOKEN_PRED TOKEN_SQR TOKEN_SQRT TOKEN_SUCC TOKEN_WRITE TOKEN_WRITELN TOKEN_BOOLEAN TOKEN_CHAR TOKEN_INTEGER TOKEN_REAL TOKEN_READ 
%token TOKEN_LP TOKEN_RP TOKEN_LB TOKEN_RB TOKEN_DOTDOT TOKEN_DOT TOKEN_COMMA TOKEN_MUL TOKEN_DIV TOKEN_UNEQUAL TOKEN_PLUS TOKEN_MINUS TOKEN_GE TOKEN_GT TOKEN_LE TOKEN_LT TOKEN_EQUAL TOKEN_ASSIGN TOKEN_SEMI TOKEN_COLON
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

program : program_head routine TOKEN_DOT { $$ = new SPLAST::ProgramASTN($1, $2); ASTRoot = $$;}
;

program_head : TOKEN_PROGRAM ID TOKEN_SEMI { $$ = new SPLAST::ProgramHeadASTN($2);}
;

ID : NAME { $$ = new SPLAST::NameASTN($1);}
;

routine : routine_head routine_body { $$ = new SPLAST::RoutineASTN($1, $2); }
;

sub_routine : routine_head routine_body { $$ = new SPLAST::RoutineASTN($1, $2); }
;

routine_head : const_part type_part var_part routine_part { $$ = new SPLAST::RoutineHeadASTN($1, $2, $3, $4); }
;

const_part : TOKEN_CONST const_expr_list { $$ = new SPLAST::ConstPartASTN($2); }
| { $$ = new SPLAST::ConstPartASTN(); }
;

const_expr_list : const_expr_list const_expr { $$ = new SPLAST::ConstPartASTN($1, $2); }
| const_expr { $$ = new SPLAST::ConstPartASTN($1); }
;

const_expr :  NAME TOKEN_EQUAL const_value TOKEN_SEMI { $$ = new SPLAST::ConstExprASTN($1, $3); }

const_value : const_int_value { $$ = new SPLAST::ConstValueASTN($1); }
| const_double_value { $$ = new SPLAST::ConstValueASTN($1); }
| const_char_value { $$ = new SPLAST::ConstValueASTN($1); }
| const_bool_value { $$ = new SPLAST::ConstValueASTN($1); }
;

const_int_value : I_VAL { $$ = $1; }
| TOKEN_MAXINT { $$ = INT_MAX; }
;

const_double_value : D_VAL { $$ = $1; }
;

const_char_value : C_VAL { $$ = $1; }
;

const_bool_value : TOKEN_TRUE { $$ = true; }
| TOKEN_FALSE { $$ = false; }
;

type_part : TOKEN_TYPE type_decl_list { $$ = new SPLAST::TypePartASTN($2); }
| { $$ = new SPLAST::TypePartASTN(); }
;

type_decl_list : type_decl_list type_definition { $$ = new SPLAST::TypePartASTN($1, $2); }
| type_definition { $$ = new SPLAST::TypePartASTN($1); }
;

type_definition : NAME TOKEN_EQUAL type_decl TOKEN_SEMI { $$ = new SPLAST::TypeDefASTN($1, $3); }
;

type_decl : simple_type_decl { $$ = new SPLAST::TypeDeclASTN($1); }
| array_type_decl { $$ = new SPLAST::TypeDeclASTN($1); }
| record_type_decl { $$ = new SPLAST::TypeDeclASTN($1); }
;

simple_type_decl : SYS_TYPE { $$ = new SPLAST::TypeDeclASTN($1); }
| NAME { $$ = new SPLAST::TypeDeclASTN($1); }
| TOKEN_LP name_list TOKEN_RP { $$ = new SPLAST::TypeDeclASTN($2); }
| const_value TOKEN_DOTDOT const_value { $$ = new SPLAST::TypeDeclASTN($1, $3); }
| TOKEN_MINUS const_value TOKEN_DOTDOT const_value { $$ = new SPLAST::TypeDeclASTN($2->Minus(), $4); delete $2; }
| TOKEN_MINUS const_value TOKEN_DOTDOT TOKEN_MINUS const_value { $$ = new SPLAST::TypeDeclASTN($2->Minus(), $5->Minus()); delete $2; delete $5;}
| NAME TOKEN_DOTDOT NAME { $$ = new SPLAST::TypeDeclASTN($1, $3);}
;

SYS_TYPE : TOKEN_BOOLEAN { $$ = _BOOL; }
| TOKEN_CHAR { $$ = _CHAR; }
| TOKEN_INTEGER { $$ = _INT; }
| TOKEN_REAL { $$ = _DOUBLE; }
;

array_type_decl : TOKEN_ARRAY TOKEN_LB simple_type_decl TOKEN_RB TOKEN_OF type_decl { $$ = new SPLAST::TypeDeclASTN($3, $6); }
;

record_type_decl : TOKEN_RECORD field_decl_list TOKEN_END { $$ = new SPLAST::TypeDeclASTN($2); }
;

field_decl_list : field_decl_list field_decl { $$ = new SPLAST::FieldListASTN($1, $2); }
| field_decl { $$ = new SPLAST::FieldListASTN($1); }
;

field_decl : name_list TOKEN_COLON type_decl TOKEN_SEMI { $$ = new SPLAST::FieldDeclASTN($1, $3); }
;

name_list : name_list TOKEN_COMMA ID { $$ = new SPLAST::NameListASTN($1, $3); }
| ID { $$ = new SPLAST::NameListASTN($1); }
;

var_part : TOKEN_VAR var_decl_list { $$ = new SPLAST::VarPartASTN($2); }
| { $$ = new SPLAST::VarPartASTN(); }
;

var_decl_list : var_decl_list var_decl { $$ = new SPLAST::VarPartASTN($1, $2); }
| var_decl { $$ = new SPLAST::VarPartASTN($1); }
;

var_decl : name_list TOKEN_COLON type_decl TOKEN_SEMI { $$ = new SPLAST::VarDeclASTN($1, $3); }
;

routine_part : routine_part function_decl { $$ = new SPLAST::RoutinePartASTN($1, $2); }
| routine_part procedure_decl { $$ = new SPLAST::RoutinePartASTN($1, $2); }
| { $$ = new SPLAST::RoutinePartASTN(); }
;

function_decl :TOKEN_FUNCTION NAME parameters TOKEN_COLON simple_type_decl TOKEN_SEMI sub_routine TOKEN_SEMI { $$ = new SPLAST::FuncDeclASTN($2, $3, $5, $7); }
;

procedure_decl : TOKEN_PROCEDURE NAME parameters TOKEN_SEMI sub_routine TOKEN_SEMI { $$ = new SPLAST::ProcDeclASTN($2, $3, $5); }
;

parameters : TOKEN_LP para_decl_list TOKEN_RP { $$ = new SPLAST::ParaASTN($2); }
| { $$ = new SPLAST::ParaASTN(); } 
;

para_decl_list : para_decl_list TOKEN_SEMI para_type_list { $$ = new SPLAST::ParaASTN($1, $3); }
| para_type_list { $$ = new SPLAST::ParaASTN($1); }
;

para_type_list : TOKEN_VAR name_list TOKEN_COLON simple_type_decl { $$ = new SPLAST::ParaTypeListASTN($2, $4, true); }
| name_list TOKEN_COLON simple_type_decl { $$ = new SPLAST::ParaTypeListASTN($1, $3, false); }
;

routine_body : compound_stmt { $$ = new SPLAST::StmtListASTN($1); }
;

compound_stmt : TOKEN_KEY_BEGIN stmt_list TOKEN_END { $$ = new SPLAST::StmtListASTN($2); }
;

stmt_list : stmt_list stmt TOKEN_SEMI { $$ = new SPLAST::StmtListASTN($1, $2); }
| { $$ = new SPLAST::StmtListASTN(); }
;

stmt : I_VAL TOKEN_COLON non_label_stmt { $$ = new SPLAST::StmtASTN($3, $1);}
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

assign_stmt : ID TOKEN_ASSIGN expression { $$ = new SPLAST::AssignStmtASTN($1, $3); }
| ID TOKEN_LB expression TOKEN_RB TOKEN_ASSIGN expression { $$ = new SPLAST::AssignStmtASTN($1, $3, $6); }
| ID TOKEN_DOT ID TOKEN_ASSIGN expression { $$ = new SPLAST::AssignStmtASTN($1, $3, $5); }
;

proc_stmt : ID { $$ = new SPLAST::ProcStmtASTN($1); }
| ID TOKEN_LP expression_list TOKEN_RP { $$ = new SPLAST::ProcStmtASTN($1, $3); }
| SYS_PROC TOKEN_LP expression_list TOKEN_RP { $$ = new SPLAST::ProcStmtASTN($1, $3); }
| TOKEN_READ TOKEN_LP factor TOKEN_RP { $$ = new SPLAST::ProcStmtASTN($3); }
;

SYS_PROC : TOKEN_WRITE { $$ = _WRITE; }
| TOKEN_WRITELN { $$ = _WRITELN; }
;

if_stmt : TOKEN_IF expression TOKEN_THEN stmt else_clause { $$ = new SPLAST::IfStmtASTN($2, $4, $5); }
;

else_clause : TOKEN_ELSE stmt { $$ = new SPLAST::ElseASTN($2); }
| { $$ = new SPLAST::ElseASTN(); }
;

repeat_stmt : TOKEN_REPEAT stmt_list TOKEN_UNTIL expression { $$ = new SPLAST::RepeatStmtASTN($2, $4); }
;

while_stmt : TOKEN_WHILE expression TOKEN_DO stmt { $$ = new SPLAST::WhileStmtASTN($2, $4); }
;

for_stmt : TOKEN_FOR ID TOKEN_ASSIGN expression direction expression TOKEN_DO stmt { $$ = new SPLAST::ForStmtASTN($2, $4, $6, $8, $5);}
;

direction : TOKEN_TO { $$ = POS; }
| TOKEN_DOWNTO { $$ = NEG; }
;

case_stmt : TOKEN_CASE expression TOKEN_OF case_expr_list TOKEN_END { $$ = new SPLAST::CaseStmtASTN($2, $4); }
;

case_expr_list : case_expr_list case_expr { $$ = new SPLAST::CaseStmtASTN($1, $2); }
| case_expr { $$ = new SPLAST::CaseStmtASTN($1); }
;

case_expr : const_value TOKEN_COLON stmt TOKEN_SEMI { $$ = new SPLAST::CaseExprASTN($1, $3); }
| ID TOKEN_COLON stmt TOKEN_SEMI { $$ = new SPLAST::CaseExprASTN($1, $3); }
;

goto_stmt : TOKEN_GOTO I_VAL { $$ = new SPLAST::GotoStmtASTN($2); }
;

expression_list : expression_list TOKEN_COMMA expression { $$ = new SPLAST::ExprListASTN($1, $3); }
| expression { $$ = new SPLAST::ExprListASTN($1); }
;

expression : expression TOKEN_GE expr { $$ = new SPLAST::ExprASTN($1, _GE, $3); }
| expression TOKEN_GT expr { $$ = new SPLAST::ExprASTN($1, _GT, $3); }
| expression TOKEN_LE expr { $$ = new SPLAST::ExprASTN($1, _LE, $3); }
| expression TOKEN_LT expr { $$ = new SPLAST::ExprASTN($1, _LT, $3); }
| expression TOKEN_EQUAL expr { $$ = new SPLAST::ExprASTN($1, _EQUAL, $3); }
| expression TOKEN_UNEQUAL expr { $$ = new SPLAST::ExprASTN($1, _UNEQUAL, $3); }
| expr { $$ = new SPLAST::ExprASTN($1); }
;

expr : expr TOKEN_PLUS term { $$ = new SPLAST::SExprASTN($1, _PLUS, $3); }
| expr TOKEN_MINUS term { $$ = new SPLAST::SExprASTN($1, _MINUS, $3); }
| expr TOKEN_OR term { $$ = new SPLAST::SExprASTN($1, _OR, $3); }
| term { $$ = new SPLAST::SExprASTN($1); }
;

term : term TOKEN_MUL factor { $$ = new SPLAST::TermASTN($1, _MUL, $3); }
| term TOKEN_DIV factor { $$ = new SPLAST::TermASTN($1, _DIV, $3); }
| term TOKEN_KEY_DIV factor { $$ = new SPLAST::TermASTN($1, _INTDIV, $3); }
| term TOKEN_MOD factor { $$ = new SPLAST::TermASTN($1, _MOD, $3); }
| term TOKEN_AND factor { $$ = new SPLAST::TermASTN($1, _AND, $3); }
| factor { $$ = new SPLAST::TermASTN($1); }
;

factor : NAME { $$ = new SPLAST::FactorASTN($1); }
| NAME TOKEN_LP expression_list TOKEN_RP { $$ = new SPLAST::FactorASTN($1, $3); }
| SYS_FUNCT { $$ = new SPLAST::FactorASTN($1); }
| SYS_FUNCT TOKEN_LP expression_list TOKEN_RP { $$ = new SPLAST::FactorASTN($1, $3); }
| const_value { $$ = new SPLAST::FactorASTN($1); }
| TOKEN_LP expression TOKEN_RP { $$ = new SPLAST::FactorASTN($2); }
| TOKEN_NOT factor { $$ = new SPLAST::FactorASTN($2, _NOT); }
| TOKEN_MINUS factor { $$ = new SPLAST::FactorASTN($2, _NEG); }
| ID TOKEN_LB expression TOKEN_RB { $$ = new SPLAST::FactorASTN($1, $3); }
| ID TOKEN_DOT ID { $$ = new SPLAST::FactorASTN($1, $3); }
;

SYS_FUNCT : TOKEN_ABS { $$ = _ABS; }
| TOKEN_CHR { $$ = _CHR; }
| TOKEN_ODD { $$ = _ODD; }
| TOKEN_ORD { $$ = _ORD; }
| TOKEN_PRED { $$ = _PRED; }
| TOKEN_SQR { $$ = _SQR; }
| TOKEN_SQRT { $$ = _SQRT; }
| TOKEN_SUCC { $$ = _SUCC; }
;


%%

extern void generator(ASTNodes::BasicNode* ASTRoot);

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
	ASTTransfer transfer(ASTRoot);
	std::cout << transfer.getProgramName() << std::endl;
	generator(std::dynamic_pointer_cast<ASTNodes::BasicNode>(transfer.getProgram()).get());
	return 0;
}
void yyerror(const char * msg)
{
	printf("Error encountered: %s \n", msg);
}