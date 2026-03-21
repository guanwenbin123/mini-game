#include <iostream>
#include <conio.h>  
#include <windows.h>
using namespace std;

class ElevatorSystem {
    public:
        int currentFloor, elevatorFloor, unused;
        ElevatorSystem() : currentFloor(0), elevatorFloor(0), unused(0) {}
        
        void checkCall() {
            if (_kbhit()) {
                if(elevatorFloor < currentFloor) {
                    for(; elevatorFloor <= currentFloor; elevatorFloor++) {
                        cout << "Elevator floor: " << elevatorFloor << endl;
                        Sleep(500);
                    }
                    cout << "Arrived" << endl;
                } else {
                    for(; elevatorFloor >= currentFloor; elevatorFloor--) {
                        cout << "Elevator floor: " << elevatorFloor << endl;
                        Sleep(500);
                    }
                    cout << "Arrived" << endl;
                }
            }    
        }
        
        void selectFloor() {
            cout << "Current floor: " << currentFloor << " Enter target floor: " << endl;
            cin >> currentFloor;
            if(elevatorFloor < currentFloor) {
                for(; elevatorFloor <= currentFloor; elevatorFloor++) {
                    cout << "Elevator floor: " << elevatorFloor << endl;
                    Sleep(500);
                }
                cout << "Arrived" << endl;
            } else {
                for(; elevatorFloor >= currentFloor; elevatorFloor--) {
                    cout << "Elevator floor: " << elevatorFloor << endl;
                    Sleep(500);
                }
                cout << "Arrived" << endl;
            }
        }
        
        void start() {
            cout << "Enter initial floor: " << endl;
            cin >> currentFloor;
            for(;;) {
                system("cls");
                cout << "Current floor: " << currentFloor << " Press any key to call elevator" << endl;
                checkCall();
                system("cls");
                selectFloor();
            }
        }
};

int main() {
    ElevatorSystem elevator;
    elevator.start();
    return 0;
}
