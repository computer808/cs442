/*
 * Andrew Kohlhagen
 *
 * Date Last Modified: 9/30/2019
 *
 * Driver for IOMngr.h
 */
 #include "IOMngr.h"
 
// int main(int argc, char **argv){
// 	char *source_file = argv[1];
// 	char *listing_file = argv[2];
	
// 	open_files(source_file, listing_file);
// 	char c = get_source_char();
// 	while(c != EOF){
// 		if(c == 't'){
// 			write_indicator(get_current_column());
// 			write_message("hes dead jim");
// 		}
// 		c = get_source_char();
// 	}
	
// 	close_files();

// 	return 0;
// }

/*
 * Open the source file.
 * If listing_name is not NULL, open the listing file whose name is given in listing_name.
 * If listing_name is NULL, the output goes to stdout.
 * Return 1 if the file open(s) were successful, otherwise return 0.
 */
bool open_files(const char *source_name, const char *listing_name){
	
	//check if source_name is null
	if(source_name == NULL){
		fprintf(stderr, "Source_name for file is empty\n");
		return false;
	}
	
	//open source_name file
	fp_source_name = fopen(source_name, "r");
	if(fp_source_name == NULL){
		fprintf(stderr, "Something went wrong opening the source file\n");
		return false;
	}
	
	//open listing_name file, if there is one
	if(listing_name != NULL){
		fp_listing_name = fopen(listing_name, "w");
		if(fp_listing_name == NULL){
			fprintf(stderr, "Something went wrong opening the listing file\n");
			return false;
		}
	}
	return true;
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
 * Return EOF when the end of the source file is reached.
 * Otherwise return the next source char
 */
char get_source_char(){
	size_t buffer_size = MAXLINE;
	char character;
	
	if(line == NULL){
		line = (char *) malloc(sizeof(char) * MAXLINE);
		line[0] = '\0';
	}		
			
	if(fp_source_name != NULL){
		if(fp_listing_name != NULL){
			//increment from -1 to 0 first
			column_number++; 
			//if the last character is '\0', get a new line from the source file
			if(line[column_number] == '\0'){
				//if the new line is null, return EOF
				if(fgets(line, buffer_size, fp_source_name) == NULL){
					return EOF;
				}
				fprintf(fp_listing_name, "%d. %s", ++line_number, line);
				//check if the last character of the line is a new line character, 
				//if it isnt we print newline (this is for the last line of file)
				if((line[strlen(line)-1]) != '\n'){
					fprintf(fp_listing_name, "\n");
				}
				column_number = 0;
			}
			character = line[column_number];
		
		}
		else{
			//increment from -1 to 0 first
			column_number++;
			//if the last character is '\0', get a new line from the source file
			if(line[column_number] == '\0'){
				//if the new line is null, return EOF
				if(fgets(line, buffer_size, fp_source_name) == NULL){
					return EOF;
				}
				already_printed_line = false;
				line_number++;
				column_number = 0;
			}
			character = line[column_number];
		}
	}
	else{
		fprintf(stderr, "There is no source file.\n");
		return EOF;
	}
	return character;
}

/*
 * Write a line containing a single '^' character in the indicated column.
 * If there is no listing file, then the current line should be echoed to stdout the first time (for that line)
 * that write_indicator or write_message is called.
 */

void write_indicator(int column){
	char *indicator_line = (char *) malloc(sizeof(char) * MAXLINE);
	int i;
	char buffer[1024];
	sprintf(buffer, "%d", line_number);
	column += 2 + strlen(buffer); // acount for '1. ' (line number, '.', and a space)
	
	for(i = 0; i < column; i++){
		strcat(indicator_line, " ");
	}
	strcat(indicator_line, "^");
	
	if(fp_listing_name != NULL){
		fprintf(fp_listing_name, "%s\n", indicator_line);
	}
	else{
		//if we have not printed the line yet,
		//print the line and the write indicator (line is already stored in the buffer)
		if(already_printed_line == false){
			fprintf(stdout, "%d. %s", line_number, line);
			if((line[strlen(line)-1]) != '\n'){
				fprintf(stdout, "\n");
			}
			already_printed_line = true;
		}
		fprintf(stdout, "%s\n", indicator_line);
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

/*
 * Return the current line number.
 */
int get_current_line(){
	return line_number;
}

/*
 * Return the current column number in the current line.
 */
int get_current_column(){
	return column_number;
}