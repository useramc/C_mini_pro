//PROGRAM TO SORT BASED ON SALARY [HIGHEST TO LOWEST]
#include"structure.h"
void display(stv_e *s, int c,FILE *fp_out) {
    for (int i = 0; i < c; i++) 
    {
		fprintf(fp_out,"%s,%s,%d\n", s[i].Name,s[i].ID,s[i].Salary);
    }
    printf("Sorting Successful, check \"sorted salary details.csv\".\n");
}
void swap(stv_e*a,stv_e*b) {
    stv_e temp = *a;
    *a = *b;
    *b = temp;
}

void sortBysal(stv_e *s, int n) {
    int i, j, pos;
    for (i = 0; i < n - 1; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) 
        {
            if (s[j].Salary >s[pos].Salary) 
            {
                pos = j;
            }
        }
        if (pos!= i) 
        {
            swap(&s[i], &s[pos]);
        }
    }
}

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

int main()
{
FILE *fp_in=fopen("indian_employee_data.csv","r");//source file location
FILE *fp_out=fopen("Sorted Salary details.csv","w");//output file
if (fp_in == NULL) 
    {
        printf("File NOT ACCESSIBLE\n");
       
    }
    
    stv_e s[100];
    int count = read(s,fp_in);
    fclose(fp_in);
    fprintf(fp_out,"NAME,EMP ID,SALARY\n");
    sortBysal(s,count);
    display(s,count,fp_out);
}
