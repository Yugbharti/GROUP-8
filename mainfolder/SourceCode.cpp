#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>
//docker run -it hospital-management-system
using namespace std;

class Patient {
public:
    string name;
    int patientID;
    string diagnosis;
    int age;
    string feedback;

    /**
     * Constructor to initialize a Patient with basic details.
     * @param n Patient's name.
     * @param id Patient's ID.
     * @param a Patient's age.
     */
    Patient(string n, int id, int a) : name(n), patientID(id), age(a) {}

    /**
     * Sets the diagnosis for the patient.
     * @param diag Diagnosis string.
     */
    void setDiagnosis(const string& diag) {
        diagnosis = diag;
    }
};

class Doctor {
public:
    string name;
    string specialty;
    int doctorID;
    vector<int> patientIDs;

    /**
     * Constructor to initialize a Doctor with basic details.
     * @param n Doctor's name.
     * @param s Doctor's specialty.
     * @param id Doctor's ID.
     */
    Doctor(string n, string s, int id) : name(n), specialty(s), doctorID(id) {}

    /**
     * Adds a patient ID to the doctor's list of assigned patients.
     * @param patientID ID of the patient to add.
     */
    void addPatient(int patientID) {
        patientIDs.push_back(patientID);
    }
};

class Hospital {
public:
    vector<Patient> patients;
    vector<Doctor> doctors;

    /**
     * Adds a new patient to the hospital if the patient ID is unique.
     * @param name Patient's name.
     * @param patientID Patient's ID.
     * @param age Patient's age.
     */
    void addPatient(const string& name, int patientID, int age) {
        for (const auto& patient : patients) {
            if (patient.patientID == patientID) {
                cout << "Patient with ID " << patientID << " already exists." << endl;
                return;
            }
        }
        patients.emplace_back(name, patientID, age);
        cout << "Patient added successfully." << endl;
    }

    /**
     * Adds a new doctor to the hospital if the doctor ID is unique.
     * @param name Doctor's name.
     * @param specialty Doctor's specialty.
     * @param doctorID Doctor's ID.
     */
    void addDoctor(const string& name, const string& specialty, int doctorID) {
        for (const auto& doctor : doctors) {
            if (doctor.doctorID == doctorID) {
                cout << "Doctor with ID " << doctorID << " already exists." << endl;
                return;
            }
        }
        doctors.emplace_back(name, specialty, doctorID);
        cout << "Doctor added successfully." << endl;
    }

    /**
     * Assigns a patient to a doctor if both IDs are valid.
     * @param patientID Patient's ID.
     * @param doctorID Doctor's ID.
     */
    void assignPatientToDoctor(int patientID, int doctorID) {
        auto patientIt = find_if(patients.begin(), patients.end(), [&](const Patient& p) { return p.patientID == patientID; });
        auto doctorIt = find_if(doctors.begin(), doctors.end(), [&](const Doctor& d) { return d.doctorID == doctorID; });

        if (patientIt != patients.end() && doctorIt != doctors.end()) {
            doctorIt->addPatient(patientID);
            cout << "Patient assigned to doctor successfully." << endl;
        } else {
            cout << "Doctor or Patient not found." << endl;
        }
    }

    /**
     * Displays details of a specific patient by patient ID.
     * @param patientID ID of the patient to display.
     */
    void displayPatient(int patientID) const {
        for (const auto& patient : patients) {
            if (patient.patientID == patientID) {
                cout << "Name: " << patient.name << endl;
                cout << "ID: " << patient.patientID << endl;
                cout << "Age: " << patient.age << endl;
                cout << "Diagnosis: " << patient.diagnosis << endl;
                cout << "Feedback: " << patient.feedback << endl;
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    /**
     * Displays details of all patients.
     */
    void displayAllPatients() const {
        if (patients.empty()) {
            cout << "No patients found." << endl;
            return;
        }
        for (const auto& patient : patients) {
            displayPatient(patient.patientID);
            cout << "-------------------------" << endl;
        }
    }

    /**
     * Updates the diagnosis for a specific patient.
     * @param patientID ID of the patient.
     * @param diagnosis Diagnosis string to update.
     */
    void markDiagnosis(int patientID, const string& diagnosis) {
        for (auto& patient : patients) {
            if (patient.patientID == patientID) {
                patient.setDiagnosis(diagnosis);
                cout << "Diagnosis updated successfully." << endl;
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    /**
     * Records feedback for a specific patient.
     * @param patientID ID of the patient.
     * @param feedback Feedback string.
     */
    void collectFeedback(int patientID, const string& feedback) {
        for (auto& patient : patients) {
            if (patient.patientID == patientID) {
                patient.feedback = feedback;
                cout << "Feedback recorded successfully." << endl;
                return;
            }
        }
        cout << "Patient not found." << endl;
    }

    /**
     * Saves patient data to a file.
     * @param filename Name of the file to save data.
     */
    void saveToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "File could not be opened." << endl;
            return;
        }
        for (const auto& patient : patients) {
            outFile << patient.patientID << " " << patient.name << " " << patient.age << " " << patient.diagnosis << " " << patient.feedback << endl;
        }
        outFile.close();
        cout << "Data saved to " << filename << " successfully." << endl;
    }

    /**
     * Loads patient data from a file.
     * @param filename Name of the file to load data from.
     */
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "File could not be opened." << endl;
            return;
        }
        patients.clear();
        int id, age;
        string name, diagnosis, feedback;
        while (inFile >> id >> ws && getline(inFile, name, ' ')) {
            inFile >> age >> ws;
            getline(inFile, diagnosis, ' ');
            getline(inFile, feedback);
            Patient patient(name, id, age);
            patient.setDiagnosis(diagnosis);
            patient.feedback = feedback;
            patients.push_back(patient);
        }
        inFile.close();
        cout << "Data loaded from " << filename << " successfully." << endl;
    }
};

class System {
public:
    map<string, string> credentials;
    Hospital hospital;

    /**
     * Adds new user credentials to the system.
     */
    void addCredentials() {
        string username, password;
        cout << "Enter new username: ";
        cin >> username;
        if (credentials.find(username) != credentials.end()) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }
        cout << "Enter password: ";
        cin >> password;
        credentials[username] = password;
        cout << "Credentials added successfully!" << endl;
    }

    /**
     * Allows the user to change their password.
     */
    void changePassword() {
        string username, oldPassword, newPassword;
        cout << "Enter username: ";
        cin >> username;
        if (credentials.find(username) != credentials.end()) {
            cout << "Enter old password: ";
            cin >> oldPassword;
            if (credentials[username] == oldPassword) {
                cout << "Enter new password: ";
                cin >> newPassword;
                credentials[username] = newPassword;
                cout << "Password updated successfully!" << endl;
            } else {
                cout << "Incorrect old password. Password not updated." << endl;
            }
        } else {
            cout << "Username not found. Cannot update password." << endl;
        }
    }

    /**
     * Allows the user to log in by verifying credentials.
     */
    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        if (credentials.find(username) != credentials.end() && credentials[username] == password) {
            cout << "Login successful!" << endl;
        } else {
            cout << "Invalid credentials. Exiting..." << endl;
            exit(0);
        }
    }

    /**
     * Displays the main menu of the hospital management system.
     */
    void menu() {
        cout << "\n=== Hospital Management System ===" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Add Doctor" << endl;
        cout << "3. Assign Patient to Doctor" << endl;
        cout << "4. Display Patient" << endl;
        cout << "5. Display All Patients" << endl;
        cout << "6. Update Diagnosis" << endl;
        cout << "7. Collect Feedback" << endl;
        cout << "8. Save Data" << endl;
        cout << "9. Load Data" << endl;
        cout << "10. Change Password" << endl;
        cout << "11. Exit" << endl;
    }

    /**
     * Main loop to run the system and interact with the user.
     */
    void run() {
        if (credentials.empty()) {
            char choice;
            cout << "No user found. Would you like to add a new user? (Y/N): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                addCredentials();
            }
        }
        login();

        while (true) {
            menu();
            int choice;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string name;
                    int id, age;
                    cout << "Enter patient name: ";
                    cin >> name;
                    cout << "Enter patient ID: ";
                    cin >> id;
                    cout << "Enter age: ";
                    cin >> age;
                    hospital.addPatient(name, id, age);
                    break;
                }
                case 2: {
                    string name, specialty;
                    int id;
                    cout << "Enter doctor name: ";
                    cin >> name;
                    cout << "Enter specialty: ";
                    cin >> specialty;
                    cout << "Enter doctor ID: ";
                    cin >> id;
                    hospital.addDoctor(name, specialty, id);
                    break;
                }
                case 3: {
                    int patientID, doctorID;
                    cout << "Enter patient ID: ";
                    cin >> patientID;
                    cout << "Enter doctor ID: ";
                    cin >> doctorID;
                    hospital.assignPatientToDoctor(patientID, doctorID);
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter patient ID: ";
                    cin >> id;
                    hospital.displayPatient(id);
                    break;
                }
                case 5:
                    hospital.displayAllPatients();
                    break;
                case 6: {
                    int id;
                    string diagnosis;
                    cout << "Enter patient ID: ";
                    cin >> id;
                    cout << "Enter diagnosis: ";
                    cin >> diagnosis;
                    hospital.markDiagnosis(id, diagnosis);
                    break;
                }
                case 7: {
                    int id;
                    string feedback;
                    cout << "Enter patient ID: ";
                    cin >> id;
                    cout << "Enter feedback: ";
                    cin >> feedback;
                    hospital.collectFeedback(id, feedback);
                    break;
                }
                case 8: {
                    string filename;
                    cout << "Enter filename: ";
                    cin >> filename;
                    hospital.saveToFile(filename);
                    break;
                }
                case 9: {
                    string filename;
                    cout << "Enter filename: ";
                    cin >> filename;
                    hospital.loadFromFile(filename);
                    break;
                }
                case 10:
                    changePassword();
                    break;
                case 11:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    System system;
    system.run();
    return 0;
}
