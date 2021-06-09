#pragma once
#include "splast.h"
#include "ASTNodes.h"

#define INT_TYPE "integer"
#define DOUBLE_TYPE "double"
#define BOOL_TYPE "bool"
#define CHAR_TYPE "char"
#define VOID_TYPE "void"
#define ERROR_TYPE "#ERRORTYPE#"

class ASTTransfer;

const bool transfertest = false;
void printfTransferMsg(std::string nodename, bool isstart);
void printfSize(ASTTransfer* ast);

int getArrLength(SPLAST::TypeDeclASTN* arrRange);
int getArrBase(SPLAST::TypeDeclASTN* arrRange);
std::string getArrType(SPLAST::TypeDeclASTN* arrType); // limited function
std::string getTypeName(SPLAST::TypeDeclASTN* typeDecl);

class ASTTransfer 
{
	std::shared_ptr<ASTNodes::ProgramNode> _program;
	std::shared_ptr<ASTNodes::BasicNode> _nodeptr;
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> _vecptr;
	std::string _programName;
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>>> _trashbin;

public:
	ASTTransfer(SPLAST::ProgramASTN* program);
	std::shared_ptr<ASTNodes::ProgramNode> getProgram() const;
	std::shared_ptr<ASTNodes::BasicNode> getNodeptr() const;
	std::shared_ptr<std::vector<std::shared_ptr<ASTNodes::BasicNode>>> getVecptr() const;
	std::string getProgramName() const;

	~ASTTransfer(){
		this->_trashbin.clear();
	}
	void TransferProgramASTN(SPLAST::ProgramASTN* astn);
	void TransferRoutineASTN(SPLAST::RoutineASTN* astn); // _vecptr = program -> parts
	void TransferRoutineHeadASTN(SPLAST::RoutineHeadASTN* astn); // _vecptr = program -> parts
	void TransferConstPartASTN(SPLAST::ConstPartASTN* astn); // _vecptr = program -> parts
	void TransferConstExprASTN(SPLAST::ConstExprASTN* astn); // _vecptr = program -> parts
	std::shared_ptr<ASTNodes::ConstantNode> TransferConstValueASTN(SPLAST::ConstValueASTN* astn); // return node
	void TransferTypePartASTN(SPLAST::TypePartASTN* astn); // _vecptr = program -> parts
	void TransferTypeDefASTN(SPLAST::TypeDefASTN* astn); // _vecptr = program -> parts , only support record
	void TransferTypeDeclASTN(SPLAST::TypeDeclASTN* astn); 
	void TransferFieldListASTN(SPLAST::FieldListASTN* astn); // _nodeptr = RecordTypeDefineNode, just set the node
	void TransferFieldDeclASTN(SPLAST::FieldDeclASTN* astn); // _nodeptr = RecordTypeDefineNode, just set the node
	void TransferNameListASTN(SPLAST::NameListASTN* astn); 
	void TransferVarPartASTN(SPLAST::VarPartASTN* astn); // _vecptr = program -> parts
	void TransferVarDeclASTN(SPLAST::VarDeclASTN* astn); // _vecptr = program -> parts
	void TransferRoutinePartASTN(SPLAST::RoutinePartASTN* astn); // _vecptr = program -> parts
	void TransferFuncDeclASTN(SPLAST::FuncDeclASTN* astn); // _vecptr = program -> parts
	void TransferProcDeclASTN(SPLAST::ProcDeclASTN* astn); // _vecptr = program -> parts
	void TransferParaASTN(SPLAST::ParaASTN* astn); // using _nodeptr = fundeclarenode
	void TransferParaTypeListASTN(SPLAST::ParaTypeListASTN* astn); // using _nodeptr = fundeclarenode
	void TransferStmtListASTN(SPLAST::StmtListASTN* astn);	// using _vecptr
	void TransferStmtASTN(SPLAST::StmtASTN* astn);	// using _vecptr
	void TransferAssignStmtASTN(SPLAST::AssignStmtASTN* astn); // using _vecptr
	void TransferProcStmtASTN(SPLAST::ProcStmtASTN* astn); // using _vecptr
	void TransferIfStmtASTN(SPLAST::IfStmtASTN* astn); // using _vecptr
	void TransferRepeatStmtASTN(SPLAST::RepeatStmtASTN* astn); // using _vecptr
	void TransferWhileStmtASTN(SPLAST::WhileStmtASTN* astn); // using _vecptr
	void TransferForStmtASTN(SPLAST::ForStmtASTN* astn); // using _vecptr	// limited function
	void TransferCaseStmtASTN(SPLAST::CaseStmtASTN* astn); // using _vecptr // limited function
	void TransferCaseExprASTN(SPLAST::CaseExprASTN* astn);
	void TransferGotoStmtASTN(SPLAST::GotoStmtASTN* astn); // using _vecptr // limited function
	void TransferExprListASTN(SPLAST::ExprListASTN* astn); // using _nodeptr = functioncallnode
	std::shared_ptr<ASTNodes::BasicNode> TransferExprASTN(SPLAST::ExprASTN* astn); // returning an ptr to this node
	std::shared_ptr<ASTNodes::BasicNode> TransferSExprASTN(SPLAST::SExprASTN* astn); // returning an ptr to this node
	std::shared_ptr<ASTNodes::BasicNode> TransferTermASTN(SPLAST::TermASTN* astn); // returning an ptr to this node
	std::shared_ptr<ASTNodes::BasicNode> TransferFactorASTN(SPLAST::FactorASTN* astn); // returning an ptr to this node
};