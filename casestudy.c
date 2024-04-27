#include<stdio.h>
#include<string.h>

struct bankaccount
{
    int account_number;
    char customer_name[50];
    float balance;
};

struct bankaccount accounts[100];
int num_accounts=0;

enum menuoption
{
    Create_account=1,check_balence,Deposit,Withdraw,exit
};

void create_account()
{
    struct bankaccount account;
    account.account_number=num_accounts+1;
    printf("Enter customer name:");
    scanf("%s",account.customer_name);
    printf("Enter initial balance:");
    scanf("%f",&account.balance);
    accounts[num_accounts]=account;
    num_accounts++;
    printf("Account created successfully. Account number: %d\n",account.account_number);
}

void displayaccountinfo(int account_number)
{
    for(int i=0;i<num_accounts;i++)
     {
        if(accounts[i].account_number==account_number)
        {
            printf("Account Number:%d\n",accounts[i].account_number);
            printf("Customer Name:%s\n",accounts[i].customer_name);
            printf("Balance:%.2f\n",accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");

}

void balenceinquiry(int account_number)
 {
    for(int i=0;i<num_accounts;i++) 
    {
        if(accounts[i].account_number==account_number)
        {
            printf("Balance:%.2f\n",accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

void deposit(int account_number,float amount)
{
    for(int i=0;i<num_accounts;i++) 
    {
        if(accounts[i].account_number==account_number)
         {
            accounts[i].balance+=amount;
            printf("Deposit successful. New balance:%.2f\n",accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}
void withdraw(int account_number,float amount)
 {
    for(int i=0;i<num_accounts;i++) 
    {
        if(accounts[i].account_number==account_number)
         {
            if(accounts[i].balance>=amount) 
            {
                accounts[i].balance-=amount;
                printf("Withdrawal successful.New balance:%.2f\n",accounts[i].balance);
            } else 
            {
                printf("Insufficient balance.\n");
            }
            return;
        }
    }
    printf("Account not found.\n");
}

int main()
{
    int choice;
    while (1) {
        printf("\nBanking System Menu:\n");
        printf("1.Create Customer Account\n");
        printf("2.Check Balance\n");
        printf("3.Deposit\n");
        printf("4.Withdraw\n");
        printf("5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) 
        {
            case Create_account:
                create_account();
                break;
            case check_balence:
                printf("Enter account number: ");
                int acc_num;
                scanf("%d",&acc_num);
                displayaccountinfo(acc_num);
                break;
            case Deposit:
                printf("Enter account number: ");
                scanf("%d",&acc_num);
                printf("Enter deposit amount: ");
                float deposit_amount;
                scanf("%f",&deposit_amount);
                deposit(acc_num,deposit_amount);
                break;
            case Withdraw:
                printf("Enter account number: ");
                scanf("%d",&acc_num);
                printf("Enter withdrawal amount: ");
                float withdraw_amount;
                scanf("%f",&withdraw_amount);
                withdraw(acc_num,withdraw_amount);
                break;
            case exit:
                printf("Exiting the program.Thank you!\n");
                return 0;
            default:
                printf("Invalid choice.Please try again.\n");
}
    }
}