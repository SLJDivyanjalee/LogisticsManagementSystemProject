#include <stdio.h>
#include <stdlib.h>

mainMenu();

int main()
{
    printf("\n      Logistics Management System  \n");
    printf("---------------------------------------\n");

    mainMenu();
    return 0;
}

void mainMenu(){
    int choice;
    do{
        printf("\n      .-Main Menu-.\n");
        printf(" 01. City Management\n");
        printf(" 02. Distance Management\n");
        printf(" 03. Vehicle Management\n");
        printf(" 04. Delivery Request Handling\n");
        printf(" 05. Cost, Time and Fuel Calculations\n");
        printf(" 06. Delivery Records\n");
        printf(" 07. Finding the Least-Cost Route\n");
        printf(" 08. Performance Reports\n");
        printf(" 09. Save Data to Files\n");
        printf(" 10. Exit\n\n");

        printf("Enter your choice (1-10): ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("\n--- City Management ---\n");
                break;
            case 2:
                printf("\n--- Distance Management ---\n");
                break;
            case 3:
                printf("\n--- Vehicle Management ---\n");
                break;
            case 4:
                printf("\n--- Delivery Request Handling ---\n");
                break;
            case 5:
                printf("\n--- Cost Time Fuel Calculations ---\n");
                break;
            case 6:
                printf("\n--- Delivery Records ---\n");
                break;
            case 7:
                printf("\n--- Least Cost Route ---\n");
                break;
            case 8:
                printf("\n--- Performance Reports ---\n");
                break;
            case 9:
                printf("\nSaving data\n");
                break;
            case 10:
                printf("\nExiting from the system\n"); //this will exit from the system without saving
                break;
            default:
                printf("\nInvalid input. please try again\n");
                break;
        }
    } while(choice != 10);
}
