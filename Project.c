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
