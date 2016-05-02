#include <regex.h>   
#include <stdio.h>
#include <stdlib.h>
regex_t regex;
int status;
char msgbuf[100];

int main()
{
  char path[2048];
  scanf("%s",path);
  
  /* (\/?[^\0/])+|\/ (a sequence of an optional slash character followed by a non nul and non slash character, or the / entry alone ---indicating the root directory)  */
  status = regcomp(&regex, "(/?[^/\\0])+|/", REG_EXTENDED);
  if (status) 
  {
      fprintf(stderr, "problem while compiling regex\n");
      exit(1);
  }

  /* Execute regular expression */
  status = regexec(&regex, path, 0, NULL, 0);
  if (!status) 
  {
      printf("Valid linux path");
  } else if (status == REG_NOMATCH)
  {
      printf("Invalid linux path");
  }
  else 
  {
      regerror(status, &regex, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "regex match failed: %s\n", msgbuf);
      exit(1);
  }

  /* Free memory allocated to the pattern buffer by regcomp() */
  regfree(&regex);
  return 0;
}