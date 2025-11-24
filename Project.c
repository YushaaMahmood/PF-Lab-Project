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

