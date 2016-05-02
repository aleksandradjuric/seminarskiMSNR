#include <regex.h>   
#include <stdio.h>
#include <stdlib.h>
regex_t regex;
int status;
char msgbuf[100];

int main()
{
  char mail[2048];
  scanf("%s",mail);
  
  /* valid e-mail address: \w+([-+.']\w+)*@\w+([.-]\w+)*\.(a-zA-Z){2,4} */
  status = regcomp(&regex, "[[:alnum:]]+([-.+'][[:alnum:]]+)*@[[:alnum:]]+([.-][[:alnum:]]+)*.([[:alpha:]]){2,4}", REG_EXTENDED);
  if (status) 
  {
      fprintf(stderr, "problem while compiling regex\n");
      exit(1);
  }

  /* Execute regular expression */
  status = regexec(&regex, mail, 0, NULL, 0);
  if (!status) 
  {
      printf("Valid mail address");
  } else if (status == REG_NOMATCH)
  {
      printf("Invalid mail address");
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