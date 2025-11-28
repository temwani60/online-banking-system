#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

int main() {
    struct user usr, usr2;
    FILE *fp, *fp2;
    char filename[50], phone[50], pword[50];
    int opt, choice;
    char cont = 'y';

    while (1) {
        printf("\n==============================");
        printf("\n   SIMPLE ONLINE BANKING APP");
        printf("\n==============================");
        printf("\n1. Register an account");
        printf("\n2. Login to your account");
        printf("\n3. Exit");
        printf("\n\nYour choice: ");
        scanf("%d", &opt);

        if (opt == 1) {
            system("clear");
            printf("Enter Account Number: ");
            scanf("%s", usr.ac);

            printf("Enter Phone Number: ");
            scanf("%s", usr.phone);

            printf("Create Password: ");
            scanf("%s", usr.password);

            usr.balance = 0;

            strcpy(filename, usr.ac);
            strcat(filename, ".dat");

            fp = fopen(filename, "w");
            if (fp == NULL) {
                printf("\nError creating account!\n");
                continue;
            }

            fwrite(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            printf("\nAccount successfully registered!\n");
        }

        else if (opt == 2) {
            system("clear");

            printf("Enter Account Number: ");
            scanf("%s", phone);

            printf("Enter Password: ");
            scanf("%s", pword);

            strcpy(filename, phone);
            strcat(filename, ".dat");

            fp = fopen(filename, "r");
            if (fp == NULL) {
                printf("\nAccount does not exist!\n");
                continue;
            }

            fread(&usr, sizeof(struct user), 1, fp);
            fclose(fp);

            if (strcmp(pword, usr.password) == 0) {
                printf("\nLogin successful!\n");

                while (cont == 'y') {
                    printf("\n==============================");
                    printf("\n      ACCOUNT MENU");
                    printf("\n==============================");
                    printf("\n1. Check Balance");
                    printf("\n2. Deposit Funds");
                    printf("\n3. Withdraw Funds");
                    printf("\n4. Change Password");
                    printf("\n5. Display Account Details");
                    printf("\n6. Transfer Funds");
                    printf("\n7. Logout");

                    printf("\n\nEnter option: ");
                    scanf("%d", &choice);

                    switch (choice) {

                    case 1:
                        printf("\nYour balance: %.2f\n", usr.balance);
                        break;

                    case 2: {
                        float amount;
                        printf("\nEnter amount to deposit: ");
                        scanf("%f", &amount);

                        usr.balance += amount;

                        fp = fopen(filename, "w");
                        fwrite(&usr, sizeof(struct user), 1, fp);
                        fclose(fp);

                        printf("\nDeposit successful! New balance: %.2f\n", usr.balance);
                        break;
                    }

                    case 3: {
                        float amount;
                        printf("\nEnter amount to withdraw: ");
                        scanf("%f", &amount);

                        if (amount > usr.balance) {
                            printf("\nInsufficient funds!\n");
                        } else {
                            usr.balance -= amount;

                            fp = fopen(filename, "w");
                            fwrite(&usr, sizeof(struct user), 1, fp);
                            fclose(fp);

                            printf("\nWithdrawal successful! New balance: %.2f\n", usr.balance);
                        }
                        break;
                    }

                    case 4: {
                        char newpass[50];
                        printf("\nEnter new password: ");
                        scanf("%s", newpass);

                        strcpy(usr.password, newpass);

                        fp = fopen(filename, "w");
                        fwrite(&usr, sizeof(struct user), 1, fp);
                        fclose(fp);

                        printf("\nPassword changed successfully!\n");
                        break;
                    }

                    case 5:
                        printf("\n===== ACCOUNT DETAILS =====");
                        printf("\nAccount Number: %s", usr.ac);
                        printf("\nPhone Number:   %s", usr.phone);
                        printf("\nBalance:        %.2f\n", usr.balance);
                        break;

                    case 6: {
                        char recv_ac[50], recv_file[50];
                        float amount;

                        printf("\nEnter receiver account number: ");
                        scanf("%s", recv_ac);

                        strcpy(recv_file, recv_ac);
                        strcat(recv_file, ".dat");

                        fp2 = fopen(recv_file, "r");
                        if (fp2 == NULL) {
                            printf("\nReceiver account does not exist!\n");
                            break;
                        }

                        fread(&usr2, sizeof(struct user), 1, fp2);
                        fclose(fp2);

                        printf("Enter amount to transfer: ");
                        scanf("%f", &amount);

                        if (amount > usr.balance) {
                            printf("\nInsufficient funds!\n");
                            break;
                        }

                        usr.balance -= amount;
                        usr2.balance += amount;

                        // Update sender file
                        fp = fopen(filename, "w");
                        fwrite(&usr, sizeof(struct user), 1, fp);
                        fclose(fp);

                        // Update receiver file
                        fp2 = fopen(recv_file, "w");
                        fwrite(&usr2, sizeof(struct user), 1, fp2);
                        fclose(fp2);

                        printf("\nTransfer successful!");
                        printf("\nYou sent %.2f to account %s", amount, recv_ac);
                        printf("\nYour new balance: %.2f\n", usr.balance);
                        break;
                    }

                    case 7:
                        cont = 'n';
                        break;

                    default:
                        printf("\nInvalid option!\n");
                    }
                }

                cont = 'y';
            } 
            else {
                printf("\nIncorrect password!\n");
            }
        }

        else if (opt == 3) {
            printf("\nThank you for using our banking system!\n");
            break;
        }

        else {
            printf("\nInvalid option. Try again.\n");
        }
    }

    return 0;
}