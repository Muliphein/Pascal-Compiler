#include "GraphGenerator.h"

Visitor::Visitor() : _level(0)
{
}

void Visitor::println(std::string msg, bool isHead, std::ostream & os)
{
	if (_level == 0)
	{
		os << msg << std::endl;
		return;
	}
	if (_level == 1)
	{
		os << "|";
		if (isHead) os << HEAD;
		else os << NONHEAD;
		os << msg << std::endl;
		return;
	}
	for (size_t i = 0; i <= _level - 2; i++)
	{
		if (_isLastChild.at(i)) os << " ";
		else os << "|";
		os << NONHEAD;
	}
	if (_isLastChild.at(_level - 1) && !isHead) os << " ";
	else if(isHead) os << "|";
	else os << "|";
	if (isHead) os << HEAD;
	else os << NONHEAD;
	os << msg << std::endl;
	return;
}

void Visitor::VisitProgramASTN(SPLAST::ProgramASTN * astn)
{
	if (astn == nullptr) {
		println("ProgramASTN : Nullptr Err!");
		return;
	}
	println("Program");
	_isLastChild.push_back(false);
	_level++;
	VisitProgramHeadASTN(astn->getProgramHeadASTN());
	_isLastChild[_level - 1] = true;
	VisitRoutineASTN(astn->getRoutineASTN());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitProgramHeadASTN(SPLAST::ProgramHeadASTN * astn)
{
	if (astn == nullptr) {
		println("ProgramHeadASTN : Nullptr Err!");
		return;
	}	
	println("Program_Head : name = " + astn->getName());
	return;
}

void Visitor::VisitNameASTN(SPLAST::NameASTN * astn)
{
	if (astn == nullptr) {
		println("NameASTN : Nullptr Err!");
		return;
	}
	println("NameASTN : name = " + astn->getName());
	return;
}

void Visitor::VisitRoutineASTN(SPLAST::RoutineASTN * astn)
{
	if (astn == nullptr) {
		println("RoutineASTN : Nullptr Err!");
		return;
	}
	println("Routine");
	_isLastChild.push_back(false);
	_level++;
	VisitRoutineHeadASTN(astn->getRoutineHeadASTN());
	_isLastChild[_level - 1] = true;
	VisitStmtListASTN(astn->getRoutineBodyASTN());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitRoutineHeadASTN(SPLAST::RoutineHeadASTN * astn)
{
	if (astn == nullptr) {
		println("RoutineHeadASTN : Nullptr Err!");
		return;
	}
	println("Routine_Head");
	_isLastChild.push_back(false);
	_level++;
	VisitConstPartASTN(astn->getConstPartASTN());
	VisitTypePartASTN(astn->getTypePartASTN());
	VisitVarPartASTN(astn->getVarPartASTN());
	_isLastChild[_level - 1] = true;
	VisitRoutinePartASTN(astn->getRoutinePartASTN());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitConstPartASTN(SPLAST::ConstPartASTN * astn)
{
	if (astn == nullptr) {
		println("ConstPartASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getConstExprNum();
	println("ConstPartASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitConstExprASTN(astn->getConstExpr(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitConstExprASTN(astn->getConstExpr(i));
	_isLastChild[_level - 1] = true;
	VisitConstExprASTN(astn->getConstExpr(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitConstExprASTN(SPLAST::ConstExprASTN * astn)
{
	if (astn == nullptr) {
		println("ConstExprASTN : Nullptr Err!");
		return;
	}
	SPLVarType type = astn->getConstValueASTN()->getType();
	void* value = astn->getConstValueASTN()->getValue();
	if (type == _BOOL)
	{
		println("ConstExprASTN : bool " + astn->getName() + " = " + (*(bool*)value ? "true" : "false"));
		return;
	}
	if (type == _CHAR)
	{
		println("ConstExprASTN : char " + astn->getName() + " = " + *(char*)value);
		return;
	}
	if (type == _INT)
	{
		println("ConstExprASTN : int " + astn->getName() + " = " + std::to_string(*(int*)value));
		return;
	}
	if (type == _DOUBLE)
	{
		println("ConstExprASTN : double " + astn->getName() + " = " + std::to_string(*(double*)value));
		return;
	}
	println("ConstExprASTN : TypeErr = " + std::to_string(type));
	return;
}

void Visitor::VisitConstValueASTN(SPLAST::ConstValueASTN * astn)
{
	if (astn == nullptr) {
		println("ConstValueASTN : Nullptr Err!");
		return;
	}
	SPLVarType type = astn->getType();
	void* value = astn->getValue();
	if (type == _BOOL)
	{
		println("ConstValueASTN : bool, " + std::string(*(bool*)value ? "true" : "false"));
		return;
	}
	if (type == _CHAR)
	{
		println(std::string("ConstValueASTN : char, ") + *(char*)value);
		return;
	}
	if (type == _INT)
	{
		println("ConstValueASTN : int, " + std::to_string(*(int*)value));
		return;
	}
	if (type == _DOUBLE)
	{
		println("ConstValueASTN : double, " + std::to_string(*(double*)value));
		return;
	}
	println("ConstValueASTN : TypeErr = " + std::to_string(type));
	return;
}

void Visitor::VisitTypePartASTN(SPLAST::TypePartASTN * astn)
{
	if (astn == nullptr) {
		println("TypePartASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getTypeDefNum();
	println("Type_Part : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitTypeDefASTN(astn->getTypeDef(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitTypeDefASTN(astn->getTypeDef(i));
	_isLastChild[_level - 1] = true;
	VisitTypeDefASTN(astn->getTypeDef(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitTypeDefASTN(SPLAST::TypeDefASTN * astn)
{
	if (astn == nullptr) {
		println("TypeDefASTN : Nullptr Err!");
		return;
	}
	println("TypeDefASTN : " + astn->getName() + " = ");
	VisitTypeDeclASTN(astn->getTypeDeclASTN());
	return;
}

void Visitor::VisitTypeDeclASTN(SPLAST::TypeDeclASTN * astn)
{
	if (astn == nullptr) {
		println("TypeDeclASTN : Nullptr Err!", false);
		return;
	}
	SPLVarType type = astn->getType();
	if (type == _USERTYPE) 
	{
		println("UserType : " + astn->getUserType(), false);
		return;
	}
	if (type == _BOOL)
	{
		println("Type : bool", false);
		return;
	}
	if (type == _CHAR)
	{
		println("Type : char", false);
		return;
	}
	if (type == _INT)
	{
		println("Type : int", false);
		return;
	}
	if (type == _DOUBLE)
	{
		println("Type : double", false);
		return;
	}
	if (type == _ENUM)
	{
		std::string enumString = "(";
		std::vector<std::string> enumType = astn->getEnumType();
		for (int i = 0; i <= enumType.size() - 1; i++)
			enumString += (enumType[i] + ", ");
		enumString[enumString.length() - 2] = ')';
		println("Type : Enum" + enumString, false);
		return;
	}
	if (type == _RANGE)
	{
		if (astn->getRangeStartVal() != nullptr) // val range
		{
			println("Type : Range, Start = ", false);
			_isLastChild.push_back(true);
			_level++;
			VisitConstValueASTN(astn->getRangeStartVal());
			_isLastChild.pop_back();
			_level--;
			println("End = ", false);
			_isLastChild.push_back(true);
			_level++;
			VisitConstValueASTN(astn->getRangeEndVal());
			_isLastChild.pop_back();
			_level--;
			return;
		}
		else{
			println("Type : Range, Start = " + astn->getRangeStartName(), false);
			println("End = " + astn->getRangeEndName(), false);
			return;
		}
	}
	if (type == _ARRAY)
	{
		println("Type : Array, Range = ", false);
		VisitTypeDeclASTN(astn->getArrayRange());
		println("Array Type = ", false);
		VisitTypeDeclASTN(astn->getArrayType());
		return;
	}
	if (type == _RECORD)
	{
		println("Type : Record ", false);
		VisitFieldListASTN(astn->getFieldListASTN());
		return;
	}
	println("TypeDeclASTN : TypeErr = " + std::to_string(astn->getType()), false);
	return;
}

void Visitor::VisitFieldListASTN(SPLAST::FieldListASTN * astn)
{
	if (astn == nullptr) {
		println("FieldListASTN : Nullptr Err!", false);
		return;
	}
	size_t size = astn->getFieldDeclNum();
	println("FieldListASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitFieldDeclASTN(astn->getFieldDecl(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitFieldDeclASTN(astn->getFieldDecl(i));
	_isLastChild[_level - 1] = true;
	VisitFieldDeclASTN(astn->getFieldDecl(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitFieldDeclASTN(SPLAST::FieldDeclASTN * astn)
{
	if (astn == nullptr) {
		println("FieldDeclASTN : Nullptr Err!");
		return;
	}
	println("FieldDeclASTN : ");
	VisitTypeDeclASTN(astn->getTypeDeclASTN());
	VisitNameListASTN(astn->getNameListASTN());
	return;
}

void Visitor::VisitNameListASTN(SPLAST::NameListASTN * astn)
{
	if (astn == nullptr) {
		println("NameListASTN : Nullptr Err!", false);
		return;
	}
	std::vector<std::string> name = astn->getNameList();
	std::string nameString = "(";
	for (int i = 0; i <= name.size() - 1; i++)
		nameString += (name[i] + ", ");
	nameString[nameString.length() - 2] = ')';
	println("NameList : " + nameString, false);
	return;
}

void Visitor::VisitVarPartASTN(SPLAST::VarPartASTN * astn)
{
	if (astn == nullptr) {
		println("VarPartASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getVarDeclNum();
	println("VarPartASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitVarDeclASTN(astn->getVarDeclASTN(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitVarDeclASTN(astn->getVarDeclASTN(i));
	_isLastChild[_level - 1] = true;
	VisitVarDeclASTN(astn->getVarDeclASTN(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitVarDeclASTN(SPLAST::VarDeclASTN * astn)
{
	if (astn == nullptr) {
		println("VarDeclASTN : Nullptr Err!");
		return;
	}
	println("VarDeclASTN : ");
	VisitTypeDeclASTN(astn->getTypeDeclASTN());
	VisitNameListASTN(astn->getNameListASTN());
	return;
}

void Visitor::VisitRoutinePartASTN(SPLAST::RoutinePartASTN * astn)
{
	if (astn == nullptr) {
		println("RoutinePartASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getTotalDeclNum();
	println("RoutinePartASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		int idx = astn->getIdx(0);
		if (idx > 0) VisitFuncDeclASTN(astn->getFuncDecl(idx - 1));
		else VisitProcDeclASTN(astn->getProcDecl(1 - idx));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
	{
		int idx = astn->getIdx(i);
		if (idx > 0) VisitFuncDeclASTN(astn->getFuncDecl(idx - 1));
		else VisitProcDeclASTN(astn->getProcDecl(1 - idx));
	}
	_isLastChild[_level - 1] = true;
	int idx = astn->getIdx(size - 1);
	if (idx > 0) VisitFuncDeclASTN(astn->getFuncDecl(idx - 1));
	else VisitProcDeclASTN(astn->getProcDecl(1 - idx));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitFuncDeclASTN(SPLAST::FuncDeclASTN * astn)
{
	if (astn == nullptr) {
		println("FuncDeclASTN : Nullptr Err!");
		return;
	}
	println("FuncDeclASTN : " + astn->getName());
	VisitTypeDeclASTN(astn->getTypeDeclASTN());
	_isLastChild.push_back(false);
	_level++;
	VisitParaASTN(astn->getParaASTN());
	_isLastChild[_level - 1] = true;
	VisitRoutineASTN(astn->getSubroutineASTN());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitProcDeclASTN(SPLAST::ProcDeclASTN * astn)
{
	if (astn == nullptr) {
		println("ProcDeclASTN : Nullptr Err!");
		return;
	}
	println("ProcDeclASTN : " + astn->getName());
	_isLastChild.push_back(false);
	_level++;
	VisitParaASTN(astn->getParaASTN());
	_isLastChild[_level - 1] = true;
	VisitRoutineASTN(astn->getSubroutineASTN());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitParaASTN(SPLAST::ParaASTN * astn)
{
	if (astn == nullptr) {
		println("ParaASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getParaTypeListNum();
	println("ParaASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitParaTypeListASTN(astn->getParaTypeListASTN(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitParaTypeListASTN(astn->getParaTypeListASTN(i));
	_isLastChild[_level - 1] = true;
	VisitParaTypeListASTN(astn->getParaTypeListASTN(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitParaTypeListASTN(SPLAST::ParaTypeListASTN * astn)
{
	if (astn == nullptr) {
		println("ParaTypeListASTN : Nullptr Err!");
		return;
	}
	if (astn->getIsVar())
		println("ParaTypeListASTN : IsVar");
	else
		println("ParaTypeListASTN : NotVar");
	VisitTypeDeclASTN(astn->getTypeDeclASTN());
	VisitNameListASTN(astn->getNameListASTN());
	return;
}

void Visitor::VisitStmtListASTN(SPLAST::StmtListASTN * astn)
{
	if (astn == nullptr) {
		println("StmtListASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getStmtNum();
	println("StmtListASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitStmtASTN(astn->getStmt(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitStmtASTN(astn->getStmt(i));
	_isLastChild[_level - 1] = true;
	VisitStmtASTN(astn->getStmt(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitStmtASTN(SPLAST::StmtASTN * astn)
{
	if (astn == nullptr) {
		println("StmtASTN : Nullptr Err!");
		return;
	}
	SPLStmtType type = astn->getType();
	if (type == _ASSIGN)
	{
		VisitAssignStmtASTN(astn->getAssignStmt());
		return;
	}
	if (type == _PROC)
	{
		VisitProcStmtASTN(astn->getProcStmt());
		return;
	}
	if (type == _COMPOUND)
	{
		VisitStmtListASTN(astn->getCompoundStmt());
		return;
	}
	if (type == _IF)
	{
		VisitIfStmtASTN(astn->getIfStmt());
		return;
	}
	if (type == _REPEAT)
	{
		VisitRepeatStmtASTN(astn->getRepeatStmt());
		return;
	}
	if (type == _WHILE)
	{
		VisitWhileStmtASTN(astn->getWhileStmt());
		return;
	}
	if (type == _FOR)
	{
		VisitForStmtASTN(astn->getForStmt());
		return;
	}
	if (type == _CASE)
	{
		VisitCaseStmtASTN(astn->getCaseStmt());
		return;
	}
	if (type == _GOTO)
	{
		VisitGotoStmtASTN(astn->getGotoStmt());
		return;
	}
	println("StmtASTN : TypeErr = " + std::to_string(type));
	return;
}

void Visitor::VisitAssignStmtASTN(SPLAST::AssignStmtASTN * astn)
{
	if (astn == nullptr) {
		println("AssignStmtASTN : Nullptr Err!");
		return;
	}
	SPLAssignType type = astn->getType();
	if (type == _VARIABLE)
	{
		println("AssignStmtASTN : Variable " + astn->getName());
		_isLastChild.push_back(true);
		_level++;
		VisitExprASTN(astn->getExpr());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (type == _ARRAYIDX)
	{
		println("AssignStmtASTN : Array " + astn->getName());
		println("Idx : ", false);
		_isLastChild.push_back(false);
		_level++;
		VisitExprASTN(astn->getArrayIdx());
		_isLastChild[_level - 1] = true;
		VisitExprASTN(astn->getExpr());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (type == _CLASSMEM)
	{
		println("AssignStmtASTN : Class " + astn->getName() + "." + astn->getMemName());
		_isLastChild.push_back(true);
		_level++;
		VisitExprASTN(astn->getExpr());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	println("AssignStmtASTN : TypeErr = " + std::to_string(type));
	return;
}

void Visitor::VisitProcStmtASTN(SPLAST::ProcStmtASTN * astn)
{
	if (astn == nullptr) {
		println("ProcStmtASTN : Nullptr Err!");
		return;
	}
	SPLProcType type = astn->getType();
	if (type == _USERPROC)
	{
		println("ProcStmtASTN : UserProc " + astn->getProcName());
		if (astn->getArgsList() != nullptr)
		{
			println("ArgsList : ", false);
			VisitExprListASTN(astn->getArgsList());
		}
		return;
	}
	if (type == _WRITE)
	{
		println("ProcStmtASTN : Write");
		VisitExprListASTN(astn->getArgsList());
		return;
	}
	if (type == _WRITELN)
	{
		println("ProcStmtASTN : Writeln");
		VisitExprListASTN(astn->getArgsList());
		return;
	}
	if (type == _READ)
	{
		println("ProcStmtASTN : Read");
		_isLastChild.push_back(true);
		_level++;
		VisitFactorASTN(astn->getReadArgs());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	println("ProcStmtASTN : TypeErr = " + std::to_string(type));
	return;
}

void Visitor::VisitIfStmtASTN(SPLAST::IfStmtASTN * astn)
{
	if (astn == nullptr) {
		println("IfStmtASTN : Nullptr Err!");
		return;
	}
	println("IfStmtASTN : Condition : ", true);
	_isLastChild.push_back(false);
	_level++;
	VisitExprASTN(astn->getCondition());
	_level--;
	println("Stmt : ", false);
	_level++;
	VisitStmtASTN(astn->getStmt());
	_isLastChild.pop_back();
	_level--;	
	VisitElseASTN(astn->getElseClause());
	return;
}

void Visitor::VisitElseASTN(SPLAST::ElseASTN * astn)
{
	if (astn == nullptr) {
		println("ElseStmtASTN : Nullptr Err!", false);
		return;
	}
	if (astn->getStmt() == nullptr)
	{
		println("ElseStmtASTN : %empty", false);
		return;
	}
	else
	{
		println("ElseStmtASTN :", false);
		_isLastChild.push_back(true);
		_level++;
		VisitStmtASTN(astn->getStmt());
		_isLastChild.pop_back();
		_level--;
		return;
	}
}

void Visitor::VisitRepeatStmtASTN(SPLAST::RepeatStmtASTN * astn)
{
	if (astn == nullptr) {
		println("RepeatStmtASTN : Nullptr Err!");
		return;
	}
	println("RepeatStmtASTN : Condition :");
	_isLastChild.push_back(false);
	_level++;
	VisitExprASTN(astn->getCondition());
	_isLastChild.pop_back();
	_level--;
	VisitStmtListASTN(astn->getStmtList());
	return;
}

void Visitor::VisitWhileStmtASTN(SPLAST::WhileStmtASTN * astn)
{
	if (astn == nullptr) {
		println("WhileStmtASTN : Nullptr Err!");
		return;
	}
	println("WhileStmtASTN : Condition: ");
	_isLastChild.push_back(false);
	_level++;
	VisitExprASTN(astn->getCondition());
	_isLastChild[_level - 1] = true;
	VisitStmtASTN(astn->getStmt());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitForStmtASTN(SPLAST::ForStmtASTN * astn)
{
	if (astn == nullptr) {
		println("ForStmtASTN : Nullptr Err!");
		return;
	}
	println("ForStmtASTN : Var = " + astn->getName() + " , Dir = " + (astn->getDir() ? "POS" : "NEG"));
	println("Start from : ", false);
	_isLastChild.push_back(false);
	_level++;
	VisitExprASTN(astn->getStart());
	_level--;
	println("End : ", false);
	_level++;
	VisitExprASTN(astn->getEnd());
	_level--;
	println("Stmt :", false);
	_level++;
	_isLastChild[_level - 1] = true;
	VisitStmtASTN(astn->getStmt());
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitCaseStmtASTN(SPLAST::CaseStmtASTN * astn)
{
	if (astn == nullptr) {
		println("CaseStmtASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getExprNum();
	println("CaseStmtASTN : size = " + std::to_string(size) + ", condition :");
	_isLastChild.push_back(false);
	_level++;
	VisitExprASTN(astn->getCondition());
	if (size == 0) return;
	if (size == 1) {
		_isLastChild[_level - 1] = true;
		VisitCaseExprASTN(astn->getCaseExpr(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	for (int i = 0; i <= size - 2; i++)
		VisitCaseExprASTN(astn->getCaseExpr(i));
	_isLastChild[_level - 1] = true;
	VisitCaseExprASTN(astn->getCaseExpr(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitCaseExprASTN(SPLAST::CaseExprASTN * astn)
{
	if (astn == nullptr) {
		println("CaseExprASTN : Nullptr Err!");
		return;
	}
	if (astn->getType() == CASE_CONST)
	{
		println("CaseExprASTN :");
		_isLastChild.push_back(false);
		_level++;
		VisitConstValueASTN(astn->getConstVal());
		_isLastChild[_level - 1] = true;
		VisitStmtASTN(astn->getStmt());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	else 
	{
		println("CaseExpr ASTN : name = " + astn->getName());
		_isLastChild.push_back(true);
		_level++;
		VisitStmtASTN(astn->getStmt());
		_isLastChild.pop_back();
		_level--;
		return;
	}
}

void Visitor::VisitGotoStmtASTN(SPLAST::GotoStmtASTN * astn)
{
	if (astn == nullptr) {
		println("GotoStmtASTN : Nullptr Err!");
		return;
	}
	println("GotoStmtASTN : GOTO" + std::to_string(astn->getVal()));
	return;
}

void Visitor::VisitExprListASTN(SPLAST::ExprListASTN * astn)
{
	if (astn == nullptr) {
		println("ExprListASTN : Nullptr Err!", false);
		return;
	}
	size_t size = astn->getExprNum();
	println("ExprListASTN : size = " + std::to_string(size), false);
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitExprASTN(astn->getExpr(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
		VisitExprASTN(astn->getExpr(i));
	_isLastChild[_level - 1] = true;
	VisitExprASTN(astn->getExpr(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitExprASTN(SPLAST::ExprASTN * astn)
{
	if (astn == nullptr) {
		println("ExprASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getSExprNum();
	println("ExprASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitSExprASTN(astn->getSExpr(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
	{
		VisitSExprASTN(astn->getSExpr(i));
		_level--;
		SPLExprOp op = astn->getOp(i);
		if (op == _GE) println("ExprOp : >=", false);
		if (op == _GT) println("ExprOp : > ", false);
		if (op == _LE) println("ExprOp : <=", false);
		if (op == _LT) println("ExprOp : < ", false);
		if (op == _EQUAL) println("ExprOp : ==", false);
		if (op == _UNEQUAL) println("ExprOp : !=", false);
		if (op == _ERROREXPROP) println("ExprOp : TypeErr = 0", false);
		_level++;
	}
	_isLastChild[_level - 1] = true;
	VisitSExprASTN(astn->getSExpr(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitSExprASTN(SPLAST::SExprASTN * astn)
{
	if (astn == nullptr) {
		println("SExprASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getTermNum();
	println("SExprASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitTermASTN(astn->getTerm(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
	{
		VisitTermASTN(astn->getTerm(i));
		_level--;
		SPLSExprOp op = astn->getOp(i);
		if (op == _PLUS) println("SExprOp : +", false);
		if (op == _MINUS) println("SExprOp : -", false);
		if (op == _OR) println("SExprOp : ||", false);
		if (op == _ERRORSEXPROP) println("SExprOp : TypeErr = 0", false);
		_level++;
	}
	_isLastChild[_level - 1] = true;
	VisitTermASTN(astn->getTerm(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitTermASTN(SPLAST::TermASTN * astn)
{
	if (astn == nullptr) {
		println("TermASTN : Nullptr Err!");
		return;
	}
	size_t size = astn->getFactorNum();
	println("TermASTN : size = " + std::to_string(size));
	if (size == 0) return;
	if (size == 1) {
		_isLastChild.push_back(true);
		_level++;
		VisitFactorASTN(astn->getFactor(0));
		_isLastChild.pop_back();
		_level--;
		return;
	}
	_isLastChild.push_back(false);
	_level++;
	for (int i = 0; i <= size - 2; i++)
	{
		VisitFactorASTN(astn->getFactor(i));
		_level--;
		SPLTermOp op = astn->getOp(i);
		if (op == _MUL) println("TermOp : *", false);
		if (op == _DIV) println("TermOp : /", false);
		if (op == _INTDIV) println("TermOp : //", false);
		if (op == _MOD) println("TermOp : %", false);
		if (op == _AND) println("TermOp : &&", false);
		if (op == _ERRORTERMOP) println("TermOp : TypeErr = 0", false);
		_level++;
	}
	_isLastChild[_level - 1] = true;
	VisitFactorASTN(astn->getFactor(size - 1));
	_isLastChild.pop_back();
	_level--;
	return;
}

void Visitor::VisitFactorASTN(SPLAST::FactorASTN * astn)
{
	if (astn == nullptr) {
		println("FactorASTN : Nullptr Err!");
		return;
	}
	SPLFactorType factorType = astn->getFactorType();
	if (factorType == _USERVAL)
	{
		println("FactorASTN : User Value : " + astn->getName());
		return;
	}
	if (factorType == _RET)
	{
		SPLFuncType funType = astn->getFuncType();
		if (funType == _USERFUNC)
		{
			println("FactorASTN : User Func : " + astn->getName() + ", Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _ABS)
		{
			println("FactorASTN : Func : ABS, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _CHR)
		{
			println("FactorASTN : Func : CHR, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _ODD)
		{
			println("FactorASTN : Func : ODD, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _ORD)
		{
			println("FactorASTN : Func : ORD, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _PRED)
		{
			println("FactorASTN : Func : PRED, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _SQR)
		{
			println("FactorASTN : Func : SQR, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _SQRT)
		{
			println("FactorASTN : Func : SQRT, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		if (funType == _SUCC)
		{
			println("FactorASTN : Func : SUCC, Args = ");
			VisitExprListASTN(astn->getArgsList());
			return;
		}
		println("FactorASTN : TypeErr = " + std::to_string(funType));
		return;
	}
	if (factorType == _SYSFUNCT)
	{
		SPLFuncType funType = astn->getFuncType();
		if (funType == _ERRORFUNC) println("FactorASTN : TypeErr = 0");
		if (funType == _USERFUNC) println("FactorASTN : TypeErr = 1");
		if (funType == _ABS) println("FactorASTN : SYSFUNCT : ABS");
		if (funType == _CHR) println("FactorASTN : SYSFUNCT : CHR");
		if (funType == _ODD) println("FactorASTN : SYSFUNCT : ODD");
		if (funType == _ORD) println("FactorASTN : SYSFUNCT : ORD");
		if (funType == _PRED) println("FactorASTN : SYSFUNCT : PRED");
		if (funType == _SQR) println("FactorASTN : SYSFUNCT : SQR");
		if (funType == _SQRT) println("FactorASTN : SYSFUNCT : SQRT");
		if (funType == _SUCC) println("FactorASTN : SYSFUNCT : SUCC");
		return;
	}
	if (factorType == _CONST)
	{
		println("FactorASTN : ConstVal");
		_isLastChild.push_back(true);
		_level++;
		VisitConstValueASTN(astn->getConstVal());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (factorType == _EXPR)
	{
		println("FactorASTN : Expr");
		_isLastChild.push_back(true);
		_level++;
		VisitExprASTN(astn->getExpr());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (factorType == _NOT)
	{
		println("FactorASTN : NOT");
		_isLastChild.push_back(true);
		_level++;
		VisitFactorASTN(astn->getFactor());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (factorType == _NEG)
	{
		println("FactorASTN : NEG");
		_isLastChild.push_back(true);
		_level++;
		VisitFactorASTN(astn->getFactor());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (factorType == _INDEX)
	{
		println("FactorASTN : Array " + astn->getName() + ", Index = ");
		_isLastChild.push_back(true);
		_level++;
		VisitExprASTN(astn->getExpr());
		_isLastChild.pop_back();
		_level--;
		return;
	}
	if (factorType == _MEMBER)
	{
		println("FactorASTN : Class " + astn->getName() + "." + astn->getMemName());
		return;
	}
	println("FactorASTN : TypeErr = " + std::to_string(factorType));
	return;
}
