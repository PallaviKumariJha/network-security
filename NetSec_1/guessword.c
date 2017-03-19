/*

Author: Pallavi
Created on: 14th February 2016
Modified on:

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crypt.h>
#include <getopt.h>

int main(int argc, char* argv[]){

	FILE *fp1,*fp2,*fp3;
	char *passwordfile, *top250;
	int opt = 0;
	char line1[1000], line2[1000];
	char *cryptPassword;
	char *hashPassword;
	char *plainPasswd;
	char *check;
	char *userName;
	char *bufferPassword;
	char *bufferDictionary;
	char method[5]= "$1$";
	char *salt;

	//getopt to take in command/makefile arguments
	while ((opt = getopt(argc, argv,"i:d:o:")) != -1) {
	    switch (opt) {
	         case 'i' : 
	         	passwordfile = optarg;
	            break;
	         case 'd' : 
	         	top250 = optarg;
	            break;
	         case 'o' :
	         	check = optarg; 
	            break;
	         default: 
	             exit(EXIT_FAILURE);
	    }
	}

	fp1 = fopen(passwordfile,"r");
	fp2 = fopen(top250,"r");
	fp3 = fopen("allcrackedpasswords.txt","w");

	if(fgets(line1, 250, fp1) != NULL){
		userName = strtok(line1, ":");
		bufferPassword = strtok(NULL,"$");
		salt = strtok(NULL,"$");
		strcat(method,salt);		
	}

	if(strncmp(check,"all",strlen(check)) != 0){
		while(1){
			if(fgets(line1,250,fp1) == NULL)
				break;
			userName = strtok(line1, ":");
			hashPassword = strtok(NULL, ":");
			if(strncmp(check,userName,strlen(check)) == 0){
				break;
			}else{
				continue;
			}
		}
	}

	while(1){
		fp1 = fopen(passwordfile,"r");
		if(fgets(line2,250,fp2) == NULL)
			break;
		bufferDictionary = strtok(line2, "\t");
		bufferDictionary = strtok(NULL, "\t");
		bufferDictionary = strtok(NULL, "\t");
		plainPasswd = strtok(NULL, "\n");
		cryptPassword = crypt(plainPasswd, method);

		if(strncmp(check,"all",strlen(check)) == 0){
			while(fgets(line1,250, fp1)){
				userName = strtok(line1, ":");
				hashPassword = strtok(NULL, ":");
				if (strcmp(cryptPassword,hashPassword) == 0){
					fprintf(fp3,"%s:%s\n",userName,plainPasswd);
				}	
			}
		}else{
			if (strcmp(cryptPassword,hashPassword) == 0){
				fprintf(fp3,"%s:%s\n",userName,plainPasswd);
			}
		}
	}
	return 0;
}