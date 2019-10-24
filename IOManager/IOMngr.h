/*
 * Andrew Kohlhagen
 *
 * Date Last Modified: 9/30/2019
 *
 * 
 */

#ifndef IOMNGR_H
#define IOMNGR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/******************************
 * Defines
 ******************************/
#define MAXLINE 1024

/******************************
 * Structures
 ******************************/


/******************************
 * Global Variables
 ******************************/
FILE *fp_source_name = NULL;
FILE *fp_listing_name = NULL;
int line_number = 0;
int column_number = -1;
char *line = NULL;
bool already_printed_line = false;

/******************************
 * Function declarations
 ******************************/

/*
 * Open the source file.
 * If listing_name is not NULL, open the listing file whose name is given in listing_name.
 * If listing_name is NULL, the output goes to stdout.
 * Return 1 if the file open(s) were successful, otherwise return 0.
 */
bool open_files(const char *source_name, const char *listing_name);

/*
 * Close the source file and the listing file, if one was created
 */
void close_files();

/*
 * Echo the lines in the source file to the listing file, if one exists.
 * The lines in the listing file should be numbered.
 * (Return/use (?)) EOF when the end of the source file is reached.
 * Return the next source char (?)
 */
char get_source_char();

/*
 * Write a line containing a single '^' character in the indicated column.
 * If there is no listing file, then the current line should be echoed to stdout the first time (for that line)
 * that write_indicator or write_message is called.
 */
void write_indicator(int column);

/*
 * Write the message on a separate line.
 */
void write_message(const char *message);

/*
 * Return the current line number.
 */
int get_current_line();

/*
 * Return the current column number in the current line.
 */
int get_current_column();

#endif