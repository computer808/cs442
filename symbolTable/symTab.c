/*
 * Andrew Kohlhagen
 *
 * Date Last Modified: 9/30/2019
 *
 * Driver for SymTab.h
 */
 #include "SymTab.h"
 #include <unistd.h>
 
struct SymTab * create_SymTab(int size){
	int i;
	struct SymTab *SymTab;
	 
	SymTab = (struct SymTab *) malloc(sizeof(struct SymTab));
	SymTab->size = size;
	SymTab->contents = (struct SymEntry **) malloc(sizeof(struct SymEntry *) * size);
	 
	for(i = 0; i < size; i++){
		SymTab->contents[i] = NULL;
	}
	return SymTab;
}
 
 void destroy_SymTab(struct SymTab *aTable){
	int i;
	int size = aTable->size;
	 
	//how to free each linked list node within the contents[i]?
	for(i = 0; i < size; i++){
		struct SymEntry *cur = aTable->contents[i];
		while(cur != NULL){
			struct SymEntry *next = cur->next;
			struct SymEntry *toFree = NULL;
			if(cur->name != NULL){
				free(cur->name);
			}
			// if(cur->attributes != NULL){
			// 	free(cur->attributes);
			// }
			free(cur);
			cur = next;
		}
	}
	free(aTable->contents);
	free(aTable);
}
 
int enter_name(struct SymTab *aTable, const char *name, struct SymEntry **anEntry) {
	char *copy_of_name;
	int hash_value = 0;
	int i = 0, len = strlen(name);
	 
	//calculate hash
	hash_value = hash_function(name, aTable->size);
	//allocate space for Name and strdup
	copy_of_name = (char *) malloc(sizeof(char) * len);
	if(copy_of_name == NULL){
		printf("Error allocating space for copy_of_name.\n");
		exit(-1);
	}
	copy_of_name = strdup(name);

	
	//allocate entry to put name into
	struct SymEntry *entry = (struct SymEntry*) malloc(sizeof(struct SymEntry));
	(*anEntry) = entry;

	entry->name = copy_of_name;
	entry->attributes = NULL;
	entry->next = NULL;



	 //if no 'name' already associated with hash value 
	 //return 1 to indicate 'name' was not in the table and now put it there
	if(aTable->contents[hash_value] == NULL){
		aTable->contents[hash_value] = entry;
		return 1;
	}
	else{
		//see if the 'name' was at the 0th index
		struct SymEntry *cur = aTable->contents[hash_value];
		if(strcmp(cur->name, copy_of_name) == 0){
			(*anEntry = cur);
			return 0;
		}
		//go through linked list to see where 'name' is
		while(cur->next != NULL){
			cur = cur->next;
			 
			if(strcmp(cur->name, copy_of_name) == 0){
				(*anEntry = cur);
				return 0;
			}
		}
		//'name' was not in table so now add it
		cur->next = entry;
		return 1;
	}
}
 
struct SymEntry * find_name(struct SymTab *aTable, const char *name){
	int hash_value = 0;
	 
	//calculate hash
	hash_value = hash_function(name, aTable->size);

	struct SymEntry *cur = aTable->contents[hash_value];
	if(cur == NULL){
		return NULL;
	}
	//return SymEntry 'name' if found at beginning of linked list
	if(strcmp(cur->name, name) == 0){
		return cur;
	}
	//loop through linked list to find SymEntry name
	while(cur->next != NULL){
		cur = cur->next;
		//return current SymEntry if found somehwere in the linked list
		if(strcmp(cur->name, name) == 0){
			return cur;
		}
	}
	//'name' is not in the list
	return NULL;
}
 
void set_attr(struct SymEntry *anEntry, void *attributes){
	anEntry->attributes = attributes;
}

void * get_attr(struct SymEntry *anEntry){
	if(anEntry->attributes == NULL){
		return NULL;
	}
	else{
		return anEntry->attributes;
	}
}

const char * get_name(struct SymEntry *anEntry){
	return anEntry->name;
}

struct SymEntry * first_entry(struct SymTab *aTable){
	struct SymEntry *cur;
	int len = aTable->size;
	int i;
	
	//loop through table indexes and return the first entry found
	for(i = 0; i < len; i++){
		cur = aTable->contents[i];
		if(cur != NULL){
			return cur;
		}
	}
	//the table is empty
	return NULL;
}

struct SymEntry * next_entry(struct SymTab *aTable, struct SymEntry *anEntry){ 
	struct SymEntry *cur = anEntry;
	int hash_value = hash_function(anEntry->name, aTable->size);
	int len = aTable->size;
	int i;
	
	//check if table is null
	if((aTable == NULL) || (aTable->contents == NULL)){
		return NULL;
	}
	
	//if cur is not the last node in a linked list, return the next node
	else if(cur->next != NULL){
		return cur->next;
	}
	
	//return the next index(row) of the table. if its the last row, start from the beginning of the table in your search
	else {
		// //find out what row were in (where we currently are) and add one to hash_value to get to next row
		int end = hash_value;
		hash_value = (hash_value + 1) % len;
		// //if hash_value is greater than table size, set hash_value to 0 to choose the 0th row
		// if(hash_value > len){
		// 	hash_value = 0;
		// }
		// //loop through rows until next node is found
		// for(i = hash_value; i < len; i++){
		// 	cur = aTable->contents[hash_value];
		// 	if(cur != NULL){
		// 		return cur;
		// 	}
		// }
		// 0     1     2  3     4
		//[NULL, NULL, 3, NULL, NULL]
		//i = 2
		for(i = hash_value; i != end; i = (i + 1) % len) {
			cur = aTable->contents[i];
			if(cur != NULL){
				return cur;
			}
		}
		//no more entries
		return NULL;
	}
}
 
int hash_function(const char *name, int table_size){
	int hash_value = 0;
	int i = 0;
	for(i = 0; i < strlen(name); i++){
		hash_value += name[i];
	}
	hash_value = hash_value % table_size;
	return hash_value;
}
 
 
 

