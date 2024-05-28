#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 100
#define MAX_USERS 100

struct Train {
    int id;
    char name[50];
    int capacity;
    int reserved;
};

struct User {
    int id;
    char name[50];
    int reserved;
};


struct Train trains[MAX_TRAINS];
int num_trains = 0;

struct User users[MAX_USERS];
int num_users = 0;


void display_menu() {
    printf("\n=== Railway Management System ===\n");
    printf("1. Admin login\n");
    printf("2. User login\n");
    printf("3. View all trains\n");
    printf("4. Delete a train\n");
    printf("5. Reserve a seat\n");
    printf("6. Cancel a reservation\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}
void load_train_data(){
 FILE *fp = fopen("trains.dat","rb");
  if (fp != NULL) {
        fread(&num_trains, sizeof(num_trains), 1, fp);
        fread(trains, sizeof(struct Train), num_trains, fp);
        fclose(fp);
    }
}
void load_user_data(){
 FILE *fp = fopen("user.dat","rb");
 if (fp != NULL) {
        fread(&num_users, sizeof(num_users), 1, fp);
        fread(users, sizeof(struct User), num_users, fp);
        fclose(fp);
    }

}

void save_train_data(){
 FILE *fp = fopen("trains.dat","wb");
 if (fp != NULL) {
        fwrite(&num_trains, sizeof(num_trains), 1, fp);
        fwrite(trains, sizeof(struct Train), num_trains, fp);
        fclose(fp);
    }
}

void save_user_data(){
 FILE *fp = fopen("user.dat","wb");
  if (fp != NULL) {
        fwrite(&num_users, sizeof(num_users), 1, fp);
        fwrite(users, sizeof(struct User), num_users, fp);
        fclose(fp);
    }
}

void display_admin_menu() {
    printf("\n=== Admin Menu ===\n");
    printf("1. Add user\n");
    printf("2. View all users\n");
    printf("3. Add a train\n");
    printf("4. View all trains\n");
    printf("5. Delete a train\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
}

void display_user_menu() {
    printf("\n=== User Menu ===\n");
    printf("1. View all trains\n");
    printf("2. Reserve seat\n");
    printf("3. Cancel seat\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
}

void add_train() {
    struct Train train;
    printf("\nEnter train id: ");
    scanf("%d", &train.id);
    printf("Enter train name: ");
    scanf("%s", train.name);
    printf("Enter train capacity: ");
    scanf("%d", &train.capacity);
    train.reserved = 0;
    trains[num_trains] = train;
    num_trains++;
    printf("\nTrain added successfully.\n");
}
void add_user(){
  struct User user;
  printf("\nEnter user id: ");
  scanf("%d", &user.id);
  printf("Enter user name: ");
  scanf("%s", user.name);
  user.reserved = 0;
  users[num_users] = user;
  num_users++;
  printf("\nUser added successfully.\n");
}
void view_trains() {
    printf("\n=== List of Trains ===\n");
    printf("ID\tName\tCapacity\tReserved\n");
    for (int i = 0; i < num_trains; i++) {
        printf("%d\t%s\t%d\t\t%d\n", trains[i].id, trains[i].name, trains[i].capacity, trains[i].reserved);
    }
}
void view_users(){
     printf("\n=== List of Users ===\n");
     printf("ID\tName\t\n");
     for (int i = 0; i < num_users; i++) {
        printf("%d\t%s\t\n", users[i].id, users[i].name);
    }

}

void delete_train() {
int train_id, train_index = -1;
printf("\nEnter the id of the train to be deleted: ");
scanf("%d", &train_id);

for (int i = 0; i < num_trains; i++) {
    if (trains[i].id == train_id) {
        train_index = i;
        break;
    }
}

if (train_index == -1) {
    printf("\nTrain not found.\n");
} else {
    for (int i = train_index; i < num_trains - 1; i++) {
        trains[i] = trains[i + 1];
    }
    num_trains--;

    printf("\nTrain deleted successfully.\n");
}
}
void reserve_seat() {
int user_id, train_id, train_index = -1, user_index = -1;
printf("\nEnter your user id: ");
scanf("%d", &user_id);

for (int i = 0; i < num_users; i++) {
    if (users[i].id == user_id) {
        user_index = i;
        break;
    }
}

if (user_index == -1) {
    printf("\nUser not found.\n");
    return;
}

printf("Enter the train id: ");
scanf("%d", &train_id);

for (int i = 0; i < num_trains; i++) {
    if (trains[i].id == train_id) {
        train_index = i;
        break;
    }
}

if (train_index == -1) {
    printf("\nTrain not found.\n");
    return;
}

if (trains[train_index].reserved == trains[train_index].capacity) {
    printf("\nSorry, the train is already full.\n");
    return;
}

users[user_index].reserved = train_id;
trains[train_index].reserved++;

printf("\nReservation successful.\n");
}

void cancel_reservation() {
int user_id, train_id, train_index = -1, user_index = -1;
printf("\nEnter your user id: ");
scanf("%d", &user_id);

for (int i = 0; i < num_users; i++) {
    if (users[i].id == user_id) {
        user_index = i;
        break;
    }
}

if (user_index == -1) {
    printf("\nUser not found.\n");
    return;
}

train_id = users[user_index].reserved;

for (int i = 0; i < num_trains; i++) {
    if (trains[i].id == train_id) {
        train_index = i;
        break;
    }
}

if (train_index == -1) {
    printf("\nTrain not found.\n");
    return;
}

users[user_index].reserved = 0;
trains[train_index].reserved--;

printf("\nReservation cancelled successfully.\n");
}

int main() {
load_train_data();
load_user_data();
int choice;
do {
display_menu();
scanf("%d", &choice);
switch (choice) {
    case 1: {
        char password[10];

        printf("\nEnter password: ");
        scanf("%s", password);

        if (strcmp(password, "admin") == 0) {
            int admin_choice;

            do {
                display_admin_menu();
                scanf("%d", &admin_choice);

                switch (admin_choice) {
                    case 1:
                        add_user();
                        save_user_data();
                        break;
                     case 2:
                        view_users();
                        break;
                    case 3:
                        add_train();
                        save_train_data();
                        break;

                    case 4:
                        view_trains();
                        break;

                    case 5:
                        delete_train();
                        save_train_data();
                        break;

                    case 6:
                        printf("\nLogged out successfully.\n");
                        break;

                    default:
                        printf("\nInvalid choice. Try again.\n");
                }
            } while (admin_choice != 4);
        } else {
            printf("\nIncorrect password. Try again.\n");
        }

        break;
    }

    case 2: {
        int user_id;
        int user_index = -1;

        printf("\nEnter user id: ");
        scanf("%d", &user_id);

        for (int i = 0; i < num_users; i++) {
            if (users[i].id == user_id) {
                user_index = i;
                break;
            }
        }

        if (user_index == -1) {
            printf("\nUser not found. Please register first.\n");
        } else {
            int user_choice;

            do {
                display_user_menu();
                scanf("%d", &user_choice);

                switch (user_choice) {
                    case 1:
                        view_trains();
                        break;

                    case 2:
                        reserve_seat(users[user_index]);
                        save_train_data();
                        save_user_data();
                        break;

                    case 3:
                        cancel_reservation(users[user_index]);
                        save_train_data();
                        save_user_data();
                        break;

                    case 4:
                        printf("\nLogged out successfully.\n");
                        break;

                    default:
                        printf("\nInvalid choice. Try again.\n");
                }
            } while (user_choice != 4);
        }

        break;
    }

    case 3:
        view_trains();
        break;

    case 4:
        delete_train();
        save_train_data();
        break;

    case 5:
        reserve_seat();
        save_train_data();
        save_user_data();
        break;

    case 6:
        cancel_reservation();
        save_train_data();
        save_user_data();
        break;

    case 7:
        printf("\nExiting program...\n");
        break;

    default:
        printf("\nInvalid choice. Try again.\n");
}
} while (choice != 7);

return 0;
}


















