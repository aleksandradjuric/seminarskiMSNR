#include <stdio.h>

int main()
{
  char c;
  int i;
  
  scanf("%c", &c);
  for(i=0; i<10; i++)
    printf("%c ",c);
  
  return 0;
}