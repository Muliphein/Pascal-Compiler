%{
#include<stdio.h>
#include<math.h>
#include<string>
extern FILE* yyin;
int yylex();
void yyerror(const char *);
using namespace std;
int yydebug = 1;
%}
%expect 1

%code requires{
#include"splast.h"
SPLAST::ProgramASTN* ASTRoot;
}

%locations

%union{
	char char_val;
	int int_val;
	double double_val;
	bool bool_val;
	const char* string_val;
	SPLVarType vartype;
	SPLStmtType stmttype;
	SPLAssignType assigntype;
	SPLProcType proctype;
	SPLExprOp exprop;
	SPLSExprOp sexprop;
	SPLTermOp termop;
	SPLFuncType functype;
	SPLFactorType factortype;
	SPLAST::ASTNode* astnode;
	SPLAST::ProgramASTN* programASTN;
	SPLAST::ProgramHeadASTN* programheadASTN;
	SPLAST::NameASTN* nameASTN;
	SPLAST::RoutineASTN* routineASTN;
	SPLAST::RoutineHeadASTN* routineheadASTN;
	SPLAST::RoutineBodyASTN* routinebodyASTN;
	SPLAST::ConstPartASTN* constpartASTN;
	SPLAST::TypePartASTN* typepartASTN;
	SPLAST::VarPartASTN* varpartASTN;
	SPLAST::RoutinePartASTN* routinepartASTN;
	SPLAST::ConstExprASTN* constexprASTN;
	SPLAST::ConstValueASTN* constvalueASTN;
	SPLAST::TypeDefASTN* typedefASTN;
	SPLAST::TypeDeclASTN* typedeclASTN;
	SPLAST::FieldListASTN* fieldlistASTN;
	SPLAST::FieldDeclASTN* fielddeclASTTN;
	SPLAST::NameListASTN* namelistASTN;
	SPLAST::VarDeclASTN* vardeclASTN;
	SPLAST::FuncDeclASTN* functdeclASTN;
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
%type<bool_val> const_bool_value
%type<char_val> C_VAL const_char_value
%type<double_val> D_VAL const_double_value
%type<string_val> NAME
%type<SPLVarType> SYS_TYPE
%type<programASTN> program
%type<programheadASTN> program_head
%type<nameASTN> ID
%type<routineASTN> routine sub_routine
%type<routineheadASTN> routine_head
%type<routinebodyASTN> routine_body
%type<constpartASTN> const_part const_expr_list
%type<constexprASTN> const_expr
%type<constvalueASTN> const_value
%type<typepartASTN> type_part type_decl_list
%type<typedefASTN> type_definition
%type<typedeclASTN> type_decl simple_type_decl array_type_decl record_type_decl
%%

program : program_head routine DOT { $$ = new ProgramASTN($1, $2); ASTRoot = $$;}
;

program_head : PROGRAM ID SEMI { $$ = new ProgamHeadASTN($2);}
;

ID : NAME { $$ = new NameASTN($1);}
;

routine : routine_head routine_body { $$ = new RoutineASTN($1, $2); }
;

sub_routine : routine_head routine_body { $$ = new RoutineASTN($1, $2); }
;

routine_head : const_part type_part var_part routine_part { $$ = new RoutineHeadASTN($1, $2, $3, $4); }
;

const_part : CONST const_expr_list { $$ = new ConstPartASTN($2); }
| { $$ = new ConstPartASTN(); }
;

const_expr_list : const_expr_list const_expr { $$ = new ConstPartASTN($1, $2); }
| const_expr { $$ = new ConstPartASTN($1); }
;

const_expr :  NAME EQUAL const_value SEMI { $$ = new ConstExprASTN($1, $3); }

const_value : const_int_value { $$ = new ConstValueASTN($1); }
| const_double_value { $$ = new ConstValueASTN($1); }
| const_char_value { $$ = new ConstValueASTN($1); }
| const_bool_value { $$ = new ConstValueASTN($1); }
;

const_int_value : I_VAL { $$ = $1; }
| MAXINT { $$ = INT_MAX; }
;

const_double_value : D_VAL { $$ = $1; }
;

const_char_value : C_VAL { $$ = $1; }
;

const_bool_value : TRUE { $$ = true; }
| FALSE { $$ = false; }
;

type_part : TYPE type_decl_list { $$ = new TypePartASTN($2); }
| { $$ = new TypePartASTN(); }
;

type_decl_list : type_decl_list type_definition { $$ = new TypePartASTN($1, $2); }
| type_definition { $$ = new TypePartASTN($1); }
;

type_definition : NAME EQUAL type_decl SEMI { $$ = new TypeDefASTN($1, $3); }
;

type_decl : simple_type_decl { $$ = new TypeDeclASTN($1); }
| array_type_decl { $$ = new TypeDeclASTN($1); }
| record_type_decl { $$ = new TypeDeclASTN($1); }
;

simple_type_decl : SYS_TYPE { $$ = new TypeDeclASTN($1); }
| NAME { $$ = new TypeDeclASTN($1); }
| LP name_list RP {}
| const_value DOTDOT const_value {}
| MINUS const_value DOTDOT const_value {}
| MINUS const_value DOTDOT MINUS const_value {}
| NAME DOTDOT NAME {}
;

SYS_TYPE : BOOLEAN { $$ = _BOOL; }
| CHAR { $$ = _CHAR; }
| INTEGER { $$ = _INT; }
| REAL { $$ = _DOUBLE; }
;

array_type_decl : ARRAY LB simple_type_decl RB OF type_decl {}
;

record_type_decl : RECORD field_decl_list END {}
;

field_decl_list : field_decl_list field_decl {}
| field_decl {}
;

field_decl : name_list COLON type_decl SEMI {}
;

name_list : name_list COMMA ID {}
| ID
;

var_part : VAR var_decl_list {}
| {}
;

var_decl_list : var_decl_list var_decl {}
| var_decl {}
;

var_decl : name_list COLON type_decl SEMI {}
;


routine_part : routine_part function_decl {}
| routine_part procedure_decl {}
| {/**/}
;

function_decl : FUNCTION NAME parameters COLON simple_type_decl SEMI sub_routine SEMI {}
;

procedure_decl : PROCEDURE NAME parameters SEMI sub_routine SEMI {}
;

parameters : LP para_decl_list RP {}
| {} 
;

para_decl_list : para_decl_list SEMI para_type_list {}
| para_type_list {//
}
;

para_type_list : VAR name_list COLON simple_type_decl {}
| name_list COLON simple_type_decl {}
;

routine_body : compound_stmt {}
;

compound_stmt : KEY_BEGIN stmt_list END {}
;

stmt_list : stmt_list stmt SEMI {}
| {}
;

stmt : I_VAL COLON non_label_stmt {}
| non_label_stmt {}
;

non_label_stmt : assign_stmt {}
| proc_stmt {}
| compound_stmt {}
| if_stmt {}
| repeat_stmt {}
| while_stmt {}
| for_stmt {}
| case_stmt {}
| goto_stmt {}
;

assign_stmt : ID ASSIGN expression {}
| ID LB expression RB ASSIGN expression {}
| ID DOT ID ASSIGN expression {}
;

proc_stmt : ID {}
| ID LP expression_list RP {}
| SYS_PROC LP expression_list RP {}
| READ LP factor RP {}
;

SYS_PROC : WRITE {}
| WRITELN {}
;

if_stmt : IF expression THEN stmt else_clause {}
;

else_clause : ELSE stmt {}
| {}
;

repeat_stmt : REPEAT stmt_list UNTIL expression {}
;

while_stmt : WHILE expression DO stmt {}
;

for_stmt : FOR ID ASSIGN expression direction expression DO stmt {}
;

direction : TO {}
| DOWNTO {}
;

case_stmt : CASE expression OF case_expr_list END {}
;

case_expr_list : case_expr_list case_expr {}
| case_expr {}
;

case_expr : const_value COLON stmt SEMI {}
| ID COLON stmt SEMI {}
;

goto_stmt : GOTO I_VAL {}
;

expression_list : expression_list COMMA expression {}
| expression {}
;

expression : expression GE expr {}
| expression GT expr {}
| expression LE expr {}
| expression LT expr {}
| expression EQUAL expr {}
| expression UNEQUAL expr {}
| expr {}
;

expr : expr PLUS term {}
| expr MINUS term {}
| expr OR term {}
| term {}
;

term : term MUL factor {}
| term DIV factor {}
| term KEY_DIV factor {}
| term MOD factor {}
| term AND factor {}
| factor {}
;

factor : NAME {}
| NAME LP expression_list RP {}
| SYS_FUNCT {}
| SYS_FUNCT LP expression_list RP {}
| const_value {}
| LP expression RP {}
| NOT factor {}
| MINUS factor {}
| ID LB expression RB {}
| ID DOT ID {}
;

SYS_FUNCT : ABS {}
| CHR {}
| ODD {}
| ORD {}
| PRED {}
| SQR {}
| SQRT {}
| SUCC {}
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
	return 0;
}
void yyerror(const char * msg)
{
	printf("Error encountered: %s \n", msg);
}