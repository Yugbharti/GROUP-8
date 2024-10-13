#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
class User {
public:
    string username;
    string password;
    string role;

    User(string uname, string pwd, string urole) : username(uname), password(pwd), role(urole) {}

    bool authenticate(string uname, string pwd) {
        return (uname == username && pwd == password);
    }
};


class Patient {
public:
    int id;
    string name;
    string medicalHistory;
    vector<string> appointmentHistory;

    Patient(int pid, string pname) : id(pid), name(pname) {}

    void addAppointment(string appointment) {
        appointmentHistory.push_back(appointment);
    }

    void showDetails() {
        cout << "Patient ID: " << id << "\nName: " << name << "\nMedical History: " << medicalHistory << endl;
        cout << "Appointments: ";
        for (const string& app : appointmentHistory) {
            cout << app << ", ";
        }
        cout << endl;
    }
};

class Doctor {
public:
    int id;
    string name;
    string specialization;

    Doctor(int did, string dname, string dspecialization) : id(did), name(dname), specialization(dspecialization) {}

    void showDetails() {
        cout << "Doctor ID: " << id << "\nName: " << name << "\nSpecialization: " << specialization << endl;
    }
};

class Appointment {
public:
    int id;
    int patientId;
    int doctorId;
    string date;
    string time;

    Appointment(int aid, int pid, int did, string adate, string atime)
        : id(aid), patientId(pid), doctorId(did), date(adate), time(atime) {}

    void showDetails() {
        cout << "Appointment ID: " << id << "\nPatient ID: " << patientId
             << "\nDoctor ID: " << doctorId << "\nDate: " << date << "\nTime: " << time << endl;
    }
};

class Billing {
public:
    int patientId;
    double amount;
    bool paid;

    Billing(int pid, double amt) : patientId(pid), amount(amt), paid(false) {}

    void makePayment() {
        paid = true;
        cout << "Payment of $" << amount << " for Patient ID: " << patientId << " is successful.\n";
    }

    void showBilling() {
        cout << "Patient ID: " << patientId << "\nAmount Due: $" << amount
             << "\nPayment Status: " << (paid ? "Paid" : "Unpaid") << endl;
    }
};

class FileHandler {
public:
    map<int, string> medicalRecords;

    void uploadFile(int patientId, string record) {
        medicalRecords[patientId] = record;
        cout << "Medical record uploaded for Patient ID: " << patientId << endl;
    }

    void showFile(int patientId) {
        if (medicalRecords.find(patientId) != medicalRecords.end()) {
            cout << "Medical record for Patient ID: " << patientId << ": " << medicalRecords[patientId] << endl;
        } else {
            cout << "No record found for Patient ID: " << patientId << endl;
        }
    }
};

class HospitalManagementSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    vector<User> users;
    vector<Billing> bills;
    FileHandler fileHandler;
public:
    bool login(string username, string password) {
        for (const User& user : users) {
            if (user.authenticate(username, password)) {
                cout << "Login successful as " << user.role << endl;
                return true;
            }
        }
        cout << "Login failed!" << endl;
        return false;
    }

    void addPatient(int id, string name) {
        patients.push_back(Patient(id, name));
    }

    void addDoctor(int id, string name, string specialization) {
        doctors.push_back(Doctor(id, name, specialization));
    }

    void scheduleAppointment(int id, int patientId, int doctorId, string date, string time) {
        appointments.push_back(Appointment(id, patientId, doctorId, date, time));
        for (Patient& p : patients) {
            if (p.id == patientId) {
                p.addAppointment("Appointment with Doctor ID " + to_string(doctorId) + " on " + date);
            }
        }
    }

    void generateBill(int patientId, double amount) {
        bills.push_back(Billing(patientId, amount));
    }

    void makePayment(int patientId) {
        for (Billing& b : bills) {
            if (b.patientId == patientId) {
                b.makePayment();
                return;
            }
        }
        cout << "No bill found for Patient ID: " << patientId << endl;
    }

    void uploadMedicalRecord(int patientId, string record) {
        fileHandler.uploadFile(patientId, record);
    }

    void showMedicalRecord(int patientId) {
        fileHandler.showFile(patientId);
    }

    void showPatientDetails(int patientId) {
        for (const Patient& p : patients) {
            if (p.id == patientId) {
                p.showDetails();
                return;
            }
        }
        cout << "No patient found with ID " << patientId << endl;
    }

    void showDoctorDetails(int doctorId) {
        for (const Doctor& d : doctors) {
            if (d.id == doctorId) {
                d.showDetails();
                return;
            }
        }
        cout << "No doctor found with ID " << doctorId << endl;
    }

    HospitalManagementSystem() {
        users.push_back(User("admin", "admin123", "Admin"));
        users.push_back(User("doctor1", "doctor123", "Doctor"));
        users.push_back(User("patient1", "patient123", "Patient"));
    }
};

int main() {
    HospitalManagementSystem hms;

    hms.login("admin", "admin123");

    hms.addPatient(1, "John Doe");
    hms.addDoctor(101, "Dr. Smith", "Cardiology");

    hms.scheduleAppointment(1, 1, 101, "2024-10-15", "10:00 AM");

    hms.generateBill(1, 150.0);

    hms.makePayment(1);

    hms.uploadMedicalRecord(1, "Blood test report");
    hms.showMedicalRecord(1);

    hms.showPatientDetails(1);
    hms.showDoctorDetails(101);

    return 0;
}
