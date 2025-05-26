// calculates the total employee claims and average employee claims
#include"structure.h"
int read(stv_e s[],FILE*fp_in)
{
    char line[100];
    char*item;
    int i=0;
    fgets(line,sizeof(line),fp_in);
    while(fgets(line,sizeof(line),fp_in)!=NULL)
    {
    item=strtok(line,",");
    if(item!=NULL)
    {
        strcpy(s[i].Name,item);
        item=strtok(NULL,",");
        {
            if(item!=NULL)
             strcpy(s[i].ID,item);
             for(int j=0;j<4;j++)
             item=strtok(NULL,",");
            if(item!=NULL)
                {
                    s[i].Claims=atoi(item);
                    i++;
                }
        }
    }
}
    return i;   
}
void display(int c,FILE*fp_in,FILE*fp_out,stv_e s[],float avg)
{
    for(int i=0;i<c;i++)
    {
        fprintf(fp_out,"\nNAME: %s\nID: %s\nCLAIMS: %ld\n",s[i].Name,s[i].ID,s[i].Claims);
    }
    fprintf(fp_out,"\nAVERAGE CLAIMS: %.2f\n",avg);
    printf("\nAVERAGE CLAIMS: %.2f\n",avg);
}
float Avg(FILE *fp_in,stv_e s[],int c)
{
    float avg=0.0;
    for(int i=0;i<c;i++)
    {
        avg=avg+s[i].Claims;
    }
    return avg/c;
}
int main()
{
    FILE *fp_in=fopen("indian_employee_data.csv","r");
    FILE *fp_out=fopen("claims_details.csv","w");
    if(fp_in==NULL)
    printf("ERROR IN OPENING INPUT FILE. \n");
    if(fp_out==NULL)
    printf("ERROR IN OPENING OUTPUT FILE. \n");

    stv_e s[100];
    int count =read(s,fp_in);
    fclose(fp_in);

    fprintf(fp_out,"EMPLOYEE CLAIM DETAILS: \n");
    float avg=Avg(fp_in,s,count);
    display(count,fp_in,fp_out,s,avg);

    printf("FUNCTION SUCCESSFUL, CHECK \"claims_details.csv\" FOR MORE DETAILS.\n");
    fclose(fp_out);
}
