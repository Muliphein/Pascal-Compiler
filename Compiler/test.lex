%{
	#include "test.tab.h"
	#include <stdio.h>
	#include <stdlib.h>
	void yyerror(const char *);
	bool testmode = true;
	bool displaydelim = false;
%}

%%
"and"		{if(testmode) printf("AND ");	return AND;}
"array"		{if(testmode) printf("ARRAY ");	return ARRAY;}
"begin"		{if(testmode) printf("BEGIN ");	return KEY_BEGIN;}
"case"		{if(testmode) printf("CASE ");	return CASE;}
"const"		{if(testmode) printf("CONST ");	return CONST;}
"div"		{if(testmode) printf("KEY_DIV ");	return KEY_DIV;}
"do"		{if(testmode) printf("DO ");		return DO;}
"downto"	{if(testmode) printf("DOWNTO ");	return DOWNTO;}
"else"		{if(testmode) printf("ELSE ");	return ELSE;}
"end"		{if(testmode) printf("END ");	return END;}
"for"		{if(testmode) printf("FOR ");	return FOR;}
"function"	{if(testmode) printf("FUNCTION ");	return FUNCTION;}
"goto"		{if(testmode) printf("GOTO ");	return GOTO;}
"if"		{if(testmode) printf("IF ");		return IF;}
"mod"|"MOD"	{if(testmode) printf("MOD ");	return MOD;}
"not"|"NOT"	{if(testmode) printf("NOT ");	return NOT;}
"of"		{if(testmode) printf("OF ");		return OF;}
"or"		{if(testmode) printf("OR ");		return OR;}
"packed"	{if(testmode) printf("PACKED "); return PACKED;}
"procedure"	{if(testmode) printf("PROCEDURE ");	return PROCEDURE;}
"program"	{if(testmode) printf("PROGRAM ");	return PROGRAM;}
"record"	{if(testmode) printf("RECORD "); return RECORD;}
"repeat"	{if(testmode) printf("REPEAT "); return REPEAT;}
"then"		{if(testmode) printf("THEN ");	return THEN;}
"to"		{if(testmode) printf("TO ");		return TO;}
"type"		{if(testmode) printf("TYPE ");	return TYPE;}
"until"		{if(testmode) printf("UNTIL ");	return UNTIL;}
"var"		{if(testmode) printf("VAR ");	return VAR;}
"while"		{if(testmode) printf("WHILE ");	return WHILE;}

"false"|"FALSE"		{if(testmode) printf("FALSE ");	return FALSE;}
"maxint"|"MAXINT"	{if(testmode) printf("MAXINT ");return MAXINT;}
"true"|"TRUE"		{if(testmode) printf("TRUE ");	return TRUE;}
"abs"		{if(testmode) printf("ABS ");	return ABS;}
"chr"		{if(testmode) printf("CHR ");	return CHR;}
"odd"		{if(testmode) printf("ODD ");	return ODD;}
"ord"		{if(testmode) printf("ORD ");	return ORD;}
"pred"		{if(testmode) printf("PRED ");	return PRED;}
"sqr"		{if(testmode) printf("SQR ");	return SQR;}
"sqrt"		{if(testmode) printf("SQRT ");	return SQRT;}
"succ"		{if(testmode) printf("SUCC ");	return SUCC;}
"write"		{if(testmode) printf("WRITE ");	return WRITE;}
"writeln"	{if(testmode) printf("WRITELN ");	return WRITELN;}
"boolean"	{if(testmode) printf("BOOLEAN ");	return BOOLEAN;}
"char"		{if(testmode) printf("CHAR ");	return CHAR;}
"integer"	{if(testmode) printf("INTEGER ");	return INTEGER;}
"real"		{if(testmode) printf("REAL ");	return REAL;}
"read"		{if(testmode) printf("READ ");	return READ;}

"("			{if(testmode) printf("LP ");		return LP;}
")"			{if(testmode) printf("RP ");		return RP;}
"["			{if(testmode) printf("LB ");		return LB;}
"]"			{if(testmode) printf("RB ");		return RB;}
".."		{if(testmode) printf("DOTDOT ");	return DOTDOT;}
"."			{if(testmode) printf("DOT ");	return DOT;}
","			{if(testmode) printf("COMMA ");	return COMMA;}
"*"			{if(testmode) printf("MUL ");	return MUL;}
"/"			{if(testmode) printf("DIV ");	return DIV;}
"<>"		{if(testmode) printf("UNEQUAL ");	return UNEQUAL;}
"+"			{if(testmode) printf("PLUS ");	return PLUS;}
"-"			{if(testmode) printf("MINUS ");	return MINUS;}
">="		{if(testmode) printf("GE ");		return GE;}
">"			{if(testmode) printf("GT ");		return GT;}
"<="		{if(testmode) printf("LE ");		return LE;}
"<"			{if(testmode) printf("LT ");		return LT;}
"="			{if(testmode) printf("EQUAL ");	return EQUAL;}
":="		{if(testmode) printf("ASSIGN ");	return ASSIGN;}
":"			{if(testmode) printf("COLON "); return COLON;}
";"			{if(testmode) printf("SEMI ");	return SEMI;}

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