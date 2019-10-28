%{
#include "lex.h"
#define YY_INPUT(buf,result,max_size) \
 { int c = get_source_char(); \
 	result = (c == EOF) ? YY_NULL : (buf[0] = c, 1); \
 } 

struct SymTab *table_identifiers;
struct SymTab *nums_and_chars;

%}


/* regular definitions */

letter	[A-Za-z]
digit	[0-9]
newline [\n]
space 	[ ]
tab		[\t]
null	[\0]
carriage[\r]



/* The two possibilities for the following section: 
	{type}
	"String"
	"&&" {return SYMBOL_ID}
*/

%%
{newline}|{space}|{tab}|{null}|{carriage} {return IGNORE;}
"while"				{return WHILE_ID;}
"if"				{return IF_ID;}
"else"				{return ELSE_ID;}
"true"				{return BOOLEAN_ID;}
"false"				{return BOOLEAN_ID;}
"print"				{return PRINT_ID;}
"println"			{return PRINTLN_ID;}
"printstr"			{return PRINTSTR_ID;}
"printsp"			{return PRINTSP_ID;}
"read"				{return READ_ID;}
\{					{return LCURLYBRACKET_ID;}
\}					{return RCURLYBRACKET_ID;}
\(					{return LPAREN_ID;}
\)					{return RPAREN_ID;}
\[					{return LBRACKET_ID;}
\]					{return RBRACKET_ID;}
\+					{return PLUS_ID;}
\-					{return MINUS_ID;}
\*					{return MULT_ID;}
\/					{return DIVIDE_ID;}
\^					{return CARET_ID;}
\&\&				{return AND_ID;}
\|\|				{return OR_ID;}
\!					{return EXCLAMATION_ID;}
\<					{return LESS_THAN_ID;}
\<\=				{return LESS_THAN_EQUAL_TO_ID;}
\>					{return GREATER_THAN_ID;}
\>\=				{return GREATER_THAN_EQUAL_TO_ID;}
\!\=				{return NOT_EQUAL_TO_ID;}
\=\=				{return EQUAL_EQUAL_ID;}
\:\=				{return COLON_EQUAL_ID;}
\,					{return COMMA_ID;}
\;					{return SEMI_COLON;}
\'[^']\'			{return CHAR_ID;}
\"[^"]*\"			{return CHARACTER_STRING_ID;}
{digit}+			{return INTEGER_ID;}
{letter}({letter}+|{digit}+)*	{return IDENTIFIER_ID;}
{digit}+\.{digit}+	{return FLOAT_ID;}
.					{write_indicator(get_current_column());
						write_message("Illegal Character");
						return ERROR;}
%%



int main(int argc, char **argv) {
	char* type_array[40];
	type_array[WHILE_ID] = "While";
	type_array[IF_ID] = "If";
	type_array[ELSE_ID] = "Else";
	type_array[INTEGER_ID] = "Integer";
	type_array[FLOAT_ID] = "Float";
	type_array[CHAR_ID] = "Char";
	type_array[BOOLEAN_ID] = "Boolean";
	type_array[TRUE_ID] = "True";
	type_array[FALSE_ID] = "False";
	type_array[PRINT_ID] = "Print";
	type_array[PRINTLN_ID] = "Println";
	type_array[PRINTSTR_ID] = "Printstr";
	type_array[PRINTSP_ID] = "Printsp";
	type_array[READ_ID] = "Read";
	type_array[LCURLYBRACKET_ID] = "Left Curly Bracket";
	type_array[RCURLYBRACKET_ID] = "Right Curly Bracket";
	type_array[LPAREN_ID] = "Left Parenthesis";
	type_array[RPAREN_ID] = "Right Parenthesis";
	type_array[LBRACKET_ID] = "Left Bracket";
	type_array[RBRACKET_ID] = "Right Bracket";
	type_array[PLUS_ID] = "Plus Operator";
	type_array[MINUS_ID] = "Minus Operator";
	type_array[MULT_ID] = "Multiply Operator";
	type_array[DIVIDE_ID] = "Divide Operator";
	type_array[CARET_ID] = "Caret";
	type_array[AND_ID] = "Logical And Operator";
	type_array[OR_ID] = "Logical Or Operator";
	type_array[EXCLAMATION_ID] = "Exclamation";
	type_array[LESS_THAN_ID] = "Less Than";
	type_array[LESS_THAN_EQUAL_TO_ID] = "Less Than Or Equal To";
	type_array[GREATER_THAN_ID] = "Greater Than";
	type_array[GREATER_THAN_EQUAL_TO_ID] = "Greater Than Or Equal To";
	type_array[NOT_EQUAL_TO_ID] = "Not Equal to";
	type_array[EQUAL_EQUAL_ID] = "Equals Equals";
	type_array[COLON_EQUAL_ID] = "Colon";
	type_array[COMMA_ID] = "Comma";
	type_array[SEMI_COLON] = "Semi-Colon";
	type_array[IDENTIFIER_ID] = "Identifier";
	type_array[CHARACTER_STRING_ID] = "Character String";

	int token;
	struct SymEntry *entry;
	struct SymEntry *the_first_entry;
	struct typeInfo *attribute;
	struct Node *cur = NULL;
	struct Node *node = NULL;
	struct Node *temp = NULL;
	
	table_identifiers = create_SymTab(19);
	nums_and_chars = create_SymTab(19);
	open_files(argv[1], argv[2]);

	int found_eof = 0;
	while(!found_eof) {
		token = yylex();
		//printf("TokenTEST: %d name: %s yytext: first character: %d\n", token, type_array[token], yytext[0]);
		switch(token) {
			case ERROR:
			case IGNORE:
				break;
				
			case EOF_ID:
				found_eof = 1;
				break;

			//cases for ints, floats, chars. these will only store times_appeared in a new table
			//also includes CHARACTER_STRING_ID which needs the line_number_list
			case INTEGER_ID:
			case FLOAT_ID:
			case CHAR_ID:
			case CHARACTER_STRING_ID:
				//Create (malloc) a Node* for get_current_line()
				node = (struct Node *) malloc(sizeof(struct Node));
				node->line_number = get_current_line();
				node->next = NULL;

				//Check if symbol 'nums_and_chars' table has an entry for yytext
				entry = find_name(nums_and_chars, yytext);

				//if it does have an entry (for yytext):	
				if(entry != NULL){
					//get that entry and add get_current_line() to our line_numbers linked list (create another new node)
					attribute = get_attr(entry);
					cur = attribute->line_number_list;
					while(cur->next != NULL){
						cur = cur->next;
					}
					cur->next = node;	
				}else{
					//This line creates a symEntry and puts it into the entry variable
					enter_name(nums_and_chars, yytext, &entry);
					attribute = (struct typeInfo *) malloc(sizeof(struct typeInfo));
					attribute->type = token;
					//fill in the line_number_list with a single node that is get_current_line()
					attribute->line_number_list = node;
					set_attr(entry, attribute);
				}
				//both cases
				attribute->times_appeared++;
				break;

			//everything else is in this table (keywords, punctuation, identifiers)
			default:
				//Create (malloc) a Node* for get_current_line()
				node = (struct Node *) malloc(sizeof(struct Node));
				node->line_number = get_current_line();
				node->next = NULL;

				//Check if symbol table_identifiers has an entry for yytext
				entry = find_name(table_identifiers, yytext);

				//if it does have an entry (for yytext):	
				if(entry != NULL){
					//get that entry and add get_current_line() to our line_numbers linked list (create another new node)
					attribute = get_attr(entry);
					cur = attribute->line_number_list;
					while(cur->next != NULL){
						cur = cur->next;
					}
					cur->next = node;		
				}
				else{
					//This line creates a symEntry and puts it into the entry variable
					enter_name(table_identifiers, yytext, &entry);
					attribute = (struct typeInfo *) malloc(sizeof(struct typeInfo));
					attribute->type = token;
					//fill in the line_number_list with a single node that is get_current_line()
					attribute->line_number_list = node;
					set_attr(entry, attribute);
				}
				//both cases
				attribute->times_appeared++;
				break;
		}
	}

	printf("\n\nPrint the tables out below.\n");


	//print out nums_and_chars table

	entry = first_entry(nums_and_chars);
	the_first_entry = entry;

	if(entry != NULL) {
		do {
			attribute = get_attr(entry);
			printf("Token: %s\n", get_name(entry));
			printf("Token Type: %s\n", type_array[attribute->type]);
			printf("Times Appeared: %d\n", attribute->times_appeared);

			if(attribute->line_number_list != NULL){
				cur = attribute->line_number_list;
				printf("lineNumbers:");
				while(cur != NULL){
					printf(" %d", cur->line_number);
					temp = cur;
					cur = cur->next;
					free(temp);
					if(cur != NULL){
						printf(",");
					}
				}
				printf("\n");
			}
			printf("\n");
			entry = next_entry(nums_and_chars, entry);
			free(attribute);
			
		} while((entry != the_first_entry) && (entry != NULL));
	}

	//print out table_identifiers

	entry = first_entry(table_identifiers);
	the_first_entry = entry;
	
	if(entry != NULL) {
		do {
			attribute = get_attr(entry);
			printf("Token: %s\n", get_name(entry));
			printf("Token Type: %s\n", type_array[attribute->type]);
			printf("Times Appeared: %d\n", attribute->times_appeared);
			if(attribute->line_number_list != NULL){
				cur = attribute->line_number_list;
				printf("lineNumbers:");
				while(cur != NULL){
					printf(" %d", cur->line_number);
					temp = cur;
					cur = cur->next;
					free(temp);
					if(cur != NULL){
						printf(",");
					}
				}
				printf("\n");
			}
			printf("\n");
			entry = next_entry(table_identifiers, entry);
			free(attribute);
		} while((entry != the_first_entry) && (entry != NULL));
	}

	destroy_SymTab(table_identifiers);
	destroy_SymTab(nums_and_chars);

	close_files();

	return 1;
}

int yywrap() {
	//printf("Done\n");
}