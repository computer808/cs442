/*
 * @author Andrew Kohlhagen
 *
 * Date Last Modified: 9/16/2019
 *
 * Driver(?) for IOMngr.h
 */
 #include "IOMngr.h"

int main(int argc, char **argv){

	return 0;
}

/*
 * Open the source file.
 * If listing_name is not NULL, open the listing file whose name is given in listing_name.
 * If listing_name is NULL, the output goes to stdout.
 * Return 1 if the file open(s) were successful, otherwise return 0.
 */
int open_files(const char *source_name, const char *listing_name){
	FILE *fp_source_name = NULL, *fp_listing_name = NULL;

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

	if(listing_name != NULL){
		fp_listing_name = fopen(listing_name, "w");
		if(fp_listing_name == NULL){
			fprintf(stderr, "Something went wrong opening the listing file\n");
			return 0;
		}


	}
	else{

	}
	return 1;
}
