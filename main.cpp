//
//  main.cpp
//  Assignment2Xcode
//
//  Created by Kyle Goosen on 19/5/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>

using namespace std;

char userType;

#include "tree.h"

void categoryDisplay(Node *current);
void itemDisplay(Node * current);

Node *tree = new Category("Main Category");

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false)
      return false;
      return true;
}

int buyItem(Node* current){
    int gonnaReturn;
    cout << endl << "Enter your offer price: ";
    double offerPrice;
    char input[10];
    cin >> input;
    offerPrice = atof(input);
    if (offerPrice >= (current->getPrice() * (1.0 - current->getMaxDiscount()))) {
        

        if (current->getQuantity() > 1){
            current->setQuantity(current->getQuantity()-1);
            gonnaReturn= 1;
        } else {
            current->GetParent()->Remove(current);
            delete current;
            gonnaReturn= 2;
        }
        
        
        cout
                << "\nThank you for buying our products. You have bought the following item at price $"
                << offerPrice << ":" << endl;
        cout << endl;
    } else {
        cout << "\nSorry, we can't sell it to you at this price.\n"
                << endl;
        gonnaReturn = 3;
    }
    
    return gonnaReturn;
}

int managerEmptyCat(Node * current){
    int choice;
    do {
        cout << "The above category is empty. Please choose" << endl ;
        cout << "=====================" << endl ;
        cout << "1: Delete the category" << endl ;
        cout << "2: Modify the category" << endl ;
        cout << "3: Other operations" << endl ;
        cout << "=====================" << endl ;
        cout << "Input a number from 1 to 3 :";
        
        cin >> choice;
        
        if (choice == 1){
            current->GetParent()->Remove(current);
            return 1;
        } else if (choice == 2){
            editCategory(current);
            return 2;
        } else if (choice == 3){
            return 3;
        }
        
    } while (choice != 3);
    
    return 1;
}

void clearScreen(){
    cout << string( 2, '\n' );
    //system("clear");
}

void traverse(Node *current){
    
   
    clearScreen();
        
    if (current->IsCategory() == true){
        categoryDisplay(current);
    } else {
        itemDisplay(current);
    }


}

void itemDisplay(Node * current){

    int choice, i;
    
    do {
        i=0;
        clearScreen();
        cout << "The following item is for sale:" << endl;
        cout << "| Item key" << setw(20) << "| Item Title" << setw(20) << "| Stock Quantity" << setw(20) << "| List Price" << setw(20) << "| Description" << endl << endl;
        cout << "1" << setw(20) <<current->title << setw(20) << current->getQuantity() << setw(20) << current->getPrice() << setw(20) << current->getDescription() << setw(20);
        
        clearScreen();
        cout << "=====================" << endl;
        cout << "1: Buy the item (for buyers)" << endl;
        cout << "2: Delete the item (for the manager)" << endl;
        cout << "3: Modify the item (for the manager)" << endl;
        cout << "4: Other operations" << endl;
        cout << "=====================" << endl;
        cout << "Input a number from 1 to 4 :";

        cin >> choice;
        
        if (choice == 1){
            int option = buyItem(current);
            if (option == 1){
                continue;
            } else if (option == 2){
                return;
            } else if (option == 3){
                continue;
            }
        } else if (choice == 2){
            if (userType == 'M'){
                current->GetParent()->Remove(current);
                return;
            } else {
                cout << "Have to be manager to delete items";
            }
        } else if (choice == 3){
            if (userType == 'M'){
            
                string title;
                string description;
                double price;
                int quantity;
                double maxDiscount;
                cout << endl << "Enter item title: ";
                cin >> title;
                
                cout << endl << "Enter item description: ";
                cin >> description;
                
                bool ok;
                do
                {
                    ok = true;
                    cout << endl << "Enter item price: ";
                    cin >> price;
                    if ( !cin )                           // Check state of stream to check that there is something numerical FIRST
                    {
                        ok = false;
                        cin.clear();                       // Clear error flags
                        cin.ignore( 1000, '\n' );          // Empty any reasonable input buffer
                    }
                    else
                    {
                        string dummy;
                        getline( cin, dummy );             // Check rest of stream to check that there is nothing non-numerical AFTER
                        if ( dummy.find_first_not_of( " " ) != string::npos ) ok = false;
                    }

                    if ( !ok ) cout << "Invalid double; try again\n";
                } while ( !ok );
                
                do
                {
                    ok = true;
                    cout <<endl<< "Enter item quantity: ";
                    cin >> quantity;
                    if ( !cin )                           // Check state of stream to check that there is something numerical FIRST
                    {
                        ok = false;
                        cin.clear();                       // Clear error flags
                        cin.ignore( 1000, '\n' );          // Empty any reasonable input buffer
                    }
                    else
                    {
                        string dummy;
                        getline( cin, dummy );             // Check rest of stream to check that there is nothing non-numerical AFTER
                        if ( dummy.find_first_not_of( " " ) != string::npos ) ok = false;
                    }

                    if ( !ok ) cout << "Invalid integer; try again\n";
                } while ( !ok );
                
                do
                {
                    ok = true;
                    cout << endl<< "Enter item discount: ";
                    cin >> maxDiscount;
                    if ( !cin )                           // Check state of stream to check that there is something numerical FIRST
                    {
                        ok = false;
                        cin.clear();                       // Clear error flags
                        cin.ignore( 1000, '\n' );          // Empty any reasonable input buffer
                    }
                    else
                    {
                        string dummy;
                        getline( cin, dummy );             // Check rest of stream to check that there is nothing non-numerical AFTER
                        if ( dummy.find_first_not_of( " " ) != string::npos ) ok = false;
                    }

                    if ( !ok ) cout << "Invalid double; try again\n";
                } while ( !ok );
            
            
            Node *temp = new Item(title, description, price, quantity, maxDiscount);
            current->GetParent()->Add(temp);
            current->GetParent()->Remove(current);
            current = temp;
            } else {
                cout << "Have to be manager to modify items";
            }
        } else if (choice == 4){
            return;
        }
        
    } while (choice != 4);
}

void categoryDisplay(Node *current){
    int i, choice;
    
    do {
        clearScreen();
        i=0;
        cout << "Current category: " << current->title << endl;
        
        list<Node *> child = current->getChildren();
        if (child.size() < 1 && userType == 'M'){
            int option = managerEmptyCat(current);
            if (option == 1)
                return;
            else if (option == 2){
                continue;
            } 
        } else {
            
            for (auto it = child.begin(); it != child.end(); ++it){
                
                if ((*it)->IsCategory()){
                    cout << (i+1) << ". " << "Category: " << (*it)->title << endl;
                    i++;
                } else {
                    cout << (i+1) << ". " << "Selling item: " << (*it)->title << endl;
                    i++;
                }
            }
        }
        
        if (userType == 'S' || userType == 'M'){
            cout << ++i << ". Add a new category" << endl;
            cout << ++i << ". Add a new selling item" << endl;
        }
        
        
        cout << ++i << ". Back to upper category" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (userType == 'S' || userType == 'M'){
            if (choice == i - 2){
                string catTitle;
                cout << "Enter category title: ";
                cin >> catTitle;
                
                Node *temp = new Category(catTitle);
                current->Add(temp);
                
            } else if (choice == i - 1){
                string title;
                string description;
                double price;
                int quantity;
                double maxDiscount;
                cout << endl << "Enter item title: ";
                cin >> title;
                
                cout << endl << "Enter item description: ";
                cin >> description;
                
                bool ok;
                do
                {
                    ok = true;
                    cout << endl << "Enter item price: ";
                    cin >> price;
                    if ( !cin )                           // Check state of stream to check that there is something numerical FIRST
                    {
                        ok = false;
                        cin.clear();                       // Clear error flags
                        cin.ignore( 1000, '\n' );          // Empty any reasonable input buffer
                    }
                    else
                    {
                        string dummy;
                        getline( cin, dummy );             // Check rest of stream to check that there is nothing non-numerical AFTER
                        if ( dummy.find_first_not_of( " " ) != string::npos ) ok = false;
                    }

                    if ( !ok ) cout << "Invalid double; try again\n";
                } while ( !ok );
                
                do
                {
                    ok = true;
                    cout <<endl<< "Enter item quantity: ";
                    cin >> quantity;
                    if ( !cin )                           // Check state of stream to check that there is something numerical FIRST
                    {
                        ok = false;
                        cin.clear();                       // Clear error flags
                        cin.ignore( 1000, '\n' );          // Empty any reasonable input buffer
                    }
                    else
                    {
                        string dummy;
                        getline( cin, dummy );             // Check rest of stream to check that there is nothing non-numerical AFTER
                        if ( dummy.find_first_not_of( " " ) != string::npos ) ok = false;
                    }

                    if ( !ok ) cout << "Invalid integer; try again\n";
                } while ( !ok );
                
                do
                {
                    ok = true;
                    cout << endl<< "Enter item discount: ";
                    cin >> maxDiscount;
                    if ( !cin )                           // Check state of stream to check that there is something numerical FIRST
                    {
                        ok = false;
                        cin.clear();                       // Clear error flags
                        cin.ignore( 1000, '\n' );          // Empty any reasonable input buffer
                    }
                    else
                    {
                        string dummy;
                        getline( cin, dummy );             // Check rest of stream to check that there is nothing non-numerical AFTER
                        if ( dummy.find_first_not_of( " " ) != string::npos ) ok = false;
                    }

                    if ( !ok ) cout << "Invalid double; try again\n";
                } while ( !ok );
                
                
                Node *temp = new Item(title, description, price, quantity, maxDiscount);
                current->Add(temp);
            }
        }
        
        if (choice == i){
            return;
        } else if (userType != 'B' && choice >= 1 && choice < i-2){
            
            
                list<Node *> child = current->getChildren();
                list<Node *>::iterator it = child.begin();
                advance(it, choice-1);
                traverse(*it);
        } else if (userType == 'B' && choice >= 1 && choice < i){
            
            
            list<Node *> child = current->getChildren();
            list<Node *>::iterator it = child.begin();
            advance(it, choice-1);
            traverse(*it);
    }
    } while (choice != i);
}

void sellerMenu(){
    char choice;
    
    do {
        clearScreen();
        cout << "======== MENU =======\n";
        cout << "P. Place a selling item" << endl;
        cout << "S. Search an item"<< endl;
        cout << "Q. Quit to main menu"<< endl;
        cout << "=====================\n";
        cout << "Enter your choice:  ";

        cin >> choice;
        
        if (choice == 'P'){
            traverse(tree);
        } else if (choice == 'S'){
            string textFind;
            
            cout << endl << "Enter text to find: ";
            cin >> textFind;
            cout << endl << endl;
            searchItem(tree, textFind);
        } else if (choice == 'Q'){
            return;
        } else {
            cout << "Invalid choice, please try again:" << endl << endl;
            sellerMenu();
        }
        
    } while (choice!='Q');
    
}

void buyerMenu(){
    char choice;

    do {
        clearScreen();

        cout << "======== MENU =======\n";
        cout << "B. Buy a selling item" << endl;
        cout << "S. Search an item"<< endl;
        cout << "Q. Quit to main menu"<< endl;
        cout << "=====================\n";
        cout << "Enter your choice:  ";
        
        cin >> choice;
        
        if (choice == 'B'){
            traverse(tree);
        } else if (choice == 'S'){
            string textFind;
            
            cout << endl << "Enter text to find: ";
            cin >> textFind;
            cout << endl << endl;
            searchItem(tree, textFind);
        } else if (choice == 'Q'){
            return;
        } else {
            cout << "Invalid choice, please try again:" << endl << endl;
            buyerMenu();
        }
    } while (choice!='Q');
    
}

void managerMenu(){
    char choice;
    do {
        clearScreen();
        cout << "======== MENU =======" << endl;
        cout << "M. Manage the catelogue" << endl;
        cout << "S. Search an item" << endl;
        cout << "Q. Quit to main menu" << endl;
        cout << "=====================" << endl;
        cout << "Enter your choice:  ";
        
        cin >> choice;
        
        if (choice == 'M'){
            traverse(tree);
        } else if (choice == 'S'){
            string textFind;
            
            cout << endl << "Enter text to find: ";
            cin >> textFind;
            cout << endl << endl;
            searchItem(tree, textFind);
        } else if (choice == 'Q'){
            return;
        } else {
            cout << "Invalid choice, please try again:" << endl << endl;
            managerMenu();
        }
    } while (choice!='Q');
    
    
}

int main() {
    
        Node *plants = new Category("Plants");
    
        Node *leaf_1 = new Item("Roses", "heelo", 10, 4, 10.00);
        Node *leaf_2 = new Item("Tulip", "heelo", 12.20, 1, 10.00);
        Node *leaf_3 = new Item("Sony", "heelo", 12.20, 1, 10.00);
    
        plants->Add(leaf_1);
        plants->Add(leaf_2);
        Node *tv = new Category("TV's");
        tv->Add(leaf_3);
        tree->Add(plants);
        tree->Add(tv);
    
    char choice;
    
    do {
        clearScreen();
        cout << "======== MENU =======\n";
        cout << "S. Sell an item\n";
        cout << "B. Buy an item\n";
        cout << "M. Manage the market\n";
        cout << "Q. Quit\n";
        cout << "=====================\n";
        cout << "Enter your choice:  ";

        cin >> choice;
        
        if (choice == 'S'){
            userType = 'S';
            sellerMenu();
        } else if (choice == 'B'){
            userType = 'B';
            buyerMenu();
        } else if (choice == 'M'){
            userType = 'M';
            managerMenu();
        } else {
            cout << "\a";
        }
            
    } while (choice != 'Q');

    
}

