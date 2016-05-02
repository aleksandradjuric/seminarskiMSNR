#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>


int main() {
	
	/* Vreme se unosi u formatu **:**:** */
	regex_t regex;
	int r;
	r = regcomp(&regex,"([0-9]|0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]",REG_EXTENDED);
	if(r) {
		printf("Greska u kompilaciji regularnog izraza");
		exit(EXIT_FAILURE);
	}
	
	char vreme[100];
	scanf("%s",vreme);
	r = regexec(&regex, vreme,0,NULL,0);

	if(!r) {
		printf("Sati: %c%c \t",vreme[0],vreme[1]);
		printf("Minuta: %c%c \t",vreme[3],vreme[4]);
		printf("Sekundi: %c%c\n",vreme[6],vreme[7]);
	}
	else 
		printf("Invalid time!");
	return 0;
	
}
