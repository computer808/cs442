/*
 * Andrew Kohlhagen
 *
 * Date Last Modified: 9/30/2019
 *
 * 
 */

#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/******************************
 * Defines
 ******************************/


/******************************
 * Structures
 ******************************/
//The symbol table structure, implemented as a hash table. Contents are dynamically allocated
 struct SymTab{
	int size;
	struct SymEntry **contents;
 };
 
 //The name/attributes association structure used in the symbol tables linked lists
 struct SymEntry{
	char *name;
	void *attributes;
	struct SymEntry *next;
 };

/******************************
 * Global Variables
 ******************************/


/******************************
 * Function declarations
 ******************************/
 
//Create and return a reference to a symbol table of approximately 'size' many entries
struct SymTab * create_SymTab(int size);

//Destroy all storage associated with a symbol table which is under the table's control.
//This does not include the attributes. (must destroy those as well)
void destroy_SymTab(struct SymTab *aTable);

//Enter a name into a symbol table. Passes back an argument containing an entry reference for the name.
//Return 1 if the name was not in the symbol table, otherwise return 0.
//Also allocates space for 'name' and copies the contents from the parameter 'name'
int enter_name(struct SymTab *aTable, const char *name, struct SymEntry **anEntry);

//hash function
int hash_function(const char *name, int table_size);

//Find a 'name' in a symbol table.
//Return an entry reference or NULL depending on whether the 'name' was found.
struct SymEntry * find_name(struct SymTab *aTable, const char *name);

//set the attribute pointer associated with an entry
void set_attr(struct SymEntry *anEntry, void *attributes);		//similar to enter name (dealing with attr tho)

//get the attribute pointer associated with an entry
void * get_attr(struct SymEntry *anEntry);						//similar to find name  (dealing with attr tho)

//get the name string associated with an entry
const char * get_name(struct SymEntry *anEntry);

//Return the first entry in a symbol table or NULL if the table is empty.
//The first entry is simply the order found in the table.
struct SymEntry * first_entry(struct SymTab *aTable);			//gives the first entry of the entire symbol table

//Return the next entry after the supplied entry or NULL if no more entries.
struct SymEntry * next_entry(struct SymTab *aTable, struct SymEntry *anEntry); //if next is null on a row, move pointer for linked list to next row, if last row then go to beginning?

#endif