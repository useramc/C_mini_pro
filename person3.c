// integrated P3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 50
#define MAX_LINE_LENGTH 256
#define PASSWORD "PES2UG24CS" 
#define MAX_ATTEMPTS 3     

typedef struct Employee {   //already present in main
    char Name[50];
    char ID[10];
    int Salary;
    int No_of_leaves;
    int No_of_paid_leaves;
    int Claims;
    int Years_of_service;
} employee_details;


int read(employee_details s[]) {   //already present in main
    FILE *fp = fopen("indian_employee_data.csv", "r");
    if (!fp) {
        printf("Error: Unable to open input file.\n");
        exit(1);
    }

    char line[200], *item;
    int i = 0;
    fgets(line, sizeof(line), fp); // Skip header
    while (fgets(line, sizeof(line), fp)) {
        item = strtok(line, ",");
        if (item) strcpy(s[i].Name, item);
        item = strtok(NULL, ",");
        if (item) strcpy(s[i].ID, item);
        item = strtok(NULL, ",");
        if (item) s[i].Salary = atoi(item);
        item = strtok(NULL, ",");
        if (item) s[i].No_of_leaves = atoi(item);
        item = strtok(NULL, ",");
        if (item) s[i].No_of_paid_leaves = atoi(item);
        item = strtok(NULL, ",");
        if (item) s[i].Claims = atoi(item);
        item = strtok(NULL, ",");
        if (item) s[i].Years_of_service = atoi(item);
        i++;
    }
    fclose(fp);
    return i;
}
int authenticate_user() {     //already present in main
    char input_password[50];
    int attempts = 0;

    printf("=== Payroll System Access ===\n");// LETS REPLACE THIS PART WITH SMTG ELSE !! SO THAT IT IN OTHER FUNCTIONS
    while (attempts < MAX_ATTEMPTS) {
        printf("Enter password (Attempt %d/%d): ", attempts + 1, MAX_ATTEMPTS);
        scanf("%s", input_password);

        if (strcmp(input_password, PASSWORD) == 0) {
            printf("Access granted!\n");
            return 1;  // Success
        } else {
            printf("Incorrect password. Try again.\n");
            attempts++;
        }
    }
    return 0;  // Failed all attempts
}
float avg_claims(employee_details s[], int c) {
    float total = 0.0;
    for (int i = 0; i < c; i++) {
        total += s[i].Claims;
    }
    return total / c;
}

void display_claims(employee_details s[], int c) {
    FILE *fp = fopen("claims_details.csv", "w");
    if (!fp) {
        printf("Error: Unable to write claims details.\n");
        return;
    }

    float avg = avg_claims(s, c);
    for (int i = 0; i < c; i++) {
        fprintf(fp, "\nNAME: %s\nID: %s\nCLAIMS: %d\n", s[i].Name, s[i].ID, s[i].Claims);
    }
    fprintf(fp, "\nAVERAGE CLAIMS: %.2f\n", avg);
    fclose(fp);

    printf("\nAVERAGE CLAIMS: %.2f\n", avg);
}

void sort_by_salary(employee_details s[], int c) {
    for (int i = 0; i < c - 1; i++) {
        for (int j = i + 1; j < c; j++) {
            if (s[j].Salary > s[i].Salary) {
                employee_details temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

void display_sorted_salary(employee_details s[], int c) {
    FILE *fp = fopen("Sorted Salary details.csv", "w");
    if (!fp) {
        printf("Error: Unable to write sorted salary details.\n");
        return;
    }

    fprintf(fp, "NAME,EMP ID,SALARY\n");
    for (int i = 0; i < c; i++) {
        fprintf(fp, "%s,%s,%d\n", s[i].Name, s[i].ID, s[i].Salary);
    }
    fclose(fp);

    printf("Sorting successful. Check \"Sorted Salary details.csv\".\n");
}

void filter_salary_range(employee_details s[], int c, long int ur, long int lr) {
    FILE *fp = fopen("details.csv", "w");
    if (!fp) {
        printf("Error: Unable to write salary range filter results.\n");
        return;
    }

    if (lr > ur) { long int t = lr; lr = ur; ur = t; }

    fprintf(fp, "EMPLOYEES WITH SALARY RANGE %ld - %ld\n\n", lr, ur);
    for (int i = 0; i < c; i++) {
        if (s[i].Salary >= lr && s[i].Salary <= ur) {
            fprintf(fp, "NAME: %s\tSALARY: %d\n\n", s[i].Name, s[i].Salary);
        }
    }
    fclose(fp);
}

void analyze_leaves(employee_details s[], int c) {
    FILE *f1 = fopen("leaves_paid1.csv", "w");
    FILE *f2 = fopen("leaves_paid2.csv", "w");
    FILE *f3 = fopen("leaves_paid3.csv", "w");
    if (!f1 || !f2 || !f3) {
        printf("Error: Unable to write leave analysis.\n");
        return;
    }

    fprintf(f1, "DETAILS\n");
    fprintf(f2, "DETAILS\n");
    fprintf(f3, "DETAILS\n");

    for (int i = 0; i < c; i++) {
        if (s[i].No_of_leaves < s[i].No_of_paid_leaves) {
            fprintf(f1, "Name: %s\nLeaves: %d\nPaid Leaves: %d\nExtra Pending: %d\n\n",
                    s[i].Name, s[i].No_of_leaves, s[i].No_of_paid_leaves, s[i].No_of_paid_leaves - s[i].No_of_leaves);
        } else if (s[i].No_of_leaves == s[i].No_of_paid_leaves) {
            fprintf(f2, "Name: %s\nLeaves: %d\nPaid Leaves: %d\nExact Match\n\n",
                    s[i].Name, s[i].No_of_leaves, s[i].No_of_paid_leaves);
        } else {
            fprintf(f3, "Name: %s\nLeaves: %d\nPaid Leaves: %d\nExtra Taken: %d\n\n",
                    s[i].Name, s[i].No_of_leaves, s[i].No_of_paid_leaves, s[i].No_of_leaves - s[i].No_of_paid_leaves);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}

void search_by_id(employee_details s[], int c) {
    char eID[10], ch;
    FILE *f1 = fopen("history.txt", "a");
    FILE *f2 = fopen("RECENT_history.txt", "w");

    if (!f1 || !f2) {
        printf("Error: Unable to write search history.\n");
        return;
    }

    fprintf(f2, "SEARCH HISTORY\n");

    do {
        printf("ENTER EMPLOYEE ID TO SEARCH: ");
        scanf("%s", eID);

        int found = 0;
        for (int i = 0; i < c; i++) {
            if (strcmp(s[i].ID, eID) == 0) {
                found = 1;
                printf("EMPLOYEE FOUND!\nNAME: %s\nSALARY: %d\nYEARS OF SERVICE: %d\n", s[i].Name, s[i].Salary, s[i].Years_of_service);
                fprintf(f1, "ID: %s\nNAME: %s\nSALARY: %d\nYEARS OF SERVICE: %d\n\n", eID, s[i].Name, s[i].Salary, s[i].Years_of_service);
                fprintf(f2, "ID: %s\nNAME: %s\nSALARY: %d\nYEARS OF SERVICE: %d\n\n", eID, s[i].Name, s[i].Salary, s[i].Years_of_service);
                break;
            }
        }

        if (!found) {
            printf("EMPLOYEE NOT FOUND\n");
            fprintf(f1, "ID: %s NOT FOUND\n\n", eID);
            fprintf(f2, "ID: %s NOT FOUND\n\n", eID);
        }

        printf("Do you want to search again? (Y/N): ");
        scanf(" %c", &ch);
    } while (ch != 'n' && ch != 'N');
   
    int n=-1,r;
    printf("\nDO YOU WANT TO VIEW SEARCH HISTORY?(Y-1/N-0)\n");
    scanf("%d",&n);
    if(n==1)
    {
        if(authenticate_user())
        printf("SEARCH HISTORY IS ENABLED IN \"recent_history\" and \"search_history\". \n");
        else
        printf("ACCESS FAILED\n");
    }

    fclose(f1);
    fclose(f2);
}


int main()
 {
    employee_details s[100];// already present in main
    int count = read(s);//already present in main
    int choice;//already present in main

    printf("DO YOU WANT TO OBTAIN CLAIMS DETAILS?(1-YES/0-NO)\n");
    scanf("%d",&choice);
    if(choice==1)
    display_claims(s, count);
    if(choice!=0&& choice!=1)
    printf("INVALID INPUT!\n");

    printf("DO YOU WANT TO SORT EMPLOYEES BY THEIR SALARY?(1-YES/0-NO)\n");
    scanf("%d",&choice);
    if(choice==1)
    {
    sort_by_salary(s, count);
    display_sorted_salary(s, count);
    }
    if(choice!=0&& choice!=1)
    printf("INVALID INPUT!\n");


    printf("DO YOU WANT DETAILS OF EMPLOYEES WITHIN A SALARY RANGE?(1-YES/0-NO)\n");
    scanf("%d",&choice);    
    if(choice==1)
    {
    long int ur, lr;
    printf("Enter salary range (upper and lower): ");
    scanf("%ld%ld", &ur, &lr);
    filter_salary_range(s, count, ur, lr);
    }
    if(choice!=0&& choice!=1)
    printf("INVALID INPUT!\n");

    printf("DO YOU WANT DETAILS OF EMPLOYEES LEAVES ?(1-YES/0-NO)\n");
    scanf("%d",&choice);  
    if(choice==1)  
    analyze_leaves(s, count);
    if(choice!=0&& choice!=1)
    printf("INVALID INPUT!\n");

    printf("DO YOU WANT TO SEARCH EMPLOYEE BY EMPLOYEE ID?(1-YES/0-NO)\n");
    scanf("%d",&choice); 
    if(choice==1)     
    search_by_id(s, count);
    if(choice!=0&& choice!=1)
    printf("INVALID INPUT!\n");

}

