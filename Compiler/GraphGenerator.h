#pragma once
#include "splast.h"
#include <iostream>
#include <string>

#define HEAD "----"
#define NONHEAD "    "

class Visitor {
	size_t _level;
	std::vector<bool> _isLastChild;
public:
	Visitor();
	void println(std::string msg, bool isHead = true, std::ostream& os = std::cout);
	void VisitProgramASTN(SPLAST::ProgramASTN* astn);
	void VisitProgramHeadASTN(SPLAST::ProgramHeadASTN* astn);
	void VisitNameASTN(SPLAST::NameASTN* astn);
	void VisitRoutineASTN(SPLAST::RoutineASTN* astn);
	void VisitRoutineHeadASTN(SPLAST::RoutineHeadASTN* astn);
	void VisitConstPartASTN(SPLAST::ConstPartASTN* astn);
	void VisitConstExprASTN(SPLAST::ConstExprASTN* astn);
	void VisitConstValueASTN(SPLAST::ConstValueASTN* astn);
	void VisitTypePartASTN(SPLAST::TypePartASTN* astn);
	void VisitTypeDefASTN(SPLAST::TypeDefASTN* astn);
	void VisitTypeDeclASTN(SPLAST::TypeDeclASTN* astn); // connected to its father, isHead = false
	void VisitFieldListASTN(SPLAST::FieldListASTN* astn); // connected to its father, isHead = false
	void VisitFieldDeclASTN(SPLAST::FieldDeclASTN* astn);
	void VisitNameListASTN(SPLAST::NameListASTN* astn); // connected to its father, isHead = false
	void VisitVarPartASTN(SPLAST::VarPartASTN* astn);
	void VisitVarDeclASTN(SPLAST::VarDeclASTN* astn);
	void VisitRoutinePartASTN(SPLAST::RoutinePartASTN* astn);
	void VisitFuncDeclASTN(SPLAST::FuncDeclASTN* astn);
	void VisitProcDeclASTN(SPLAST::ProcDeclASTN* astn);
	void VisitParaASTN(SPLAST::ParaASTN* astn);
	void VisitParaTypeListASTN(SPLAST::ParaTypeListASTN* astn);
	void VisitStmtListASTN(SPLAST::StmtListASTN* astn);
	void VisitStmtASTN(SPLAST::StmtASTN* astn);
	void VisitAssignStmtASTN(SPLAST::AssignStmtASTN* astn);
	void VisitProcStmtASTN(SPLAST::ProcStmtASTN* astn);
	void VisitIfStmtASTN(SPLAST::IfStmtASTN* astn);
	void VisitElseASTN(SPLAST::ElseASTN* astn); // connected to its father, isHead = false
	void VisitRepeatStmtASTN(SPLAST::RepeatStmtASTN* astn);
	void VisitWhileStmtASTN(SPLAST::WhileStmtASTN* astn);
	void VisitForStmtASTN(SPLAST::ForStmtASTN* astn);
	void VisitCaseStmtASTN(SPLAST::CaseStmtASTN* astn);
	void VisitCaseExprASTN(SPLAST::CaseExprASTN* astn);
	void VisitGotoStmtASTN(SPLAST::GotoStmtASTN* astn);
	void VisitExprListASTN(SPLAST::ExprListASTN* astn); // connected to its father, isHead = false
	void VisitExprASTN(SPLAST::ExprASTN* astn);
	void VisitSExprASTN(SPLAST::SExprASTN* astn);
	void VisitTermASTN(SPLAST::TermASTN* astn);
	void VisitFactorASTN(SPLAST::FactorASTN* astn);
};