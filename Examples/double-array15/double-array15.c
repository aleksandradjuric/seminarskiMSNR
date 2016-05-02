#include <stdio.h>

int main()
{
  double sum = 0;
  double array[15];
  int i;
  
  for(i=0; i<15; i++)
  {
    scanf("%lf", &array[i]);
    sum += array[i];
  }
  
  printf("%f", sum);
  
  return 0;
}