// presents the details of employees who have taken leaves equal to ,less than or greater than paid leaves. and displays pending leaves
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"  
int read(stv_e *s, FILE *fp) {
    char line[100];
    char *item;
    int i = 0;

    fgets(line, sizeof(line), fp); // Skip header
    while (fgets(line, sizeof(line), fp) != NULL) {
        item = strtok(line, ",");
        if (item != NULL)
        {
            strcpy(s[i].Name, item);

            item = strtok(NULL, ",");
            if (item != NULL)
                strcpy(s[i].ID, item);

            item = strtok(NULL, ",");
            if (item != NULL)
                s[i].Salary = atoi(item);

            // no.of leaves column
            item = strtok(NULL, ",");
            if (item != NULL) {
                s[i].Leaves = atoi(item);
            }
            item = strtok(NULL, ",");
            if (item != NULL) {
                s[i].Paid_Leaves = atoi(item);
                i++;
            }
        }
    }
    return i;
}
void less(FILE*fp_in,stv_e s[],FILE*fp_out1,int c)
{
    for(int i=0;i<c;i++)
    {
        if(s[i].Leaves<s[i].Paid_Leaves)
        {
        int n=s[i].Paid_Leaves-s[i].Leaves;
fprintf(fp_out1,"\nName:%s\nLeaves: %d\nPaid Leaves:%d\nEXTRA LEAVES PENDING: %d\n",s[i].Name,s[i].Leaves,s[i].Paid_Leaves,n);
        }
    }
}

void equal(FILE*fp_in,stv_e s[],FILE*fp_out2,int c)
{
    for(int i=0;i<c;i++)
    {
        if(s[i].Leaves==s[i].Paid_Leaves)
        {
        int n=s[i].Leaves-s[i].Paid_Leaves;
fprintf(fp_out2,"\nName:%s\nLeaves: %d\nPaid Leaves:%d\nEXTRA LEAVES PENDING: %d\n",s[i].Name,s[i].Leaves,s[i].Paid_Leaves,n);
        }
    }
}

void more(FILE*fp_in,stv_e s[],FILE*fp_out3,int c)
{
    for(int i=0;i<c;i++)
    {
        if(s[i].Leaves>s[i].Paid_Leaves)
        {
        int n=s[i].Leaves-s[i].Paid_Leaves;
fprintf(fp_out3,"\nName:%s\nLeaves: %d\nPaid Leaves:%d\nEXTRA LEAVES TAKEN: %d\n",s[i].Name,s[i].Leaves,s[i].Paid_Leaves,n);
        }
    }
}

int main()
{
FILE *fp_in=fopen("indian_employee_data.csv","r");
FILE *fp_out1=fopen("leaves_paid1.csv","w");
FILE *fp_out2=fopen("leaves_paid2.csv","w");
FILE *fp_out3=fopen("leaves_paid3.csv","w");
if (fp_in == NULL) 
    {
        printf("File NOT ACCESSIBLE\n");
    }
    if (!fp_out1 || !fp_out2 || !fp_out3) 
    {
    printf("One or more output files could not be opened.\n");
    exit(1);
    }

    stv_e s[100];
    int count = read(s,fp_in);
    char c='y';
    fclose(fp_in);
    while(c!='n'&& c!='N')
    {
    int ch;
    printf("MENU:\n");
    printf("1. EMPLOYEES WITH LEAVES LESS THAN PAID LEAVES\n");
    printf("2. EMPLOYEES WITH LEAVES EQUAL TO THAT OF PAID LEAVES\n");
    printf("3. EMPLOYEES WITH LEAVES GREATER THAN PAID LEAVES\n");
    printf("ENTER YOUR CHOICE 1 ,2 ,3\n");
    scanf("%d",&ch);
    switch(ch)
{
    case 1:
        fprintf(fp_out1, "DETAILS\n");
        less(fp_in, s, fp_out1, count);  // leaves < paid
        printf("UPLOAD SUCCESSFUL, CHECK \"leaves_paid1.csv\" .\n");
        break;

    case 2:
        fprintf(fp_out2, "DETAILS\n");
        equal(fp_in, s, fp_out2, count);  // leaves = paid
        printf("UPLOAD SUCCESSFUL, CHECK \"leaves_paid2.csv\" .\n");
        break;

    case 3:
        fprintf(fp_out3, "DETAILS\n");
        more(fp_in, s, fp_out3, count);  // leaves > paid
        printf("UPLOAD SUCCESSFUL, CHECK \"leaves_paid3.csv\" .\n");
        break;

    default:
        printf("Invalid\n");
}

    printf("\nDO YOU WANT TO CONTINUE?(Y/N): ");
    scanf(" %c",&c);
    }
   fclose(fp_out1);
   fclose(fp_out2);
    fclose(fp_out3);
}

