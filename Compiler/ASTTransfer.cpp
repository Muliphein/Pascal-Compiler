#include "ASTTransfer.h"

ASTTransfer::ASTTransfer(SPLAST::ProgramASTN * program) : _program(new ASTNodes::ProgramNode()), _nodeptr(std::dynamic_pointer_cast<ASTNodes::BasicNode>(_program))
{
	TransferProgramASTN(program);
	return;
}

std::shared_ptr<ASTNodes::ProgramNode> ASTTransfer::getProgram() const
{
	return _program;
}

std::shared_ptr<ASTNodes::BasicNode> ASTTransfer::getNodeptr() const
{
	return _nodeptr;
}

std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> ASTTransfer::getVecptr() const
{
	return _vecptr;
}

std::string ASTTransfer::getProgramName() const
{
	return _programName;
}

void ASTTransfer::TransferProgramASTN(SPLAST::ProgramASTN * astn)
{
	printfTransferMsg("ProgramASTN", true);
	_programName = astn->getProgramHeadASTN()->getName();
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(_program->parts);
	TransferRoutineASTN(astn->getRoutineASTN());
	printfTransferMsg("ProgramASTN", false);
	return;
}

void ASTTransfer::TransferRoutineASTN(SPLAST::RoutineASTN * astn)
{
	printfTransferMsg("RoutineASTN", true);
	TransferRoutineHeadASTN(astn->getRoutineHeadASTN());

	std::shared_ptr<ASTNodes::FunctionNode> mainFunc(new ASTNodes::FunctionNode());
	std::shared_ptr<ASTNodes::FunDeclareNode> mainDecl(new ASTNodes::FunDeclareNode());
	std::shared_ptr<ASTNodes::FunctionBodyNode> mainBody(new ASTNodes::FunctionBodyNode());
	mainDecl->function_name = "main";
	mainDecl->ret_type_name = INT_TYPE;
	mainFunc->func_declare = mainDecl;
	mainFunc->func_body = mainBody;
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(mainFunc));

	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> temp = _vecptr;
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(mainBody->stmts);
	TransferStmtListASTN(astn->getRoutineBodyASTN());
	std::shared_ptr<ASTNodes::ReturnNode> ret(new ASTNodes::ReturnNode());
	_vecptr->push_back(ret);
	_vecptr = temp;
	printfTransferMsg("RoutineASTN", false);
	return;
}

void ASTTransfer::TransferRoutineHeadASTN(SPLAST::RoutineHeadASTN * astn)
{
	printfTransferMsg("RoutineHeadASTN", true);
	TransferConstPartASTN(astn->getConstPartASTN());
	TransferTypePartASTN(astn->getTypePartASTN());
	TransferVarPartASTN(astn->getVarPartASTN());
	TransferRoutinePartASTN(astn->getRoutinePartASTN());
	printfTransferMsg("RoutineHeadASTN", false);
	return;
}

void ASTTransfer::TransferConstPartASTN(SPLAST::ConstPartASTN * astn)
{
	printfTransferMsg("ConstPartASTN", true);
	size_t exprNum = astn->getConstExprNum();
	if (exprNum == 0) {
		printfTransferMsg("ConstPartASTN", false);
		return;
	}
	for (int i = 0; i <= exprNum - 1; i++)
		TransferConstExprASTN(astn->getConstExpr(i));
	printfTransferMsg("ConstPartASTN", false);
	return;
}

void ASTTransfer::TransferConstExprASTN(SPLAST::ConstExprASTN * astn)
{
	printfTransferMsg("ConstExprASTN", true);
	std::string name = astn->getName();
	SPLVarType type = astn->getConstValueASTN()->getType();
	std::shared_ptr<ASTNodes::VariableDefineNode> varDef(new ASTNodes::VariableDefineNode("ERROR",false,0,name));
	if (type == _INT) varDef->type = INT_TYPE;
	if (type == _BOOL) varDef->type = BOOL_TYPE;
	if (type == _CHAR) varDef->type = CHAR_TYPE;
	if (type == _DOUBLE) varDef->type = DOUBLE_TYPE;
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(varDef));

	std::shared_ptr<ASTNodes::AssignNode> varAss(new ASTNodes::AssignNode());
	std::shared_ptr<ASTNodes::VarBaseNode> lhs(new ASTNodes::VarBaseNode(name, nullptr, nullptr));
	varAss->LHS = lhs;
	varAss->RHS = std::dynamic_pointer_cast<ASTNodes::BasicNode>(TransferConstValueASTN(astn->getConstValueASTN()));
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(varAss));
	printfTransferMsg("ConstExprASTN", false);
	return;
}

std::shared_ptr<ASTNodes::ConstantNode> ASTTransfer::TransferConstValueASTN(SPLAST::ConstValueASTN * astn)
{
	printfTransferMsg("ConstValueASTN", true);
	std::shared_ptr<ASTNodes::ConstantNode> constptr(new ASTNodes::ConstantNode());
	SPLVarType type = astn->getType();
	if (type == _INT) constptr->constant_type = IntType;
	if (type == _BOOL) constptr->constant_type = BoolType;
	if (type == _CHAR) constptr->constant_type = CharType;
	if (type == _DOUBLE) constptr->constant_type = RealType;
	constptr->constant_value = (Value*)(astn->getValue());
	printfTransferMsg("ConstValueASTN", false);
	return constptr;
}

void ASTTransfer::TransferTypePartASTN(SPLAST::TypePartASTN * astn)
{
	printfTransferMsg("TypePartASTN", true);
	size_t defNum = astn->getTypeDefNum();
	if (defNum == 0) {
		printfTransferMsg("TypePartASTN", false);
		return;
	}
	for (int i = 0; i <= defNum - 1; i++)
		TransferTypeDefASTN(astn->getTypeDef(i));
	printfTransferMsg("TypePartASTN", false);
	return;
}

void ASTTransfer::TransferTypeDefASTN(SPLAST::TypeDefASTN * astn)
{
	printfTransferMsg("TypeDefASTN", true);
	SPLVarType type = astn->getTypeDeclASTN()->getType();
	if (type != _RECORD) {
		std::cout << "Undefined Behavior : Defining illegal type! Err = " << type << std::endl;
		return;
	}
	std::string name = astn->getName();
	std::shared_ptr<ASTNodes::RecordTypeDefineNode> recDef(new ASTNodes::RecordTypeDefineNode());
	recDef->record_name = name;
	std::shared_ptr<ASTNodes::BasicNode> temp = _nodeptr;
	_nodeptr = std::dynamic_pointer_cast<ASTNodes::BasicNode>(recDef);
	TransferFieldListASTN(astn->getTypeDeclASTN()->getFieldListASTN());
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(recDef));
	_nodeptr = temp;
	printfTransferMsg("TypeDefASTN", false);
	return;
}

void ASTTransfer::TransferFieldListASTN(SPLAST::FieldListASTN * astn)
{
	printfTransferMsg("FieldListASTN", true);
	size_t declNum = astn->getFieldDeclNum();
	if (declNum == 0) {
		printfTransferMsg("FieldListASTN", false);
		return;
	}
	for (int i = 0; i <= declNum - 1; i++)
		TransferFieldDeclASTN(astn->getFieldDecl(i));
	printfTransferMsg("FieldListASTN", false);
	return;
}

void ASTTransfer::TransferFieldDeclASTN(SPLAST::FieldDeclASTN * astn)
{
	printfTransferMsg("FieldDeclASTN", true);
	std::shared_ptr<ASTNodes::RecordTypeDefineNode> recDef(std::dynamic_pointer_cast<ASTNodes::RecordTypeDefineNode>(_nodeptr));
	std::vector<std::string> nameList = astn->getNameListASTN()->getNameList();
	SPLVarType type = astn->getTypeDeclASTN()->getType();
	std::string typeName = "";
	bool isArray = false;
	int arrLen = 0;
	int arrLower = 0;
	
	SPLAST::TypeDeclASTN* arrRange;
	SPLAST::TypeDeclASTN* arrType;

	switch (type)
	{
	case _ERRORVAR:
		std::cout << "Undefined Behavior : ERROR Record member type! Err = 0\n";
		return;
		break;
	case _USERTYPE:
		typeName = astn->getTypeDeclASTN()->getUserType();
		break;
	case _BOOL:
		typeName = BOOL_TYPE;
		break;
	case _CHAR:
		typeName = CHAR_TYPE;
		break;
	case _INT:
		typeName = INT_TYPE;
		break;
	case _DOUBLE:
		typeName = DOUBLE_TYPE;
		break;
	case _ENUM:
		std::cout << "Undefined Behavior : Defining nested enumtype as record member!\n";
		return;
		break;
	case _RANGE:
		std::cout << "Undefined Behavior : Defining range as record member!\n";
		return;
		break;
	case _ARRAY:
		arrRange = astn->getTypeDeclASTN()->getArrayRange();
		arrType = astn->getTypeDeclASTN()->getArrayType();
		if (arrRange->getType() != _RANGE) {
			std::cout << "Undefined Behavior : Illegal array range ! Err = " << arrRange->getType() << std::endl;
			return;
		}
		if (arrRange->getRangeStartVal() == nullptr) {
			// limited function
			std::cout << "Undefined Behavior : Illegal array range : Variable as Length!\n";
			return;
		}
		isArray = true;
		arrLen = getArrLength(arrRange);
		if (arrLen <= 0) {
			std::cout << "Array Length Error : Err = " << arrLen << std::endl;
			return;
		}
		arrLower = getArrBase(arrRange);
		if (arrLower == INT_MIN) {
			std::cout << "Array Base Error!\n";
			return;
		}
		typeName = getArrType(arrType);
		if (typeName == ERROR_TYPE) {
			std::cout << "Array Type Error!\n";
			return;
		}
		break;
	case _RECORD:
		std::cout << "Undefined Behavior : Defining nested record as record member!\n";
		return;
		break;
	case _FUNCTION:
		std::cout << "Undefined Behavior : Defining function as record member!\n";
		return;
		break;
	case _PROCEDURE:
		std::cout << "Undefined Behavior : Defining procedure as record member!\n";
		return;
		break;
	default:
		std::cout << "Undefined Behavior : ERROR Record member type! Err = " << type << std::endl;
		return;
		break;
	}

	size_t num = nameList.size();
	if (num == 0) {
		printfTransferMsg("FieldDeclASTN", false);
		return;
	}
	for (int i = 0; i <= num - 1; i++) {
		recDef->member_var_name.push_back(nameList.at(i));
		recDef->member_type_name.push_back(typeName);
		recDef->mem_is_array.push_back(isArray);
		recDef->mem_array_length.push_back(arrLen);
		recDef->mem_array_lower.push_back(arrLower);
	}
	printfTransferMsg("FieldDeclASTN", false);
	return;
}

void ASTTransfer::TransferVarPartASTN(SPLAST::VarPartASTN * astn)
{
	printfTransferMsg("VarPartASTN", true);
	size_t declNum = astn->getVarDeclNum();
	if (declNum == 0) {
		printfTransferMsg("VarPartASTN", false);
		return;
	}
	for (int i = 0; i <= declNum - 1; i++)
		TransferVarDeclASTN(astn->getVarDeclASTN(i));
	printfTransferMsg("VarPartASTN", false);
	return;
}

void ASTTransfer::TransferVarDeclASTN(SPLAST::VarDeclASTN * astn)
{
	printfTransferMsg("VarDeclASTN", true);
	std::vector<std::string> nameList = astn->getNameListASTN()->getNameList();
	SPLVarType type = astn->getTypeDeclASTN()->getType();
	std::string typeName = "";
	bool isArray = false;
	int arrLen = 0;
	int arrLower = 0;
	
	SPLAST::TypeDeclASTN* arrRange;
	SPLAST::TypeDeclASTN* arrType;

	switch (type)
	{
	case _ERRORVAR:
		std::cout << "Undefined Behavior : ERROR var type! Err = 0\n";
		return;
		break;
	case _USERTYPE:
		typeName = astn->getTypeDeclASTN()->getUserType();
		break;
	case _BOOL:
		typeName = BOOL_TYPE;
		break;
	case _CHAR:
		typeName = CHAR_TYPE;
		break;
	case _INT:
		typeName = INT_TYPE;
		break;
	case _DOUBLE:
		typeName = DOUBLE_TYPE;
		break;
	case _ENUM:
		std::cout << "Undefined Behavior : Defining enumtype as var!\n";
		return;
		break;
	case _RANGE:
		std::cout << "Undefined Behavior : Defining range as var!\n";
		return;
		break;
	case _ARRAY:
		arrRange = astn->getTypeDeclASTN()->getArrayRange();
		arrType = astn->getTypeDeclASTN()->getArrayType();
		if (arrRange->getType() != _RANGE) {
			std::cout << "Undefined Behavior : Illegal array range ! Err = " << arrRange->getType() << std::endl;
			return;
		}
		if (arrRange->getRangeStartVal() == nullptr) {
			// limited function
			std::cout << "Undefined Behavior : Illegal array range : Variable as Length!\n";
			return;
		}
		isArray = true;
		arrLen = getArrLength(arrRange);
		if (arrLen <= 0) {
			std::cout << "Array Length Error : Err = " << arrLen << std::endl;
			return;
		}
		arrLower = getArrBase(arrRange);
		if (arrLower == INT_MIN) {
			std::cout << "Array Base Error!\n";
			return;
		}
		typeName = getArrType(arrType);
		if (typeName == ERROR_TYPE) {
			std::cout << "Array Type Error!\n";
			return;
		}
		break;
	case _RECORD:
		std::cout << "Undefined Behavior : Defining record as var!\n";
		return;
		break;
	case _FUNCTION:
		std::cout << "Undefined Behavior : Defining function as var!\n";
		return;
		break;
	case _PROCEDURE:
		std::cout << "Undefined Behavior : Defining procedure as var!\n";
		return;
		break;
	default:
		std::cout << "Undefined Behavior : ERROR var type! Err = " << type << std::endl;
		return;
		break;
	}

	size_t num = nameList.size();
	if (num == 0) {
		printfTransferMsg("VarDeclASTN", false);
		return;
	}
	for (int i = 0; i <= num - 1; i++) {
		std::shared_ptr<ASTNodes::VariableDefineNode> varDef(new ASTNodes::VariableDefineNode());
		varDef->name = nameList.at(i);
		varDef->type = typeName;
		varDef->is_array = isArray;
		varDef->array_length = arrLen;
		varDef->lower_bound = arrLower;
		_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(varDef));
	}
	printfTransferMsg("VarDeclASTN", false);
	return;
}

void ASTTransfer::TransferRoutinePartASTN(SPLAST::RoutinePartASTN * astn)
{
	printfTransferMsg("RoutinePartASTN", true);
	size_t declNum = astn->getTotalDeclNum();
	if (declNum == 0) {
		printfTransferMsg("RoutinePartASTN", false);
		return;
	}
	for (int i = 0; i <= declNum - 1; i++) {
		int idx = astn->getIdx(i);
		if (idx > 0) TransferFuncDeclASTN(astn->getFuncDecl(idx - 1));
		else TransferProcDeclASTN(astn->getProcDecl(1 - idx));
	}
	printfTransferMsg("RoutinePartASTN", false);
	return;
}

void ASTTransfer::TransferFuncDeclASTN(SPLAST::FuncDeclASTN * astn)
{
	printfTransferMsg("FuncDeclASTN", true);
	std::shared_ptr<ASTNodes::FunctionNode> func(new ASTNodes::FunctionNode());
	std::shared_ptr<ASTNodes::FunDeclareNode> funcDecl(new ASTNodes::FunDeclareNode());
	std::shared_ptr<ASTNodes::FunctionBodyNode> funcBody(new ASTNodes::FunctionBodyNode());
	func->func_declare = funcDecl;
	func->func_body = funcBody;
	funcDecl->function_name = astn->getName();
	funcDecl->ret_type_name = getTypeName(astn->getTypeDeclASTN());
	if (funcDecl->ret_type_name == ERROR_TYPE) {
		std::cout << "ERROR : Error function return type name!\n";
		return;
	}
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(func));
	// funcDecl
	std::shared_ptr<ASTNodes::BasicNode> temp = _nodeptr;
	_nodeptr = std::dynamic_pointer_cast<ASTNodes::BasicNode>(funcDecl);
	TransferParaASTN(astn->getParaASTN());
	_nodeptr = temp;
	// funcBody
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> tempvec = _vecptr;
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(funcBody->stmts);
	TransferRoutineHeadASTN(astn->getSubroutineASTN()->getRoutineHeadASTN());
	TransferStmtListASTN(astn->getSubroutineASTN()->getRoutineBodyASTN());
	std::shared_ptr<ASTNodes::ReturnNode> ret(new ASTNodes::ReturnNode());
	_vecptr->push_back(ret);
	_vecptr = tempvec;
	printfTransferMsg("FuncDeclASTN", false);
	return;
}

void ASTTransfer::TransferProcDeclASTN(SPLAST::ProcDeclASTN * astn)
{
	printfTransferMsg("ProcDeclASTN", true);
	std::shared_ptr<ASTNodes::FunctionNode> func(new ASTNodes::FunctionNode());
	std::shared_ptr<ASTNodes::FunDeclareNode> funcDecl(new ASTNodes::FunDeclareNode());
	std::shared_ptr<ASTNodes::FunctionBodyNode> funcBody(new ASTNodes::FunctionBodyNode());
	func->func_declare = funcDecl;
	func->func_body = funcBody;
	funcDecl->function_name = astn->getName();
	funcDecl->ret_type_name = VOID_TYPE;
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(func));
	// funcDecl
	std::shared_ptr<ASTNodes::BasicNode> temp = _nodeptr;
	_nodeptr = std::dynamic_pointer_cast<ASTNodes::BasicNode>(funcDecl);
	TransferParaASTN(astn->getParaASTN());
	_nodeptr = temp;
	// funcBody
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> tempvec = _vecptr;
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(funcBody->stmts);
	TransferRoutineHeadASTN(astn->getSubroutineASTN()->getRoutineHeadASTN());
	TransferStmtListASTN(astn->getSubroutineASTN()->getRoutineBodyASTN());
	std::shared_ptr<ASTNodes::ReturnNode> ret(new ASTNodes::ReturnNode());
	_vecptr->push_back(ret);
	_vecptr = tempvec;
	printfTransferMsg("ProcDeclASTN", false);
	return;
}

void ASTTransfer::TransferParaASTN(SPLAST::ParaASTN * astn)
{
	printfTransferMsg("ParaASTN", true);
	size_t paraNum = astn->getParaTypeListNum();
	if (paraNum == 0) {
		printfTransferMsg("ParaASTN", false);
		return;
	}
	for (int i = 0; i <= paraNum - 1; i++)
		TransferParaTypeListASTN(astn->getParaTypeListASTN(i));
	printfTransferMsg("ParaASTN", false);
	return;
}

void ASTTransfer::TransferParaTypeListASTN(SPLAST::ParaTypeListASTN * astn)
{
	printfTransferMsg("ParaTypeListASTN", true);
	bool isVar = astn->getIsVar();
	std::string typeName = getTypeName(astn->getTypeDeclASTN());
	if (typeName == ERROR_TYPE) {
		std::cout << "ERROR Parameter type!\n";
		return;
	}
	std::shared_ptr<ASTNodes::FunDeclareNode> funcDecl(std::dynamic_pointer_cast<ASTNodes::FunDeclareNode>(_nodeptr));
	size_t paraNum = astn->getNameListASTN()->getNameNum();
	if (paraNum == 0) {
		printfTransferMsg("ParaTypeListASTN", false);
		return;
	}
	for (int i = 0; i <= paraNum - 1; i++) {
		funcDecl->function_arg_var.push_back(isVar);
		funcDecl->function_arg_names.push_back(astn->getNameListASTN()->getName(i));
		funcDecl->function_arg_types_names.push_back(typeName);
	}
	printfTransferMsg("ParaTypeListASTN", false);
	return;
}

void ASTTransfer::TransferStmtListASTN(SPLAST::StmtListASTN * astn)
{
	printfTransferMsg("StmtListASTN", true);
	size_t stmtNum = astn->getStmtNum();
	if (stmtNum == 0) {
		printfTransferMsg("StmtASTN", false);
		return;
	}	
	for (int i = 0; i <= stmtNum - 1; i++)
		TransferStmtASTN(astn->getStmt(i));
	printfTransferMsg("StmtListASTN", false);
	return;
}

void ASTTransfer::TransferStmtASTN(SPLAST::StmtASTN * astn)
{
	printfTransferMsg("StmtASTN", true);
	std::shared_ptr<ASTNodes::StmtSeqNode> seq(new ASTNodes::StmtSeqNode());
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> temp;
	switch (astn->getType()) {
	case _ASSIGN:
		TransferAssignStmtASTN(astn->getAssignStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _PROC:
		TransferProcStmtASTN(astn->getProcStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _COMPOUND:
		_vecptr->push_back(seq);
		temp = _vecptr;
		_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(seq->stmts);
		TransferStmtListASTN(astn->getCompoundStmt());
		_vecptr = temp;
		printfTransferMsg("StmtASTN", false);
		return;
	case _IF:
		TransferIfStmtASTN(astn->getIfStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _REPEAT:
		TransferRepeatStmtASTN(astn->getRepeatStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _WHILE:
		TransferWhileStmtASTN(astn->getWhileStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _FOR:
		TransferForStmtASTN(astn->getForStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _CASE:
		TransferCaseStmtASTN(astn->getCaseStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _GOTO:
		TransferGotoStmtASTN(astn->getGotoStmt());
		printfTransferMsg("StmtASTN", false);
		return;
	case _ERRORSTMT:
	default:
		std::cout << "Error stmt type! Err = " << astn->getType() << std::endl;
		break;
	}
	printfTransferMsg("StmtASTN", false);
	return;
}

void ASTTransfer::TransferAssignStmtASTN(SPLAST::AssignStmtASTN * astn)
{
	printfTransferMsg("AssignStmtASTN", true);
	std::shared_ptr<ASTNodes::AssignNode> assign(new ASTNodes::AssignNode());
	assign->LHS = std::shared_ptr<ASTNodes::VarBaseNode>(new ASTNodes::VarBaseNode(astn->getName(), nullptr, nullptr));
	assign->RHS = TransferExprASTN(astn->getExpr());
	switch (astn->getType()) {
	case _VARIABLE:
		break;
	case _ARRAYIDX:
		assign->LHS->idx = TransferExprASTN(astn->getArrayIdx());
		break;
	case _CLASSMEM:
		assign->LHS->nested_var = std::shared_ptr<ASTNodes::VarAccessNode>(new ASTNodes::VarAccessNode());
		assign->LHS->nested_var->var_name = astn->getName();
		assign->LHS->nested_var->nested_var = nullptr;
		assign->LHS->nested_var->idx = nullptr;
		assign->LHS->var_name = astn->getMemName();
		break;
	default:
		std::cout << "Error Assign Type! Err = " << astn->getType() << std::endl;
	}
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(assign));
	printfTransferMsg("AssignStmtASTN", false);
	return;
}

void ASTTransfer::TransferProcStmtASTN(SPLAST::ProcStmtASTN * astn)
{
	printfTransferMsg("ProcStmtASTN", true);
	if (astn->getType() == _USERPROC) {
		std::shared_ptr<ASTNodes::FunctionCallNode> funcall(new ASTNodes::FunctionCallNode());
		funcall->func_name = astn->getProcName();
		if (astn->getArgsList() != nullptr) {
			std::shared_ptr<ASTNodes::BasicNode> temp = _nodeptr;
			_nodeptr = std::dynamic_pointer_cast<ASTNodes::BasicNode>(funcall);
			TransferExprListASTN(astn->getArgsList());
			_nodeptr = temp;
		}
		_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(funcall));
		printfTransferMsg("ProcStmtASTN", false);
		return;
	}
	if (astn->getType() == _WRITE) {
		std::shared_ptr<ASTNodes::SysWriteNode> syswrite(new ASTNodes::SysWriteNode());
		syswrite->has_newline = false;
		SPLAST::ExprListASTN* temp = astn->getArgsList();
		size_t exprNum = temp->getExprNum();
		if (exprNum == 0) {
			printfTransferMsg("ProcStmtASTN", false);
			return;
		}
		for (int i = 0; i <= exprNum - 1; i++) {
			syswrite->args.push_back(TransferExprASTN(temp->getExpr(i)));
		}
		_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(syswrite));
		printfTransferMsg("ProcStmtASTN", false);
		return;
	}
	if (astn->getType() == _WRITELN) {
		std::shared_ptr<ASTNodes::SysWriteNode> syswrite(new ASTNodes::SysWriteNode());
		syswrite->has_newline = true;
		SPLAST::ExprListASTN* temp = astn->getArgsList();
		size_t exprNum = temp->getExprNum();
		if (exprNum == 0) {
			printfTransferMsg("ProcStmtASTN", false);
			return;
		}
		for (int i = 0; i <= exprNum - 1; i++) {
			syswrite->args.push_back(TransferExprASTN(temp->getExpr(i)));
		}
		_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(syswrite));
		printfTransferMsg("ProcStmtASTN", false);
		return;
	}
	if (astn->getType() == _READ) {
		std::shared_ptr<ASTNodes::SysReadNode> sysread(new ASTNodes::SysReadNode());
		sysread->has_newline = false;
		sysread->args.push_back(std::dynamic_pointer_cast<ASTNodes::VarBaseNode>(TransferFactorASTN(astn->getReadArgs())));
		_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(sysread));
		printfTransferMsg("ProcStmtASTN", false);
		return;
	}
	std::cout << "Error Proc Stmt! Err = " << astn->getType() << std::endl;
	printfTransferMsg("ProcStmtASTN", false);
	return;
}

void ASTTransfer::TransferIfStmtASTN(SPLAST::IfStmtASTN * astn)
{
	printfTransferMsg("IfStmtASTN", true);
	std::shared_ptr<ASTNodes::IfElseNode> ifelse(new ASTNodes::IfElseNode());
	ifelse->cond = TransferExprASTN(astn->getCondition());
	ifelse->then_body = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::StmtSeqNode>(new ASTNodes::StmtSeqNode()));
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> temp = _vecptr;
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(std::dynamic_pointer_cast<ASTNodes::StmtSeqNode>(ifelse->then_body)->stmts);
	TransferStmtASTN(astn->getStmt());
	ifelse->else_body = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::StmtSeqNode>(new ASTNodes::StmtSeqNode()));
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(std::dynamic_pointer_cast<ASTNodes::StmtSeqNode>(ifelse->else_body)->stmts);
	TransferStmtASTN(astn->getElseClause()->getStmt());
	_vecptr = temp;
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(ifelse));
	printfTransferMsg("IfStmtASTN", false);
	return;
}

void ASTTransfer::TransferRepeatStmtASTN(SPLAST::RepeatStmtASTN * astn)
{
	printfTransferMsg("RepeatStmtASTN", true);
	std::shared_ptr<ASTNodes::RepeatNode> repeat(new ASTNodes::RepeatNode());
	repeat->is_start = false;
	repeat->reverse = true;
	repeat->rep_con = TransferExprASTN(astn->getCondition());
	repeat->rep_body_node = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::StmtSeqNode>(new ASTNodes::StmtSeqNode()));
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> temp = _vecptr;
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(std::dynamic_pointer_cast<ASTNodes::StmtSeqNode>(repeat->rep_body_node)->stmts);
	TransferStmtListASTN(astn->getStmtList());
	_vecptr = temp;
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(repeat));
	printfTransferMsg("RepeatStmtASTN", false);
	return;
}

void ASTTransfer::TransferWhileStmtASTN(SPLAST::WhileStmtASTN * astn)
{
	printfTransferMsg("WhileStmtASTN", true);
	std::shared_ptr<ASTNodes::RepeatNode> repeat(new ASTNodes::RepeatNode());
	repeat->is_start = true;
	repeat->reverse = false;
	repeat->rep_con = TransferExprASTN(astn->getCondition());
	repeat->rep_body_node = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::StmtSeqNode>(new ASTNodes::StmtSeqNode()));
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> temp = _vecptr;
	_vecptr = std::make_shared<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>(std::dynamic_pointer_cast<ASTNodes::StmtSeqNode>(repeat->rep_body_node)->stmts);
	TransferStmtASTN(astn->getStmt());
	_vecptr = temp;
	_vecptr->push_back(std::dynamic_pointer_cast<ASTNodes::BasicNode>(repeat));
	printfTransferMsg("WhileStmtASTN", false);
	return;
}

void ASTTransfer::TransferForStmtASTN(SPLAST::ForStmtASTN * astn)
{
	printfTransferMsg("ForStmtASTN", true);
	std::cout << "For Stmt : limited function.\n";
	printfTransferMsg("ForStmtASTN", false);
	return;
}

void printfTransferMsg(std::string nodename, bool isstart)
{
	if (transfertest) {
		if (isstart) std::cout << "Start Transferring " << nodename << std::endl;
		else std::cout << "Transaction of " << nodename << " Finished!" << std::endl;
	}
	return;
}

int getArrLength(SPLAST::TypeDeclASTN * arrRange)
{
	if (arrRange->getType() != _RANGE) {
		std::cout << "Caution [Caused by getArrLength()] : Calculating a non-range variable!\n";
		return -1;
	}
	if (arrRange->getRangeStartVal() == nullptr) {
		// limited function
		std::cout << "Caution [Caused by getArrLength()] : Array Range is a variable!\n";
		return -2;
	}
	SPLAST::ConstValueASTN* start = arrRange->getRangeStartVal();
	SPLAST::ConstValueASTN* end = arrRange->getRangeEndVal();
	if (start->getType() != end->getType()) {
		std::cout << "Caution [Caused by getArrLength()] : Array Range stands different type!\n";
		return -3;
	}
	switch (start->getType())
	{
	case _CHAR:
		return *(char*)(end->getValue()) - *(char*)(start->getValue()) + 1;
		break;
	case _INT:
		return *(int*)(end->getValue()) - *(int*)(start->getValue()) + 1;
		break;
	case _ERRORVAR:
	case _USERTYPE:
	case _BOOL:
	case _DOUBLE:
	case _ENUM:
	case _RANGE:
	case _ARRAY:
	case _RECORD:
	case _FUNCTION:
	case _PROCEDURE:
	default:
		std::cout << "Caution [Caused by getArrLength()] : Array Range type err = " << start->getType() << std::endl;
		return -4;
		break;
	}
}

int getArrBase(SPLAST::TypeDeclASTN * arrRange)
{
	if (arrRange->getType() != _RANGE) {
		std::cout << "Caution [Caused by getArrBase()] : Calculating a non-range variable!\n";
		return -1;
	}
	if (arrRange->getRangeStartVal() == nullptr) {
		// limited function
		std::cout << "Caution [Caused by getArrBase()] : Array Range is a variable!\n";
		return -2;
	}
	SPLAST::ConstValueASTN* start = arrRange->getRangeStartVal();
	SPLAST::ConstValueASTN* end = arrRange->getRangeEndVal();
	if (start->getType() != end->getType()) {
		std::cout << "Caution [Caused by getArrBase()] : Array Range stands different type!\n";
		return -3;
	}
	switch (start->getType())
	{
	case _CHAR:
		return *(char*)(start->getValue());
		break;
	case _INT:
		return *(int*)(start->getValue());
		break;
	case _ERRORVAR:
	case _USERTYPE:
	case _BOOL:
	case _DOUBLE:
	case _ENUM:
	case _RANGE:
	case _ARRAY:
	case _RECORD:
	case _FUNCTION:
	case _PROCEDURE:
	default:
		std::cout << "Caution [Caused by getArrBase()] : Array Range type err = " << start->getType() << std::endl;
		return INT_MIN;
		break;
	}
}

std::string getArrType(SPLAST::TypeDeclASTN * arrType)
{
	switch (arrType->getType())
	{
	case _USERTYPE:
		return arrType->getUserType();
	case _BOOL:
		return BOOL_TYPE;
	case _CHAR:
		return CHAR_TYPE;
	case _INT:
		return INT_TYPE;
	case _DOUBLE:
		return DOUBLE_TYPE;
	case _ENUM:
	case _RANGE:
	case _ARRAY:
	case _RECORD:
	case _FUNCTION:
	case _PROCEDURE:
	case _ERRORVAR:
	default:
		std::cout << "Caution [Caused by getArrType()] : Array type err = " << arrType->getType() << std::endl;
		return ERROR_TYPE;
	}
}

std::string getTypeName(SPLAST::TypeDeclASTN * typeDecl)
{
	switch (typeDecl->getType())
	{
	case _USERTYPE:
		return typeDecl->getUserType();
	case _BOOL:
		return BOOL_TYPE;
	case _CHAR:
		return CHAR_TYPE;
	case _INT:
		return INT_TYPE;
	case _DOUBLE:
		return DOUBLE_TYPE;
	case _ENUM:
	case _RANGE:
	case _ARRAY:
	case _RECORD:
	case _FUNCTION:
	case _PROCEDURE:
	case _ERRORVAR:
	default:
		std::cout << "Caution [Caused by getTypeName()] : Type err = " << typeDecl->getType() << std::endl;
		return ERROR_TYPE;
	}
}

void ASTTransfer::TransferCaseStmtASTN(SPLAST::CaseStmtASTN * astn)
{
	printfTransferMsg("CaseStmtASTN", true);
	std::cout << "Case Stmt : limited function.\n";
	printfTransferMsg("CaseStmtASTN", false);
	return;
}

void ASTTransfer::TransferGotoStmtASTN(SPLAST::GotoStmtASTN * astn)
{
	printfTransferMsg("GotoStmtASTN", true);
	std::cout << "Goto Stmt : limited function.\n";
	printfTransferMsg("GotoStmtASTN", false);
	return;
}

void ASTTransfer::TransferExprListASTN(SPLAST::ExprListASTN * astn)
{
	printfTransferMsg("ExprListASTN", true);
	std::shared_ptr<ASTNodes::FunctionCallNode> funcall = std::dynamic_pointer_cast<ASTNodes::FunctionCallNode>(_nodeptr);
	size_t exprNum = astn->getExprNum();
	if (exprNum == 0) {
		printfTransferMsg("ExprListASTN", false);
		return;
	}
	for (int i = 0; i <= exprNum - 1; i++)
		funcall->args.push_back(TransferExprASTN(astn->getExpr(i)));
	printfTransferMsg("ExprListASTN", false);
	return;
}

std::shared_ptr<ASTNodes::BasicNode> ASTTransfer::TransferExprASTN(SPLAST::ExprASTN * astn)
{
	printfTransferMsg("ExprASTN", true);
	if (astn->getSExprNum() == 1) return TransferSExprASTN(astn->getSExpr(0));
	std::shared_ptr<ASTNodes::BinaryExprNode> root(new ASTNodes::BinaryExprNode());
	std::shared_ptr<ASTNodes::BinaryExprNode> now = root;
	size_t sexprNum = astn->getSExprNum();
	if (sexprNum == 0) {
		printfTransferMsg("ExprASTN", false);
		return nullptr;
	}
	for (int i = 0; i <= sexprNum - 2; i++) {
		switch (astn->getOp(i)) {
		case _GE:
			now->expr_op = BinaryOper::GE;
			break;
		case _GT:
			now->expr_op = BinaryOper::GT;
			break;
		case _LE:
			now->expr_op = BinaryOper::LE;
			break;
		case _LT:
			now->expr_op = BinaryOper::LT;
			break;
		case _EQUAL:
			now->expr_op = BinaryOper::EQUAL;
			break;
		case _UNEQUAL:
			now->expr_op = BinaryOper::UNEQUAL;
			break;
		default:
			std::cout << "Error Expr op : err = " << astn->getOp(i) << std::endl;
		}
		now->LHS = TransferSExprASTN(astn->getSExpr(i));
		if (i == sexprNum - 2) now->RHS = TransferSExprASTN(astn->getSExpr(sexprNum - 1));
		else {
			now->RHS = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::BinaryExprNode>(new ASTNodes::BinaryExprNode()));
			now = std::dynamic_pointer_cast<ASTNodes::BinaryExprNode>(now->RHS);
		}
	}
	printfTransferMsg("ExprASTN", false);
	return std::dynamic_pointer_cast<ASTNodes::BasicNode>(root);
}

std::shared_ptr<ASTNodes::BasicNode> ASTTransfer::TransferSExprASTN(SPLAST::SExprASTN * astn)
{
	printfTransferMsg("SexprASTN", true);
	if (astn->getTermNum() == 1) return TransferTermASTN(astn->getTerm(0));
	std::shared_ptr<ASTNodes::BinaryExprNode> root(new ASTNodes::BinaryExprNode());
	std::shared_ptr<ASTNodes::BinaryExprNode> now = root;
	size_t termNum = astn->getTermNum();
	if (termNum == 0) {
		printfTransferMsg("SexprASTN", false);
		return nullptr;
	}
	for (int i = 0; i <= termNum - 2; i++) {
		switch (astn->getOp(i)) {
		case _PLUS:
			now->expr_op = BinaryOper::PLUS;
			break;
		case _MINUS:
			now->expr_op = BinaryOper::MINUS;
			break;
		case _OR:
			now->expr_op = BinaryOper::OR;
			break;
		default:
			std::cout << "Error Sexpr op : err = " << astn->getOp(i) << std::endl;
		}
		now->LHS = TransferTermASTN(astn->getTerm(i));
		if (i == termNum - 2) now->RHS = TransferTermASTN(astn->getTerm(termNum - 1));
		else {
			now->RHS = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::BinaryExprNode>(new ASTNodes::BinaryExprNode()));
			now = std::dynamic_pointer_cast<ASTNodes::BinaryExprNode>(now->RHS);
		}
	}
	printfTransferMsg("SexprASTN", false);
	return std::dynamic_pointer_cast<ASTNodes::BasicNode>(root);
}

std::shared_ptr<ASTNodes::BasicNode> ASTTransfer::TransferTermASTN(SPLAST::TermASTN * astn)
{
	printfTransferMsg("TermASTN", true);
	if (astn->getFactorNum() == 1) return TransferFactorASTN(astn->getFactor(0));
	std::shared_ptr<ASTNodes::BinaryExprNode> root(new ASTNodes::BinaryExprNode());
	std::shared_ptr<ASTNodes::BinaryExprNode> now = root;
	size_t facNum = astn->getFactorNum();
	if (facNum == 0) {
		printfTransferMsg("TermASTN", false);
		return nullptr;
	}
	for (int i = 0; i <= facNum - 2; i++) {
		switch (astn->getOp(i)) {
		case _MUL:
			now->expr_op = BinaryOper::MUL;
			break;
		case _DIV:
			now->expr_op = BinaryOper::DIV;
			break;
		case _INTDIV:
			now->expr_op = BinaryOper::DIVISION;
			break;
		case _MOD:
			now->expr_op = BinaryOper::MOD;
			break;
		case _AND:
			now->expr_op = BinaryOper::AND;
			break;
		default:
			std::cout << "Error Term op : err = " << astn->getOp(i) << std::endl;
		}
		now->LHS = TransferFactorASTN(astn->getFactor(i));
		if (i == facNum - 2) now->RHS = TransferFactorASTN(astn->getFactor(facNum - 1));
		else {
			now->RHS = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::BinaryExprNode>(new ASTNodes::BinaryExprNode()));
			now = std::dynamic_pointer_cast<ASTNodes::BinaryExprNode>(now->RHS);
		} 
	}
	printfTransferMsg("TermASTN", false);
	return std::dynamic_pointer_cast<ASTNodes::BasicNode>(root);
}

std::shared_ptr<ASTNodes::BasicNode> ASTTransfer::TransferFactorASTN(SPLAST::FactorASTN * astn)
{
	printfTransferMsg("FactorASTN", true);
	std::shared_ptr<ASTNodes::BasicNode> ptr;
	std::shared_ptr<ASTNodes::VarBaseNode> varbase;
	std::shared_ptr<ASTNodes::FunctionCallNode> funptr;
	std::shared_ptr<ASTNodes::BinaryExprNode> binary;
	std::shared_ptr<ASTNodes::VarAccessNode> varacc;
	switch (astn->getFactorType()) {
	case _USERVAL:
		ptr = std::dynamic_pointer_cast<ASTNodes::BasicNode>(std::shared_ptr<ASTNodes::VarBaseNode>(new ASTNodes::VarBaseNode(astn->getName(), nullptr, nullptr)));
		printfTransferMsg("FactorASTN", false);
		return ptr;
	case _SYSFUNCT:
		std::cout << "Error Factor type! Err = " << astn->getFactorType() << std::endl;
		printfTransferMsg("FactorASTN", false);
		return nullptr;
	case _RET:
		if (astn->getFuncType() != _USERFUNC) {
			std::cout << "Error Factor Funtion type! Err = " << astn->getFuncType() << std::endl;
			return nullptr;
		}
		ptr = _nodeptr;
		funptr = std::shared_ptr<ASTNodes::FunctionCallNode>(new ASTNodes::FunctionCallNode());
		_nodeptr = std::dynamic_pointer_cast<ASTNodes::BasicNode>(funptr);
		TransferExprListASTN(astn->getArgsList());
		_nodeptr = ptr;
		funptr->func_name = astn->getName();
		printfTransferMsg("FactorASTN", false);
		return std::dynamic_pointer_cast<ASTNodes::BasicNode>(funptr);
	case _CONST:
		printfTransferMsg("FactorASTN", false);
		return std::dynamic_pointer_cast<ASTNodes::BasicNode>(TransferConstValueASTN(astn->getConstVal()));
	case _EXPR:
		printfTransferMsg("FactorASTN", false);
		return TransferExprASTN(astn->getExpr());
	case _NOT:
		// limited function
		std::cout << "NOT instruction not finished yet.\n";
		printfTransferMsg("FactorASTN", false);
		return nullptr;
	case _NEG:
		binary = std::shared_ptr<ASTNodes::BinaryExprNode>(new ASTNodes::BinaryExprNode());
		binary->expr_op = BinaryOper::MINUS;
		binary->RHS = TransferFactorASTN(astn->getFactor());
		binary->LHS = std::dynamic_pointer_cast<ASTNodes::BasicNode>(TransferConstValueASTN(new SPLAST::ConstValueASTN(0)));
		printfTransferMsg("FactorASTN", false);
		return std::dynamic_pointer_cast<ASTNodes::BasicNode>(binary);
	case _INDEX:
		varbase = std::shared_ptr<ASTNodes::VarBaseNode>(new ASTNodes::VarBaseNode(astn->getName(), TransferExprASTN(astn->getExpr()), nullptr));
		printfTransferMsg("FactorASTN", false);
		return std::dynamic_pointer_cast<ASTNodes::BasicNode>(varbase);
	case _MEMBER:
		varacc = std::shared_ptr<ASTNodes::VarAccessNode>(new ASTNodes::VarAccessNode());
		varacc->nested_var = nullptr;
		varacc->var_name = astn->getMemName();
		varacc->idx = nullptr;
		varbase = std::shared_ptr<ASTNodes::VarBaseNode>(new ASTNodes::VarBaseNode(astn->getName(), nullptr, varacc));
		printfTransferMsg("FactorASTN", false);
		return std::dynamic_pointer_cast<ASTNodes::BasicNode>(varbase);
	case _ERRORFACTOR:
	default:
		std::cout << "Error Factor type! Err = " << astn->getFactorType() << std::endl;
		printfTransferMsg("FactorASTN", false);
		return nullptr;
	}
	printfTransferMsg("FactorASTN", false);
	return nullptr;
}
