#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EMPLOYEES 1000
#define FILENAME "indian_employee_data.csv"
#define OUTPUT_FILENAME "updated_employees.csv"
typedef struct Employee {
    char Name[50];
    char ID[10];
    int Salary;
    int No_of_leaves;
    int No_of_paid_leaves;
    int Claims;
    int Years_of_service;
} employee_details;
int loadEmployees(employee_details employees[]) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file.\n");
        return 0;
    }
    int count = 0;
    char line[256];
    fgets(line, sizeof(line), file); // Skip header
    while (fgets(line, sizeof(line), file) && count < MAX_EMPLOYEES) {
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%d,%d",
               employees[count].Name,
               employees[count].ID,
               &employees[count].Salary,
               &employees[count].No_of_leaves,
               &employees[count].No_of_paid_leaves,
               &employees[count].Claims,
               &employees[count].Years_of_service);
        count++;
    }
    fclose(file);
    return count;
}
void saveEmployees(employee_details employees[], int count) {
    FILE *file = fopen(OUTPUT_FILENAME, "w");
    if (!file) {
        printf("Error saving file.\n");
        return;
    }
    fprintf(file, "Name,ID,Salary,No_of_leaves,No_of_paid_leaves,Claims,Years_of_service\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%s,%d,%d,%d,%d,%d\n",
                employees[i].Name,
                employees[i].ID,
                employees[i].Salary,
                employees[i].No_of_leaves,
                employees[i].No_of_paid_leaves,
                employees[i].Claims,
                employees[i].Years_of_service);
    }
    fclose(file);
    printf("Changes saved to '%s'\n", OUTPUT_FILENAME);
}
void viewBySalary(employee_details employees[], int count, int salary) {
    printf("\nEmployees with Salary = %d:\n", salary);
    for (int i = 0; i < count; i++) {
        if (employees[i].Salary == salary) {
            printf("%s (%s)\n", employees[i].Name, employees[i].ID);
        }
    }
}
int deleteEmployee(employee_details employees[], int count, char id[]) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].ID, id) == 0) {
            for (int j = i; j < count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            found = 1;
            count--;
            break;
        }
    }
    if (found) {
        printf("Employee with ID %s deleted.\n", id);
    } else {
        printf("Employee with ID %s not found.\n", id);
    }
    return count;
}
void salaryDistribution(employee_details employees[], int count) {
    int below30 = 0, between30and50 = 0, above50 = 0;
    for (int i = 0; i < count; i++) {
        if (employees[i].Salary < 30000)
            below30++;
        else if (employees[i].Salary <= 50000)
            between30and50++;
        else
            above50++;
    }
    printf("\nSalary Distribution:\n");
    printf("< 30,000: %d employees\n", below30);
    printf("30k – 50k: %d employees\n", between30and50);
    printf("> 50,000: %d employees\n", above50);
}
void calculateBonus(employee_details employees[], int count) {
    printf("\nBonus Report:\n");
    for (int i = 0; i < count; i++) {
        int bonus = employees[i].Years_of_service * 1000;
        printf("%s (%s) => Bonus: ₹%d\n", employees[i].Name, employees[i].ID, bonus);
    }
}
int main() {
    employee_details employees[MAX_EMPLOYEES];
    int count = loadEmployees(employees);
    int choice;

    if (count == 0) {
        printf("No data loaded. Exiting...\n");
        return 1;
    }
    do {
        printf("\n--- Employee Management (Person 4) ---\n");
        printf("1. View Employees with a Given Salary\n");
        printf("2. Delete Employee by ID\n");
        printf("3. Salary Distribution Report\n");
        printf("4. Calculate Bonus\n");
        printf("5. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 
        if (choice == 1) {
            int salary;
            printf("Enter salary to search: ");
            scanf("%d", &salary);
            viewBySalary(employees, count, salary);
        } else if (choice == 2) {
            char id[10];
            printf("Enter ID to delete: ");
            scanf("%s", id);
            count = deleteEmployee(employees, count, id);
        } else if (choice == 3) {
            salaryDistribution(employees, count);
        } else if (choice == 4) {
            calculateBonus(employees, count);
        } else if (choice == 5) {
            saveEmployees(employees, count);
        } else {
            printf("Invalid choice.\n");
        }
    } while (choice != 5);
    return 0;
}
