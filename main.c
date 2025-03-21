#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void initializeSystem(int rooms, int lights[], int temp[], int motion[], int locks[]);
void displayMenu();
void controlLights(int rooms, int lights[]);
void readTemperature(int rooms, int temp[]);
void detectMotion(int rooms, int motion[]);
void securitySystem(int rooms, int locks[]);
void analyzeHouseStatus(int rooms, int lights[], int temp[], int motion[], int locks[]);
void autoLockSystem(int rooms, int motion[], int locks[], int *noMotionCount);
void temperatureAlert(int rooms, int temp[]);
void energySavingMode(int rooms, int lights[], int *lightsOnCount);

int main() {
    int rooms;
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);

    // Dynamically allocate memory
    int *lights = (int *)malloc(rooms * sizeof(int));
    int *temp = (int *)malloc(rooms * sizeof(int));
    int *motion = (int *)malloc(rooms * sizeof(int));
    int *locks = (int *)malloc(rooms * sizeof(int));

    if (lights == NULL || temp == NULL || motion == NULL || locks == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Exit with error
    }

    initializeSystem(rooms, lights, temp, motion, locks);

    int choice, noMotionCount = 0, lightsOnCount = 0;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                controlLights(rooms, lights);
                energySavingMode(rooms, lights, &lightsOnCount);
                break;
            case 2:
                readTemperature(rooms, temp);
                temperatureAlert(rooms, temp);
                break;
            case 3:
                detectMotion(rooms, motion);
                autoLockSystem(rooms, motion, locks, &noMotionCount);
                break;
            case 4:
                securitySystem(rooms, locks);
                break;
            case 5:
                analyzeHouseStatus(rooms, lights, temp, motion, locks);
                break;
            case 6:
                printf("Exiting...\n");
                free(lights);
                free(temp);
                free(motion);
                free(locks);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void initializeSystem(int rooms, int lights[], int temp[], int motion[], int locks[]) {
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;
        temp[i] = 22 + (i % 5); // Assigning some default temperatures
        motion[i] = 0;
        locks[i] = 1;
    }
    printf("Initializing system...\n");
}

void displayMenu() {
    printf("\n===== Smart Home Menu =====\n");
    printf("1. Toggle Light\n");
    printf("2. Read Temperature\n");
    printf("3. Check Motion Sensor\n");
    printf("4. Lock/Unlock Security System\n");
    printf("5. House Status Summary\n");
    printf("6. Exit\n");
}

void controlLights(int rooms, int lights[]) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number.\n");
    }
}

void readTemperature(int rooms, int temp[]) {
    int room;
    printf("Enter room number to read temperature (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Temperature in Room %d: %d°C\n", room, temp[room - 1]);
    } else {
        printf("Invalid room number.\n");
    }
}

void detectMotion(int rooms, int motion[]) {
    int room;
    printf("Enter room number to check motion (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        printf("Motion in Room %d: %s\n", room, motion[room - 1] ? "Detected" : "No Motion");
    } else {
        printf("Invalid room number.\n");
    }
}

void securitySystem(int rooms, int locks[]) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", rooms);
    scanf("%d", &room);
    if (room >= 1 && room <= rooms) {
        locks[room - 1] = !locks[room - 1];
        printf("Room %d is now %s.\n", room, locks[room - 1] ? "Locked" : "Unlocked");
    } else {
        printf("Invalid room number.\n");
    }
}

void analyzeHouseStatus(int rooms, int lights[], int temp[], int motion[], int locks[]) {
    printf("\nHouse Status:\n");
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, %s, %s\n", i + 1, 
               lights[i] ? "ON" : "OFF", 
               temp[i], 
               motion[i] ? "Motion Detected" : "No Motion", 
               locks[i] ? "Locked" : "Unlocked");
    }
}

void autoLockSystem(int rooms, int motion[], int locks[], int *noMotionCount) {
    int allNoMotion = 1;
    for (int i = 0; i < rooms; i++) {
        if (motion[i] == 1) {
            allNoMotion = 0;
            *noMotionCount = 0;
            break;
        }
    }

    if (allNoMotion) {
        (*noMotionCount)++;
        if (*noMotionCount >= 5) {
            for (int i = 0; i < rooms; i++) {
                locks[i] = 1;
            }
            printf("Auto-lock activated: All doors are now locked.\n");
            *noMotionCount = 0;
        }
    }
}

void temperatureAlert(int rooms, int temp[]) {
    for (int i = 0; i < rooms; i++) {
        if (temp[i] > 30) {
            printf("Warning: High temperature detected in Room %d (Temp: %d°C)\n", i + 1, temp[i]);
        }
    }
}

void energySavingMode(int rooms, int lights[], int *lightsOnCount) {
    int allLightsOn = 1;
    for (int i = 0; i < rooms; i++) {
        if (lights[i] == 0) {
            allLightsOn = 0;
            *lightsOnCount = 0;
            break;
        }
    }

    if (allLightsOn) {
        (*lightsOnCount)++;
        if (*lightsOnCount >= 3) {
            printf("Energy Saving Mode: All lights have been ON for too long. Consider turning them OFF.\n");
        }
    }
}
