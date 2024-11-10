typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Medicine;

typedef struct {
    int id;
    char name[50];
    char phone[20];
} Customer;

void addSaleRecord(Medicine medicine, int quantity) {
    FILE *file = fopen("sales.txt", "a");
    if (!file) return;
    fprintf(file, "%d %s %d %.2f\n", medicine.id, medicine.name, quantity, medicine.price * quantity);
    fclose(file);
}

void viewSalesList() {
    FILE *file = fopen("sales.txt", "r");
    if (!file) return;
    int id, quantity;
    char name[50];
    float price;
    while (fscanf(file, "%d %s %d %f", &id, name, &quantity, &price) != EOF) {
        printf("ID: %d, Name: %s, Quantity: %d, Total Price: %.2f\n", id, name, quantity, price);
    }
    fclose(file);
}

void addOrder(Medicine medicine, int quantity) {
    FILE *file = fopen("orders.txt", "a");
    if (!file) return;
    fprintf(file, "%d %s %d %.2f\n", medicine.id, medicine.name, quantity, medicine.price * quantity);
    fclose(file);
}

void viewOrderList() {
    FILE *file = fopen("orders.txt", "r");
    if (!file) return;
    int id, quantity;
    char name[50];
    float price;
    while (fscanf(file, "%d %s %d %f", &id, name, &quantity, &price) != EOF) {
        printf("ID: %d, Name: %s, Quantity: %d, Total Price: %.2f\n", id, name, quantity, price);
    }
    fclose(file);
}

void customerSupportPanel() {
    printf("Welcome to Customer Support. For assistance, please contact: support@medicalstore.com or call +123456789.\n");
}

void searchMedicine(char *medicineName) {
    FILE *file = fopen("medicines.txt", "r");
    if (!file) return;
    int id, quantity;
    char name[50];
    float price;
    while (fscanf(file, "%d %s %d %f", &id, name, &quantity, &price) != EOF) {
        if (strcmp(name, medicineName) == 0) {
            printf("Medicine Found - ID: %d, Name: %s, Quantity: %d, Price: %.2f\n", id, name, quantity, price);
            fclose(file);
            return;
        }
    }
    printf("Medicine not found.\n");
    fclose(file);
}

void adminPanel() {
    printf("Welcome to the Admin Panel.\n");
    printf("Options: Add/Update Medicines, View Sales, View Orders, Manage Discounts.\n");
}

void addDiscount(int medicineId, float discountPercentage) {
    FILE *file = fopen("medicines.txt", "r+");
    if (!file) return;
    int id, quantity;
    char name[50];
    float price;
    while (fscanf(file, "%d %s %d %f", &id, name, &quantity, &price) != EOF) {
        if (id == medicineId) {
            float discountedPrice = price * (1 - discountPercentage / 100);
            fseek(file, -((int)sizeof(price)), SEEK_CUR);
            fprintf(file, "%.2f", discountedPrice);
            printf("Discount applied. New price: %.2f\n", discountedPrice);
            fclose(file);
            return;
        }
    }
    printf("Medicine ID not found.\n");
    fclose(file);
}
