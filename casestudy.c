#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define filename "case.txt"

// Structure to represent a bank account
struct account {
    int accno;
    char name[50];
    float balance;
};

// Function prototypes
void createaccount();
void deposit();
void withdraw();
void checkbalance();
void displayall();

int main() {
    int choice;

    while (1) {
        printf("\nBanking Management System\n");
        printf("1. Create account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check balance\n");
        printf("5. Display all accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createaccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkbalance();
                break;
            case 5:
                displayall();
                break;
            case 6:
                printf("Exiting.Thank you");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

// Function to create a new account
void createaccount() {
    struct account acc;
    FILE *fp;

    printf("\nEnter account number: ");
    scanf("%d", &acc.accno);
    printf("Enter name: ");
    scanf("%s", acc.name);
    printf("Enter initial balance: ");
    scanf("%f", &acc.balance);

    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error in opening file\n");
        return;
    }

    fprintf(fp, "%d %s %.2f\n", acc.accno, acc.name, acc.balance);
    fclose(fp);
    printf("account created successfully.\n");
}

// Function to deposit money into an account
void deposit() {
    int accno;
    float amount;
    struct account acc;
    FILE *fp, *temp;

    printf("\nEnter account number: ");
    scanf("%d", &accno);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error in opening file!n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error in opening file\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %f", &acc.accno, acc.name, &acc.balance) != EOF) {
        if (acc.accno == accno) {
            acc.balance += amount;
        }
        fprintf(temp, "%d %s %.2f\n", acc.accno, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
    printf("Amount deposited successfully.\n");
}

// Function to withdraw money from an account
void withdraw() {
    int accno;
    float amount;
    struct account acc;
    FILE *fp, *temp;

    printf("\nEnter account number: ");
    scanf("%d", &accno);
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error in opening file\n");
        return;
    }

    temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error in opening file\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %f", &acc.accno, acc.name, &acc.balance) != EOF) {
        if (acc.accno == accno) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
            } else {
                printf("Insufficient balance.\n");
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }
        }
        fprintf(temp, "%d %s %.2f\n", acc.accno, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
    printf("Amount withdrawn successfully\n");
}

// Function to check balance of an account
void checkbalance() {
    int accno;
    struct account acc;
    FILE *fp;

    printf("\nEnter account number: ");
    scanf("%d", &accno);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error in  opening file\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &acc.accno, acc.name, &acc.balance) != EOF) {
        if (acc.accno == accno) {
            printf("Balance: %.2f\n", acc.balance);
            fclose(fp);
            return;
        }
    }

    printf("account not found.\n");
    fclose(fp);
}

// Function to display details of all accounts
void displayall() {
    struct account acc;
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nAccount Details\n");
    printf("--------------------------------------------------\n");
    printf("Acc No\tName\t\tBalance\n");
    printf("--------------------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &acc.accno, acc.name, &acc.balance) != EOF) {
        printf("%d\t%s\t\t%.2f\n", acc.accno, acc.name, acc.balance);
    }

    fclose(fp);
}
