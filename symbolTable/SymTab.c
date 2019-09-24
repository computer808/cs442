/*
 * @author Andrew Kohlhagen
 *
 * Date Last Modified: 9/11/2019
 *
 * Driver for SymTab.h
 */
 #include "SymTab.h"
 
 int main(int argc, char **argv){

	 return 0;
 }
 
 struct SymTab * create_SymTab(int size){
	 int i;
	 struct SymTab *SymTab;
	 
	 SymTab = (struct SymTab *) malloc(sizeof(struct SymTab));
	 SymTab->size = size;
	 SymTab->contents = (struct SymEntry **) malloc(sizeof(struct SymEntry *) * size);
	 
	 for(i = 0; i < size; i++){
		 SymTab->contents[i] = (struct SymEntry *) malloc(sizeof(struct SymEntry) * size);
		 SymTab->contents[i]->name = NULL;
		 SymTab->contents[i]->attributes = NULL;
		 SymTab->contents[i]->next = NULL;
		 
		 //if(i > 0){
			 //SymTab->contents[i-1]->next = SymTab->contents[i];
		 //}
	 }
	 return SymTab;
 }
 
 void destroy_SymTab(struct SymTab *aTable){
	 int i;
	 int size = aTable->size;
	 
	 for(i = 0; i < size; i++){
		 if(aTable->contents[i]->next != NULL){
			free(aTable->contents[i]->next);
		 }
		 if(aTable->contents[i]->attributes != NULL){
			free(aTable->contents[i]->attributes);
		 }
		 if(aTable->contents[i]->name != NULL){
			free(aTable->contents[i]->name);
		 }
		 free(aTable->contents[i]);
	 }
	 free(aTable->contents);
	 free(aTable);
 }
 
 int enter_name(struct SymTab *aTable, const char *name, struct SymEntry **anEntry){
	 //(*anEntry) = something
	 
 }
 
 //what causes collisions in the hash table, where does that happen in this file, because there is no add attr only set
 //what kind of language are we compiliing, what syntax of language are we going to be compiling
 //if the symbol table is supposed to be instantiated dynamically, why does createSymTab specify a size
 
 //monday 1-3:30pm EST
