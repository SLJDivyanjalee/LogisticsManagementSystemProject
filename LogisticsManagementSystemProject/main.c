#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50

void mainMenu();
void cityManagement();
void distanceManagement();

//city management functions
void addCity();
void displayCities();
void renameCity();
void removeCity();
int searchCity(char name[]);
void toLowerCase(char str[]);

//distance management functions
void initializeDistances();
void inputDistance();
void editDistance();
void viewDistanceTable();

char cities[MAX_CITIES][NAME_LENGTH];
int cityCount = 0;
int distances[MAX_CITIES][MAX_CITIES];

int main()
{
    printf("\n      Logistics Management System  \n");
    printf("---------------------------------------\n");

    initializeDistances();

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
                cityManagement();
                break;
            case 2:
                printf("\n--- Distance Management ---\n");
                distanceManagement();
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

// -------------------------- City Management ----------------------
void cityManagement() {
    int choice;
    do {
        printf(" \tMenu \n");
        printf("1. Add a new city\n");
        printf("2. Display all cities\n");
        printf("3. Rename a city\n");
        printf("4. Remove a city\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCity(); //add a new city
                break;
            case 2:
                displayCities(); //view all cities
                break;
            case 3:
                renameCity(); // rename a city
                break;
            case 4:
                removeCity(); //delete a city
                break;
            case 5:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}

void addCity() {
    if (cityCount >= MAX_CITIES) {
        printf("Can't add more cities; list is full.\n");
        return;
    }

    char cityName[NAME_LENGTH];

    while (getchar() != '\n');

    printf("Enter city name: ");
    fgets(cityName, NAME_LENGTH, stdin);
    cityName[strcspn(cityName, "\n")] = '\0'; // remove newline

    if (strlen(cityName) == 0) {
        printf("City name can't be empty!\n");
        return;
    }

    if (searchCity(cityName) != -1) {
        printf("City '%s' already exists!\n", cityName);
        return;
    }

    strcpy(cities[cityCount], cityName);
    cityCount++;
    printf("%s added successfully!\n", cityName);
}

void displayCities() {
    if (cityCount == 0) {
        printf("No cities in the system.\n");
        return;
    }

    printf("=== List of Cities (%d/%d) ===\n", cityCount, MAX_CITIES);
    for (int i = 0; i < cityCount; i++) {
        printf("%d. %s\n", i + 1, cities[i]);
    }
}

int searchCity(char name[]) {
    char searchCity[NAME_LENGTH];
    strcpy(searchCity, name);
    toLowerCase(searchCity);

    for (int i = 0; i < cityCount; i++) {
        char currentCity[NAME_LENGTH];
        strcpy(currentCity, cities[i]);
        toLowerCase(currentCity);

        if (strcmp(currentCity, searchCity) == 0) {
            return i;
        }
    }
    return -1;
}

void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
}

void renameCity() {
    if (cityCount == 0) {
        printf("No cities available\n");
        return;
    }

    char cityName[NAME_LENGTH], newCityName[NAME_LENGTH];

    while (getchar() != '\n');

    printf("Enter city name you want to rename :");
    fgets(cityName, NAME_LENGTH, stdin);
    cityName[strcspn(cityName, "\n")] = '\0';

    int index = searchCity(cityName);
    if (index == -1) {
        printf("%s not found!\n", cityName);
        return;
    }

    printf("Enter new city name: ");
    fgets(newCityName, NAME_LENGTH, stdin);
    newCityName[strcspn(newCityName, "\n")] = '\0';

    if (strlen(newCityName) == 0) {
        printf("city name can't be empty!\n");
        return;
    }

    printf("City renamed from '%s' to '%s'\n", cities[index], newCityName);
    strcpy(cities[index], newCityName); //overwrite city name
}

void removeCity() {
    if (cityCount == 0) {
        printf("No cities available\n");
        return;
    }

    char cityName[NAME_LENGTH];

    while (getchar() != '\n');

    printf("Enter city name you want to remove:");
    fgets(cityName, NAME_LENGTH, stdin);
    cityName[strcspn(cityName, "\n")] = '\0'; // remove newline

    int index = searchCity(cityName);
    if (index == -1) {
        printf("Error: City '%s' not found!\n", cityName);
        return;
    }

    for (int i = index; i < cityCount - 1; i++) {
        strcpy(cities[i], cities[i + 1]);  //copies a string from one array position to another
    }
    cityCount--;
    printf("City '%s' removed successfully!\n", cityName);
    }

// -------------------------- Distance Management ----------------------
void distanceManagement() {
    int choice;
    do {
        printf(" \tMenu \n");
        printf("1. Input distance between cities\n");
        printf("2. Edit distance between cities\n");
        printf("3. Display distance table\n");
        printf("4. Back to Main Menu\n");

        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                inputDistance();
                break;
            case 2:
                editDistance();
                break;
            case 3:
                viewDistanceTable();
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);
}

void initializeDistances() {
    for (int i = 0; i < MAX_CITIES; i++) {
        for (int j = 0; j < MAX_CITIES; j++) {
            if (i == j) {
                distances[i][j] = 0;
            } else {
                distances[i][j] = -1;
            }
        }
    }
}

void inputDistance() {
    if (cityCount < 2) {
        printf("need at least 2 cities to input distances!\n");
        return;
    }

    char cityOne[NAME_LENGTH], cityTwo[NAME_LENGTH];
    int distance;

    printf("\nCities:\n");
    displayCities();

    printf("\nEnter first city name: ");
    fgets(cityOne, NAME_LENGTH, stdin);
    cityOne[strlen(cityOne)-1] = '\0';

    printf("Enter second city name: ");
    fgets(cityTwo, NAME_LENGTH, stdin);
    cityTwo[strlen(cityTwo)-1] = '\0';

    int inputOne = searchCity(cityOne);
    int inputTwo = searchCity(cityTwo);

    if (inputOne == -1 || inputTwo == -1) {
        printf("Error: One or both cities not found!\n");
        return;
    }

    if (inputOne == inputTwo) {
        printf("Error: Cannot set distance from city to itself!\n");
        return;
    }

    printf("Enter distance between %s and %s (in km): ", cities[inputOne], cities[inputTwo]);
    scanf("%d", &distance);
    getchar();

    if (distance <= 0) {
        printf("Error: Distance must be positive!\n");
        return;
    }

    distances[inputOne][inputTwo] = distance;
    distances[inputTwo][inputOne] = distance;
    printf("Distance set successfully!\n");
}

void viewDistanceTable() {
    if (cityCount == 0) {
        printf("No cities in the system.\n");
        return;
    }

    printf("\n=== Distance Table ===\n\n");
    printf("%-15s", "");
    for (int i = 0; i < cityCount; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    for (int i = 0; i < cityCount; i++) {
        printf("%-15s", cities[i]);
        for (int j = 0; j < cityCount; j++) {
            if (i == j) {
                printf("%-15s", "0");
            } else if (distances[i][j] == -1) {
                printf("%-15s", "-");
            } else {
                printf("%-15d", distances[i][j]);
            }
        }
        printf("\n");
    }
}

void editDistance() {
    if (cityCount < 2) {
        printf("need at least 2 cities to edit distances!\n");
        return;
    }

    char cityOne[NAME_LENGTH], cityTwo[NAME_LENGTH];
    int distance;

    printf("\nEnter first city name: ");
    fgets(cityOne, NAME_LENGTH, stdin);
    cityOne[strlen(cityOne)-1] = '\0';

    printf("Enter second city name: ");
    fgets(cityTwo, NAME_LENGTH, stdin);
    cityTwo[strlen(cityTwo)-1] = '\0';

    int inputOne = searchCity(cityOne);
    int inputTwo = searchCity(cityTwo);

    if (inputOne == -1 || inputTwo == -1) {
        printf("cities not found!\n");
        return;
    }

    if (distances[inputOne][inputTwo] == -1) {
        printf("no distance entered between these cities!\n");
        return;
    }

    printf("Current distance: %d km\n", distances[inputOne][inputTwo]);
    printf("Enter new distance(km): ");
    scanf("%d", &distance);
    getchar();

    distances[inputOne][inputTwo] = distance;
    distances[inputTwo][inputOne] = distance;
    printf("Distance updated successfully!\n");
}

