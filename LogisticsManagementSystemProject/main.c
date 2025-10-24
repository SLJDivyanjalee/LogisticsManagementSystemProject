#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 50
#define NUM_VEHICLES 3
#define MAX_DELIVERIES 100
#define FUEL_PRICE 310

void mainMenu();
void cityManagement();
void distanceManagement();
void vehicleManagement();
void deliveryRequestHandling();
void costTimeFuelCalculations();

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

//vehicle management functions
void initializeVehicles();
void displayVehicles();
int selectVehicle();

//delivery handling functions
void processDelivery();
void viewActiveDeliveries();

//cost,time,fuel calculation
void calculateDeliveryCost();
void viewAllCalculations();
void displayCalculationResults(int index);

char cities[MAX_CITIES][NAME_LENGTH];
int cityCount = 0;
int distances[MAX_CITIES][MAX_CITIES];

char vehicleTypes[3][20];
int vehicleCapacity[3];
int vehicleRatePerKm[3];
int vehicleAvgSpeed[3];
int vehicleFuelEfficiency[3];

int deliveryCount = 0;
int nextDeliveryId = 1;
int deliveryId[MAX_DELIVERIES];
int deliverytoCity[MAX_DELIVERIES];
int deliveryfromCity[MAX_DELIVERIES];
int deliveryWeight[MAX_DELIVERIES];
int deliveryVehicle[MAX_DELIVERIES];
int deliveryCompleted[MAX_DELIVERIES];
char deliveryCompletionTime[MAX_DELIVERIES][20];
float deliveryActualTime[MAX_DELIVERIES];

float deliveryCost[MAX_DELIVERIES];
float estimatedTime[MAX_DELIVERIES];
float fuelUsed[MAX_DELIVERIES];
float fuelCost[MAX_DELIVERIES];
float totalCost[MAX_DELIVERIES];
float profit[MAX_DELIVERIES];
float customerCharge[MAX_DELIVERIES];

int main()
{
    printf("\n      Logistics Management System  \n");
    printf("---------------------------------------\n");

    initializeDistances();
    initializeVehicles();

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
                vehicleManagement();
                break;
            case 4:
                printf("\n--- Delivery Request Handling ---\n");
                deliveryRequestHandling();
                break;
            case 5:
                printf("\n--- Cost Time Fuel Calculations ---\n");
                costTimeFuelCalculations();
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

// -------------------------- Vehicle Management ----------------------
void vehicleManagement() {
    int choice;
    do {
        printf(" \tMenu\n");
        printf("1. Select vehicle for estimation\n");
        printf("2. Back to Main Menu\n\n");
        printf("Enter your choice (1-2): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                selectVehicle();
                break;
            case 2:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 2);
}

void initializeVehicles() {
    strcpy(vehicleTypes[0], "Van");
    strcpy(vehicleTypes[1], "Truck");
    strcpy(vehicleTypes[2], "Lorry");

    vehicleCapacity[0] = 1000;
    vehicleCapacity[1] = 5000;
    vehicleCapacity[2] = 10000;

    vehicleRatePerKm[0] = 30;
    vehicleRatePerKm[1] = 40;
    vehicleRatePerKm[2] = 80;

    vehicleAvgSpeed[0] = 60;
    vehicleAvgSpeed[1] = 50;
    vehicleAvgSpeed[2] = 45;

    vehicleFuelEfficiency[0] = 12;
    vehicleFuelEfficiency[1] = 6;
    vehicleFuelEfficiency[2] = 4;
}

void displayVehicles() {
    printf("\n    - Available Vehicles -\n\n");
    printf("Type       Capacity    Rate/km    Speed    Fuel Efficiency   \n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < NUM_VEHICLES; i++) {
        printf("%-11s %-10d %-9d %-10d %-11d \n",
               vehicleTypes[i],
               vehicleCapacity[i],
               vehicleRatePerKm[i],
               vehicleAvgSpeed[i],
               vehicleFuelEfficiency[i]);

    }
}

int selectVehicle() {
    int choice;
    displayVehicles();

    printf("\n\nSelect vehicle type:\n");
    printf("1. Van\n");
    printf("2. Truck\n");
    printf("3. Lorry\n");
    printf("\nEnter your choice (1-3): ");
    scanf("%d", &choice);
    getchar();

    if (choice >= 1 && choice <= 3) {
        int index = choice - 1;
        printf("\nVehicle selected: %s\n", vehicleTypes[index]);
        return index;
    } else {
        printf("Invalid choice!\n");
        return -1;
    }
}

// -------------------------- Delivery Request Handling ----------------------
void deliveryRequestHandling() {
    int choice;
    do {
        printf(" \tMenu\n");
        printf("1. Create new delivery request\n");
        printf("2. View active deliveries\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                processDelivery();
                break;
            case 2:
                viewActiveDeliveries();
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

void processDelivery() {
    if (cityCount < 2) {
        printf("need at least 2 cities!\n");
        return;
    }

    if (deliveryCount >= MAX_DELIVERIES) {
        printf("maximum delivery capacity reached!\n");
        return;
    }

    int fromCity, toCity, weight, vehicleChoice;

    printf("\n cities:\n");
    displayCities();

    printf("\nEnter departure city number (1-%d): ", cityCount);
    scanf("%d", &fromCity);
    printf("Enter destination city number (1-%d): ", cityCount);
    scanf("%d", &toCity);
    printf("Enter package weight (kg): ");
    scanf("%d", &weight);
    printf("Select vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleChoice);
    getchar();

    fromCity--;
    toCity--;
    int vehicleIndex = vehicleChoice - 1;

    if (fromCity < 0 || fromCity >= cityCount || toCity < 0 || toCity >= cityCount) {
        printf("invalid city selection!\n");
        return;
    }

    if (fromCity == toCity) {
        printf("departure and destination cannot be same!\n");
        return;
    }

    if (distances[fromCity][toCity] == -1) {
        printf("no distance entered between these cities!\n");
        return;
    }

    if (weight > vehicleCapacity[vehicleIndex]) {
        printf("weight exceeds vehicle capacity!\n");
        return;
    }

    deliveryId[deliveryCount] = nextDeliveryId;
    deliveryfromCity[deliveryCount] = fromCity;
    deliverytoCity[deliveryCount] = toCity;
    deliveryWeight[deliveryCount] = weight;
    deliveryVehicle[deliveryCount] = vehicleIndex;
    deliveryCompleted[deliveryCount] = 0;

    printf("\nDelivery Created Successfully!\n");
    printf("ID: %d | Route: %s => %s\n", nextDeliveryId, cities[fromCity], cities[toCity]);

    nextDeliveryId++;
    deliveryCount++;
}

void viewActiveDeliveries() {
    if (deliveryCount == 0) {
        printf("No active deliveries.\n");
        return;
    }

    printf("\n\t Active Deliveries (%d) \n\n", deliveryCount);
    printf("%-12s %-20s %-12s %-10s %-15s\n",
           "Delivery ID", "Route", "Distance", "Weight", "Vehicle");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < deliveryCount; i++) {
        if (!deliveryCompleted[i]) {
            printf("%-12d %s => %-8s %-12d %-10d %-15s\n",
                   deliveryId[i],
                   cities[deliveryfromCity[i]],
                   cities[deliverytoCity[i]],
                   distances[deliveryfromCity[i]][deliverytoCity[i]],
                   deliveryWeight[i],
                   vehicleTypes[deliveryVehicle[i]]);
        }
    }
}

// -------------------------- Cost, Time and Fuel Calculations ----------------------
void costTimeFuelCalculations() {
    int choice;
    do {
        printf(" \tMenu\n");
        printf("1. Calculate cost for delivery\n");
        printf("2. View all calculations\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                calculateDeliveryCost();
                break;
            case 2:
                viewAllCalculations();
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

void calculateDeliveryCost() {
    if (deliveryCount == 0) {
        printf("no deliveries available!\n");
        return;
    }

    int deliveryChoice;
    printf("\n Deliveries:\n");
    viewActiveDeliveries();

    printf("\nEnter delivery ID to calculate cost: ");
    scanf("%d", &deliveryChoice);
    getchar();

    int deliveryIndex = -1;
    for (int i = 0; i < deliveryCount; i++) {
        if (deliveryId[i] == deliveryChoice && !deliveryCompleted[i]) {
            deliveryIndex = i;
            break;
        }
    }

    if (deliveryIndex == -1) {
        printf("Error: Delivery not found!\n");
        return;
    }

    int fromCity = deliveryfromCity[deliveryIndex];
    int toCity = deliverytoCity[deliveryIndex];
    int weight = deliveryWeight[deliveryIndex];
    int vehicleIndex = deliveryVehicle[deliveryIndex];
    int distance = distances[fromCity][toCity];

    int rate = vehicleRatePerKm[vehicleIndex];
    int speed = vehicleAvgSpeed[vehicleIndex];
    int efficiency = vehicleFuelEfficiency[vehicleIndex];

    // a. Delivery Cost:𝑪𝒐𝒔𝒕=𝑫 x 𝑹 x (𝟏+𝑾 X/𝟏𝟎𝟎𝟎𝟎)
    deliveryCost[deliveryIndex] = distance * rate * (1 + weight / 10000.0);
    // b. Estimated Delivery Time (hours):𝑻𝒊𝒎𝒆= 𝑫/𝑺
    estimatedTime[deliveryIndex] = (float)distance / speed;
    // c. Fuel Consumption:𝑭𝒖𝒆𝒍𝑼𝒔𝒆𝒅=𝑫/𝑬
    fuelUsed[deliveryIndex] = (float)distance / efficiency;
    // d. Fuel Cost:𝑭𝒖𝒆𝒍𝑪𝒐𝒔𝒕=𝑭𝒖𝒆𝒍𝑼𝒔𝒆𝒅 x 𝑭
    fuelCost[deliveryIndex] = fuelUsed[deliveryIndex] * FUEL_PRICE;
    // e. Total Operational Cost:𝑻𝒐𝒕𝒂𝒍𝑪𝒐𝒔𝒕=𝐃𝐞𝐥𝐢𝐯𝐞𝐫𝐲𝑪𝒐𝒔𝒕+𝑭𝒖𝒆𝒍𝑪𝒐𝒔𝒕
    totalCost[deliveryIndex] = deliveryCost[deliveryIndex] + fuelCost[deliveryIndex];
    // f. Profit Calculation: 𝑷𝒓𝒐𝒇𝒊𝒕=(𝑪𝒐𝒔𝒕 x 𝟎.𝟐𝟓)
    profit[deliveryIndex] = deliveryCost[deliveryIndex] * 0.25;
    // g. Final Charge to Customer: 𝑪𝒖𝒔𝒕𝒐𝒎𝒆𝒓𝑪𝒉𝒂𝒓𝒈𝒆=𝑻𝒐𝒕𝒂𝒍𝑪𝒐𝒔𝒕+𝑷𝒓𝒐𝒇𝒊𝒕
    customerCharge[deliveryIndex] = totalCost[deliveryIndex] + profit[deliveryIndex];

    printf("\nCalculations completed!\n");
    displayCalculationResults(deliveryIndex);
}

void displayCalculationResults(int index) {

    int fromCity = deliveryfromCity[index];
    int toCity = deliverytoCity[index];
    int distance = distances[fromCity][toCity];

    printf("\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cities[fromCity]);
    printf("To: %s\n", cities[toCity]);
    printf("Distance: %d km\n", distance);
    printf("Vehicle: %s\n", vehicleTypes[deliveryVehicle[index]]);
    printf("Weight: %d kg\n", deliveryWeight[index]);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %.2f LKR\n", deliveryCost[index]);
    printf("Fuel Used: %.2f L\n", fuelUsed[index]);
    printf("Fuel Cost: %.2f LKR\n", fuelCost[index]);
    printf("Total Cost: %.2f LKR\n", totalCost[index]);
    printf("Profit: %.2f LKR\n", profit[index]);
    printf("Customer Charge: %.2f LKR\n", customerCharge[index]);
    printf("Estimated Time: %.2f hours\n", estimatedTime[index]);
    printf("======================================================\n");
}

void viewAllCalculations() {
    if (deliveryCount == 0) {
        printf("no deliveries available.\n");
        return;
    }

    printf("\n=== All Delivery Calculations ===\n\n");
    printf("%-12s %-20s %-10s %-15s %-15s\n",
           "Delivery ID", "Route", "Weight", "Total Cost", "Time (hrs)");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < deliveryCount; i++) {
        if (customerCharge[i] > 0) {
            printf("%-12d %s -> %-8s %-10d LKR %-11.2f %-14.2f\n",
                   deliveryId[i],
                   cities[deliveryfromCity[i]],
                   cities[deliverytoCity[i]],
                   deliveryWeight[i],
                   customerCharge[i],
                   estimatedTime[i]);
        }
    }
}

