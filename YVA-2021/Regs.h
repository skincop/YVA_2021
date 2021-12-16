#pragma once

#define REG_DECLARE "new"
#define REG_STRING "line"
#define REG_INTEGER "number"
#define REG_SYMBOL "symbol"
#define REG_FUNCTION "method"
#define REG_RETURN "return"
#define REG_PRINT "output"
#define REG_MAIN "main"
#define REG_ID "[a-z]+"
#define REG_INTEGER_LIT "([1-9]+[0-9]*)|0(o|b)?|([1-7]+[0-7]*o)|(1(1|0)*b)"
#define REG_STRING_LIT "'(.)*'"
#define REG_SYMBOL_LIT "'(.){1}'"
#define REG_SEMICOLON ";"
#define REG_EQUAL "="
#define REG_COMMA ","
#define REG_MREQUAL "\\{"
#define REG_LSEQUAL "\\}"
#define REG_LEFTTHESIS "\\("
#define REG_RIGHTTHESIS "\\)"
#define REG_PLUS "\\+"
#define REG_MINUS "\\-"
#define REG_STAR "\\*"
#define REG_DIRSLASH "/"
#define REG_IF "if"
#define REG_ELSE "else"
#define REG_MORE ">"
#define REG_LESS "<"
#define REG_MORE_OR_EQUALS ">="
#define REG_LESS_OR_EQUALS "<="
#define REG_FULL_EQUALS "=="
#define REG_NOT_FULL_EQUALS "!="
#define REG_AND "&&"
#define REG_OR "!!"
#define REG_NOT "!"
#define REG_MODULUS "%"