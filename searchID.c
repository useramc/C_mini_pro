// program to search EMPLOYEE by ID and display their details
//BONUS: RECENT SEARCH HISTORY AND COMPLETE SEARCH HISTORY CAN BE ACCESSED
#include "structure.h"  // Ensure stv_e is defined properly here

int read(stv_e *s, FILE *fp) {
    char line[100];
    char *item;
    int i = 0;

    fgets(line, sizeof(line), fp); 
    while (fgets(line, sizeof(line), fp) != NULL) {
        item = strtok(line, ",");
        if (item != NULL) {
            strcpy(s[i].Name, item);

            item = strtok(NULL, ",");
            if (item != NULL)
                strcpy(s[i].ID, item);

            item = strtok(NULL, ",");
            if (item != NULL)
                s[i].Salary = atoi(item);

            // Skip next 3 columns
            for (int j = 0; j < 3; j++) item = strtok(NULL, ",");

            // Years column
            item = strtok(NULL, ",");
            if (item != NULL) {
                s[i].Years = atoi(item);
                i++;
            }
        }
    }
    return i;
}

void search(char eID[20], stv_e s[], int c, FILE *fp_out2, FILE *fp_out1) {
    int flag = 0;
    for (int i = 0; i < c; i++) {
        if (strcmp(s[i].ID, eID) == 0) {
            flag = 1;
            printf("EMPLOYEE FOUND!\n");
            printf("NAME: %s\nSALARY: %ld\nYEARS OF SERVICE: %d\n", s[i].Name, s[i].Salary, s[i].Years);
            fprintf(fp_out2, "ID SEARCHED: %s\nNAME: %s\nSALARY: %ld\nYEARS OF SERVICE: %d\n\n", eID, s[i].Name, s[i].Salary, s[i].Years);
            fprintf(fp_out1, "ID SEARCHED: %s\nNAME: %s\nSALARY: %ld\nYEARS OF SERVICE: %d\n\n", eID, s[i].Name, s[i].Salary, s[i].Years);
            break;
        }
    }
    if (!flag) {
        printf("EMPLOYEE NOT FOUND\n");
        fprintf(fp_out2, "ID SEARCHED: %s\nID NOT FOUND, NO DATA AVAILABLE\n\n", eID);
        fprintf(fp_out1, "ID SEARCHED: %s\nID NOT FOUND, NO DATA AVAILABLE\n\n", eID);
    }
}

int main() {
    FILE *fp_out2 = fopen("history.txt", "a");
    FILE *fp_out1 = fopen("RECENT_history.txt", "w");
    if (fp_out1) fprintf(fp_out1, "SEARCH HISTORY\n");

    char ch = 'Y';
    while (ch != 'n' && ch != 'N') {
        FILE *fp_in = fopen("indian_employee_data.csv", "r");
        if (fp_in == NULL) {
            printf("File NOT ACCESSIBLE\n");
            return 1;
        }

        char eID[20];
        printf("ENTER THE ID: ");
        scanf("%s", eID);

        stv_e s[100];
        int count = read(s, fp_in);
        fclose(fp_in);

        search(eID, s, count, fp_out2, fp_out1);

        printf("\nDO YOU WANT TO CONTINUE? (Y/N): ");
        scanf(" %c", &ch);
    }

    printf("\nDO YOU WANT TO ACCESS SEARCH HISTORY? (y/n): ");
    scanf(" %c", &ch);
    if (ch == 'y' || ch == 'Y') 
    {
        printf("PLEASE REFER THE DOCUMENT \"history.txt\".\n");
    }
    else
    printf("EXITING...");

    fclose(fp_out1);
    fclose(fp_out2);
    return 0;
}
