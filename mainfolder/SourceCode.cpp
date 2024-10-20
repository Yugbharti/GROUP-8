#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Function to authenticate the user
// @return true if authentication is successful; otherwise false
bool authenticate() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == "admin" && password == "admin123") {
        return true;
    } else {
        cout << "Invalid credentials!\n";
        return false;
    }
}

// Enhanced Patient Class to manage patient details
class Patient {
public:
    string name;        // Patient's name
    int age;           // Patient's age
    string disease;    // Patient's disease

    // Default constructor
    Patient() {}

    // Parameterized constructor to initialize a Patient object
    // @param n Name of the patient
    // @param a Age of the patient
    // @param d Disease of the patient
    Patient(string n, int a, string d) : name(n), age(a), disease(d) {}

    // Function to save patient information to a file
    void saveToFile() const {
        ofstream file("patients.txt", ios::app);
        if (file) {
            file << name << " " << age << " " << disease << "\n";
        }
        file.close();
    }

    // Function to display patient information
    void displayInfo() const {
        cout << "Name: " << name << "\nAge: " << age << "\nDisease: " << disease << "\n\n";
    }

    // Static function to read patients from a file
    // @return A vector of Patient objects read from the file
    static vector<Patient> readFromFile() {
        vector<Patient> patients;
        ifstream file("patients.txt");
        if (!file) {
            cout << "Error opening file 'patients.txt'. Please ensure the file exists and you have permission to read it.\n";
            return patients;
        }

        string name, disease;
        int age;
        while (file >> name >> age >> disease) {
            patients.emplace_back(name, age, disease);
        }

        if (patients.empty()) {
            cout << "No patients found in the file.\n";
        }

        file.close();
        return patients;
    }
};

// Function to manage patients (add/view)
// Prompts the user to either add a new patient or view all patients
void patientManagement() {
    int choice;
    cout << "1. Add new patient\n2. View all patients\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        string name, disease;
        int age;
        cout << "Enter patient name: ";
        cin >> name;
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter disease: ";
        cin >> disease;

        Patient p(name, age, disease);
        p.saveToFile();
        cout << "Patient added successfully!\n";
    } else if (choice == 2) {
        cout << "\n--- List of Patients ---\n";
        vector<Patient> patients = Patient::readFromFile();
        for (const auto& p : patients) {
            p.displayInfo();
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Class for Doctor Management
class Doctor {
public:
    string name;            // Doctor's name
    string specialization;  // Doctor's specialization

    // Default constructor
    Doctor() {}

    // Parameterized constructor to initialize a Doctor object
    // @param n Name of the doctor
    // @param s Specialization of the doctor
    Doctor(string n, string s) : name(n), specialization(s) {}

    // Function to save doctor information to a file
    void saveToFile() {
        ofstream file("doctors.txt", ios::app);
        file << name << " " << specialization << "\n";
        file.close();
    }
};

// Function to manage doctors (Add only)
// Allows the user to add a new doctor to the system
void doctorManagement() {
    int choice;
    cout << "1. Add new doctor\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        string name, specialization;
        cout << "Enter doctor name: ";
        cin >> name;
        cout << "Enter specialization: ";
        cin >> specialization;

        Doctor d(name, specialization);
        d.saveToFile();
        cout << "Doctor added successfully!\n";
    } else {
        cout << "Invalid choice!\n";
    }
}

// Class for Appointment Scheduling
class Appointment {
public:
    string patientName;  // Name of the patient
    string doctorName;   // Name of the doctor
    string date;         // Appointment date

    // Default constructor
    Appointment() {}

    // Parameterized constructor to initialize an Appointment object
    // @param pName Name of the patient
    // @param dName Name of the doctor
    // @param d Date of the appointment
    Appointment(string pName, string dName, string d) : patientName(pName), doctorName(dName), date(d) {}

    // Function to save appointment information to a file
    void saveToFile() {
        ofstream file("appointments.txt", ios::app);
        file << patientName << " " << doctorName << " " << date << "\n";
        file.close();
    }
};

// Function to schedule appointments
// Prompts the user for appointment details and saves them
void appointmentScheduling() {
    string patientName, doctorName, date;
    cout << "Enter patient name: ";
    cin >> patientName;
    cout << "Enter doctor name: ";
    cin >> doctorName;
    cout << "Enter appointment date (DD/MM/YYYY): ";
    cin >> date;

    Appointment app(patientName, doctorName, date);
    app.saveToFile();
    cout << "Appointment scheduled successfully!\n";
}

// Class for Billing System
class Billing {
public:
    string patientName;  // Name of the patient
    double amount;       // Billing amount

    // Default constructor
    Billing() {}

    // Parameterized constructor to initialize a Billing object
    // @param pName Name of the patient
    // @param amt Amount to be billed
    Billing(string pName, double amt) : patientName(pName), amount(amt) {}

    // Function to save billing information to a file
    void saveToFile() {
        ofstream file("billing.txt", ios::app);
        file << patientName << " " << amount << "\n";
        file.close();
    }
};

// Function to handle billing
// Prompts the user for billing details and saves them
void billingSystem() {
    string patientName;
    double amount;
    cout << "Enter patient name: ";
    cin >> patientName;
    cout << "Enter billing amount: ";
    cin >> amount;

    Billing bill(patientName, amount);
    bill.saveToFile();
    cout << "Billing processed successfully!\n";
}

// Main function
// The entry point of the program
int main() {
    if (!authenticate()) {
        return 0; // Exit if authentication fails
    }

    int choice;
    do {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Patient Management\n2. Doctor Management\n3. Appointment Scheduling\n4. Billing System\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                patientManagement(); // Manage patients
                break;
            case 2:
                doctorManagement();  // Manage doctors
                break;
            case 3:
                appointmentScheduling(); // Schedule appointments
                break;
            case 4:
                billingSystem(); // Handle billing
                break;
            case 5:
                cout << "Exiting the system...\n"; // Exit the program
                break;
            default:
                cout << "Invalid choice!\n"; // Handle invalid input
        }
    } while (choice != 5);

    return 0; // End of the program
}
