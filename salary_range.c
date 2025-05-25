// enter the salary range and the employees with salary in given range are presented in a new file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

int read(stv_e*s, FILE *fp) 
{
    char line[100];
    char *item;
    int i = 0;
    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp) != NULL) {
         item = strtok(line, ",");
        if (item != NULL) 
        {
            strcpy(s[i].Name, item);
            item = strtok(NULL, ",");
            if (item != NULL) {
				strcpy(s[i].ID, item);
            }

            item = strtok(NULL, ",");
            if (item != NULL) {
                s[i].Salary = atoi(item);
                i++;
        }}}
    return i; 
}
void sal_in_range(stv_e s[],int c,long int ur,long int lr,FILE *fp_out)
{
    if (lr > ur)
    {
    long int temp = lr;
    lr = ur;
    ur = temp;
    }
    for(int i=0;i<c;i++)
    {
        if(s[i].Salary>=lr && s[i].Salary<=ur)
        fprintf(fp_out,"NAME:%s\t\tSALARY:%ld\n\n",s[i].Name,s[i].Salary);
    }
}
void display()
{
    printf("THE EMPLOYEE LIST IS GENERATED IN FILE \"details.csv\".\n");
}
int main()
{
FILE *fp_in=fopen("indian_employee_data.csv","r");
FILE *fp_out=fopen("details.csv","w");
if (fp_in == NULL) 
    {
        printf("File NOT ACCESSIBLE\n");
    }
    
    stv_e s[100];
    int count = read(s,fp_in);
    fclose(fp_in);
    long int ur,lr;
    printf("ENTER THE RANGE [HIGHEST SALARY and LOWEST SALARY]\n");
    scanf("%ld%ld",&ur,&lr);
    fprintf(fp_out,"EMPLOYEES WITH SALARY RANGE %ld - %ld\n\n",ur,lr);
    sal_in_range(s,count,ur,lr,fp_out);
    display();
    fclose(fp_out);
}
