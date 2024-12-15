#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Structure to represent an inventory item
struct Item {
    string name;
    int quantity;
    double price;
};

// Function prototypes
void displayMenu();
void viewInventory(Item inventory[], int size);
void addItem(Item inventory[], int &size, int capacity);
void processSale(Item inventory[], int size);
void generateReport(Item inventory[], int size);
void saveInventoryToFile(Item inventory[], int size, const string& filename);
void loadInventoryFromFile(Item inventory[], int &size, int capacity, const string& filename);

int main() {
    const int capacity = 100;
    Item inventory[capacity];
    int size = 0;
    string filename = "inventory.txt";

    // Load inventory from file
    loadInventoryFromFile(inventory, size, capacity, filename);

    int choice;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1:
                viewInventory(inventory, size);
                break;
            case 2:
                addItem(inventory, size, capacity);
                break;
            case 3:
                processSale(inventory, size);
                break;
            case 4:
                generateReport(inventory, size);
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    // Save inventory to file
    saveInventoryToFile(inventory, size, filename);

    return 0;
}

void displayMenu() {
    cout << "\n=== Smart Inventory Management System ===\n";
    cout << "1. View Inventory\n";
    cout << "2. Add Item to Inventory\n";
    cout << "3. Process Sale\n";
    cout << "4. Generate Report\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void viewInventory(Item inventory[], int size) {
    cout << "\n--- Inventory List ---\n";
    if (size == 0) {
        cout << "Inventory is empty.\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        cout << "Name: " << inventory[i].name << ", Quantity: " << inventory[i].quantity
             << ", Price: $" << inventory[i].price << endl;
    }
}

void addItem(Item inventory[], int &size, int capacity) {
    if (size >= capacity) {
        cout << "Inventory is full. Cannot add more items.\n";
        return;
    }

    Item newItem;
    cout << "Enter item name: ";
    getline(cin, newItem.name);
    cout << "Enter item quantity: ";
    cin >> newItem.quantity;
    cout << "Enter item price: ";
    cin >> newItem.price;
    cin.ignore(); // Clear input buffer

    inventory[size++] = newItem;
    cout << "Item added successfully.\n";
}

void processSale(Item inventory[], int size) {
    string itemName;
    int quantitySold;

    cout << "Enter item name: ";
    getline(cin, itemName);
    cout << "Enter quantity sold: ";
    cin >> quantitySold;
    cin.ignore(); // Clear input buffer

    for (int i = 0; i < size; ++i) {
        if (inventory[i].name == itemName) {
            if (inventory[i].quantity >= quantitySold) {
                inventory[i].quantity -= quantitySold;
                cout << "Sale processed successfully.\n";
            } else {
                cout << "Insufficient stock.\n";
            }
            return;
        }
    }

    cout << "Item not found in inventory.\n";
}

void generateReport(Item inventory[], int size) {
    cout << "\n--- Inventory Report ---\n";
    double totalValue = 0.0;

    for (int i = 0; i < size; ++i) {
        double itemValue = inventory[i].quantity * inventory[i].price;
        cout << "Name: " << inventory[i].name << ", Quantity: " << inventory[i].quantity
             << ", Total Value: $" << itemValue << endl;
        totalValue += itemValue;
    }

    cout << "\nTotal Inventory Value: $" << totalValue << endl;
}

void saveInventoryToFile(Item inventory[], int size, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error saving inventory to file.\n";
        return;
    }

    for (int i = 0; i < size; ++i) {
        outFile << inventory[i].name << "\n" << inventory[i].quantity << "\n" << inventory[i].price << "\n";
    }

    outFile.close();
    cout << "Inventory saved to file successfully.\n";
}

void loadInventoryFromFile(Item inventory[], int &size, int capacity, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No inventory file found. Starting with an empty inventory.\n";
        return;
    }

    size = 0;
    while (size < capacity && getline(inFile, inventory[size].name)) {
        inFile >> inventory[size].quantity;
        inFile >> inventory[size].price;
        inFile.ignore(); // Clear newline character
        ++size;
    }

    inFile.close();
    cout << "Inventory loaded from file successfully.\n";
}
