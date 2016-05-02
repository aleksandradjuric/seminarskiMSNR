#include <stdio.h>

int main()
{
  int sum = 0;
  int array[10];
  int i;
  
  for(i=0; i<10; i++)
  {
    scanf("%d", &array[i]);
    sum += array[i];
  }
  
  printf("%f", sum/10.0);
  
  return 0;
}