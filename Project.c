#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 50
#define MAX_CUSTOMERS 100

// Structure definitions
typedef struct {
    int roomNumber;
    int isBooked;
    char customerName[50];
    int days;
    float pricePerDay;
} Room;

typedef struct {
    int customerID;
    char name[50];
    int roomNumber;
    int days;
    float totalBill;
} Customer;

// Global arrays
Room rooms[MAX_ROOMS];
Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

void initializeRooms();
void displayRooms();
void bookRoom();
void checkOut();
void viewCustomers();
void saveData();
void loadData();
void restoreRoomStatus();

void initializeRooms() {
    int i;
    for (i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = 0;
        strcpy(rooms[i].customerName, "");
        rooms[i].days = 0;
        rooms[i].pricePerDay = 5000.0;
    }
}

void restoreRoomStatus() {
    int i;
    
    for (i = 0; i < customerCount; i++) {
        int roomIndex = customers[i].roomNumber - 1;
        
        
        rooms[roomIndex].isBooked = 1;
        strcpy(rooms[roomIndex].customerName, customers[i].name);
        rooms[roomIndex].days = customers[i].days;
    }
    
    if (customerCount > 0) {
        printf("Restored %d booked room(s) from previous session.\n", customerCount);
    }
}

void displayRooms() {
    int i;
    printf("\nRoom Number\tStatus\n");
    for (i = 0; i < MAX_ROOMS; i++) {
        if (rooms[i].isBooked) {
            printf("%d\t\tBooked by %s\n", rooms[i].roomNumber, rooms[i].customerName);
        } else {
            printf("%d\t\tAvailable\n", rooms[i].roomNumber);
        }
    }
}

void bookRoom() {
    int roomNum;
    char name[50];
    char buffer[100];
    int days;
    int i;

    printf("\nEnter room number to book (1-%d): ", MAX_ROOMS);
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &roomNum);

    if (roomNum < 1 || roomNum > MAX_ROOMS) {
        printf("Invalid room number.\n");
        return;
    }

    if (rooms[roomNum - 1].isBooked) {
        printf("Room is already booked.\n");
        return;
    }

    printf("Enter customer name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  

    printf("Enter number of days: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &days);

    rooms[roomNum - 1].isBooked = 1;
    strcpy(rooms[roomNum - 1].customerName, name);
    rooms[roomNum - 1].days = days;

    Customer newCustomer;
    newCustomer.customerID = customerCount + 1;
    strcpy(newCustomer.name, name);
    newCustomer.roomNumber = roomNum;
    newCustomer.days = days;
    newCustomer.totalBill = days * rooms[roomNum - 1].pricePerDay;

    customers[customerCount] = newCustomer;
    customerCount++;

    printf("Room %d successfully booked for %s. Total bill: %.2f\n", roomNum, name, newCustomer.totalBill);
}

void checkOut() {
    int roomNum;
    char buffer[100];
    int i, j;
    
    printf("\nEnter room number to check out: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &roomNum);

    if (roomNum < 1 || roomNum > MAX_ROOMS || !rooms[roomNum - 1].isBooked) {
        printf("Invalid room number or room not booked.\n");
        return;
    }

    printf("Customer %s checked out. Total Bill: %.2f\n", rooms[roomNum - 1].customerName,
           rooms[roomNum - 1].days * rooms[roomNum - 1].pricePerDay);

    
    for (i = 0; i < customerCount; i++) {
        if (customers[i].roomNumber == roomNum) {
            
            for (j = i; j < customerCount - 1; j++) {
                customers[j] = customers[j + 1];
            }
            customerCount--;
            break;
        }
    }
