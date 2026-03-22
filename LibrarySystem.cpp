#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class LibrarySystem {
private:
    struct Book {
        int count;
        string name;
        string author;
        int isbn;
    };
    Book books[100];
    int currentCount;
    
public:
    LibrarySystem() { currentCount = 0; }
    
    void run() {
        int choice;
        bool running = true;
        
        while(running) {
            system("cls");
            cout << "=== Library Management System ===" << endl;
            cout << "Borrow(1) Return(2) Add(3) Exit(0)" << endl;
            cout << "Please choose: ";
            cin >> choice;
            
            switch(choice) {
                case 0: 
                    running = false; 
                    break;
                case 1: 
                    borrowBook(); 
                    break;
                case 2: 
                    returnBook(); 
                    break;
                case 3: 
                    addBook(); 
                    break;
                default: 
                    cout << "Invalid input, please try again!" << endl;
                    Sleep(1000);
                    break;
            }
        }
    }
    
    void borrowBook() {
        system("cls");
        int isbn;
        cout << "Please enter the ISBN of the book to borrow: ";
        cin >> isbn;
        
        for(int i = 0; i < currentCount; i++) {
            if(isbn == books[i].isbn) {
                if(books[i].count <= 0) {
                    cout << "Insufficient stock, cannot borrow!" << endl;
                } else {
                    cout << "Book title: " << books[i].name << endl;
                    cout << "Confirm borrowing? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    if(confirm == 'y' || confirm == 'Y') {
                        books[i].count--;
                        cout << "Borrow successful, remaining quantity: " << books[i].count << endl;
                    }
                }
                Sleep(2000);
                return;
            }
        }
        cout << "Book with this ISBN not found!" << endl;
        Sleep(2000);
    }
    
    void returnBook() {
        system("cls");
        int isbn;
        cout << "Please enter the ISBN of the book to return: ";
        cin >> isbn;
        
        for(int i = 0; i < currentCount; i++) {
            if(isbn == books[i].isbn) {
                if(books[i].count >= 5) {
                    cout << "Maximum stock reached, cannot return!" << endl;
                } else {
                    cout << "Book title: " << books[i].name << endl;
                    cout << "Confirm return? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    if(confirm == 'y' || confirm == 'Y') {
                        books[i].count++;
                        cout << "Return successful, remaining quantity: " << books[i].count << endl;
                    }
                }
                Sleep(2000);
                return;
            }
        }
        cout << "Book with this ISBN not found!" << endl;
        Sleep(2000);
    }
    
    void addBook() {
        system("cls");
        if(currentCount >= 100) {
            cout << "Storage is full!" << endl;
            Sleep(1000);
            return;
        }
        
        cout << "Please enter the quantity of books (1-5): ";
        cin >> books[currentCount].count;
        
        if(books[currentCount].count < 1 || books[currentCount].count > 5) {
            cout << "Quantity must be between 1-5!" << endl;
            Sleep(1000);
            return;
        }
        
        cout << "Please enter the book title: ";
        cin.ignore();
        getline(cin, books[currentCount].name);
        
        cout << "Please enter the author: ";
        getline(cin, books[currentCount].author);
        
        cout << "Please enter the ISBN: ";
        cin >> books[currentCount].isbn;
        
        cout << "Book added successfully!" << endl;
        cout << "Information: " << books[currentCount].count << " copy(ies) of 《" 
             << books[currentCount].name << "》 Author:" 
             << books[currentCount].author << " ISBN:" 
             << books[currentCount].isbn << endl;
        
        currentCount++;
        Sleep(2000);
    }
};

int main() {
    LibrarySystem library;
    library.run();
    return 0;
}

