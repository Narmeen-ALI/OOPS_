#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_TRIPS = 100;

struct Trip {
    string destination;
    int days;
    double budget;
    string startDate;
};

Trip trips[MAX_TRIPS];
int tripCount = 0;

void addTrip();
void displayTrips();
void saveTripsToFile();
void loadTripsFromFile();
void searchTrip();
void deleteTrip();
void showMenuOptions();
int getUserChoice();
string inputDestination();
int inputDays();
double inputBudget();
string inputStartDate();
bool checkStorageFull();
void addTripToArray(Trip t);
void displayTripHeader();
void displaySingleTrip(int i);
void displayNoTripsMessage();
double calculateTripBudget(Trip t);
void printTotalBudget(double total);
void displayPackingList(Trip t);
void exitMessage();
void enterbutton();

int main() {
    loadTripsFromFile();
    int choice;
    do {
        showMenuOptions();
        choice = getUserChoice();
        switch(choice) {
            case 1: addTrip(); break;
            case 2: displayTrips(); break;
            case 3: saveTripsToFile(); break;
            case 4: searchTrip(); break;
            case 5: deleteTrip(); break;
            case 6: exitMessage(); break;
            default: cout << "Invalid choice.\n"; enterbutton();
        }
    } while(choice != 6);
    return 0;
}

void enterbutton() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void showMenuOptions() {
    cout << "\nTrip Planning System:\n";
    cout << "1. Add Trip\n";
    cout << "2. Display Trips\n";
    cout << "3. Save Trips to File\n";
    cout << "4. Search Trip\n";
    cout << "5. Delete Trip\n";
    cout << "6. Exit\n";
}

int getUserChoice() {
    int ch;
    cout << "Enter your choice: ";
    cin >> ch;
    return ch;
}

string inputDestination() {
    string dest;
    cout << "Enter destination: ";
    cin.ignore();
    getline(cin, dest);
    return dest;
}

int inputDays() {
    int d;
    cout << "Enter number of days: ";
    cin >> d;
    return d;
}

double inputBudget() {
    double b;
    cout << "Enter budget per day: ";
    cin >> b;
    return b;
}

string inputStartDate() {
    string date;
    cout << "Enter start date (DD/MM/YYYY): ";
    cin.ignore();
    getline(cin, date);
    return date;
}

bool checkStorageFull() {
    if(tripCount >= MAX_TRIPS) {
        cout << "Cannot add more trips. Storage full.\n";
        enterbutton();
        return true;
    }
    return false;
}

void addTripToArray(Trip t) {
    trips[tripCount++] = t;
}

double calculateTripBudget(Trip t) {
    return t.days * t.budget;
}

void printTotalBudget(double total) {
    cout << "Estimated total budget: $" << total << endl;
}

void displayPackingList(Trip t) {
    int type;
    cout << "\nSelect trip type:\n";
    cout << "1. Mountain\n";
    cout << "2. Beach\n";
    cout << "3. City / Land\n";
    cout << "Enter option: ";
    cin >> type;
    
    cout << "\nPacking List for " << t.destination << ":\n";
    cout << "- Clothes for " << t.days << " days\n";
    cout << "- Travel documents\n";
    cout << "- Toiletries\n";
    cout << "- Money & cards\n";
    
    if(type == 1) {
        cout << "\nMountain Recommendations:\n";
        cout << "- Temperature: 0°C to 15°C\n";
        cout << "- Warm jackets & sweaters\n";
        cout << "- Gloves\n";
        cout << "- Hiking shoes\n";
    }
    else if(type == 2) {
        cout << "\nBeach Recommendations:\n";
        cout << "- Temperature: 25°C to 35°C\n";
        cout << "- Cotton clothes\n";
        cout << "- Sunglasses\n";
        cout << "- Sunscreen\n";
        cout << "- Swimwear\n";
    }
    else if(type == 3) {
        cout << "\nCity / Land Recommendations:\n";
        cout << "- Temperature: 15°C to 30°C\n";
        cout << "- Comfortable clothes\n";
        cout << "- Walking shoes\n";
        cout << "- Power bank\n";
    }
    else {
        cout << "\nInvalid selection.\n";
    }
}

void addTrip() {
    if(checkStorageFull()) return;
    
    Trip t;
    t.destination = inputDestination();
    t.days = inputDays();
    t.budget = inputBudget();
    t.startDate = inputStartDate();
    
    displayPackingList(t);
    double total = calculateTripBudget(t);
    printTotalBudget(total);
    
    addTripToArray(t);
    cout << "Trip added successfully!\n";
    enterbutton();
}

void displayTrips() {
    if(tripCount == 0) {
        displayNoTripsMessage();
        return;
    }
    
    displayTripHeader();
    for(int i = 0; i < tripCount; i++) {
        displaySingleTrip(i);
    }
    enterbutton();
}

void displayTripHeader() {
    cout << "\nAll Trips:\n";
}

void displaySingleTrip(int i) {
    double total = calculateTripBudget(trips[i]);
    cout << "\nTrip " << (i+1) << ":\n";
    cout << "Destination: " << trips[i].destination << endl;
    cout << "Days: " << trips[i].days << endl;
    cout << "Budget/day: $" << trips[i].budget << endl;
    cout << "Total Budget: $" << total << endl;
    cout << "Start Date: " << trips[i].startDate << endl;
}

void displayNoTripsMessage() {
    cout << "No trips available.\n";
    enterbutton();
}

void saveTripsToFile() {
    ofstream out("trips.txt");
    if(!out) {
        cout << "Error saving file.\n";
        enterbutton();
        return;
    }
    
    out << tripCount << endl;
    for(int i = 0; i < tripCount; i++) {
        out << trips[i].destination << endl;
        out << trips[i].days << endl;
        out << trips[i].budget << endl;
        out << trips[i].startDate << endl;
    }
    
    out.close();
    cout << "Trips saved.\n";
    enterbutton();
}

void loadTripsFromFile() {
    ifstream in("trips.txt");
    if(!in) return;
    
    in >> tripCount;
    in.ignore();
    
    for(int i = 0; i < tripCount; i++) {
        getline(in, trips[i].destination);
        in >> trips[i].days;
        in >> trips[i].budget;
        in.ignore();
        getline(in, trips[i].startDate);
    }
    
    in.close();
}

void exitMessage() {
    cout << "Exiting Trip Planning System. Goodbye!\n";
}

void searchTrip() {
    if(tripCount == 0) {
        cout << "No trips available.\n";
        enterbutton();
        return;
    }
    
    string key;
    cout << "Enter destination to search: ";
    cin.ignore();
    getline(cin, key);
    
    bool found = false;
    for(int i = 0; i < tripCount; i++) {
        if(trips[i].destination == key) {
            found = true;
            double total = calculateTripBudget(trips[i]);
            cout << "\nTrip Found:\n";
            cout << "Destination: " << trips[i].destination << endl;
            cout << "Days: " << trips[i].days << endl;
            cout << "Budget/day: $" << trips[i].budget << endl;
            cout << "Total Budget: $" << total << endl;
            cout << "Start Date: " << trips[i].startDate << endl;
        }
    }
    
    if(!found) {
        cout << "No trip found for destination: " << key << endl;
    }
    enterbutton();
}

void deleteTrip() {
    if(tripCount == 0) {
        cout << "No trips available to delete.\n";
        enterbutton();
        return;
    }
    
    string key;
    cout << "Enter destination to delete: ";
    cin.ignore();
    getline(cin, key);
    
    bool deleted = false;
    for(int i = 0; i < tripCount; i++) {
        if(trips[i].destination == key) {
            for(int j = i; j < tripCount - 1; j++) {
                trips[j] = trips[j + 1];
            }
            tripCount--;
            deleted = true;
            cout << "Trip deleted successfully.\n";
            break;
        }
    }
    
    if(!deleted) {
        cout << "No trip found for destination: " << key << endl;
    }
    enterbutton();
}

