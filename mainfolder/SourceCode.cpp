#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Authentication system
/**
 * @brief Prompts the user for a username and password, and authenticates the user.
 * @return true if the credentials are correct, otherwise false.
 */
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

// Enhanced Patient Class
/**
 * @class Patient
 * @brief Represents a patient with attributes like name, age, and disease.
 */
class Patient {
public:
    string name;
    int age;
    string disease;

    // Default constructor
    Patient() {}

    // Parameterized constructor
    /**
     * @brief Constructs a patient with given name, age, and disease.
     * @param n The patient's name.
     * @param a The patient's age.
     * @param d The disease the patient has.
     */
    Patient(string n, int a, string d) : name(n), age(a), disease(d) {}

    /**
     * @brief Saves patient information to a file.
     */
    void saveToFile() const {
        ofstream file("patients.txt", ios::app);
        if (file) {
            file << name << " " << age << " " << disease << "\n";
        }
        file.close();
    }

    /**
     * @brief Displays patient information.
     */
    void displayInfo() const {
        cout << "Name: " << name << "\nAge: " << age << "\nDisease: " << disease << "\n\n";
    }

    /**
     * @brief Reads patient data from the file and returns a vector of patients.
     * @return A vector of patients.
     */
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

/**
 * @brief Manages patient-related tasks like adding new patients and viewing all patients.
 */
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
/**
 * @class Doctor
 * @brief Represents a doctor with attributes like name and specialization.
 */
class Doctor {
public:
    string name;
    string specialization;

    Doctor() {}

    // Parameterized constructor
    /**
     * @brief Constructs a doctor with given name and specialization.
     * @param n The doctor's name.
     * @param s The doctor's specialization.
     */
    Doctor(string n, string s) : name(n), specialization(s) {}

    /**
     * @brief Saves doctor information to a file.
     */
    void saveToFile() const {
        ofstream file("doctors.txt", ios::app);
        file << name << " " << specialization << "\n";
        file.close();
    }

    /**
     * @brief Reads doctor data from the file and returns a vector of doctors.
     * @return A vector of doctors.
     */
    static vector<Doctor> readFromFile() {
        vector<Doctor> doctors;
        ifstream file("doctors.txt");
        if (!file) {
            cout << "Error opening file 'doctors.txt'. Please ensure the file exists.\n";
            return doctors;
        }

        string name, specialization;
        while (file >> name >> specialization) {
            doctors.emplace_back(name, specialization);
        }

        if (doctors.empty()) {
            cout << "No doctors found in the file.\n";
        }

        file.close();
        return doctors;
    }

    /**
     * @brief Displays doctor information.
     */
    void displayInfo() const {
        cout << "Doctor Name: " << name << "\nSpecialization: " << specialization << "\n\n";
    }
};

/**
 * @brief Manages doctor-related tasks like adding new doctors and viewing all doctors.
 */
void doctorManagement() {
    int choice;
    cout << "1. Add new doctor\n2. View all doctors\nEnter choice: ";
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
    } else if (choice == 2) {
        cout << "\n--- List of Doctors ---\n";
        vector<Doctor> doctors = Doctor::readFromFile();
        for (const auto& d : doctors) {
            d.displayInfo();
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Class for Appointment Scheduling
/**
 * @class Appointment
 * @brief Represents an appointment with attributes like patient name, doctor name, and date.
 */
class Appointment {
public:
    string patientName;
    string doctorName;
    string date;

    Appointment() {}

    // Parameterized constructor
    /**
     * @brief Constructs an appointment with given patient name, doctor name, and date.
     * @param pName The patient's name.
     * @param dName The doctor's name.
     * @param d The appointment date.
     */
    Appointment(string pName, string dName, string d) : patientName(pName), doctorName(dName), date(d) {}

    /**
     * @brief Saves appointment information to a file.
     */
    void saveToFile() const {
        ofstream file("appointments.txt", ios::app);
        if (file) {
            file << patientName << " " << doctorName << " " << date << "\n";
        }
        file.close();
    }

    /**
     * @brief Reads appointment data from the file and returns a vector of appointments.
     * @return A vector of appointments.
     */
    static vector<Appointment> readFromFile() {
        vector<Appointment> appointments;
        ifstream file("appointments.txt");
        if (!file) {
            cout << "Error opening file 'appointments.txt'. Please ensure the file exists.\n";
            return appointments;
        }

        string patientName, doctorName, date;
        while (file >> patientName >> doctorName >> date) {
            appointments.emplace_back(patientName, doctorName, date);
        }

        if (appointments.empty()) {
            cout << "No appointments found in the file.\n";
        }

        file.close();
        return appointments;
    }

    /**
     * @brief Displays appointment information.
     */
    void displayInfo() const {
        cout << "Patient Name: " << patientName << "\nDoctor Name: " << doctorName << "\nAppointment Date: " << date << "\n\n";
    }
};

/**
 * @brief Manages appointment-related tasks like scheduling new appointments and viewing all appointments.
 */
void appointmentScheduling() {
    int choice;
    cout << "1. Schedule new appointment\n2. View all appointments\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
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
    } else if (choice == 2) {
        cout << "\n--- List of Appointments ---\n";
        vector<Appointment> appointments = Appointment::readFromFile();
        for (const auto& app : appointments) {
            app.displayInfo();
        }
    } else {
        cout << "Invalid choice!\n";
    }
}

// Class for Billing System
/**
 * @class Billing
 * @brief Represents billing information with attributes like patient name and amount.
 */
class Billing {
public:
    string patientName;
    double amount;

    Billing() {}

    Billing(string pName, double amt) : patientName(pName), amount(amt) {}

    // Function to save bill to file
    void saveToFile() const {
        ofstream file("billing.txt", ios::app);
        if (file) {
            file << patientName << " " << amount << "\n";
        }
        file.close();
    }

    // Static function to read bills from file
    static vector<Billing> readFromFile() {
        vector<Billing> bills;
        ifstream file("billing.txt");
        if (!file) {
            cout << "Error opening file 'billing.txt'. Please ensure the file exists.\n";
            return bills;
        }

        string patientName;
        double amount;
        while (file >> patientName >> amount) {
            bills.emplace_back(patientName, amount);
        }

        if (bills.empty()) {
            cout << "No billing records found in the file.\n";
        }

        file.close();
        return bills;
    }

    // Function to display bill information
    void displayInfo() const {
        cout << "Patient Name: " << patientName << "\nBilling Amount: $" << amount << "\n\n";
    }
};

// Function to handle billing (Add/View)
void billingSystem() {
    int choice;
    cout << "1. Add new billing record\n2. View all billing records\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        string patientName;
        double amount;
        cout << "Enter patient name: ";
        cin >> patientName;
        cout << "Enter billing amount: ";
        cin >> amount;

        Billing bill(patientName, amount);
        bill.saveToFile();
        cout << "Billing record added successfully!\n";
    } else if (choice == 2) {
        cout << "\n--- List of Billing Records ---\n";
        vector<Billing> bills = Billing::readFromFile();
        for (const auto& bill : bills) {
            bill.displayInfo();
        }
    } else {
        cout << "Invalid choice!\n";
    }
}
/**
 * @brief Main function to manage the hospital system.
 * 
 * This function handles the hospital management system by providing options 
 * for patient management, doctor management, appointment scheduling, 
 * and the billing system. It first authenticates the user, and if successful,
 * allows access to the respective modules. The user can choose between 
 * different options in a loop and exit the system when done.
 * 
 * @return 0 if authentication fails or after exiting the system.
 */
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
                /**
                 * @brief Calls the patientManagement function for adding/viewing patients.
                 */
                patientManagement();
                break;
            case 2:
                /**
                 * @brief Calls the doctorManagement function for adding/viewing doctors.
                 */
                doctorManagement();
                break;
            case 3:
                /**
                 * @brief Calls the appointmentScheduling function for scheduling/viewing appointments.
                 */
                appointmentScheduling();
                break;
            case 4:
                /**
                 * @brief Calls the billingSystem function for adding/viewing billing records.
                 */
                billingSystem();
                break;
            case 5:
                /**
                 * @brief Exits the system.
                 */
                cout << "Exiting the system...\n";
                break;
            default:
                /**
                 * @brief Displays an error message for invalid choices.
                 */
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
