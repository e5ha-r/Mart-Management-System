#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <ctime>
#include <iomanip>
#include <utility>
#include<algorithm>

using namespace std;

// Constants
const int MAX_ITEMS = 100;
const int MAX_CUSTOMERS = 100;
const string inventoryFile = "inventory.txt";
const string bill_file = "bill.txt";
const string customersFile = "customers.txt";
const string flashMessagesLogFile = "flash_messages_log.txt";
const int max_employees = 100;


// Struct for Inventory Items
struct Item 
{
    string name;
    double price;
    int quantity;
    double profitMargin;
    int sold;
    string barcode;
    int aisle;
    int shelf;
    string side;
    int date;
    int month;
    int year;
    string season;
    
};

struct purchased 
{
    string barcode;
    string name;
    int quantity;
    int price;
    long long bill_id;
    double total;
};

struct Customer {
    int id;
    string name;
    string email;
    string phoneNumber;
    string category;
    double totalSpent;
    
};

struct Employee
{
    string name;
    string role;
    string phone;
    double salary;
};

// Function Prototypes
void Manage_inventory(Item* inventory, int* itemCount);
void loadInventory(Item* inventory, int* itemCount);
void saveInventory(Item* inventory, int itemCount);
void Add_Item(Item* inventory, int* itemCount);
void Update_Item(Item* inventory, int* itemCount);
void Remove_Item(Item* inventory, int* itemCount);
void displayInventory(Item* inventory, int itemCount);
////////////////////////////////////////////////
void Billing(Item* inventory, int* itemCount);
////////////////////////////////////////////////////
void Stock_Alerts(Item* inventory,int *itemCount);
void Generate_Stock_Alert(Item* inventory,int *itemCount);
void Restock_Notification(Item* inventory,int *itemCount);
void Generate_OutOfStock_Alert(Item* inventory,int *itemCount);
void Generate_Custom_Expiry_Alert(Item *inventory, int* itemCount);
void Remove_Expired_Items(Item *inventory, int* itemCount);
void Generate_Expiry_Alert(Item *inventory, int* itemCount);
/////////////////////////////////////////////////
void CheckAvailabilty( Item *inventory, int* itemCount) ;
//////////////////////////////////
void Sales_Profit_Analysis(Item* inventory,int* itemcount);
void Slow_Movers(Item* inventory,int* itemcount);
void Hot_Sell(Item* inventory,int* itemcount);
void Sales_rep(Item* inventory,int* itemcount);
void Profit_rep(Item* inventory,int* itemcount);
/////////////////////////////////
void Refund(Item* inventory,int* itemcount);
//////////////////////////////////////
void add_employee(Employee* employees,int* employee_count);
void delete_employee(Employee* employees,int* employee_count);
void display_employees(Employee* employees,int* employee_count);
void saveEmployees(Employee* employees,int employee_count);
void loadEmployees(Employee* employees,int* employee_count);
void search_employee(Employee* employees,int* employee_count);
void Employee_managemnet();

///////////////////////
void Customer_Management(Customer* customer,int* customerCount);
void Add_Customer(Customer* customer,int* customerCount);
void Update_Customer(Customer* customer,int* customerCount);
void Track_Purchase(Customer* customer,int* customerCount);
void Generate_Customer_Report(Customer* customer,int* customerCount);
void Send_Flash_Messages(Customer* customer,int* customerCount);
string generateMessage(const Customer&);
void logFlashMessage(const Customer&, const string&);
void Load_Customers_From_File(Customer* customer,int* customerCount);
void Save_Customers_To_File(Customer* customer,int* customerCount);
////////////////////////////
void Merchandising(Customer* customers,int* customerCount,Item* inventory,int* itemcount);
void Display_Expiring_Soon_Products(Item* inventory,int* itemcount);
void Display_Clearance_Sale(Item* inventory,int* itemcount);
void Display_Products_for_Customer(Customer* customer,int* customerCount,Item* inventory,int* itemcount);
void Display_Seasonal_Products(Item* inventory,int* itemcount);
void Display_Bestsellers(Item* inventory,int* itemcount);

////////////////////////////////
void clearInputBuffer();
bool invalid_in();
int getValidatedInt(string prompt);
////////////////////


int main() {
    // Local Inventory Array and Count
    Item inventory[MAX_ITEMS];
    int itemCount = 0;
    Customer customers[MAX_CUSTOMERS];
    int customerCount = 0;

    // Load inventory from file

    loadInventory(inventory, &itemCount);
    Load_Customers_From_File(customers,&customerCount);

    int choice;
    do {
        cout << "\nMart Management System\n";
        cout << "1. Manage Inventory\n";
        cout << "2. Billing\n";
        cout << "3. Stock Alerts\n";
        cout << "4. Find item\n";
        cout << "5. Sales and Profit Analytics\n";
        cout << "6. Refund\n";
        cout << "7. Customer Management\n";
        cout << "8. Employee Managment\n";
        cout << "9. Merchandising function\n";
        cout << "0. Exit\n";
        do{cout << "Enter your choice: ";
        cin >> choice;}while(invalid_in());

        switch (choice) {
            case 1:
                Manage_inventory(inventory, &itemCount);
                break;
            case 2:
                Billing(inventory, &itemCount);
                break;
            case 3:
                Stock_Alerts(inventory,&itemCount);
                break;
            case 4:
                CheckAvailabilty(inventory,&itemCount);
                break;
            case 5:
                Sales_Profit_Analysis(inventory,&itemCount);
                break;
            case 6:
                Refund(inventory,&itemCount);
                break;
            case 7:
                Customer_Management(customers,&customerCount);
                break;
            case 8:
                Employee_managemnet();
                break;
            case 9:
                Merchandising(customers,&customerCount,inventory,&itemCount);
                break;
            case 0:
                saveInventory(inventory,itemCount);
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

// Inventory Management Menu
void Manage_inventory(Item* inventory, int* itemCount) {
    int choice;
    do {
        cout << "\nMart Management System\\Inventory Management\n";
        cout << "1. Add Item\n";
        cout << "2. Update Item\n";
        cout << "3. Remove Item\n";
        cout << "4. Display Inventory\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";
        do{cin >> choice;}while(invalid_in());

        switch (choice) {
            case 1:
                Add_Item(inventory, itemCount);
                break;
            case 2:
                Update_Item(inventory, itemCount);
                break;
            case 3:
                Remove_Item(inventory, itemCount);
                break;
            case 4:
                displayInventory(inventory, *itemCount);
                break;
            case 0:
                saveInventory(inventory, *itemCount);
                cout << "Going back.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

// Load Inventory from File
void loadInventory(Item* inventory, int* itemCount) {
    ifstream file(inventoryFile);
    if (!file) {
        cout << "Error: Unable to open inventory file!" << endl;
        return;
    }

    *itemCount = 0;
    while (file >> inventory[*itemCount].name
                >> inventory[*itemCount].price
                >> inventory[*itemCount].quantity
                >> inventory[*itemCount].profitMargin
                >> inventory[*itemCount].barcode
                >> inventory[*itemCount].aisle
                >> inventory[*itemCount].shelf
                >> inventory[*itemCount].side
                >> inventory[*itemCount].year
                >> inventory[*itemCount].month
                >> inventory[*itemCount].date
                >> inventory[*itemCount].sold
                >>inventory[*itemCount].season) {
        (*itemCount)++;
        if (*itemCount >= MAX_ITEMS) break;
    }
    file.close();
    cout << "Inventory loaded successfully!" << endl;
}

// Save Inventory to File
void saveInventory(Item* inventory, int itemCount) {
    ofstream file(inventoryFile);
    for (int i = 0; i < itemCount; ++i) {
        file << inventory[i].name << " "
             << inventory[i].price << " "
             << inventory[i].quantity << " "
             << inventory[i].profitMargin << " "
             << inventory[i].barcode << " "
             << inventory[i].aisle << " "
             << inventory[i].shelf << " "
             << inventory[i].side <<" "
             << inventory[i].year << " "
             << inventory[i].month << " "
             << inventory[i].date << " "
             <<inventory[i].sold<<" "
             <<inventory[i].season<<"\n";
    }
    file.close();
}

// Add Item to Inventory
void Add_Item(Item* inventory, int* itemCount) {
    if (*itemCount >= MAX_ITEMS) {
        cout << "Inventory is full!\n";
        return;
    }

    Item newItem;
    cout << "Enter item details:\n";
    cout << "Name: "; cin >> newItem.name;
    cout << "Price: "; do{cin >> newItem.price;}while (invalid_in());
    cout << "Quantity: "; do{cin >> newItem.quantity;}while(invalid_in());
    cout << "Profit Margin (%): "; do{cin >> newItem.profitMargin;}while(invalid_in());
    cout << "Barcode: "; cin >> newItem.barcode;
    cout << "Aisle: "; do{cin >> newItem.aisle;}while(invalid_in());
    cout << "Shelf: "; do{cin >> newItem.shelf;}while(invalid_in());
    cout << "Side (Left/Right): "; cin >> newItem.side;
    cout <<" Enter Expiry:\n ";
    cout <<" Year: "; do{cin>>newItem.year;}while(invalid_in());
    cout <<" Month: "; do{cin>>newItem.month;}while(invalid_in());
    cout <<" Date: "; do{cin>>newItem.date;}while(invalid_in());
    cout <<" Season: "; cin>>newItem.season;
    newItem.sold=0;
    inventory[(*itemCount)++] = newItem;
    saveInventory(inventory, *itemCount);
    cout << "Item added successfully!\n";
}

// Update an Item in Inventory
void Update_Item(Item* inventory, int* itemCount) {
    string barcode;
    cout << "Enter barcode of the item to update: ";
    cin >> barcode;

    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].barcode == barcode) {
            cout << "Updating item " << inventory[i].name << ":\n";
            cout << "Enter new details (enter -1 to keep current value):\n";

            double price;
            int quantity;
            double profitMargin;
            int aisle, shelf,date,month,year;
            string side,season;

            cout<<"Note: Enter -1 if you dont want any change in a particular placeholder.\n";
            cout << "Price (" << inventory[i].price << "): "; cin >> price;
            if (price != -1) inventory[i].price = price;

            cout << "Quantity (" << inventory[i].quantity << "): "; cin >> quantity;
            if (quantity != -1) inventory[i].quantity = quantity;

            cout << "Profit Margin (%) (" << inventory[i].profitMargin << "): "; cin >> profitMargin;
            if (profitMargin != -1) inventory[i].profitMargin = profitMargin;

            cout << "Aisle (" << inventory[i].aisle << "): "; cin >> aisle;
            if (aisle != -1) inventory[i].aisle = aisle;

            cout << "Shelf (" << inventory[i].shelf << "): "; cin >> shelf;
            if (shelf != -1) inventory[i].shelf = shelf;

            cout << "Side (" << inventory[i].side << "): "; cin >> side;
            if (side != "-1") inventory[i].side = side;

            cout<<"Expiry:\n";

            cout << "Date (" << inventory[i].date << "): "; cin >> date;
            if (side != "-1") inventory[i].date = date;

            cout << "Month (" << inventory[i].month << "): "; cin >> month;
            if (side != "-1") inventory[i].month = month;

            cout << "Year (" << inventory[i].year << "): "; cin >> year;
            if (side != "-1") inventory[i].year = year;

            cout << "Season (" << inventory[i].season << "): "; cin >> season;
            if (side != "-1") inventory[i].season = season;



            saveInventory(inventory, *itemCount);
            cout << "Item updated successfully!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

// Remove an Item from Inventory
void Remove_Item(Item* inventory, int* itemCount) {
    string barcode;
    cout << "Enter barcode of the item to remove: ";
    cin >> barcode;

    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].barcode == barcode) {
            for (int j = i; j < *itemCount - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            (*itemCount)--;
            saveInventory(inventory, *itemCount);
            cout << "Item removed successfully!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

// Display Inventory
void displayInventory(Item* inventory, int itemCount) {
    if (itemCount == 0) {
        cout << "Inventory is empty!\n";
        return;
    }

    cout << "\nInventory:\n";
    cout << "Name\tPrice\tQty\tProfit%\tBarcode\tAisle\tShelf\tSide\tExpiry\t\tSeason\n";
    cout << "--------------------------------------------------------------------------\n";

    for (int i = 0; i < itemCount; ++i) {
        cout << inventory[i].name << "\t"
             << inventory[i].price << "\t"
             << inventory[i].quantity << "\t"
             << inventory[i].profitMargin << "\t"
             << inventory[i].barcode << "\t"
             << inventory[i].aisle << "\t"
             << inventory[i].shelf << "\t"
             << inventory[i].side << "\t"
             << inventory[i].date << "-"
             << inventory[i].month << "-"
             << inventory[i].year << "\t"
             <<inventory[i].season<<"\n";
    }

    
}

int bill_id()
{
    static long long bill_id=1000000;;
    const string id_file="bill_id.txt";
    if (bill_id==1000000)
    {
    ifstream file(id_file);
    if(file)
    {
        file>>bill_id;
        bill_id++;
    }
    file.close();
    }
    else
    bill_id++;

    ofstream outFile(id_file);
    if (outFile) 
    {
        outFile << bill_id;
        outFile.close();
    } 
    else 
    {
        cout << "Error: Unable to open file for writing!" << endl;
    }
return bill_id;;

}


void Billing(Item* inventory, int* itemCount)
{
    bool found=false;
    float subtotal=0;
    purchased current_item;
    purchased item[100];
    cout<<"\n\nMart Managemnet System \\ Billing\n";
    current_item.bill_id=bill_id();
    //opening file to store it in file
    ofstream file(bill_file,ios::app);
    file << current_item.bill_id << " ";
    int item_no=0,index=0;
    do{
        found=false;
    cout<<"Enter the barcode of product (enter done is all items entered): ";
    cin>>current_item.barcode;
    if(current_item.barcode=="done"|| current_item.barcode=="Done")
    break;
    
    for(int i=0;i<*itemCount;i++){
        if(current_item.barcode==inventory[i].barcode)
        {current_item.price=inventory[i].price;
         current_item.name=inventory[i].name;
         index=i;
         found=true;
        break;
        }
    }

    if(!found)
    cout<<"Product not in Inventory\n" ;
    if(!found)
    continue;
    do {
        cout << "Enter quantity: ";
        cin >> current_item.quantity;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
        } 
        else 
        {
            if(current_item.quantity>inventory[index].quantity)
            {
            cout<<"That much quantity is not in the stock. Make sure you're entering the right quantity\n";
            continue;
            }
            else
            break; // Exit loop if input is valid
        }
    } while (true);
    current_item.total=current_item.price*current_item.quantity;
    inventory[index].quantity-=current_item.quantity;//removing that much quantity from stock
    inventory[index].sold+=current_item.quantity;
    item[item_no]=current_item;
    subtotal+=current_item.total;
    item_no++;
    
    
        file << current_item.barcode << " "
             << current_item.price << " "
             << current_item.quantity << " "
             << current_item.total << " ";
             
    
    }while(item_no<MAX_ITEMS);
    int u_choice;
    float tax_p,tax;
    do{
    cout<<"Enter payment method (1.cash , 2.card) :";
    cin>>u_choice;
    if(u_choice==1) {tax_p=0.05;}
    else if(u_choice==2) {tax_p=0.15;}    
    else
    cout<<"invalid option\n";
    }while(!(u_choice==1||u_choice==2)&&item_no<MAX_ITEMS);
    tax=tax_p*subtotal;
    int total=subtotal+tax;
    file<<"=  " <<total<<" \n";
    file.close();

    cout << "\nName\tQty\t\tPrice\n";
    cout << "--------------------------------"<< endl;

    for (int i = 0; i < item_no; ++i) {
        cout << item[i].name << "\t"
             << item[i].quantity << "\t\t"
             << item[i].total << "\n\n";
    }
    cout<<"\tSub total: \t"<<subtotal<<"\n"
        <<"\tTax: \t\t"<<tax<<"\n "
        <<"\tTotal: \t\t"<<total<<"\n";
        saveInventory(inventory, *itemCount);
}

void Stock_Alerts(Item* inventory,int *itemCount) 
{
    cout<<"STOCK ALERTS\n";
    Generate_Stock_Alert(inventory,itemCount);
    Restock_Notification(inventory,itemCount);
    Generate_Expiry_Alert(inventory,itemCount);
    Generate_Custom_Expiry_Alert(inventory,itemCount);
    Remove_Expired_Items(inventory,itemCount);

}

void Generate_Stock_Alert(Item* inventory,int *itemCount) {
    int threshold;
    cout << "Enter stock threshold to trigger alert: ";
    cin >> threshold;

    bool alertTriggered = false;
    cout << "\nItems below the stock threshold:\n";
    cout << "------------------------------------------------------------\n";
    cout << "\nName\tQty\t\tPrice\n";
    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].quantity < threshold) {
            cout << inventory[i].name << "\t\t" << inventory[i].quantity << "\t" 
                 << inventory[i].price << "\t" << inventory[i].barcode << "\n";
            alertTriggered = true;
        }
    }
    if (!alertTriggered) cout << "No items need restocking at this time.\n";
}

// Function to check expiry and generate alerts
// uses sscanf to extract the year, month, and day from the expiry date string (assuming the format is YYYY-MM-DD).

// Function to suggest restocking based on sales trends (simplified)
void Restock_Notification(Item* inventory,int *itemCount) {
    const int salesThreshold = 50;

    bool alertTriggered = false;
    cout << "\nItems that may need restocking:\n";
    cout << "------------------------------------------------------------\n";
    cout << "Name\tQty.\tPrice\tBarcode\n";
    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].quantity < salesThreshold) {
            cout << inventory[i].name << "\t" << inventory[i].quantity << "\t"
                 << inventory[i].price << "\t" << inventory[i].barcode << "\n";
            alertTriggered = true;
        }
    }
    if (!alertTriggered) cout << "No items need restocking at this time.\n";
}

// Array operations

//out of stock items alert
void Generate_OutOfStock_Alert(Item* inventory,int *itemCount) {
    bool alertTriggered = false;
    cout << "\nItems out of stock (quantity = 0):\n";
    cout << "------------------------------------------------------------\n";
    cout << "Name\tQty.\tPrice\tBarcode\n";
    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].quantity == 0) {
            cout << inventory[i].name << "\t" << inventory[i].quantity << "\t" 
                 << inventory[i].price << "\t" << inventory[i].barcode << "\n";
            alertTriggered = true;
        }
    }
    if (!alertTriggered) {
        cout << "No items are out of stock.\n";
    }
}




void Generate_Expiry_Alert(Item *inventory, int* itemCount) {
    int daysBeforeExpiry = 30;
    time_t t = time(0);
    struct tm *now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    bool alertTriggered = false;
    cout << "\nItems nearing expiry:\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < *itemCount; ++i) {
        int year, month, date;
        year=inventory[i].year;
        month=inventory[i].month;
        date=inventory[i].date;


        int daysLeft = (year - currentYear) * 365 + (month - currentMonth) * 30 + (date - currentDay);

        if (daysLeft <= daysBeforeExpiry) {
            cout << inventory[i].name << "\t"<< daysLeft << " days left before expiry\n";
            alertTriggered = true;
        }
    }
    if (!alertTriggered) cout << "No items are near expiry.\n";
}

void Generate_Custom_Expiry_Alert(Item *inventory, int* itemCount) {
    int threshold;
    cout << "Enter stock threshold of expiry to trigger alert(in days): ";
    cin >> threshold;
    time_t t = time(0);
    struct tm *now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    bool alertTriggered = false;
    cout << "\nItems nearing expiry within " << threshold << " days:\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < *itemCount; ++i) {
        int year, month, date;
        year=inventory[i].year;
        month=inventory[i].month;
        date=inventory[i].date;

        int daysLeft = (year - currentYear) * 365 + (month - currentMonth) * 30 + (date - currentDay);

        if (daysLeft <= threshold) {
            cout << inventory[i].name <<"\t" << daysLeft << " days left before expiry\n";
            alertTriggered = true;
        }
    }
    if (!alertTriggered) cout << "No items are near expiry.\n";
}
//removing expiry items
void Remove_Expired_Items(Item *inventory, int* itemCount) {
    time_t t = time(0);
    struct tm *now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;

    bool alertTriggered = false;
    cout << "\nRemoving expired items:\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < *itemCount; ++i) {
        int year, month, date;
        year=inventory[i].year;
        month=inventory[i].month;
        date=inventory[i].date;

        int daysLeft = (year - currentYear) * 365 + (month - currentMonth) * 30 + (date - currentDay);

        if (daysLeft < 0) {  // Expired item
            cout << inventory[i].name << "\t" << " (Expired)\n";
            for (int j = i; j < *itemCount - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            itemCount--;
            alertTriggered = true;
            i--;  // Adjust index after item removal
        }
        saveInventory(inventory, *itemCount);
    }
    if (!alertTriggered) {
        cout << "No expired items found.\n";
    }

}
//end for stock alert function

//CheckAvailabity of a product and locate it
void CheckAvailabilty( Item *inventory, int* itemCount) 
{
    string str;
    cout<<"Enter the Name or Barcode of the item you are looking for: ";
    cin>>str;
    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].barcode == str||inventory[i].name== str) 
        {
            if(inventory[i].quantity>0)
            {
            cout << "The item is located in Aisle: "<< inventory[i].aisle<<" at Shelf: "<<inventory[i].shelf 
                 <<" on "<<inventory[i].side <<" side.\n";
                 return;
            }
            else
            cout<<"The item is out of stock\n";
        
            return;
        }
    }
    cout << "Item not found.\n";
}


//Sales analyzer

void Sales_Profit_Analysis(Item* inventory,int* itemcount) {
    int choice;
     do{
        cout << "\n========== Sales and Profit Analysis ==========\n";
        cout << "1. Generate Sales Report\n";
        cout << "2. Generate Profit Report\n";
        cout << "3. Track Hot-Selling Products\n";
        cout << "4. Identify Slow-Moving Products\n";
        cout << "0. Back to Main Menu\n";
        cout << "======================================================================\n";
        cout << "Enter your choice: ";
        do{cin >> choice;}while(invalid_in());
        
        switch (choice) {
            case 1: Sales_rep(inventory,itemcount); break;
            case 2: Profit_rep(inventory,itemcount); break;
            case 3: Hot_Sell(inventory,itemcount); break;
            case 4: Slow_Movers(inventory,itemcount); break;
            case 0: cout << "Returning to the main menu...\n"; break;
            default: cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 0);
}

void Sales_rep(Item* inventory,int* itemcount)
{
    cout << "\n=== Sales Report ===\n";
    double totalSales = 0.0;
    cout << "Barcode\tQuantity\tRevenue\n";
    cout << "----------------------------------\n";
    for (int i = 0; i <*itemcount; ++i) {
        double revenue = inventory[i].sold * inventory[i].price;
        cout << inventory[i].barcode << "\t"
             << inventory[i].sold << "\t\t"
             << fixed << setprecision(2) << revenue << "\n";
        totalSales += revenue;
    }
    cout << "----------------------------------\n";
    cout << "Total Sales Revenue: " << totalSales << "\n";
}

void Profit_rep(Item* inventory,int* itemcount)
{
    cout << "\n=== Profit Report ===\n";
    double totalProfit = 0.0;
    cout << "Barcode\tQuantity\tProfit\n";
    cout << "----------------------------------\n";
    for (int i = 0; i < *itemcount; ++i) {
        double profit = inventory[i].sold *(inventory[i].price*( inventory[i].profitMargin/100.0));
        cout << inventory[i].barcode << "\t"
             << inventory[i].sold << "\t\t"
             << fixed << setprecision(2) << profit << "\n";
        totalProfit += profit;
    }
    cout << "----------------------------------\n";
    cout << "Total Profit: " << totalProfit << "\n";
}

void Hot_Sell(Item* inventory,int* itemcount)
{
    cout << "\n=== Hot-Selling Products ===\n";
    // Sort sales array based on quantity sold
    for (int i = 0; i < *itemcount - 1; ++i) {
        for (int j = i + 1; j < *itemcount; ++j) {
            if (inventory[j].sold > inventory[i].sold) {
                swap(inventory[i], inventory[j]);
            }
        }
    }
    // Display top 5 selling products
    int topN = 5;
    cout << "Name\tBarcode\tQuantity\n";
    cout << "----------------------------------\n";
    for (int i = 0; i < min(*itemcount, topN); ++i) {
        cout << inventory[i].name<< "\t"<< inventory[i].barcode << "\t" << inventory[i].sold << "\n";
    }
}

void Slow_Movers(Item* inventory,int* itemcount)
{
    cout << "\n=== Slow-Moving Products ===\n";
    cout << "Name\tBarcode\tQuantity\n";
    cout << "----------------------------------\n";
    bool found = false;
    for (int i = 0; i < *itemcount; ++i) {
        if (inventory[i].sold < 5) { // Threshold for "slow-moving"
            cout << inventory[i].name << "\t" << inventory[i].barcode << "\t"
                 << inventory[i].sold << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No slow-moving products found.\n";
    }
}



void Refund(Item* inventory, int* itemCount) {
    int price, ret_qty, pur_qty, index = -1;
    string user_bill_id, barcode;
    string current_bill_id, current_barcode, temp;

    ifstream file(bill_file);
    if (!file.is_open()) {
        cout << "Error: Unable to open bill file." << endl;
        return;
    }

    cout << "Enter the bill ID: ";
    cin >> user_bill_id;

    bool bill_found = false, item_found = false;
    while (file >> current_bill_id) {
        if (current_bill_id == user_bill_id) {
            bill_found = true;

            // Read items within this bill
            while (file >> current_barcode) {
                if (current_barcode == "=") break; // "=" indicates end of items in the bill

                file >> price >> pur_qty>> temp;

                cout << "Enter the barcode of the item to return: ";
                cin >> barcode;

                if (current_barcode == barcode) {
                    item_found = true;

                    // Ask user for quantity to return
                    do {
                        cout << "Enter the quantity you want to return: ";
                        cin >> ret_qty;

                        if (ret_qty <= 0) {
                            cout << "Quantity must be greater than 0. Please try again.\n";
                        } else if (ret_qty > pur_qty) {
                            cout << "You cannot return more than you purchased. You can return up to " << pur_qty << " items.\n";
                        } else {
                            break; // Valid quantity
                        }
                    } while (true);

                    // Update inventory
                    for (int i = 0; i < *itemCount; i++) {
                        if (inventory[i].barcode == barcode) {
                            inventory[i].quantity += ret_qty;
                            inventory[i].sold -= ret_qty;
                            index = i;
                            break;
                        }
                    }

                    if (index != -1) {
                        cout << "You have returned " << inventory[index].name << " x" << ret_qty << ".\n";
                        cout << "You have been given a refund of: " << ret_qty * price << " units.\n";
                    } else {
                        cout << "Error: Item not found in inventory.\n";
                    }

                    file.close();
                    saveInventory(inventory,*itemCount); // Refund completed
                    return;
                }
            }

            if (!item_found) {
                cout << "The item with barcode " << barcode << " was not found in this bill.\n";
            }

            break; // Exit after processing the bill
        } else {
            // Skip the current line if the bill ID does not match
            getline(file, temp);
        }
    }

    if (!bill_found) {
        cout << "Bill ID " << user_bill_id << " not found.\n";
    }

    file.close();
    saveInventory(inventory,*itemCount);
}
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


void Customer_Management(Customer* customers,int* customerCount) {
    int choice;
    do {
        cout << "\nCustomer Management\n";
        cout << "1. Add Customer\n";
        cout << "2. Update Customer\n";
        cout << "3. Track Purchase\n";
        cout << "4. Generate Customer Report\n";
        cout << "5. Send Flash Messages\n";
        cout << "0. Back\n";
        cout << "Enter your choice: ";
        choice = getValidatedInt("");
        switch (choice) {
            case 1: Add_Customer(customers,customerCount); break;
            case 2: Update_Customer(customers,customerCount); break;
            case 3: Track_Purchase(customers,customerCount); break;
            case 4: Generate_Customer_Report(customers,customerCount); break;
            case 5: Send_Flash_Messages(customers,customerCount); break;
            case 0: cout << "Exiting Customer Management.\n"; break;
            default: cout << "Invalid choice. Please try again.\n"; 
        }
    } while (choice != 0);
}


void Add_Customer(Customer* customers,int* customerCount) {
    if (*customerCount >= MAX_CUSTOMERS) {
        cout << "Customer limit reached. Cannot add more customers.\n";
        return;
    }
    Customer newCustomer;
    cout << "Enter Customer ID: ";
    newCustomer.id = getValidatedInt("");
    for (int i = 0; i < *customerCount; ++i) {
        if (customers[i].id == newCustomer.id) {
            cout << "Customer ID already exists. Please enter a unique ID.\n";
            return;
        }
    }
    cout << "Enter Customer Name: ";
    cin>> newCustomer.name;
    cout << "Enter Customer Email: ";
    cin>>newCustomer.email;
    cout << "Enter Customer Phone Number: ";
    cin>> newCustomer.phoneNumber;
    cout << "Enter Customer Category: ";
    cin>>newCustomer.category;
    newCustomer.totalSpent = 0.0;
    customers[*customerCount] = newCustomer;
    *customerCount+=1;
    Save_Customers_To_File(customers,customerCount);
    cout << "Customer added successfully.\n";
}

void Update_Customer(Customer* customers,int *customerCount) {
    cout << "Enter Customer ID to Update: ";
    int id = getValidatedInt("");
    for (int i = 0; i < *customerCount; ++i) {
        if (customers[i].id == id) {
            cout << "Enter New Customer Name: ";
            cin >>customers[i].name;
            cout << "Enter New Customer Email: ";
            cin >>customers[i].email;
            cout << "Enter New Customer Phone Number: ";
            cin >> customers[i].phoneNumber;
            cout << "Enter New Customer Category: ";
            cin >> customers[i].category;

            Save_Customers_To_File(customers,customerCount);
            cout << "Customer updated successfully.\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}

void Track_Purchase(Customer* customers,int* customerCount) {
    cout << "Enter Customer ID: ";
    int id = getValidatedInt("");
    cout << "Enter Purchase Amount: ";
    double amount;
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid purchase amount. Please enter a positive value.\n";
        return;
    }
    for (int i = 0; i < *customerCount; ++i) {
        if (customers[i].id == id) {
            customers[i].totalSpent += amount;
            Save_Customers_To_File(customers,customerCount);
            cout << "Purchase logged successfully.\n";
            return;
        }
    }
    cout << "Customer not found.\n";
}

void Generate_Customer_Report(Customer* customers,int* customerCount) {
    cout << "\n=== Customer Report ===\n";
    cout << "ID\tName\t\tEmail\t\tPhone\t\tTotal Spent\n";
    cout << "------------------------------------------------------------\n";
    for (int i = 0; i < *customerCount; ++i) {
        cout << customers[i].id << "\t"
             << customers[i].name << "\t"
             << customers[i].email << "\t"
             << customers[i].phoneNumber << "\t"
             << fixed << setprecision(2) << customers[i].totalSpent << "\n";
    }
    cout << "------------------------------------------------------------\n";
}

void Send_Flash_Messages(Customer* customers,int* customerCount) {
    cout << "Enter the spending threshold for regular customers: ";
    double threshold = getValidatedInt("");
    ofstream logFile(flashMessagesLogFile, ios::app);
    if (!logFile.is_open()) {
        cerr << "Error: Could not open log file.\n";
        return;
    }
    for (int i = 0; i < *customerCount; ++i) {
        if (customers[i].totalSpent > threshold) {
            string message = generateMessage(customers[i]);
            cout << "Flash message sent to:\n"
                 << "Name: " << customers[i].name << "\n"
                 << "Email: " << customers[i].email << "\n"
                 << "Message:\n" << message << "\n";
            logFlashMessage(customers[i], message);
        }
    }
    logFile.close();
    cout << "All eligible flash messages have been sent successfully and logged.\n";
}

string generateMessage(const Customer& customer) {
    return "Dear " + customer.name + ",\n"
           "Thank you for being a loyal customer! We are excited to offer you exclusive discounts and sales on your next visit.\n"
           "Visit us soon to make the most of these offers!\n"
           "Best regards,\nMart Management Team";
}

void logFlashMessage(const Customer& customer, const string& message) {
    ofstream logFile(flashMessagesLogFile, ios::app);
    logFile << "Flash Message Sent:\n"
            << "Name: " << customer.name << "\n"
            << "Email: " << customer.email << "\n"
            << "Message:\n" << message << "\n"
            << "--------------------------------------------\n";
}

void Load_Customers_From_File(Customer* customers, int* customerCount) {
    ifstream file(customersFile);
    if (!file.is_open()) {
        cout << "No customer data file found. Starting fresh.\n";
        *customerCount = 0; // Reset the customer count
        return;
    }

    int count = 0; // Temporary counter
    while (file >> customers[count].id) {
        file.ignore(); // Ignore leftover characters
        getline(file, customers[count].name);
        getline(file, customers[count].email);
        getline(file, customers[count].phoneNumber);
        getline(file, customers[count].category);
        file >> customers[count].totalSpent;
        file.ignore(); // Ignore leftover characters

        count++;
        if (count >= MAX_CUSTOMERS) {
            cout << "Warning: Maximum customer limit reached while loading data.\n";
            break;
        }
    }
    file.close();
    *customerCount = count; // Update the actual count
    cout << "Customer data loaded successfully.\n";
}

void Save_Customers_To_File(Customer* customers, int* customerCount) {
    if (*customerCount <= 0) {
        cerr << "Error: No customer data to save.\n";
        return;
    }

    ofstream file(customersFile);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for saving.\n";
        return;
    }

    for (int i = 0; i < *customerCount; ++i) {
        file << customers[i].id << "\n"
             << customers[i].name << "\n"
             << customers[i].email << "\n"
             << customers[i].phoneNumber << "\n"
             << customers[i].category << "\n"
             << customers[i].totalSpent << "\n";
    }
    file.close();
    cout << "Customer data saved successfully.\n";
}


int getValidatedInt(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid number.\n";
    }
    return value;
}




//end of customer management
///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//start of merchandising


void Merchandising(Customer* customers,int* customerCount,Item* inventory,int* itemCount) {
    int choice;

    do{
        cout << "\n=== Merchandising Options ===\n";
        cout << "1. Display Expiring Soon Products\n";
        cout << "2. Display Clearance Sale for Low Stock Products\n";
        cout << "3. Display Products for Customer Based on Category\n";
        cout << "4. Display Seasonal Products\n";
        cout << "5. Display Bestselling Products\n";
        cout << "0. Back\n";
        do{cout << "Enter your choice: ";
        cin >> choice;}while(invalid_in());

        switch (choice) {
            case 1:
                Display_Expiring_Soon_Products(inventory, itemCount);
                break;
            case 2:
                Display_Clearance_Sale(inventory, itemCount);
                break;
            case 3:
                Display_Products_for_Customer(customers, customerCount, inventory, itemCount);
                break;
            case 4:
                Display_Seasonal_Products(inventory, itemCount);
                break;
            case 5:
                Display_Bestsellers(inventory, itemCount);
                break;
            case 0:
                cout << "Exiting Merchandising.\n";
                return; // Exit the function
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }while(choice!=0);
}


void Display_Expiring_Soon_Products(Item* inventory,int* itemCount) {
    cout << "\n=== Expiring Soon Products ===\n";
    for (int i = 0; i < * itemCount; ++i) {
        if ((inventory[i].year < 2024) || 
            (inventory[i].year == 2024 && inventory[i].month < 12) || 
            (inventory[i].year == 2024 && inventory[i].month == 12 && inventory[i].date < 28)) {
            cout << "Expiring soon: " << inventory[i].name << " at Rs"
                 << fixed << setprecision(2) << inventory[i].price << "\n";
        }
    }
}

// Display Clearance Sale for Low Stock Products
void Display_Clearance_Sale(Item* inventory,int* itemCount) {
    const int lowStockThreshold = 5;
    cout << "\n=== Clearance Sale ===\n";
    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].quantity < lowStockThreshold) {
            cout << "Clearance Sale: " << inventory[i].name << " - Discounted Price: Rs"
                 << fixed << setprecision(2) << inventory[i].price * 0.7 << "\n"; // 30% off
        }
    }
}

// Display Products for Customer Based on Category
void Display_Products_for_Customer(Customer* customers, int* customerCount, Item* inventory,int* itemCount) {
    int customerId;
    cout<<"Enter Customer id for which you want products for: ";
    cin>>customerId;
    if (customerId <= 0 || customerId > *customerCount) {
        cout << "Invalid Customer ID.\n";
        return;
    }

    Customer customer = customers[customerId - 1]; // Assumes customer IDs are 1-based
    double discount = 1.0;

    // Apply discount based on customer category
    if (customer.category == "frequent") {
        discount = 0.9;  // 10% discount for frequent buyers
    } else if (customer.category == "vip") {
        discount = 0.8;  // 20% discount for VIP customers
    }

    cout << "\n=== Product List for " << customer.name << " ===\n";
    for (int i = 0; i < *itemCount; ++i) {
        cout << inventory[i].name << " - Rs"
             << fixed << setprecision(2) << inventory[i].price * discount << "\n";
    }
}

// Display Seasonal Products Based on Current Season
void Display_Seasonal_Products(Item* inventory,int* itemCount) {
    string currentSeason;
    cout << "\nEnter current season to display seasonal products: ";
    while (true) {
        cin >> currentSeason;

        // Convert currentSeason to lowercase
        transform(currentSeason.begin(), currentSeason.end(), currentSeason.begin(), ::tolower);

        if (currentSeason != "winter" && currentSeason != "summer" &&
            currentSeason != "spring" && currentSeason != "fall") {
            cout << "Invalid season, please enter a valid season (Winter, Summer, Spring, Fall): ";
        } else {
            break; // If valid, break out of the loop
        }
    }

    cout << "\n=== Seasonal Promotions for " << currentSeason << " ===\n";
    for (int i = 0; i < *itemCount; ++i) {
        string itemSeason = inventory[i].season;
        transform(itemSeason.begin(), itemSeason.end(), itemSeason.begin(), ::tolower);

        if (itemSeason == currentSeason) {
            cout << currentSeason << " Special: " << inventory[i].name << " - Rs"
                 << fixed << setprecision(2) << inventory[i].price * 0.8 << "\n"; // 20% off for seasonal sale
        }
    }
}

// Display Bestselling Products Based on Sales
void Display_Bestsellers(Item* inventory,int* itemCount) {
    int bestsellerThreshold;
    cout << "Enter the threshold for the bestseller products: ";
    cin >> bestsellerThreshold;
    cout << "\n=== Bestselling Products ===\n";
    for (int i = 0; i < *itemCount; ++i) {
        if (inventory[i].sold >= bestsellerThreshold) {
            cout << "Bestseller: " << inventory[i].name << " - Rs"
                 << fixed << setprecision(2) << inventory[i].price << "\n";
        }
    }
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
void Employee_managemnet()
{
    int choice;
    Employee employees[max_employees];
    int employee_count=0;
    loadEmployees(employees,&employee_count);
    do
    {
        cout << "\nEmployee Management System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Display Employees" << endl;
        cout << "3. Search Employee" << endl;
        cout << "4. Delete Employee" << endl;
        cout << "0. Back" << endl;
        cout << "Enter your choice: ";
        do{cin>> choice;}while(invalid_in());
        

        switch (choice)
        {
        case 1:
            add_employee(employees,&employee_count);
            saveEmployees(employees, employee_count);
            break;
        case 2:
            display_employees(employees,&employee_count);
            break;
        case 3:
            search_employee(employees,&employee_count);
            break;
        case 4:
            delete_employee(employees,&employee_count);
            saveEmployees(employees, employee_count);
            break;
        case 0:
            cout << "Exiting Employee Management system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }while(choice!=0);
    return;
}

void add_employee(Employee* employees,int* employee_count)
{
    if (*employee_count >= max_employees)
    {
        cout << "Employee list is full!" << endl;
        return;
    }
    Employee new_employee;

    cout << "Enter employee name: ";
    clearInputBuffer();
    getline(cin, new_employee.name);    
    cout << "Enter employee role: ";
    getline(cin, new_employee.role);
    cout << "Enter employee phone number: ";
    getline(cin, new_employee.phone);
    cout << "Enter employee salary: ";
    do{cin >> new_employee.salary;}while(invalid_in());

    employees[*employee_count] = new_employee;
    *employee_count+=1;
    cout << "Employee added successfully!" << endl;
    cout << "_______________________________________________________________\n";
    saveEmployees(employees,*employee_count);
}

void display_employees(Employee* employees,int* employee_count)
{
    if (*employee_count == 0)
    {
        cout << "No employees to display." << endl;
        return;
    }
    cout << "\nEmployee List: " << endl;
    for (int i = 0; i <*employee_count; i++)
    {
        const Employee& employee = employees[i];
        cout << "Name: " << employee.name << endl;
        cout << "Role: " << employee.role << endl;
        cout << "Phone: " << employee.phone << endl;
        cout << "Salary: " << employee.salary << endl;
        cout << "_______________________________________________________________\n";
    }
}

void search_employee(Employee* employees,int* employee_count)
{
    if (*employee_count == 0)
    {
        cout << "No employees to search!" << endl;
        return;
    }
    
    string name;
    cout << "\nEnter the employee name to search: ";
    clearInputBuffer();
    getline(cin, name);

    for (int i = 0; i < *employee_count; i++)
    {
        if (employees[i].name == name)
        {
            cout << "Employee Found!" << endl;
            const Employee& employee = employees[i];
            cout << "Name: " << employee.name << endl;
            cout << "Role: " << employee.role << endl;
            cout << "Phone: " << employee.phone << endl;
            cout << "Salary: " << employee.salary << endl;
            cout << "________________________________________________________________\n";
            return;
        }
    }
    cout << "Employee not found!" << endl;
}


void delete_employee(Employee* employees,int* employee_count)
{
    if (*employee_count == 0)
    {
        cout << "No employees to delete!" << endl;
        return;
    }
    
    string name;
    cout << "\nEnter the employee name to delete: ";
    clearInputBuffer();
    getline(cin, name);

    for (int i = 0; i < *employee_count; i++)
    {
        if (employees[i].name == name)
        {
            // Shift remaining employees to fill the gap
            for (int j = i; j <*employee_count - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            employee_count--;
            cout << "Employee \"" << name << "\" deleted successfully!" << endl;
            cout << "_______________________________________________________________\n";
            return;
        }
    }
    cout << "Employee not found!" << endl;
}


// Save Employees to File
void saveEmployees(Employee* employees, int employeeCount) {
    const string employeeFile = "employees.txt"; // File to store employee data
    ofstream file(employeeFile);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing employees.\n";
        return;
    }

    for (int i = 0; i < employeeCount; ++i) {
        file << employees[i].name << " "
             << employees[i].role << " "
             << employees[i].phone << " "
             << employees[i].salary << "\n";
    }

    file.close();
    cout << "Employee data saved successfully.\n";
}




void loadEmployees(Employee* employees, int* employee_count)
{
    ifstream file("employees.txt");

    if (file.is_open())
    {
        *employee_count = 0;
        string line;

        while (*employee_count < max_employees && 
               file >> employees[*employee_count].name 
                    >> employees[*employee_count].role 
                    >> employees[*employee_count].phone 
                    >> employees[*employee_count].salary)
        {
            (*employee_count)++;
        }

        file.close();
        cout << "Employees loaded from file successfully! Total employees: " << *employee_count << endl;
    }
    else
    {
        cout << "Unable to open file or file doesn't exist!" << endl;
    }
}


void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
} 
//////////////////////////////////////////////////



//a function for checking valid input datatype
bool invalid_in()
{
    if (cin.fail())
    {

        cin.clear(); // Clear the failure state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout<<"<invalid input>\n";
        return true;
    }
    return false;
}