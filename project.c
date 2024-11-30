#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
    float discount;
} Medicine;

typedef struct {
    char username[50];
    char password[50];
    char bkash[20]; 
    char rocket[20];
} User;

typedef struct {
    char username[50];
    int medicineID;
    int quantity;
    float totalPrice;
    int status; 
} Order;


void adminModule();
void customerModule();
void resetAdminCredentials();
void salesListCheck();
void searchMedicineAdmin();
void customerSupportAdmin();
void refundAndReturnCheck();
void medicineRequestCheck();
void addDiscount();
void addToCart();
void paymentMethod();
void resetCustomerCredentials();
void customerSupport();


FILE *medicineFile, *userFile, *orderFile;


void adminRegister();
void adminLogin();
void addMedicine();
void deleteMedicine();
void updateMedicine();
void viewMedicines();
void viewOrders();
void searchMedicineAdmin();


void customerRegister();
void customerLogin();
void searchMedicine();
void buyMedicine();
void viewCart();
void requestRefund();

int main() {
    int choice;

    while (1) {
        printf("\n=== Medicine Store Management System ===\n");
        printf("1. Admin Module\n");
        printf("2. Customer Module\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminModule();
                break;
            case 2:
                customerModule();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Admin module
void adminModule() {
    int choice;

    while (1) {
        printf("\n=== Admin Module ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                adminRegister();
                break;
            case 2:
                adminLogin();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void adminRegister() {
    User admin;
    userFile = fopen("admins.txt", "a");

    if (!userFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", admin.username);
    printf("Enter password: ");
    scanf("%s", admin.password);

    fwrite(&admin, sizeof(User), 1, userFile);
    fclose(userFile);

    printf("Admin registered successfully!\n");
}

void adminLogin() {
    User admin, temp;
    int found = 0;

    userFile = fopen("admins.txt", "r");

    if (!userFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", temp.username);
    printf("Enter password: ");
    scanf("%s", temp.password);

    while (fread(&admin, sizeof(User), 1, userFile)) {
        if (strcmp(admin.username, temp.username) == 0 && strcmp(admin.password, temp.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(userFile);

    if (found) {
        printf("Login successful!\n");
        int choice;
        while (1) {
            printf("\n=== Admin Panel ===\n");
            printf("1. Add Medicine\n");
            printf("2. Delete Medicine\n");
            printf("3. Update Medicine\n");
            printf("4. View Medicines\n");
            printf("5. View Orders\n");
            printf("6. Reset Credentials\n");
            printf("7. Sales List Check\n");
            printf("8. Search Medicine\n");
            printf("9. Customer Support Panel\n");
            printf("10. Refund and Return Request Check\n");
            printf("11. Medicine Request Check\n");
            printf("12. Add Discount\n");
            printf("13. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addMedicine();
                    break;
                case 2:
                    deleteMedicine();
                    break;
                case 3:
                    updateMedicine();
                    break;
                case 4:
                    viewMedicines();
                    break;
                case 5:
                    viewOrders();
                    break;
                case 6:
                    resetAdminCredentials();
                    break;
                case 7:
                    salesListCheck();
                    break;
                case 8:
                    searchMedicineAdmin();
                    break;
                case 9:
                    customerSupportAdmin();
                    break;
                case 10:
                    refundAndReturnCheck();
                    break;
                case 11:
                    medicineRequestCheck();
                    break;
                case 12:
                    addDiscount();
                    break;
                case 13:
                    return;
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        }
    } else {
        printf("Invalid credentials.\n");
    }
}

void addMedicine() {
    Medicine medicine;

    medicineFile = fopen("medicines.txt", "a");
    if (!medicineFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine ID: ");
    scanf("%d", &medicine.id);
    printf("Enter medicine name: ");
    scanf("%s", medicine.name);
    printf("Enter quantity: ");
    scanf("%d", &medicine.quantity);
    printf("Enter price: ");
    scanf("%f", &medicine.price);
    printf("Enter discount: ");
    scanf("%f", &medicine.discount);

    fwrite(&medicine, sizeof(Medicine), 1, medicineFile);
    fclose(medicineFile);

    printf("Medicine added successfully!\n");
}

void deleteMedicine() {
    int id, found = 0;
    Medicine medicine;

    FILE *tempFile = fopen("temp.txt", "w");
    medicineFile = fopen("medicines.txt", "r");

    if (!medicineFile || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine ID to delete: ");
    scanf("%d", &id);

    while (fread(&medicine, sizeof(Medicine), 1, medicineFile)) {
        if (medicine.id != id) {
            fwrite(&medicine, sizeof(Medicine), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(medicineFile);
    fclose(tempFile);

    remove("medicines.txt");
    rename("temp.txt", "medicines.txt");

    if (found) {
        printf("Medicine deleted successfully!\n");
    } else {
        printf("Medicine not found.\n");
    }
}

void updateMedicine() {
    int id, found = 0;
    Medicine medicine;

    FILE *tempFile = fopen("temp.txt", "w");
    medicineFile = fopen("medicines.txt", "r");

    if (!medicineFile || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine ID to update: ");
    scanf("%d", &id);

    while (fread(&medicine, sizeof(Medicine), 1, medicineFile)) {
        if (medicine.id == id) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", medicine.name);
            printf("Enter new quantity: ");
            scanf("%d", &medicine.quantity);
            printf("Enter new price: ");
            scanf("%f", &medicine.price);
            printf("Enter new discount: ");
            scanf("%f", &medicine.discount);
        }
        fwrite(&medicine, sizeof(Medicine), 1, tempFile);
    }

    fclose(medicineFile);
    fclose(tempFile);

    remove("medicines.txt");
    rename("temp.txt", "medicines.txt");

    if (found) {
        printf("Medicine updated successfully!\n");
    } else {
        printf("Medicine not found.\n");
    }
}

void viewMedicines() {
    Medicine medicine;

    medicineFile = fopen("medicines.txt", "r");
    if (!medicineFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n=== Medicine List ===\n");
    while (fread(&medicine, sizeof(Medicine), 1, medicineFile)) {
        printf("ID: %d | Name: %s | Quantity: %d | Price: %.2f | Discount: %.2f\n",
               medicine.id, medicine.name, medicine.quantity, medicine.price, medicine.discount);
    }

    fclose(medicineFile);
}

void viewOrders() {
    Order order;

    orderFile = fopen("orders.txt", "r");
    if (!orderFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n=== Order List ===\n");
    while (fread(&order, sizeof(Order), 1, orderFile)) {
        printf("Customer: %s | Medicine ID: %d | Quantity: %d | Total Price: %.2f | Status: %s\n",
               order.username, order.medicineID, order.quantity, order.totalPrice, order.status == 0 ? "Pending" : "Refunded");
    }

    fclose(orderFile);
}

void resetAdminCredentials() {
    printf("Contact with 3idiot@gmail.com\n");
}

void salesListCheck() {
    printf("Sales list check feature not implemented yet.\n");
}

void searchMedicineAdmin() {
    Medicine medicine;
    int found = 0;
    char name[50];

    medicineFile = fopen("medicines.txt", "r");
    if (!medicineFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine Name to search: ");
    scanf("%s", name);

    while (fread(&medicine, sizeof(Medicine), 1, medicineFile)) {
        if (strcmp(medicine.name, name) == 0) {
            found = 1;
            printf("ID: %d | Name: %s | Quantity: %d | Price: %.2f | Discount: %.2f\n",
                   medicine.id, medicine.name, medicine.quantity, medicine.price, medicine.discount);
            break;
        }
    }

    fclose(medicineFile);

    if (!found) {
        printf("Medicine not found.\n");
    }
}


void customerSupportAdmin() {
    printf("Contact with 3idiot@gmail.com\n");
}

void refundAndReturnCheck() {
    printf("Refund and return request check feature not implemented yet.\n");
}

void medicineRequestCheck() {
    printf("Medicine request check feature not implemented yet.\n");
}

void addDiscount() {
    printf("You can add when adding new medicine or update medicine\n");
}

void customerModule() {
    int choice;

    while (1) {
        printf("\n=== Customer Module ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerRegister();
                break;
            case 2:
                customerLogin();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void customerRegister() {
    User customer;
    userFile = fopen("customers.txt", "a");

    if (!userFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", customer.username);
    printf("Enter password: ");
    scanf("%s", customer.password);
    printf("Enter Bkash number: ");
    scanf("%s", customer.bkash);
    printf("Enter Rocket number: ");
    scanf("%s", customer.rocket);

    fwrite(&customer, sizeof(User), 1, userFile);
    fclose(userFile);

    printf("Customer registered successfully!\n");
}

void customerLogin() {
    User customer, temp;
    int found = 0;

    userFile = fopen("customers.txt", "r");

    if (!userFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", temp.username);
    printf("Enter password: ");
    scanf("%s", temp.password);

    while (fread(&customer, sizeof(User), 1, userFile)) {
        if (strcmp(customer.username, temp.username) == 0 && strcmp(customer.password, temp.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(userFile);

    if (found) {
        printf("Login successful!\n");
        int choice;
        while (1) {
            printf("\n=== Customer Panel ===\n");
            printf("1. Search Medicine\n");
            printf("2. Buy Medicine\n");
            printf("3. View Cart\n");
            printf("4. Request Refund\n");
            printf("5. Add to Cart\n");
            printf("6. Payment Method\n");
            printf("7. Reset Credentials\n");
            printf("8. Customer Support Panel\n");
            printf("9. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    searchMedicine();
                    break;
                case 2:
                    buyMedicine();
                    break;
                case 3:
                    viewCart();
                    break;
                case 4:
                    requestRefund();
                    break;
                case 5:
                    addToCart();
                    break;
                case 6:
                    paymentMethod();
                    break;
                case 7:
                    resetCustomerCredentials();
                    break;
                case 8:
                    customerSupport();
                    break;
                case 9:
                    return;
                default:
                    printf("Invalid choice! Please try again.\n");
            }
        }
    } else {
        printf("Invalid credentials.\n");
    }
}

void searchMedicine() {
    Medicine medicine;
    int found = 0;
    char name[50];

    medicineFile = fopen("medicines.txt", "r");
    if (!medicineFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine Name to search: ");
    scanf("%s", name);

    while (fread(&medicine, sizeof(Medicine), 1, medicineFile)) {
        if (strcmp(medicine.name, name) == 0) {
            found = 1;
            printf("ID: %d | Name: %s | Quantity: %d | Price: %.2f | Discount: %.2f\n",
                   medicine.id, medicine.name, medicine.quantity, medicine.price, medicine.discount);
            break;
        }
    }

    fclose(medicineFile);

    if (!found) {
        printf("Medicine not found.\n");
    }
}


void buyMedicine() {
    Order order;
    Medicine medicine;
    int id, quantity, found = 0;

    medicineFile = fopen("medicines.txt", "r");
    if (!medicineFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter medicine ID to buy: ");
    scanf("%d", &id);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    FILE *tempFile = fopen("temp.txt", "w");
    while (fread(&medicine, sizeof(Medicine), 1, medicineFile)) {
        if (medicine.id == id && medicine.quantity >= quantity) {
            found = 1;
            medicine.quantity -= quantity;
            orderFile = fopen("orders.txt", "a");

            printf("Enter your username: ");
            scanf("%s", order.username);
            order.medicineID = id;
            order.quantity = quantity;
            order.totalPrice = quantity * medicine.price * (1 - (medicine.discount / 100)); 

            fwrite(&order, sizeof(Order), 1, orderFile);
            fclose(orderFile);
        }
        fwrite(&medicine, sizeof(Medicine), 1, tempFile);
    }

    fclose(medicineFile);
    fclose(tempFile);

    remove("medicines.txt");
    rename("temp.txt", "medicines.txt");

    if (found) {
        printf("Order placed successfully!\n");
    } else {
        printf("Medicine not available in the desired quantity.\n");
    }
}

void viewCart() {
    Order order;
    char username[50];
    int found = 0;

    orderFile = fopen("orders.txt", "r");
    if (!orderFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter your username to view cart: ");
    scanf("%s", username);

    printf("\n=== Your Cart ===\n");
    while (fread(&order, sizeof(Order), 1, orderFile)) {
        if (strcmp(order.username, username) == 0) {
            found = 1;
            printf("Medicine ID: %d | Quantity: %d | Total Price: %.2f | Status: %s\n",
                   order.medicineID, order.quantity, order.totalPrice, order.status == 0 ? "Pending" : "Refunded");
        }
    }

    fclose(orderFile);

    if (!found) {
        printf("No items in your cart.\n");
    }
}

void requestRefund() {
    Order order;
    char username[50];
    int id, found = 0;

    FILE *tempFile = fopen("temp.txt", "w");
    orderFile = fopen("orders.txt", "r");

    if (!orderFile || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter medicine ID for refund: ");
    scanf("%d", &id);

    while (fread(&order, sizeof(Order), 1, orderFile)) {
        if (strcmp(order.username, username) == 0 && order.medicineID == id && order.status == 0) {
            found = 1;
            order.status = 1; 
            printf("Refund request accepted for Medicine ID: %d\n", id);
        }
        fwrite(&order, sizeof(Order), 1, tempFile);
    }

    fclose(orderFile);
    fclose(tempFile);

    remove("orders.txt");
    rename("temp.txt", "orders.txt");

    if (!found) {
        printf("Order not found for refund.\n");
    }
}

void addToCart() {
    printf("You can buy directly\n");
}

void paymentMethod() {
    printf("Already added when you create your account\n");
}

void resetCustomerCredentials() {
    printf("Contact with 3idiot@gmail.com\n");
}

void customerSupport() {
    printf("Contact with 3idiot@gmail.com\n");
}
