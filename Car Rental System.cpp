#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Car {
private:
    string brand;
    string model;
    double pricePerDay;

public:
    Car(const string& brand, const string& model, double pricePerDay)
        : brand(brand), model(model), pricePerDay(pricePerDay) {}

    string getBrand() const {
        return brand;
    }

    string getModel() const {
        return model;
    }

    double getPricePerDay() const {
        return pricePerDay;
    }
};

class CarRentalSystem {
private:
    vector<Car> cars;

public:
    void addCar(const string& brand, const string& model, double pricePerDay) {
        cars.push_back(Car(brand, model, pricePerDay));
    }

    void showCarOptions() const {
        cout << "Available cars for rent:\n";
        for (size_t i = 0; i < cars.size(); ++i) {
            cout << i + 1 << ". " << cars[i].getBrand() << " " << cars[i].getModel() << endl;
        }
    }

    double calculateRent(int carIndex, int numberOfDays) const {
        if (carIndex >= 0 && carIndex < static_cast<int>(cars.size()) && numberOfDays > 0) {
            return cars[carIndex].getPricePerDay() * numberOfDays;
        }
        return 0.0;
    }

    const vector<Car>& getCars() const {
        return cars;
    }
};

class Admin {
public:
    bool login() {
        string password;
        cout << "Enter the admin password: ";
        cin >> password;

        // Hardcoded admin password for demonstration purposes
        if (password == "admin123") {
            cout << "Admin login successful\n";
            return true;
        } else {
            cout << "Admin login failed. Incorrect password\n";
            return false;
        }
    }

    void addCar(CarRentalSystem& carRentalSystem) {
        string brand, model;
        double pricePerDay;

        cout << "Enter the car brand: ";
        cin >> brand;
        cout << "Enter the car model: ";
        cin >> model;
        cout << "Enter the price per day: ";
        cin >> pricePerDay;

        carRentalSystem.addCar(brand, model, pricePerDay);
        cout << "Car added successfully\n";

        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        system("CLS");
//        clearScreen();
    }
};

class Customer {
public:
    void login(const CarRentalSystem& carRentalSystem) {
        cout << "Customer login\n";

        string customerName;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, customerName);

        carRentalSystem.showCarOptions();

        int carIndex;
        cout << "Choose a car (enter car number): ";
        cin >> carIndex;

        if (carIndex > 0 && carIndex <= static_cast<int>(carRentalSystem.getCars().size())) {
            carIndex--;

            int numberOfDays;
            cout << "Enter the number of days for renting: ";
            cin >> numberOfDays;

            double totalRent = carRentalSystem.calculateRent(carIndex, numberOfDays);
            cout << "Calculating rent please wait" << endl;
            cout << "Press Enter to Get Receipt" << endl;
            cin.ignore();
            cin.get();

            // Display the customer invoice
            sleep(5);
             system("CLS");
//            clearScreen();
            cout << "\n                       Car Rental - Customer Invoice                  " << endl;
            cout << "    ///////////////////////////////////////////////////////////" << endl;
            cout << "    | Invoice No. :" << setw(18) << "| #" << setw(10) << "Cnb81353" << " |" << endl;
            cout << "    | Customer Name:" << setw(17) << "| " << setw(10) << customerName << " |" << endl;
            cout << "    | Car Model :" << setw(20) << "| " << setw(10) << carRentalSystem.getCars()[carIndex].getModel() << " |" << endl;
            cout << "    | Number of days :" << setw(15) << "| " << setw(10) << numberOfDays << " |" << endl;
            cout << "    | Your Rental Amount is :" << setw(10) << "| $" << setw(10) << totalRent << " |" << endl;
            cout << "    | Caution Money :" << setw(19) << "| " << setw(10) << "0" << " |" << endl;
            cout << "    | Advanced :" << setw(24) << "| " << setw(10) << "0" << " |" << endl;
            cout << "     ________________________________________________________" << endl;
            cout << "\n";
            cout << "    | Total Rental Amount is :" << setw(13) << "| $" << setw(10) << totalRent << " |" << endl;
            cout << "     ________________________________________________________" << endl;
            cout << "     # This is a computer-generated invoice and does not require an authorized signature #" << endl;
            cout << " " << endl;
            cout << "    ///////////////////////////////////////////////////////////" << endl;
            cout << "    You are advised to pay up the amount before the due date." << endl;
            cout << "    Otherwise, a penalty fee will be applied." << endl;
            cout << "    ///////////////////////////////////////////////////////////" << endl;

            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
 system("Cls");
//            clearScreen();
        } else {
            cout << "Invalid car choice. Please try again!\n";
        }
    }
};

void sleep(int seconds) {
    usleep(seconds * 1000000);
}

void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For UNIX/Linux
#endif
}

int main() {
    CarRentalSystem carRentalSystem;
    carRentalSystem.addCar("Toyota", "Corolla", 50.0);
    carRentalSystem.addCar("Honda", "Civic", 60.0);
    carRentalSystem.addCar("Ford", "Mustang", 100.0);

    Admin admin;
    Customer customer;

    while (true) {
        int choice;
        cout << "1. Admin Login\n";
        cout << "2. Customer Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (admin.login()) {
                admin.addCar(carRentalSystem);
            }
        } else if (choice == 2) {
            customer.login(carRentalSystem);
        } else if (choice == 3) {
            cout << "Thank you for using the car rental system. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again!\n";
        }
    }

    return 0;
}

