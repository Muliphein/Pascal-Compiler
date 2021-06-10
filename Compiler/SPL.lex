%{
	#include "SPL.tab.h"
	#include <stdio.h>
	#include <stdlib.h>
	void yyerror(const char *);
	bool testmode = false;
	bool displaydelim = false;
%}

%%
"and"		{if(testmode) printf("AND ");	return TOKEN_AND;}
"array"		{if(testmode) printf("ARRAY ");	return TOKEN_ARRAY;}
"begin"		{if(testmode) printf("BEGIN ");	return TOKEN_KEY_BEGIN;}
"case"		{if(testmode) printf("CASE ");	return TOKEN_CASE;}
"const"		{if(testmode) printf("CONST ");	return TOKEN_CONST;}
"div"		{if(testmode) printf("KEY_DIV ");	return TOKEN_KEY_DIV;}
"do"		{if(testmode) printf("DO ");		return TOKEN_DO;}
"downto"	{if(testmode) printf("DOWNTO ");	return TOKEN_DOWNTO;}
"else"		{if(testmode) printf("ELSE ");	return TOKEN_ELSE;}
"end"		{if(testmode) printf("END ");	return TOKEN_END;}
"for"		{if(testmode) printf("FOR ");	return TOKEN_FOR;}
"function"	{if(testmode) printf("FUNCTION ");	return TOKEN_FUNCTION;}
"goto"		{if(testmode) printf("GOTO ");	return TOKEN_GOTO;}
"if"		{if(testmode) printf("IF ");		return TOKEN_IF;}
"mod"|"MOD"	{if(testmode) printf("MOD ");	return TOKEN_MOD;}
"not"|"NOT"	{if(testmode) printf("NOT ");	return TOKEN_NOT;}
"of"		{if(testmode) printf("OF ");		return TOKEN_OF;}
"or"		{if(testmode) printf("OR ");		return TOKEN_OR;}
"packed"	{if(testmode) printf("PACKED "); return TOKEN_PACKED;}
"procedure"	{if(testmode) printf("PROCEDURE ");	return TOKEN_PROCEDURE;}
"program"	{if(testmode) printf("PROGRAM ");	return TOKEN_PROGRAM;}
"record"	{if(testmode) printf("RECORD "); return TOKEN_RECORD;}
"repeat"	{if(testmode) printf("REPEAT "); return TOKEN_REPEAT;}
"then"		{if(testmode) printf("THEN ");	return TOKEN_THEN;}
"to"		{if(testmode) printf("TO ");		return TOKEN_TO;}
"type"		{if(testmode) printf("TYPE ");	return TOKEN_TYPE;}
"until"		{if(testmode) printf("UNTIL ");	return TOKEN_UNTIL;}
"var"		{if(testmode) printf("VAR ");	return TOKEN_VAR;}
"while"		{if(testmode) printf("WHILE ");	return TOKEN_WHILE;}

"false"|"FALSE"		{if(testmode) printf("FALSE ");	return TOKEN_FALSE;}
"maxint"|"MAXINT"	{if(testmode) printf("MAXINT ");return TOKEN_MAXINT;}
"true"|"TRUE"		{if(testmode) printf("TRUE ");	return TOKEN_TRUE;}
"abs"		{if(testmode) printf("ABS ");	return TOKEN_ABS;}
"chr"		{if(testmode) printf("CHR ");	return TOKEN_CHR;}
"odd"		{if(testmode) printf("ODD ");	return TOKEN_ODD;}
"ord"		{if(testmode) printf("ORD ");	return TOKEN_ORD;}
"pred"		{if(testmode) printf("PRED ");	return TOKEN_PRED;}
"sqr"		{if(testmode) printf("SQR ");	return TOKEN_SQR;}
"sqrt"		{if(testmode) printf("SQRT ");	return TOKEN_SQRT;}
"succ"		{if(testmode) printf("SUCC ");	return TOKEN_SUCC;}
"write"		{if(testmode) printf("WRITE ");	return TOKEN_WRITE;}
"writeln"	{if(testmode) printf("WRITELN ");	return TOKEN_WRITELN;}
"boolean"	{if(testmode) printf("BOOLEAN ");	return TOKEN_BOOLEAN;}
"char"		{if(testmode) printf("CHAR ");	return TOKEN_CHAR;}
"integer"	{if(testmode) printf("INTEGER ");	return TOKEN_INTEGER;}
"real"		{if(testmode) printf("REAL ");	return TOKEN_REAL;}
"read"		{if(testmode) printf("READ ");	return TOKEN_READ;}

"("			{if(testmode) printf("LP ");		return TOKEN_LP;}
")"			{if(testmode) printf("RP ");		return TOKEN_RP;}
"["			{if(testmode) printf("LB ");		return TOKEN_LB;}
"]"			{if(testmode) printf("RB ");		return TOKEN_RB;}
".."		{if(testmode) printf("DOTDOT ");	return TOKEN_DOTDOT;}
"."			{if(testmode) printf("DOT ");	return TOKEN_DOT;}
","			{if(testmode) printf("COMMA ");	return TOKEN_COMMA;}
"*"			{if(testmode) printf("MUL ");	return TOKEN_MUL;}
"/"			{if(testmode) printf("DIV ");	return TOKEN_DIV;}
"<>"		{if(testmode) printf("UNEQUAL ");	return TOKEN_UNEQUAL;}
"+"			{if(testmode) printf("PLUS ");	return TOKEN_PLUS;}
"-"			{if(testmode) printf("MINUS ");	return TOKEN_MINUS;}
">="		{if(testmode) printf("GE ");		return TOKEN_GE;}
">"			{if(testmode) printf("GT ");		return TOKEN_GT;}
"<="		{if(testmode) printf("LE ");		return TOKEN_LE;}
"<"			{if(testmode) printf("LT ");		return TOKEN_LT;}
"="			{if(testmode) printf("EQUAL ");	return TOKEN_EQUAL;}
":="		{if(testmode) printf("ASSIGN ");	return TOKEN_ASSIGN;}
":"			{if(testmode) printf("COLON "); return TOKEN_COLON;}
";"			{if(testmode) printf("SEMI ");	return TOKEN_SEMI;}
"%"			{if(testmode) printf("MOD ");	return TOKEN_MOD;}

" "|"\n"|"\t"	{if(testmode&&displaydelim) printf("DELIM ");}
[0-9]*\.[0-9]+([eE][-+]?[0-9]+)? {if(testmode) printf("double_val "); yylval.double_val = (double)atof(yytext);	return D_VAL;}
[0-9]+			{if(testmode) printf("int_val "); yylval.int_val = atoi(yytext);	return I_VAL;}
"'"[A-Za-z]"'"	{if(testmode) printf("char_val "); yylval.char_val = yytext[0];	return C_VAL;}
[a-zA-Z][_a-zA-Z0-9]* {if(testmode) printf("NAME "); yylval.string_val = strdup(yytext);	return NAME;}
.			{if(testmode) printf("OTHER: %d\n",(int)yytext[0]);}

%%

int yywrap()
{
	return 1;
}