#include "splast.h"

SPLAST::ProgramASTN::ProgramASTN(ProgramHeadASTN * programHeadASTN, RoutineASTN * routineASTN) : _programHeadASTN(programHeadASTN), _routineASTN(routineASTN)
{
}

SPLAST::ProgramHeadASTN * SPLAST::ProgramASTN::getProgramHeadASTN() const
{
	return _programHeadASTN;
}

SPLAST::RoutineASTN * SPLAST::ProgramASTN::getRoutineASTN() const
{
	return _routineASTN;
}

SPLAST::NameASTN::NameASTN(std::string name) : _name(name)
{
}

const std::string SPLAST::NameASTN::getName()
{
	return _name;
}

SPLAST::RoutineASTN::RoutineASTN(RoutineHeadASTN * routineHeadASTN, RoutineBodyASTN * routineBodyASTN) : _routineHeadASTN(routineHeadASTN), _routineBodyASTN(routineBodyASTN)
{
}

SPLAST::RoutineHeadASTN * SPLAST::RoutineASTN::getRoutineHeadASTN() const
{
	return _routineHeadASTN;
}

SPLAST::RoutineBodyASTN * SPLAST::RoutineASTN::getRoutineBodyASTN() const
{
	return _routineBodyASTN;
}

SPLAST::RoutineHeadASTN::RoutineHeadASTN(ConstPartASTN * constPartASTN, TypePartASTN * typePartASTN, VarPartASTN * varPartASTN, RoutinePartASTN * routinePartASTN) :
	_constPartASTN(constPartASTN), _typePartASTN(typePartASTN), _varPartASTN(varPartASTN), _routinePartASTN(routinePartASTN)
{
}

SPLAST::ConstPartASTN * SPLAST::RoutineHeadASTN::getConstPartASTN() const
{
	return _constPartASTN;
}

SPLAST::TypePartASTN * SPLAST::RoutineHeadASTN::getTypePartASTN() const
{
	return _typePartASTN;
}

SPLAST::VarPartASTN * SPLAST::RoutineHeadASTN::getVarPartASTN() const
{
	return _varPartASTN;
}

SPLAST::RoutinePartASTN * SPLAST::RoutineHeadASTN::getRoutinePartASTN() const
{
	return _routinePartASTN;
}

SPLAST::ConstPartASTN::ConstPartASTN()
{
}

SPLAST::ConstPartASTN::ConstPartASTN(ConstPartASTN * constPart) : _constExprList(constPart->getConstExprList())
{
}

SPLAST::ConstPartASTN::ConstPartASTN(ConstPartASTN * constPart, ConstExprASTN * constExpr) : _constExprList(constPart->getConstExprList())
{
	_constExprList.push_back(constExpr);
}

SPLAST::ConstPartASTN::ConstPartASTN(ConstExprASTN * constExpr)
{
	_constExprList.push_back(constExpr);
}

size_t SPLAST::ConstPartASTN::getConstExprNum() const
{
	return _constExprList.size();
}

std::vector<SPLAST::ConstExprASTN*> SPLAST::ConstPartASTN::getConstExprList() const
{
	return _constExprList;
}

SPLAST::ConstExprASTN * SPLAST::ConstPartASTN::getConstExpr(size_t idx) const
{
	return _constExprList.at(idx);
}

SPLAST::ConstExprASTN::ConstExprASTN(NameASTN * nameASTN, ConstValueASTN * constValueASTN) : _nameASTN(nameASTN), _constValueASTN(constValueASTN)
{
}

SPLAST::NameASTN * SPLAST::ConstExprASTN::getNameASTN() const
{
	return _nameASTN;
}

SPLAST::ConstValueASTN * SPLAST::ConstExprASTN::getConstValueASTN() const
{
	return _constValueASTN;
}

SPLAST::ConstValueASTN::ConstValueASTN(int value) : _type(_INT), _intValue(value)
{
}

SPLAST::ConstValueASTN::ConstValueASTN(char value) : _type(_CHAR), _charValue(value)
{
}

SPLAST::ConstValueASTN::ConstValueASTN(bool value) : _type(_BOOL), _boolValue(value)
{
}

SPLAST::ConstValueASTN::ConstValueASTN(double value) : _type(_DOUBLE), _doubleValue(value)
{
}

SPLVarType SPLAST::ConstValueASTN::getType() const
{
	return _type;
}

void * SPLAST::ConstValueASTN::getValue() const
{
	if (_type == _INT) return (void*)&_intValue;
	if (_type == _CHAR) return (void*)&_charValue;
	if (_type == _BOOL) return (void*)&_boolValue;
	if (_type == _DOUBLE) return (void*)&_doubleValue;
	return nullptr;
}

SPLAST::TypePartASTN::TypePartASTN()
{
}

SPLAST::TypePartASTN::TypePartASTN(TypePartASTN * typePartASTN) : _typeDefList(typePartASTN->getTypeDefList())
{
}

SPLAST::TypePartASTN::TypePartASTN(TypeDefASTN * typeDefASTN)
{
	_typeDefList.push_back(typeDefASTN);
}

SPLAST::TypePartASTN::TypePartASTN(TypePartASTN * typePartASTN, TypeDefASTN * typeDefASTN) : _typeDefList(typePartASTN->getTypeDefList())
{
	_typeDefList.push_back(typeDefASTN);
}

size_t SPLAST::TypePartASTN::getTypeDefNum() const
{
	return _typeDefList.size();
}

std::vector<SPLAST::TypeDefASTN*> SPLAST::TypePartASTN::getTypeDefList() const
{
	return _typeDefList;
}

SPLAST::TypeDefASTN * SPLAST::TypePartASTN::getTypeDef(size_t idx) const
{
	return _typeDefList.at(idx);
}

SPLAST::TypeDeclASTN::TypeDeclASTN(TypeDeclASTN * typeDefASTN) :
	_type(typeDefASTN->getType()), _userType(typeDefASTN->getUserType()),
	_rangeStartName(typeDefASTN->getRangeStartName()), _rangeEndName(typeDefASTN->getRangeEndName()),
	_rangeStartVal(typeDefASTN->getRangeStartVal()), _rangeEndVal(typeDefASTN->getRangeEndVal()),
	_enumType(typeDefASTN->getEnumType()), _arrayRange(typeDefASTN->getArrayRange()),
	_arrayType(typeDefASTN->getArrayType()), _fieldListASTN(typeDefASTN->getFieldListASTN())

{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(SPLVarType type) : _type(type)
{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(std::string userType) : _type(_USERTYPE), _userType(userType)
{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(std::vector<std::string> enumType) : _type(_ENUM), _enumType(enumType)
{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(ConstValueASTN * rangeStartVal, ConstValueASTN * rangeEndVal) : _type(_RANGE),
	_rangeStartVal(rangeStartVal), _rangeEndVal(rangeEndVal)
{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(std::string rangeStartName, std::string rangeEndName) : _type(_RANGE),
	_rangeStartName(rangeStartName), _rangeEndName(rangeEndName)
{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(TypeDeclASTN * arrayRange, TypeDeclASTN * arrayType) : _type(_ARRAY),
	_arrayRange(arrayRange), _arrayType(arrayType)
{
}

SPLAST::TypeDeclASTN::TypeDeclASTN(FieldListASTN * fieldListASTN) : _type(_RECORD),
	_fieldListASTN(fieldListASTN)
{
}

SPLVarType SPLAST::TypeDeclASTN::getType() const
{
	return _type;
}

std::string SPLAST::TypeDeclASTN::getUserType() const
{
	return _userType;
}

std::string SPLAST::TypeDeclASTN::getRangeStartName() const
{
	return _rangeStartName;
}

std::string SPLAST::TypeDeclASTN::getRangeEndName() const
{
	return _rangeEndName;
}

SPLAST::ConstValueASTN * SPLAST::TypeDeclASTN::getRangeStartVal() const
{
	return _rangeStartVal;
}

SPLAST::ConstValueASTN * SPLAST::TypeDeclASTN::getRangeEndVal() const
{
	return _rangeEndVal;
}

std::vector<std::string> SPLAST::TypeDeclASTN::getEnumType() const
{
	return _enumType;
}

SPLAST::TypeDeclASTN * SPLAST::TypeDeclASTN::getArrayRange() const
{
	return _arrayRange;
}

SPLAST::TypeDeclASTN * SPLAST::TypeDeclASTN::getArrayType() const
{
	return _arrayType;
}

SPLAST::FieldListASTN * SPLAST::TypeDeclASTN::getFieldListASTN() const
{
	return _fieldListASTN;
}

SPLAST::FieldListASTN::FieldListASTN(FieldDeclASTN * fieldDeclASTN)
{
	_fieldDeclList.push_back(fieldDeclASTN);
}

SPLAST::FieldListASTN::FieldListASTN(FieldListASTN * fieldListASTN, FieldDeclASTN * fieldDeclASTN) : _fieldDeclList(fieldListASTN->getFieldDeclList())
{
	_fieldDeclList.push_back(fieldDeclASTN);
}

size_t SPLAST::FieldListASTN::getFieldDeclNum() const
{
	return _fieldDeclList.size();
}

std::vector<SPLAST::FieldDeclASTN*> SPLAST::FieldListASTN::getFieldDeclList() const
{
	return _fieldDeclList;
}

SPLAST::FieldDeclASTN * SPLAST::FieldListASTN::getFieldDecl(size_t idx) const
{
	return _fieldDeclList.at(idx);
}

SPLAST::NameListASTN::NameListASTN(NameListASTN * nameListASTN, NameASTN * name) : _nameList(nameListASTN->getNameList())
{
	_nameList.push_back(name->getName());
}

SPLAST::NameListASTN::NameListASTN(NameASTN * name)
{
	_nameList.push_back(name->getName());
}

size_t SPLAST::NameListASTN::getNameNum() const
{
	return _nameList.size();
}

std::vector<std::string> SPLAST::NameListASTN::getNameList() const
{
	return _nameList;
}

std::string SPLAST::NameListASTN::getName(size_t idx) const
{
	return _nameList.at(idx);
}

SPLAST::TypeDefASTN::TypeDefASTN(std::string name, TypeDeclASTN * typeDeclASTN) : _name(name), _typeDeclASTN(typeDeclASTN)
{
}

std::string SPLAST::TypeDefASTN::getName() const
{
	return _name;
}

SPLAST::TypeDeclASTN * SPLAST::TypeDefASTN::getTypeDeclASTN() const
{
	return _typeDeclASTN;
}

SPLAST::FieldDeclASTN::FieldDeclASTN(NameListASTN * nameListASTN, TypeDeclASTN * typeDeclASTN) : _nameListASTN(nameListASTN) , _typeDeclASTN(typeDeclASTN)
{
}

SPLAST::NameListASTN * SPLAST::FieldDeclASTN::getNameListASTN() const
{
	return _nameListASTN;
}

SPLAST::TypeDeclASTN * SPLAST::FieldDeclASTN::getTypeDeclASTN() const
{
	return _typeDeclASTN;
}

SPLAST::VarPartASTN::VarPartASTN()
{
}

SPLAST::VarPartASTN::VarPartASTN(VarDeclASTN * varDeclASTN)
{
	_varDeclList.push_back(varDeclASTN);
}

SPLAST::VarPartASTN::VarPartASTN(VarPartASTN * varPartASTN, VarDeclASTN * varDeclASTN) : _varDeclList(varPartASTN->getVarDeclList())
{
	_varDeclList.push_back(varDeclASTN);
}

size_t SPLAST::VarPartASTN::getVarDeclNum() const
{
	return _varDeclList.size();
}

std::vector<SPLAST::VarDeclASTN*> SPLAST::VarPartASTN::getVarDeclList() const
{
	return _varDeclList;
}

SPLAST::VarDeclASTN * SPLAST::VarPartASTN::getVarDeclASTN(size_t idx) const
{
	return _varDeclList.at(idx);
}

SPLAST::VarDeclASTN::VarDeclASTN(NameListASTN * nameListASTN, TypeDeclASTN * typeDeclASTN) : _nameListASTN(nameListASTN), _typeDeclASTN(typeDeclASTN)
{
}

SPLAST::NameListASTN * SPLAST::VarDeclASTN::getNameListASTN() const
{
	return _nameListASTN;
}

SPLAST::TypeDeclASTN * SPLAST::VarDeclASTN::getTypeDeclASTN() const
{
	return _typeDeclASTN;
}

SPLAST::RoutinePartASTN::RoutinePartASTN()
{
}

SPLAST::RoutinePartASTN::RoutinePartASTN(RoutinePartASTN * routinePartASTN, FuncDeclASTN * funcDeclASTN) : 
	_funcDeclList(routinePartASTN->getFuncDeclList()), 
	_procDeclList(routinePartASTN->getProcDeclList()),
	_idxList(routinePartASTN->getIdxList())
{
	_funcDeclList.push_back(funcDeclASTN);
	_idxList.push_back(_funcDeclList.size());
}

SPLAST::RoutinePartASTN::RoutinePartASTN(RoutinePartASTN * routinePartASTN, ProcDeclASTN * procDeclASTN) :
	_funcDeclList(routinePartASTN->getFuncDeclList()),
	_procDeclList(routinePartASTN->getProcDeclList()),
	_idxList(routinePartASTN->getIdxList())
{
	_procDeclList.push_back(procDeclASTN);
	_idxList.push_back(-_procDeclList.size());
}

std::vector<SPLAST::FuncDeclASTN*> SPLAST::RoutinePartASTN::getFuncDeclList() const
{
	return _funcDeclList;
}

std::vector<SPLAST::ProcDeclASTN*> SPLAST::RoutinePartASTN::getProcDeclList() const
{
	return _procDeclList;
}

std::vector<int> SPLAST::RoutinePartASTN::getIdxList() const
{
	return _idxList;
}

size_t SPLAST::RoutinePartASTN::getFuncDeclNum() const
{
	return _funcDeclList.size();
}

size_t SPLAST::RoutinePartASTN::getProcDeclNum() const
{
	return _procDeclList.size();
}

size_t SPLAST::RoutinePartASTN::getTotalDeclNum() const
{
	return _funcDeclList.size() + _procDeclList.size();
}

int SPLAST::RoutinePartASTN::getIdx(size_t idx) const
{
	return _idxList.at(idx);
}

SPLAST::FuncDeclASTN * SPLAST::RoutinePartASTN::getFuncDecl(size_t idx) const
{
	return _funcDeclList.at(idx);
}

SPLAST::ProcDeclASTN * SPLAST::RoutinePartASTN::getProcDecl(size_t idx) const
{
	return _procDeclList.at(idx);
}

SPLAST::FunctionDeclASTN::FunctionDeclASTN(std::string name, ParaASTN * paraASTN, TypeDeclASTN * typeDeclASTN, RoutineASTN * subroutineASTN) : _name(name),
	_paraASTN(paraASTN), _typeDeclASTN(typeDeclASTN), _subroutineASTN(subroutineASTN)
{
}

std::string SPLAST::FunctionDeclASTN::getName() const
{
	return _name;
}

SPLAST::ParaASTN * SPLAST::FunctionDeclASTN::getParaASTN() const
{
	return _paraASTN;
}

SPLAST::TypeDeclASTN * SPLAST::FunctionDeclASTN::getTypeDeclASTN() const
{
	return _typeDeclASTN;
}

SPLAST::RoutineASTN * SPLAST::FunctionDeclASTN::getSubroutineASTN() const
{
	return _subroutineASTN;
}

SPLAST::ProcedureDeclASTN::ProcedureDeclASTN(std::string name, ParaASTN * paraASTN, RoutineASTN * subroutineASTN) : _name(name),
	_paraASTN(paraASTN), _subroutineASTN(subroutineASTN)
{
}

std::string SPLAST::ProcedureDeclASTN::getName() const
{
	return _name;
}

SPLAST::ParaASTN * SPLAST::ProcedureDeclASTN::getParaASTN() const
{
	return _paraASTN;
}

SPLAST::RoutineASTN * SPLAST::ProcedureDeclASTN::getSubroutineASTN() const
{
	return _subroutineASTN;
}

SPLAST::ParaASTN::ParaASTN()
{
}

SPLAST::ParaASTN::ParaASTN(ParaASTN * paraDeclListASTN) : _paraTypeList(paraDeclListASTN->getParaTypeList())
{

}

SPLAST::ParaASTN::ParaASTN(ParaASTN * paraDeclListASTN, ParaTypeListASTN * paraTypeListASTN) : _paraTypeList(paraDeclListASTN->getParaTypeList())
{
	_paraTypeList.push_back(paraTypeListASTN);
}

SPLAST::ParaASTN::ParaASTN(ParaTypeListASTN * paraTypeListASTN)
{
	_paraTypeList.push_back(paraTypeListASTN);
}

size_t SPLAST::ParaASTN::getParaTypeListNum() const
{
	return _paraTypeList.size();
}

std::vector<SPLAST::ParaTypeListASTN*> SPLAST::ParaASTN::getParaTypeList() const
{
	return _paraTypeList;
}

SPLAST::ParaTypeListASTN * SPLAST::ParaASTN::getParaTypeListASTN(size_t idx) const
{
	return _paraTypeList.at(idx);
}

SPLAST::ParaTypeListASTN::ParaTypeListASTN(NameListASTN * nameListASTN, TypeDeclASTN * typeDeclASTN, bool isVar) : _isVar(isVar),
	_nameListASTN(nameListASTN), _typeDeclASTN(typeDeclASTN)
{
}

bool SPLAST::ParaTypeListASTN::getIsVar() const
{
	return _isVar;
}

SPLAST::NameListASTN * SPLAST::ParaTypeListASTN::getNameListASTN() const
{
	return _nameListASTN;
}

SPLAST::TypeDeclASTN * SPLAST::ParaTypeListASTN::getTypeDeclASTN() const
{
	return _typeDeclASTN;
}

SPLAST::StmtListASTN::StmtListASTN(StmtListASTN * stmtListASTN) : _stmtList(stmtListASTN->getStmtList())
{
}

SPLAST::StmtListASTN::StmtListASTN(StmtListASTN * stmtListASTN, StmtASTN * stmtASTN) : _stmtList(stmtListASTN->getStmtList())
{
	_stmtList.push_back(stmtASTN);
}

size_t SPLAST::StmtListASTN::getStmtNum() const
{
	return _stmtList.size();
}

std::vector<SPLAST::StmtASTN*> SPLAST::StmtListASTN::getStmtList() const
{
	return _stmtList;
}

SPLAST::StmtASTN * SPLAST::StmtListASTN::getStmt(size_t idx) const
{
	return _stmtList.at(idx);
}

SPLAST::StmtASTN::StmtASTN(StmtASTN * stmtASTN, int label) : _label(label), _type(stmtASTN->getType()),
	_assignStmt(stmtASTN->getAssignStmt()),
	_procStmt(stmtASTN->getProcStmt()),
	_compoundStmt(stmtASTN->getCompoundStmt()),
	_ifStmt(stmtASTN->getIfStmt()),
	_repeatStmt(stmtASTN->getRepeatStmt()),
	_whileStmt(stmtASTN->getWhileStmt()),
	_forStmt(stmtASTN->getForStmt()),
	_caseStmt(stmtASTN->getCaseStmt()),
	_gotoStmt(stmtASTN->getGotoStmt())
{
}

SPLAST::StmtASTN::StmtASTN(AssignStmtASTN * assignStmt) : _type(_ASSIGN), _assignStmt(assignStmt)
{
}

SPLAST::StmtASTN::StmtASTN(ProcStmtASTN * procStmt) : _type(_PROC), _procStmt(procStmt)
{
}

SPLAST::StmtASTN::StmtASTN(StmtListASTN * compoundStmt) : _type(_COMPOUND), _compoundStmt(compoundStmt)
{
}

SPLAST::StmtASTN::StmtASTN(IfStmtASTN * ifStmt) : _type(_IF), _ifStmt(ifStmt)
{
}

SPLAST::StmtASTN::StmtASTN(RepeatStmtASTN * repeatStmt) : _type(_REPEAT), _repeatStmt(repeatStmt)
{
}

SPLAST::StmtASTN::StmtASTN(WhileStmtASTN * whileStmt) : _type(_WHILE), _whileStmt(whileStmt)
{
}

SPLAST::StmtASTN::StmtASTN(ForStmtASTN * forStmt) : _type(_FOR), _forStmt(forStmt)
{
}

SPLAST::StmtASTN::StmtASTN(CaseStmtASTN * caseStmt) : _type(_CASE), _caseStmt(caseStmt)
{
}

SPLAST::StmtASTN::StmtASTN(GotoStmtASTN * gotoStmt) : _type(_GOTO), _gotoStmt(gotoStmt)
{
}

int SPLAST::StmtASTN::getLabel() const
{
	return _label;
}

SPLStmtType SPLAST::StmtASTN::getType() const
{
	return _type;
}

SPLAST::AssignStmtASTN * SPLAST::StmtASTN::getAssignStmt() const
{
	return _assignStmt;
}

SPLAST::ProcStmtASTN * SPLAST::StmtASTN::getProcStmt() const
{
	return _procStmt;
}

SPLAST::StmtListASTN * SPLAST::StmtASTN::getCompoundStmt() const
{
	return _compoundStmt;
}

SPLAST::IfStmtASTN * SPLAST::StmtASTN::getIfStmt() const
{
	return _ifStmt;
}

SPLAST::RepeatStmtASTN * SPLAST::StmtASTN::getRepeatStmt() const
{
	return _repeatStmt;
}

SPLAST::WhileStmtASTN * SPLAST::StmtASTN::getWhileStmt() const
{
	return _whileStmt;
}

SPLAST::ForStmtASTN * SPLAST::StmtASTN::getForStmt() const
{
	return _forStmt;
}

SPLAST::CaseStmtASTN * SPLAST::StmtASTN::getCaseStmt() const
{
	return _caseStmt;
}

SPLAST::GotoStmtASTN * SPLAST::StmtASTN::getGotoStmt() const
{
	return _gotoStmt;
}

SPLAST::AssignStmtASTN::AssignStmtASTN(std::string name, ExprASTN * expr) : _type(_VARIABLE), _name(name), _expr(expr)
{
}

SPLAST::AssignStmtASTN::AssignStmtASTN(std::string name, ExprASTN * arrayIdx, ExprASTN * expr) :
	_type(_ARRAYIDX), _name(name), _arrayIdx(arrayIdx), _expr(expr)
{
}

SPLAST::AssignStmtASTN::AssignStmtASTN(std::string name, std::string memberName, ExprASTN * expr) : 
	_type(_CLASSMEM), _name(name), _memberName(memberName), _expr(expr)
{
}

SPLAssignType SPLAST::AssignStmtASTN::getType() const
{
	return _type;
}

std::string SPLAST::AssignStmtASTN::getName() const
{
	return _name;
}

std::string SPLAST::AssignStmtASTN::getMemName() const
{
	return _memberName;
}

SPLAST::ExprASTN * SPLAST::AssignStmtASTN::getExpr() const
{
	return _expr;
}

SPLAST::ExprASTN * SPLAST::AssignStmtASTN::getArrayIdx() const
{
	return _arrayIdx;
}

SPLAST::ProcStmtASTN::ProcStmtASTN(std::string name) : _type(_USERPROC), _funcName(name)
{
}

SPLAST::ProcStmtASTN::ProcStmtASTN(std::string name, ExprListASTN * argsList) :
	_type(_USERPROC), _funcName(name), _argsList(argsList)
{
}

SPLAST::ProcStmtASTN::ProcStmtASTN(SPLProcType type, ExprListASTN * argsList) : _type(type), _argsList(argsList)
{
}

SPLAST::ProcStmtASTN::ProcStmtASTN(FactorASTN * readArgs) : _type(_READ), _readArgs(readArgs)
{
}

SPLProcType SPLAST::ProcStmtASTN::getType() const
{
	return _type;
}

std::string SPLAST::ProcStmtASTN::getFuncName() const
{
	return _funcName;
}

SPLAST::ExprListASTN * SPLAST::ProcStmtASTN::getArgsList() const
{
	return _argsList;
}

SPLAST::FactorASTN * SPLAST::ProcStmtASTN::getReadArgs() const
{
	return _readArgs;
}

SPLAST::IfStmtASTN::IfStmtASTN(ExprASTN * condition, StmtASTN * stmt, ElseASTN * elseClause) :
	_condition(condition), _stmt(stmt), _elseClause(elseClause)
{
}

SPLAST::ExprASTN * SPLAST::IfStmtASTN::getCondition() const
{
	return _condition;
}

SPLAST::StmtASTN * SPLAST::IfStmtASTN::getStmt() const
{
	return _stmt;
}

SPLAST::ElseASTN * SPLAST::IfStmtASTN::getElseClause() const
{
	return _elseClause;
}

SPLAST::ElseASTN::ElseASTN() : _stmt(nullptr)
{
}

SPLAST::ElseASTN::ElseASTN(StmtASTN * stmt) : _stmt(stmt)
{
}

SPLAST::StmtASTN * SPLAST::ElseASTN::getStmt() const
{
	return _stmt;
}

SPLAST::RepeatStmtASTN::RepeatStmtASTN(StmtListASTN * stmtList, ExprASTN * condition) :
	_stmtList(stmtList), _condition(condition)
{
}

SPLAST::StmtListASTN * SPLAST::RepeatStmtASTN::getStmtList() const
{
	return _stmtList;
}

SPLAST::ExprASTN * SPLAST::RepeatStmtASTN::getCondition() const
{
	return _condition;
}

SPLAST::WhileStmtASTN::WhileStmtASTN(ExprASTN * condition, StmtASTN * stmt) :
	_condition(condition), _stmt(stmt)
{
}

SPLAST::ExprASTN * SPLAST::WhileStmtASTN::getCondition() const
{
	return _condition;
}

SPLAST::StmtASTN * SPLAST::WhileStmtASTN::getStmt() const
{
	return _stmt;
}

SPLAST::ForStmtASTN::ForStmtASTN(std::string name, ExprASTN * start, ExprASTN * end, bool dir) :
	_name(name), _start(start), _end(end), _dir(dir)
{
}

std::string SPLAST::ForStmtASTN::getName() const
{
	return _name;
}

SPLAST::ExprASTN * SPLAST::ForStmtASTN::getStart() const
{
	return _start;
}

SPLAST::ExprASTN * SPLAST::ForStmtASTN::getEnd() const
{
	return _end;
}

bool SPLAST::ForStmtASTN::getDir() const
{
	return _dir;
}

SPLAST::CaseStmtASTN::CaseStmtASTN(CaseExprASTN * caseExpr) : _condition(nullptr)
{
	_caseExprList.push_back(caseExpr);
}

SPLAST::CaseStmtASTN::CaseStmtASTN(CaseStmtASTN * caseStmt, CaseExprASTN * caseExpr) : _condition(nullptr),
	_caseExprList(caseStmt->getCaseExprList())
{
	_caseExprList.push_back(caseExpr);
}

SPLAST::CaseStmtASTN::CaseStmtASTN(ExprASTN * condition, CaseStmtASTN * caseStmt) : _condition(condition),
	_caseExprList(caseStmt->getCaseExprList())
{
}

SPLAST::ExprASTN * SPLAST::CaseStmtASTN::getCondition() const
{
	return _condition;
}

size_t SPLAST::CaseStmtASTN::getExprNum() const
{
	return _caseExprList.size();
}

std::vector<SPLAST::CaseExprASTN*> SPLAST::CaseStmtASTN::getCaseExprList() const
{
	return _caseExprList;
}

SPLAST::CaseExprASTN * SPLAST::CaseStmtASTN::getCaseExpr(size_t idx) const
{
	return _caseExprList.at(idx);
}

SPLAST::CaseExprASTN::CaseExprASTN(ConstValueASTN * constVal, StmtASTN * stmt) : _type(CASE_CONST),
	_constVal(constVal), _stmt(stmt)
{
}

SPLAST::CaseExprASTN::CaseExprASTN(std::string name, StmtASTN * stmt) : _type(CASE_VAR),
	_name(name), _stmt(stmt)
{
}

bool SPLAST::CaseExprASTN::getType() const
{
	return _type;
}

SPLAST::ConstValueASTN * SPLAST::CaseExprASTN::getConstVal() const
{
	return _constVal;
}

std::string SPLAST::CaseExprASTN::getName() const
{
	return _name;
}

SPLAST::StmtASTN * SPLAST::CaseExprASTN::getStmt() const
{
	return _stmt;
}

SPLAST::GotoStmtASTN::GotoStmtASTN(int val) : _val(val)
{
}

int SPLAST::GotoStmtASTN::getVal() const
{
	return _val;
}

SPLAST::ExprListASTN::ExprListASTN(ExprListASTN * exprList, ExprASTN * expr) : _exprList(exprList->getExprList())
{
	_exprList.push_back(expr);
}

SPLAST::ExprListASTN::ExprListASTN(ExprASTN * expr)
{
	_exprList.push_back(expr);
}

size_t SPLAST::ExprListASTN::getExprNum() const
{
	return _exprList.size();
}

std::vector<SPLAST::ExprASTN*> SPLAST::ExprListASTN::getExprList() const
{
	return _exprList;
}

SPLAST::ExprASTN * SPLAST::ExprListASTN::getExpr(size_t idx) const
{
	return _exprList.at(idx);
}

SPLAST::ExprASTN::ExprASTN(ExprASTN * expr, SPLExprOp op, SExprASTN * sexpr) :
	_sexprList(expr->getSExprList()), _opList(expr->getOpList())
{
	_sexprList.push_back(sexpr);
	_opList.push_back(op);
}

SPLAST::ExprASTN::ExprASTN(SExprASTN * sexpr)
{
	_sexprList.push_back(sexpr);
}

std::vector<SPLAST::SExprASTN*> SPLAST::ExprASTN::getSExprList() const
{
	return _sexprList;
}

std::vector<SPLExprOp> SPLAST::ExprASTN::getOpList() const
{
	return _opList;
}

size_t SPLAST::ExprASTN::getSExprNum() const
{
	return _sexprList.size();
}

SPLAST::SExprASTN * SPLAST::ExprASTN::getSExpr(size_t idx) const
{
	return _sexprList.at(idx);
}

SPLExprOp SPLAST::ExprASTN::getOp(size_t idx) const
{
	return _opList.at(idx);
}

SPLAST::SExprASTN::SExprASTN(SExprASTN * sexpr, SPLSExprOp op, TermASTN * term) :
	_termList(sexpr->getTermList()), _opList(sexpr->getOpList())
{
	_termList.push_back(term);
	_opList.push_back(op);
}

SPLAST::SExprASTN::SExprASTN(TermASTN * term)
{
	_termList.push_back(term);
}

std::vector<SPLAST::TermASTN*> SPLAST::SExprASTN::getTermList() const
{
	return _termList;
}

std::vector<SPLSExprOp> SPLAST::SExprASTN::getOpList() const
{
	return _opList;
}

size_t SPLAST::SExprASTN::getTermNum() const
{
	return _termList.size();
}

SPLAST::TermASTN * SPLAST::SExprASTN::getTerm(size_t idx) const
{
	return _termList.at(idx);
}

SPLSExprOp SPLAST::SExprASTN::getOp(size_t idx) const
{
	return _opList.at(idx);
}

SPLAST::TermASTN::TermASTN(TermASTN * term, SPLTermOp op, FactorASTN * factor) :
	_factorList(term->getFactorList()), _opList(term->getOpList())
{
	_factorList.push_back(factor);
	_opList.push_back(op);
}

SPLAST::TermASTN::TermASTN(FactorASTN * factor)
{
	_factorList.push_back(factor);
}

std::vector<SPLAST::FactorASTN*> SPLAST::TermASTN::getFactorList() const
{
	return _factorList;
}

std::vector<SPLTermOp> SPLAST::TermASTN::getOpList() const
{
	return _opList;
}

size_t SPLAST::TermASTN::getFactorNum() const
{
	return _factorList.size();
}

SPLAST::FactorASTN * SPLAST::TermASTN::getFactor(size_t idx) const
{
	return _factorList.at(idx);
}

SPLTermOp SPLAST::TermASTN::getOp(size_t idx) const
{
	return _opList.at(idx);
}

SPLAST::FactorASTN::FactorASTN(std::string name) : _name(name), _type(_USERTYPE), _factorType(_USERVAL)
{
}

SPLAST::FactorASTN::FactorASTN(std::string name, ExprListASTN * argsList) : _name(name), _type(_FUNCTION), 
	_funcType(_USERFUNC), _factorType(_RET), _argsList(argsList)
{
}

SPLAST::FactorASTN::FactorASTN(SPLFuncType funcType) : _type(_FUNCTION), _funcType(funcType), _factorType(_SYSFUNCT)
{
}

SPLAST::FactorASTN::FactorASTN(SPLFuncType funcType, ExprListASTN * argsList) : _type(_FUNCTION), _funcType(funcType), 
	_factorType(_RET), _argsList(_argsList)
{
}

SPLAST::FactorASTN::FactorASTN(ConstValueASTN * constVal) : _type(constVal->getType()),  _factorType(_CONST), 
	_constVal(constVal)
{
}

SPLAST::FactorASTN::FactorASTN(ExprASTN * expr) : _type(_USERTYPE), _factorType(_EXPR), _expr(expr)
{
}

SPLAST::FactorASTN::FactorASTN(FactorASTN * factor, SPLFactorType factorType) : _factor(factor), _factorType(factorType)
{
}

SPLAST::FactorASTN::FactorASTN(std::string name, ExprASTN * idx) : _type(_USERTYPE), _factorType(_INDEX), _name(name), _expr(idx)
{
}

SPLAST::FactorASTN::FactorASTN(std::string name, std::string memName) : _type(_USERTYPE), _factorType(_MEMBER), _name(name), _memName(memName)
{
}

SPLVarType SPLAST::FactorASTN::getType() const
{
	return _type;
}

SPLFuncType SPLAST::FactorASTN::getFuncType() const
{
	return _funcType;
}

SPLFactorType SPLAST::FactorASTN::getFactorType() const
{
	return _factorType;
}

std::string SPLAST::FactorASTN::getName() const
{
	return _name;
}

SPLAST::ExprListASTN * SPLAST::FactorASTN::getArgsList() const
{
	return _argsList;
}

SPLAST::ConstValueASTN * SPLAST::FactorASTN::getConstVal() const
{
	return _constVal;
}

SPLAST::ExprASTN * SPLAST::FactorASTN::getExpr() const
{
	return _expr;
}

std::string SPLAST::FactorASTN::getMemName() const
{
	return _memName;
}

SPLAST::FactorASTN * SPLAST::FactorASTN::getFactor() const
{
	return _factor;
}

SPLAST::ProgramHeadASTN::ProgramHeadASTN(NameASTN * nameASTN) : _name(nameASTN->getName())
{
}

std::string SPLAST::ProgramHeadASTN::getName() const
{
	return _name;
}
