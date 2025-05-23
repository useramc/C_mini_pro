#include<stdio.h>
void main()
{
printf("Hello ");
FILE*p=fopen("https://github.com/useramc/C_mini_pro/blob/main/indian_employee_data.csv","r");
if(p==NULL)
  printf("ERROR");
}
