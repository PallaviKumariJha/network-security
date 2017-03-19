/*

Author: Pallavi
Created on: 13th February 2016
Modified on:

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to slipt string and save it into an array
char** strSplit(char *str, const char *delimiters)
{
    char * token; 
    char **parsedArray;
    int count=0;
    token = (char *)strtok(str, delimiters); 
    
    // Dynamic allocation of parsedArray
    parsedArray = (char**)malloc(1 * sizeof(char*)); 
    parsedArray[0] = NULL;
    if (!token) {       
        return parsedArray;  
    } 
    while (token != NULL) { 
        parsedArray[count] = (char*)strdup(token);
        
        count++;
        // token added now reallocate the parsedArray size
        parsedArray = (char **)realloc(parsedArray, sizeof(char *) * (count + 1));
        token = (char *)strtok(NULL, delimiters); // Get the next token
    }
    // Terminate the array
    parsedArray[count] = NULL;  
    return parsedArray;
}

int main(int argc, char* argv[]){

	FILE *fp1, *fp2, *fp3;
	char line1[400], line2[400];

	// Open all three files
	fp1 = fopen(argv[2],"r");
	fp2 = fopen(argv[1],"r");
	fp3 = fopen("passwordfile.txt","w");

	while(1){
		if(fgets(line1,250,fp1)==NULL)
			break;
		line1[strcspn(line1,"\n")] = 0;

		// Split string from shadow file
		char ** splitArray1 = (char **)strSplit(line1,":");
		int i=0;
		int counter = 0;
		while(splitArray1[i] != NULL){
			if (counter <1){
				fprintf(fp3, "%s:",splitArray1[i]);
			}
			else if (counter == 1){
				fprintf(fp3, "%s",splitArray1[i]);
			}else{
				// do nothing
			}
			counter++;
			i++;
		}
		
		if(fgets(line2,250,fp2)==NULL)
			break;

		// Split string from password files
		char ** splitArray2 = (char **)strSplit(line2,":");
		int j=2;
		while(splitArray2[j] != NULL){
			fprintf(fp3, ":%s",splitArray2[j]);
			j++;
		}

	}

	//close all the file pointers
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}