/*
 * Andrew Kohlhagen
 *
 * Date Last Modified: 10/16/2019
 *
 *
 */
 
#include "SymTab.h"
// #include "IOMngr.h"

#define WHILE_ID 1
#define IF_ID 2
#define ELSE_ID 3
#define INTEGER_ID 4
#define FLOAT_ID 5
#define CHAR_ID 6
#define BOOLEAN_ID 7
#define TRUE_ID 8
#define FALSE_ID 9
#define PRINT_ID 10
#define PRINTLN_ID 11
#define PRINTSTR_ID 12
#define PRINTSP_ID 13
#define READ_ID 14
#define LCURLYBRACKET_ID 15
#define RCURLYBRACKET_ID 16
#define LPAREN_ID 17
#define RPAREN_ID 18
#define LBRACKET_ID 19
#define RBRACKET_ID 20
#define PLUS_ID 21
#define MINUS_ID 22
#define MULT_ID 23
#define DIVIDE_ID 24
#define CARET_ID  25
#define AND_ID 26
#define OR_ID 27
#define EXCLAMATION_ID 28
#define LESS_THAN_ID 29
#define LESS_THAN_EQUAL_TO_ID 30
#define GREATER_THAN_ID 31
#define GREATER_THAN_EQUAL_TO_ID 32
#define NOT_EQUAL_TO_ID 33
#define EQUAL_EQUAL_ID 34
#define COLON_EQUAL_ID 35
#define COMMA_ID 36
#define SEMI_COLON 37
#define IDENTIFIER_ID 38
#define CHARACTER_STRING_ID 39
#define EOF_ID 0
#define ERROR -1
#define IGNORE -2

struct Node {
	int line_number;
	struct Node* next;
};

struct typeInfo{
	int type;
	struct Node* line_number_list;
	int times_appeared;
};

//ask about includes