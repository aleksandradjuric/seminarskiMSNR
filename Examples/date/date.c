#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>


int main() {
	
	/* Datum se unosi u formatu **.**.**** */
	regex_t regex;
	int r;
	r = regcomp(&regex,"((0)*[1-9]|[1-2][0-9]|3[0-1])[./-]((0)*[1-9]|1[0-2])[./-][0-9]{4}",REG_EXTENDED);
	if(r) {
		printf("Greska u kompilaciji regularnog izraza");
		exit(EXIT_FAILURE);
	}
	
	char datum[100];
	scanf("%s",datum);
	r = regexec(&regex, datum,0,NULL,0);

	if(!r) {
		printf("Dan: %c%c \t",datum[0],datum[1]);
		printf("Mesec: %c%c \t",datum[3],datum[4]);
		printf("Godina: %c%c%c%c\n",datum[6],datum[7],datum[8],datum[9]);
	}
	else if (r == REG_NOMATCH)
	{
  	    printf("Invalid date !\n");
  	}
	return 0;
	
}
