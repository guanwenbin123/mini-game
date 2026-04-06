#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <windows.h>  // For Sleep function

using namespace std;

// Vehicle information structure
struct Car {
    int id;            // Vehicle ID
    string plate;      // License plate
    time_t parkTime;   // Parking time
    bool isParked;     // Is currently parked
};

class ParkingSystem {
private:
    vector<Car> cars;  // Store all vehicles
    double hourlyRate; // Hourly fee
    int nextId;        // Next vehicle ID
    
public:
    ParkingSystem(double rate) {
        hourlyRate = rate;
        nextId = 1;
        cout << "Parking system started. Fee rate: " << rate << " yuan/hour" << endl;
    }
    
    // Park a car
    void parkCar() {
        string plate;
        cout << "\nEnter license plate: ";
        cin >> plate;
        
        // Check if plate already exists
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].plate == plate && cars[i].isParked) {
                cout << "This car is already parked!" << endl;
                return;
            }
        }
        
        Car newCar;
        newCar.id = nextId++;
        newCar.plate = plate;
        newCar.parkTime = time(0);  // Get current time
        newCar.isParked = true;
        
        cars.push_back(newCar);
        
        cout << "Car parked successfully!" << endl;
        cout << "Vehicle ID: " << newCar.id << endl;
        cout << "License plate: " << newCar.plate << endl;
        cout << "Parking time: " << ctime(&newCar.parkTime);
    }
    
    // Take a car
    void takeCar() {
        int id;
        cout << "\nEnter vehicle ID: ";
        cin >> id;
        
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].id == id && cars[i].isParked) {
                time_t now = time(0);
                double hours = difftime(now, cars[i].parkTime) / 3600.0;
                
                // Minimum 1 hour
                if (hours < 1) hours = 1;
                
                double fee = hours * hourlyRate;
                
                cout << "\n=== Vehicle Retrieval Information ===" << endl;
                cout << "License plate: " << cars[i].plate << endl;
                cout << "Parking time: " << ctime(&cars[i].parkTime);
                cout << "Retrieval time: " << ctime(&now);
                cout << "Parking duration: " << fixed << setprecision(1) << hours << " hours" << endl;
                cout << "Fee: " << fixed << setprecision(2) << fee << " yuan" << endl;
                cout << "===================================" << endl;
                
                cars[i].isParked = false;
                return;
            }
        }
        
        cout << "Vehicle not found or already taken!" << endl;
    }
    
    // Check parking lot status
    void showStatus() {
        int parkedCount = 0;
        
        cout << "\n=== Parking Lot Status ===" << endl;
        for (int i = 0; i < cars.size(); i++) {
            if (cars[i].isParked) {
                parkedCount++;
                cout << "ID: " << cars[i].id 
                     << "  Plate: " << cars[i].plate
                     << "  Parking time: " << ctime(&cars[i].parkTime);
            }
        }
        
        cout << "Currently " << parkedCount << " cars in parking lot" << endl;
        cout << "==========================" << endl;
    }
};

int main() {
    // Set hourly fee to 5 yuan
    ParkingSystem parking(5.0);
    int choice;
    
    while (true) {
        cout << "\n=== Parking Management System ===" << endl;
        cout << "1. Park a car" << endl;
        cout << "2. Take a car" << endl;
        cout << "3. Check parking lot status" << endl;
        cout << "4. Exit system" << endl;
        cout << "Choose option (1-4): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                parking.parkCar();
                break;
            case 2:
                parking.takeCar();
                break;
            case 3:
                parking.showStatus();
                break;
            case 4:
                cout << "Thank you for using! Goodbye!" << endl;
                Sleep(2000);  // Wait 2 seconds before exit
                return 0;
            default:
                cout << "Wrong input, please try again!" << endl;
        }
        
        // Pause 1 second after each operation
        cout << "\nOperation completed. Returning to menu in 1 second..." << endl;
        Sleep(1000);
    }
    
    return 0;
}
