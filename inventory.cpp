#include<iostream>
#include<fstream>
using namespace std;
class Product
 {
protected:
int id;
char name[30];
float price;
int quantity;

public:
void input() {
cout << "Enter product ID: ";
cin >> id;
cin.ignore(); 
cout << "Enter product name: ";
cin.getline(name, 30);
cout << "Enter price: ";
cin >> price;
cout << "Enter quantity: ";
cin >> quantity;
}

void display() {
cout << "ID: " << id << endl
<< "Name: " << name << endl
<< "Price: " << price << endl
<< "Quantity: " << quantity << endl;
}

int getId()
{
return id;
}

void setQuantity(int q)
{
quantity = q;
}
};

// File handling functions
void write_records() {
int n;
Product p;
fstream fout;
fout.open("Inventory.dat", ios::out | ios::app | ios::binary);
cout << "Enter number of products to add: ";
cin >> n;
cin.ignore(); // To clear the newline
cout << "Enter the information of products:" << endl;
for(int i = 0; i < n; i++) {
p.input();
fout.write((char*)&p, sizeof(p));
}
fout.close();
cout << "Products added successfully!" << endl;
}

void read_records() {
Product p;
fstream fin("Inventory.dat", ios::binary | ios::in);
if (!fin) {
cout << "No products found!" << endl;
return;
}
while (fin.read((char*)&p, sizeof(p))) {
p.display();
}
fin.close();
}

void search_product() {
int searchId;
Product p;
fstream fin;
int found = 0;
cout << "Enter product ID to search: ";
cin >> searchId;
fin.open("Inventory.dat", ios::in | ios::binary);
if(!fin) {
cout << "No products found!" << endl;
return;
}
while(fin.read((char*)&p, sizeof(p))) {
if(p.getId() == searchId) {
cout << "Product found:" << endl;
p.display();
found = 1;
break;
}
}
if(found == 0) {
cout << "Product not found!" << endl;
}
fin.close();
}

void update_quantity() {
    int searchId, newQty;
    Product p;
    fstream fin, fout;
    int found = 0;
    cout << "Enter product ID to update: ";
    cin >> searchId;
    cout << "Enter new quantity: ";
    cin >> newQty;
    fin.open("Inventory.dat", ios::in | ios::binary);
    if (!fin) {
        cout << "Error: Cannot open Inventory.dat. File may not exist!" << endl;
        return;
    }
    fout.open("temp.dat", ios::out | ios::binary);  
    if (!fout) {
        cout << "Error: Cannot create temporary file!" << endl;
        fin.close();
        return;
    }
        if (p.getId() == searchId) {
            p.setQuantity(newQty);
            found = 1;
        }
        fout.write((char*)&p, sizeof(p));
    fin.close();
    fout.close();
    if (found)
	 {
        remove("Inventory.dat");           
		rename("temp.dat", "Inventory.dat"); 
        cout << "Quantity updated successfully!" << endl;
    } 
    else{
        remove("temp.dat"); // Clean up temp file
        cout << "Product not found!" << endl;
    }
}

void delete_product()
{
int searchId;
Product p;
fstream fin, fout;
int found = 0;
cout << "Enter product ID to delete: ";
cin >> searchId;
fin.open("Inventory.dat", ios::in | ios::binary);
fout.open("temp.dat", ios::out | ios::binary);
if(!fin)
 {
cout << "No products found!" << endl;
return;
}

while(fin.read((char*)&p, sizeof(p))) 
{
if(p.getId() != searchId)
 {
fout.write((char*)&p, sizeof(p));
} 
else
{
found = 1;
}
}
fin.close();
fout.close();
if(found == 1)
 {
remove("Inventory.dat");
rename("temp.dat", "Inventory.dat");
cout << "Product deleted successfully!" << endl;
} 
else
 {
remove("temp.dat");
cout << "Product not found!" << endl;
}
}

int main() {
int choice;
while(1) {
cout << "\n--- Inventory Management System ---" << endl;
cout << "1. Add Products" << endl;
cout << "2. Display All Products" << endl;
cout << "3. Search Product" << endl;
cout << "4. Update Quantity" << endl;
cout << "5. Delete Product" << endl;
cout << "6. Exit" << endl;
cout << "Enter your choice: ";
cin >> choice;

switch(choice) 
{
case 1: 
write_records(); 
break;
case 2: 
read_records(); 
break;
case 3:
search_product(); 
break;
case 4:
update_quantity();
break;
case 5:
delete_product(); 
break;
case 6:
cout << "Exiting program..." << endl; 
exit(0);
default: 
cout << "Invalid choice! Try again." << endl;
}
}
return 0;
}
