/*
 * @author Andrew Kohlhagen
 *
 * Date Last Modified: 9/16/2019
 *
 * Driver for IOMngr.h
 */
 #include "IOMngr.h"
 
int main(int argc, char **argv){
	char *source_file = argv[1];
	char *listing_file = argv[2];
	printf("%s\n", source_file);
	//printf("%s\n", listing_file);
	
	open_files(source_file, listing_file);
	get_source_char();
	
	close_files();

	return 0;
}

/*
 * Open the source file.
 * If listing_name is not NULL, open the listing file whose name is given in listing_name.
 * If listing_name is NULL, the output goes to stdout.
 * Return 1 if the file open(s) were successful, otherwise return 0.
 */
int open_files(const char *source_name, const char *listing_name){
	
	//check if source_name is null
	if(source_name == NULL){
		fprintf(stderr, "Source_name for file is empty\n");
		return 0;
	}
	
	//open source_name file
	fp_source_name = fopen(source_name, "r");
	if(fp_source_name == NULL){
		fprintf(stderr, "Something went wrong opening the source file\n");
		return 0;
	}
	
	//open listing_name file, if there is one
	if(listing_name != NULL){
		fp_listing_name = fopen(listing_name, "w");
		if(fp_listing_name == NULL){
			fprintf(stderr, "Something went wrong opening the listing file\n");
			return 0;
		}
	}
	return 1;
}

/*
 * Close the source file and the listing file, if one was created
 */
void close_files(){
	if(fp_source_name != NULL){
		fclose(fp_source_name);
	}
	if(fp_listing_name != NULL){
		fclose(fp_listing_name);
	}
}

/*
 * Echo the lines in the source file to the listing file, if one exists.
 * The lines in the listing file should be numbered.
 * (Return/use (?)) EOF when the end of the source file is reached.
 * Return the next source char (?)
 */
char get_source_char(){
	size_t buffer_size = MAXLINE;
	char *line = (char *) malloc(sizeof(char) * MAXLINE);
	int i = 1;
			
	if(line == NULL){
		printf("Error allocating space for line in get_source_char.\n");
		exit(-1);
	}
			
	if(fp_source_name != NULL){
		if(fp_listing_name != NULL){
			//echo lines into listing file from source file
			while(fgets(line, buffer_size, fp_source_name) != NULL){
				fprintf(fp_listing_name, "%d. %s", i, line);
				write_indicator(2);				// if its last line in file, we need a newline indicator
				write_message("error at column 2.");
				i++;
			}
		}
		else{
			//echo lines to stdout from source file
			while(fgets(line, buffer_size, fp_source_name) != NULL){
					fprintf(stdout, "%d. %s", i, line);
					write_indicator(2);			// if its last line in file, we need a newline indicator
					write_message("error at column 2.");
					i++;
				}
		}
		//return next source char (?)
	}
	else{
		fprintf(stderr, "There is no source file.\n");
		return NULL; //(?)
	}
	//not sure what/where to return
}

/*
 * Write a line containing a single '^' character in the indicated column.
 * If there is no listing file, then the current line should be echoed to stdout the first time (for that line)
 * that write_indicator or write_message is called.
 */
void write_indicator(int column){
	char *line = (char *) malloc(sizeof(char) * MAXLINE);
	int i;
	
	for(i = 0; i < column; i++){
		strcat(line, " ");
	}
	strcat(line, "^");
	
	if(fp_listing_name != NULL){
		fprintf(fp_listing_name, "%s\n", line);
	}
	else{
		fprintf(stdout, "%s\n", line);
	}
}

/*
 * Write the message on a separate line.
 */
void write_message(const char *message){ //last line also needs a newline indicator like before
	if(fp_listing_name != NULL){
		fprintf(fp_listing_name, "%s\n", message);
	}
	else{
		fprintf(stdout, "%s\n", message);
	}
}