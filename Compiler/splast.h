#include<string>
#include<memory>
#include<vector>
#define NOLABEL -1
#define POS true
#define NEG false
#define CASE_CONST true
#define CASE_VAR false

enum SPLVarType {
	_ERRORVAR,	// mark the error
	_USERTYPE,	// user-defined type or not calculated yet
	_BOOL,
	_CHAR,
	_INT,
	_DOUBLE,
	_ENUM,
	_RANGE,
	_ARRAY,
	_RECORD,
	_FUNCTION,
	_PROCEDURE
};

enum SPLStmtType {
	_ERRORSTMT, 
	_ASSIGN,
	_PROC,
	_COMPOUND,
	_IF,
	_REPEAT,
	_WHILE,
	_FOR,
	_CASE,
	_GOTO
};

enum SPLAssignType {
	_ERRORASSIGN,
	_VARIABLE,
	_ARRAYIDX,
	_CLASSMEM
};

enum SPLProcType {
	_ERRORPROC,
	_USERPROC,
	_WRITE,
	_WRITELN,
	_READ
};

enum SPLExprOp {
	_ERROREXPROP,
	_GE,
	_GT,
	_LE,
	_LT,
	_EQUAL,
	_UNEQUAL
};

enum SPLSExprOp {
	_ERRORSEXPROP,
	_PLUS,
	_MINUS,
	_OR
};

enum SPLTermOp {
	_ERRORTERMOP,
	_MUL,
	_DIV,
	_INTDIV,
	_MOD,
	_AND
};

enum SPLFuncType {
	_ERRORFUNC,
	_USERFUNC,
	_ABS,
	_CHR,
	_ODD,
	_ORD,
	_PRED,
	_SQR,
	_SQRT,
	_SUCC
};

enum SPLFactorType {
	_ERRORFACTOR,
	_USERVAL,
	_SYSFUNCT,
	_RET,
	_CONST,
	_EXPR,
	_NOT,
	_NEG,
	_INDEX,
	_MEMBER
};

namespace SPLAST 
{
	class ASTNode;
	class ProgramASTN;
	class ProgramHeadASTN;
	class NameASTN;
	class RoutineASTN;
	class RoutineHeadASTN;
	class RoutineBodyASTN;
	class ConstPartASTN;
	class TypePartASTN;
	class VarPartASTN;
	class RoutinePartASTN;
	class ConstExprASTN;
	class ConstValueASTN;
	class TypeDefASTN;
	class TypeDeclASTN;
	class FieldListASTN;
	class FieldDeclASTN;
	class NameListASTN;
	class VarDeclASTN;
	class FuncDeclASTN;
	class ProcDeclASTN;
	class ParaASTN;
	class ParaTypeListASTN;
	class StmtListASTN;
	class StmtASTN;
	class AssignStmtASTN;
	class ProcStmtASTN;
	class IfStmtASTN;
	class RepeatStmtASTN;
	class WhileStmtASTN;
	class ForStmtASTN;
	class CaseStmtASTN;
	class GotoStmtASTN;
	class ExprASTN;
	class ExprListASTN;
	class FactorASTN;
	class ElseASTN;
	class CaseExprASTN;
	class SExprASTN;
	class TermASTN;

	class ASTNode {
	};

	// program -> program_head routine (dot)
	class ProgramASTN : public ASTNode {
		ProgramHeadASTN* _programHeadASTN;
		RoutineASTN* _routineASTN;
	public:
		ProgramASTN(ProgramHeadASTN* programHeadASTN, RoutineASTN* routineASTN);
		ProgramHeadASTN* getProgramHeadASTN() const;
		RoutineASTN* getRoutineASTN() const;
	};

	// program_head -> (program) id (semi)
	class ProgramHeadASTN : public ASTNode {
		NameASTN* _nameASTN;
	public:
		ProgramHeadASTN(NameASTN* nameASTN);
		NameASTN* getNameASTN() const;
	};

	// id -> name
	class NameASTN : public ASTNode {
		std::string _name;
	public:
		NameASTN(std::string name);
		const std::string getName();
	};

	// routine -> routine_head routine_body
	// sub_routine -> routine_head routine_body
	class RoutineASTN : public ASTNode{
		RoutineHeadASTN* _routineHeadASTN;
		RoutineBodyASTN* _routineBodyASTN;
	public:
		RoutineASTN(RoutineHeadASTN* routineHeadASTN, RoutineBodyASTN* routineBodyASTN);
		RoutineHeadASTN* getRoutineHeadASTN() const;
		RoutineBodyASTN* getRoutineBodyASTN() const;
	};

	// routine_head -> const_part type_part var_part routine_part
	class RoutineHeadASTN : public ASTNode{
		ConstPartASTN* _constPartASTN;
		TypePartASTN* _typePartASTN;
		VarPartASTN* _varPartASTN;
		RoutinePartASTN* _routinePartASTN;
	public:
		RoutineHeadASTN(ConstPartASTN* constPartASTN, TypePartASTN* typePartASTN, VarPartASTN* varPartASTN, RoutinePartASTN* routinePartASTN);
		ConstPartASTN* getConstPartASTN() const;
		TypePartASTN* getTypePartASTN() const;
		VarPartASTN* getVarPartASTN() const;
		RoutinePartASTN* getRoutinePartASTN() const;
	};

	// const_part -> (CONST) const_expr_list | %empty
	// const_expr_list -> const expr*
	class ConstPartASTN : public ASTNode{
		std::vector<ConstExprASTN*> _constExprList;
	public:
		ConstPartASTN();
		ConstPartASTN(std::vector<ConstExprASTN*> constExprList);
		size_t getConstExprNum() const;
		std::vector<ConstExprASTN*> getConstExprList() const;
		ConstExprASTN* getConstExpr(size_t idx) const;
	};

	// const_expr -> NAME EQUAL const_value
	class ConstExprASTN : public ASTNode {
		NameASTN* _nameASTN;
		ConstValueASTN* _constValueASTN;
	public:
		ConstExprASTN(NameASTN* nameASTN, ConstValueASTN* constValueASTN);
		NameASTN* getNameASTN() const;
		ConstValueASTN* getConstValueASTN() const;
	};

	// const_value -> const_int_value(int)
	// const_value -> const_double_value(double)
	// const_value -> const_char_value(char)
	// const_value -> const_bool_value(bool)
	class ConstValueASTN : public ASTNode{
		const SPLVarType _type; // valid : bool | char | int | double
		const int _intValue = 0;
		const char _charValue = 0;
		const bool _boolValue = 0;
		const double _doubleValue = 0;
	public:
		ConstValueASTN(int value);
		ConstValueASTN(char value);
		ConstValueASTN(bool value);
		ConstValueASTN(double value);
		SPLVarType getType() const;
		void* getValue() const;
	};

	// type_part -> (TYPE) type_decl_list | %empty
	// type_decl_list -> {type_definition}*
	class TypePartASTN : public ASTNode {
		std::vector<TypeDefASTN*> _typeDefList;
	public:
		TypePartASTN();
		TypePartASTN(TypePartASTN* typePartASTN);
		TypePartASTN(TypeDefASTN* typeDefASTN);
		TypePartASTN(TypePartASTN* typePartASTN, TypeDefASTN* typeDefASTN);
		size_t getTypeDefNum() const;
		std::vector<TypeDefASTN*> getTypeDefList() const;
		TypeDefASTN* getTypeDef(size_t idx) const;
	};

	// type_definition -> NAME (EQUAL) type_decl SEMI
	class TypeDefASTN : public ASTNode {
		std::string _name;
		TypeDeclASTN* _typeDeclASTN;
	public:
		TypeDefASTN(std::string name, TypeDeclASTN* typeDeclASTN);
		std::string getName() const;
		TypeDeclASTN* getTypeDeclASTN() const;
	};

	// type_decl -> simple_type_decl | array_type_decl | record_type_decl
	// simple_type_decl ->  SYS_TYPE | NAME(_userType) | (LP) name_list (RP) (_enumType)
	// simple_type_decl -> (MINUS) const_value DOTDOT (MINUS) const_value (_rangeStartVal, _rangeEndVal)
	// simple_type_decl -> NAME (DOTDOT) NAME (_rangeStartName, _rangeEndName)
	// array_type_decl -> (ARRAY) (LB) simple_type_decl (RB) (OF) type_decl (_arrayRange, _arrayType)
	// reccord_type_decl -> (RECORD) field_decl_list (END) (_fieldListASTN)
	class TypeDeclASTN : public ASTNode {
		SPLVarType _type;
		std::string _userType;
		std::string _rangeStartName;
		std::string _rangeEndName;
		ConstValueASTN* _rangeStartVal;
		ConstValueASTN* _rangeEndVal;
		std::vector<std::string> _enumType;
		TypeDeclASTN* _arrayRange; // valid : _RANGE, _ENUM
		TypeDeclASTN* _arrayType;
		FieldListASTN* _fieldListASTN;
	public:
		TypeDeclASTN(TypeDeclASTN* typeDefASTN);
		TypeDeclASTN(SPLVarType type);
		TypeDeclASTN(std::string userType);
		TypeDeclASTN(std::vector<std::string> enumType);
		TypeDeclASTN(ConstValueASTN* rangeStartVal, ConstValueASTN* rangeEndVal);
		TypeDeclASTN(std::string rangeStartName, std::string rangeEndName);
		TypeDeclASTN(TypeDeclASTN* arrayRange, TypeDeclASTN* arrayType);
		TypeDeclASTN(FieldListASTN* fieldListASTN);
		SPLVarType getType() const;
		std::string getUserType() const;
		std::string getRangeStartName() const;
		std::string getRangeEndName() const;
		ConstValueASTN* getRangeStartVal() const;
		ConstValueASTN* getRangeEndVal() const;
		std::vector<std::string> getEnumType() const;
		TypeDeclASTN* getArrayRange() const;
		TypeDeclASTN* getArrayType() const;
		FieldListASTN* getFieldListASTN() const;
	};

	// field_decl_list -> field_decl+
	class FieldListASTN : public ASTNode {
		std::vector<FieldDeclASTN*> _fieldDeclList;
	public:
		FieldListASTN(FieldDeclASTN* fieldDeclASTN);
		FieldListASTN(FieldListASTN* fieldListASTN, FieldDeclASTN* fieldDeclASTN);
		size_t getFieldDeclNum() const;
		std::vector<FieldDeclASTN*> getFieldDeclList() const;
		FieldDeclASTN* getFieldDecl(size_t idx) const;
	};

	// field_decl -> name_list (COLON) type_decl (SEMI)
	class FieldDeclASTN : public ASTNode {
		NameListASTN* _nameListASTN;
		TypeDeclASTN* _typeDeclASTN;
	public:
		FieldDeclASTN(NameListASTN* nameListASTN, TypeDeclASTN* typeDeclASTN);
		NameListASTN* getNameListASTN() const;
		TypeDeclASTN* getTypeDeclASTN() const;
	};

	// name_list -> name_list (COMMA) ID | ID
	class NameListASTN : public ASTNode {
		std::vector<std::string> _nameList;
	public:
		NameListASTN(NameListASTN* nameListASTN, NameASTN* name);
		NameListASTN(NameASTN* name);
		size_t getNameNum() const;
		std::vector<std::string> getNameList() const;
		std::string getName(size_t idx) const;
	};

	// var_part -> var_decl_list
	// var_decl_list -> var_decl+
	class VarPartASTN : public ASTNode {
		std::vector<VarDeclASTN*> _varDeclList;
	public:
		VarPartASTN();
		VarPartASTN(VarDeclASTN* varDeclASTN);
		VarPartASTN(VarPartASTN* varPartASTN, VarDeclASTN* varDeclASTN);
		size_t getVarDeclNum() const;
		std::vector<VarDeclASTN*> getVarDeclList() const;
		VarDeclASTN* getVarDeclASTN(size_t idx) const;
	};

	// var_decl -> name_list (COLON) type_decl (SEMI)
	class VarDeclASTN : public ASTNode {
		NameListASTN* _nameListASTN;
		TypeDeclASTN* _typeDeclASTN;
	public:
		VarDeclASTN(NameListASTN* nameListASTN, TypeDeclASTN* typeDeclASTN);
		NameListASTN* getNameListASTN() const;
		TypeDeclASTN* getTypeDeclASTN() const;
	};

	// routine_part -> routine_part function_decl
	// routine_part -> routine_part procedure_decl
	// routine_part -> %empty
	class RoutinePartASTN : public ASTNode {
		std::vector<FuncDeclASTN*> _funcDeclList;
		std::vector<ProcDeclASTN*> _procDeclList;
		std::vector<int> _idxList; // positive for func, negative for proc
	public:
		RoutinePartASTN();
		RoutinePartASTN(RoutinePartASTN* routinePartASTN, FuncDeclASTN* funcDeclASTN);
		RoutinePartASTN(RoutinePartASTN* routinePartASTN, ProcDeclASTN* procDeclASTN);
		std::vector<FuncDeclASTN*> getFuncDeclList() const;
		std::vector<ProcDeclASTN*> getProcDeclList() const;
		std::vector<int> getIdxList() const;
		size_t getFuncDeclNum() const;
		size_t getProcDeclNum() const;
		size_t getTotalDeclNum() const;
		int getIdx(size_t idx) const; // positive for func, negative for proc
		FuncDeclASTN* getFuncDecl(size_t idx) const;
		ProcDeclASTN* getProcDecl(size_t idx) const;
	};

	// function_decl -> (FUNCTION) NAME parameters (COLON) simple_type_decl (SEMI) sub_routine (SEMI)
	class FunctionDeclASTN : public ASTNode {
		std::string _name;
		ParaASTN* _paraASTN;
		TypeDeclASTN* _typeDeclASTN;
		RoutineASTN* _subroutineASTN;
	public:
		FunctionDeclASTN(std::string name, ParaASTN* paraASTN, TypeDeclASTN* typeDeclASTN, RoutineASTN* subroutineASTN);
		std::string getName() const;
		ParaASTN* getParaASTN() const;
		TypeDeclASTN* getTypeDeclASTN() const;
		RoutineASTN* getSubroutineASTN() const;
	};

	// procedure_decl -> (PROCEDURE) NAME parameters (SEMI) sub_routine (SEMI)
	class ProcedureDeclASTN : public ASTNode {
		std::string _name;
		ParaASTN* _paraASTN;
		RoutineASTN* _subroutineASTN;
	public:
		ProcedureDeclASTN(std::string name, ParaASTN* paraASTN, RoutineASTN* subroutineASTN);
		std::string getName() const;
		ParaASTN* getParaASTN() const;
		RoutineASTN* getSubroutineASTN() const;
	};

	// parameters -> (LP) para_decl_list (RP) | %empty
	// para_decl_list -> para_decl_list (SEMI) para_type_list | para_type_list
	class ParaASTN : public ASTNode {
		std::vector<ParaTypeListASTN*> _paraTypeList;
	public:
		ParaASTN();
		ParaASTN(ParaASTN* paraDeclListASTN);
		ParaASTN(ParaASTN* paraDeclListASTN, ParaTypeListASTN* paraTypeListASTN);
		ParaASTN(ParaTypeListASTN* paraTypeListASTN);
		size_t getParaTypeListNum() const;
		std::vector<ParaTypeListASTN*> getParaTypeList() const;
		ParaTypeListASTN* getParaTypeListASTN(size_t idx) const;
	};

	// para_type_list -> (VAR) name_list (COLON) simple_type_decl
	// para_type_list -> name_list (COLON) simple_type_decl
	class ParaTypeListASTN : public ASTNode {
		bool _isVar; // 0 for val_list_decl, 1 for var_list_decl
		NameListASTN* _nameListASTN;
		TypeDeclASTN* _typeDeclASTN;
	public:
		ParaTypeListASTN(NameListASTN* nameListASTN, TypeDeclASTN* typeDeclASTN, bool isVar = 0);
		bool getIsVar() const;
		NameListASTN* getNameListASTN() const;
		TypeDeclASTN* getTypeDeclASTN() const;
	};

	// routine_body : compound_stmt
	// compound_stmt : (KEY_BEGIN) stmt_list (END)
	// stmt_list : stmt_list stmt (SEMI)
	class StmtListASTN : public ASTNode {
		std::vector<StmtASTN*> _stmtList;
	public:
		StmtListASTN(StmtListASTN* stmtListASTN);
		StmtListASTN(StmtListASTN* stmtListASTN, StmtASTN* stmtASTN);
		size_t getStmtNum() const;
		std::vector<StmtASTN*> getStmtList() const;
		StmtASTN* getStmt(size_t idx) const;
	};

	// stmt -> I_VAL (COLON) non_label_stmt
	// stmt -> non_label_stmt
	// non_label_stmt -> assign_stmt
	// non_label_stmt -> proc_stmt
	// non_label_stmt -> compound_stmt
	// non_label_stmt -> if_stmt
	// non_label_stmt -> repeat_stmt
	// non_label_stmt -> while_stmt
	// non_label_stmt -> for_stmt
	// non_label_stmt -> case_stmt
	// non_label_stmt -> goto_stmt
	class StmtASTN : public ASTNode {
		int _label = NOLABEL; // -1 for no label
		SPLStmtType _type;
		AssignStmtASTN* _assignStmt;
		ProcStmtASTN* _procStmt;
		StmtListASTN* _compoundStmt;
		IfStmtASTN* _ifStmt;
		RepeatStmtASTN* _repeatStmt;
		WhileStmtASTN* _whileStmt;
		ForStmtASTN* _forStmt;
		CaseStmtASTN* _caseStmt;
		GotoStmtASTN* _gotoStmt;
	public:
		StmtASTN(StmtASTN* stmtASTN, int label = NOLABEL);
		StmtASTN(AssignStmtASTN* assignStmt);
		StmtASTN(ProcStmtASTN* procStmt);
		StmtASTN(StmtListASTN* compoundStmt);
		StmtASTN(IfStmtASTN* ifStmt);
		StmtASTN(RepeatStmtASTN* repeatStmt);
		StmtASTN(WhileStmtASTN* whileStmt);
		StmtASTN(ForStmtASTN* forStmt);
		StmtASTN(CaseStmtASTN* caseStmt);
		StmtASTN(GotoStmtASTN* gotoStmt);
		int getLabel() const;
		SPLStmtType getType() const;
		AssignStmtASTN* getAssignStmt() const;
		ProcStmtASTN* getProcStmt() const;
		StmtListASTN* getCompoundStmt() const;
		IfStmtASTN* getIfStmt() const;
		RepeatStmtASTN* getRepeatStmt() const;
		WhileStmtASTN* getWhileStmt() const;
		ForStmtASTN* getForStmt() const;
		CaseStmtASTN* getCaseStmt() const;
		GotoStmtASTN* getGotoStmt() const;
	};

	// assign_stmt -> ID (ASSIGN) expression 
	// assign_stmt -> ID (LB) expression (RB) (ASSIGN) expression
	// assign_stmt -> ID (DOT) ID (ASSIGN) expression
	class AssignStmtASTN : public ASTNode {
		SPLAssignType _type;
		std::string _name;
		std::string _memberName;
		ExprASTN* _expr;
		ExprASTN* _arrayIdx;
	public:
		AssignStmtASTN(std::string name, ExprASTN* expr);
		AssignStmtASTN(std::string name, ExprASTN* arrayIdx, ExprASTN* expr);
		AssignStmtASTN(std::string name, std::string memberName, ExprASTN* expr);
		SPLAssignType getType() const;
		std::string getName() const;
		std::string getMemName() const;
		ExprASTN* getExpr() const;
		ExprASTN* getArrayIdx() const;
  	};

	// proc_stmt -> ID
	// proc_stmt -> ID (LP) expression_list (RP)
	// proc_stmt -> SYS_PROC (LP) expression_list (RP)
	// proc_stmt -> READ (LP) factor (RP)
	class ProcStmtASTN : public ASTNode{
		SPLProcType _type;
		std::string _funcName;
		ExprListASTN* _argsList;
		FactorASTN* _readArgs;
	public:
		ProcStmtASTN(std::string name);
		ProcStmtASTN(std::string name, ExprListASTN* argsList);
		ProcStmtASTN(SPLProcType type, ExprListASTN* argsList);
		ProcStmtASTN(FactorASTN* readArgs);
		SPLProcType getType() const;
		std::string getFuncName() const;
		ExprListASTN* getArgsList() const;
		FactorASTN* getReadArgs() const;
	};

	// SYS_PROC -> WRITE | WRITELN  // type : SPLProcType

	// if_stmt -> (IF) expression (THEN) stmt else_clause 
	class IfStmtASTN : public ASTNode {
		ExprASTN* _condition;
		StmtASTN* _stmt;
		ElseASTN* _elseClause;
	public:
		IfStmtASTN(ExprASTN* condition, StmtASTN* stmt, ElseASTN* elseClause);
		ExprASTN* getCondition() const;
		StmtASTN* getStmt() const;
		ElseASTN* getElseClause() const;
	};

	// else_clause -> (ELSE) stmt | %empty
	class ElseASTN : public ASTNode {
		StmtASTN* _stmt;
	public:
		ElseASTN();
		ElseASTN(StmtASTN* stmt);
		StmtASTN* getStmt() const;
	};

	// repeat_stmt -> (REPEAT) stmt_list (UNTIL) expression
	class RepeatStmtASTN : public ASTNode {
		StmtListASTN* _stmtList;
		ExprASTN* _condition;
	public:
		RepeatStmtASTN(StmtListASTN* stmtList, ExprASTN* condition);
		StmtListASTN* getStmtList() const;
		ExprASTN* getCondition() const;
	};

	// while_stmt -> (WHILE) expression (DO) stmt
	class WhileStmtASTN : public ASTNode {
		ExprASTN* _condition;
		StmtASTN* _stmt;
	public:
		WhileStmtASTN(ExprASTN* condition, StmtASTN* stmt);
		ExprASTN* getCondition() const;
		StmtASTN* getStmt() const;
	};

	// for_stmt -> (FOR) ID (ASSIGN) expression direction expression (DO) stmt 
	class ForStmtASTN : public ASTNode {
		std::string _name;
		ExprASTN* _start;
		ExprASTN* _end;
		bool _dir = POS;
	public:
		ForStmtASTN(std::string name, ExprASTN* start, ExprASTN* end, bool dir = POS);
		std::string getName() const;
		ExprASTN* getStart() const;
		ExprASTN* getEnd() const;
		bool getDir() const;
	};

	// direction -> TO | DOWNTO  (type : bool)

	// case_stmt -> (CASE) expression (OF) case_expr_list (END)
	// case_expr_list -> case_expr_list case_expr
	// case_expr_list -> case_expr
	class CaseStmtASTN : public ASTNode {
		ExprASTN* _condition;
		std::vector<CaseExprASTN*> _caseExprList;
	public:
		CaseStmtASTN(CaseExprASTN* caseExpr);
		CaseStmtASTN(CaseStmtASTN* caseStmt, CaseExprASTN* caseExpr);
		CaseStmtASTN(ExprASTN* condition, CaseStmtASTN* caseStmt);
		ExprASTN* getCondition() const;
		size_t getExprNum() const;
		std::vector<CaseExprASTN*> getCaseExprList() const;
		CaseExprASTN* getCaseExpr(size_t idx) const;
	};

	// case_expr -> const_value (COLON) stmt (SEMI)
	// case_expr -> ID (COLON) stmt (SEMI)
	class CaseExprASTN : public ASTNode {
		bool _type; // CASE_CONST | CASE_VAR
		ConstValueASTN* _constVal;
		std::string _name;
		StmtASTN* _stmt;
	public:
		CaseExprASTN(ConstValueASTN* constVal, StmtASTN* stmt);
		CaseExprASTN(std::string name, StmtASTN* stmt);
		bool getType() const;
		ConstValueASTN* getConstVal() const;
		std::string getName() const;
		StmtASTN* getStmt() const;
	};

	// goto_stmt -> (GOTO) I_VAL
	class GotoStmtASTN : public ASTNode {
		int _val;
	public:
		GotoStmtASTN(int val);
		int getVal() const;
	};

	// expression_list -> expression_list (COMMA) expression
	// expression_list -> expression
	class ExprListASTN : public ASTNode {
		std::vector<ExprASTN*> _exprList;
	public:
		ExprListASTN(ExprListASTN* exprList, ExprASTN* expr);
		ExprListASTN(ExprASTN* expr);
		size_t getExprNum() const;
		std::vector<ExprASTN*> getExprList() const;
		ExprASTN* getExpr(size_t idx) const;
	};

	// expression -> expression GE expr
	// expression -> expression GT expr
	// expression -> expression LE expr
	// expression -> expression LT expr
	// expression -> expression EQUAL expr
	// expression -> expression UNEQUAL expr
	// expression -> expr
	class ExprASTN : public ASTNode {
		std::vector<SExprASTN*> _sexprList;
		std::vector<SPLExprOp> _opList;
	public:
		ExprASTN(ExprASTN* expr, SPLExprOp op, SExprASTN* sexpr);
		ExprASTN(SExprASTN* sexpr);
		std::vector<SExprASTN*> getSExprList() const;
		std::vector<SPLExprOp> getOpList() const;
		size_t getSExprNum() const;
		SExprASTN* getSExpr(size_t idx) const;
		SPLExprOp getOp(size_t idx) const;
	};

	// expr -> expr PLUS term
	// expr -> expr MINUS term
	// expr -> expr OR term
	// term
	class SExprASTN : public ASTNode {
		std::vector<TermASTN*> _termList;
		std::vector<SPLSExprOp> _opList;
	public:
		SExprASTN(SExprASTN* sexpr, SPLSExprOp op, TermASTN* term);
		SExprASTN(TermASTN* term);
		std::vector<TermASTN*> getTermList() const;
		std::vector<SPLSExprOp> getOpList() const;
		size_t getTermNum() const;
		TermASTN* getTerm(size_t idx) const;
		SPLSExprOp getOp(size_t idx) const;
	};

	// term -> term MUL factor
	// term -> term DIV factor
	// term -> term KEY_DIV factor
	// term -> term MOD factor
	// term -> term AND factor
	// term -> factor
	class TermASTN : public ASTNode {
		std::vector<FactorASTN*> _factorList;
		std::vector<SPLTermOp> _opList;
	public:
		TermASTN(TermASTN* term, SPLTermOp op, FactorASTN* factor);
		TermASTN(FactorASTN* factor);
		std::vector<FactorASTN*> getFactorList() const;
		std::vector<SPLTermOp> getOpList() const;
		size_t getFactorNum() const;
		FactorASTN* getFactor(size_t idx) const;
		SPLTermOp getOp(size_t idx) const;
	};

	// factor -> NAME
	// factor -> NAME (LP) expression_list (RP)
	// factor -> SYS_FUNCT
	// factor -> SYS_FUNCT (LP) expression_list (RP)
	// factor -> const_value
	// factor -> (LP) expression (RP)
	// factor -> NOT factor
	// factor -> MINUS factor (Using _NEG)
	// factor -> ID (LB) expression (RB)
	// factor -> ID (DOT) ID
	class FactorASTN : public ASTNode {
		SPLVarType _type;
		SPLFuncType _funcType;
		SPLFactorType _factorType;
		std::string _name;
		ExprListASTN* _argsList;
		ConstValueASTN* _constVal;
		ExprASTN* _expr;
		std::string _memName;
		FactorASTN* _factor;
	public:
		FactorASTN(std::string name);
		FactorASTN(std::string name, ExprListASTN* argsList);
		FactorASTN(SPLFuncType funcType);
		FactorASTN(SPLFuncType funcType, ExprListASTN* argsList);
		FactorASTN(ConstValueASTN* constVal);
		FactorASTN(ExprASTN* expr);
		FactorASTN(FactorASTN* factor, SPLFactorType factorType);
		FactorASTN(std::string name, ExprASTN* idx);
		FactorASTN(std::string name, std::string memName);
		SPLVarType getType() const;
		SPLFuncType getFuncType() const;
		SPLFactorType getFactorType() const;
		std::string getName() const;
		ExprListASTN* getArgsList() const;
		ConstValueASTN* getConstVal() const;
		ExprASTN* getExpr() const;
		std::string getMemName() const;
		FactorASTN* getFactor() const;
	};

}
