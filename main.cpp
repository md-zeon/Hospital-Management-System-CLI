#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // i used it for Sleep() and system("cls") function
using namespace std;

bool login() {
    string user, pass;
    int attempts = 3;
    while (attempts--) {
        system("cls"); // Clears Screen of the terminal
        cout << "========================================" << endl;
        cout << "       HOSPITAL MANAGEMENT SYSTEM       " << endl;
        cout << "========================================" << endl << endl;
        cout << " LOGIN " << endl;
        cout << "----------------------------------------" << endl;
        cout << "Enter Username: ";
        getline(cin, user); // to take multiple words
        cout << "Enter Password: ";
        getline(cin, pass);
        if (user == "admin" && pass == "Admin@1234") {
            cout << "\nPlease Wait";
            for(int i = 1; i <= 3; i++) {
                cout << ".";
                Sleep(600); // Pause for 600 milliseconds
            }
            cout << "\nLogin Successful! Redirecting to Dashboard." << endl;
            Sleep(700); // Pause for 700 milliseconds 0.7s
            return true;
        }
        cout << "\n----------------------------------------" << endl;
        cout << "Invalid credentials! Try again. (" << attempts << " attempts left)\n";
        cout << "----------------------------------------" << endl;

        if (attempts == 0) {
            cout << "Your Account Has Been Locked Because Of Too Many Attempts." << endl;
            cout << "[Please Contact The Administration If You Have Forgot Your Password Or Think This Is An Error]" << endl << endl;
            Sleep(700); // Pause for 700 milliseconds
        }
        Sleep(2000); // Pause for 2000 milliseconds
    }
    return false;
}

class Patient {
    // Here I declared All variables I need for the Patient Class
    string patientId, name, gender, bloodGroup, address, contact, emergencyContact, disease, doctorAssigned;
    int age;
public:
    // Setter and Getter Functions I hope you reviewed it
    void setId(string id) {
        patientId = id; 
    }
    string getId() {
        return patientId;
    }
    void setName(string name) {
        this->name = name;
    }
    string getName() {
        return name;
    }
    void setAge(int age) {
        this->age = age;
    }
    int getAge() {
        return age;
    }
    void setGender(string gender) {
        this->gender = gender;
    }
    string getGender() {
        return gender;
    }
    void setBloodGroup(string bloodGroup) {
        this->bloodGroup = bloodGroup;
    }
    string getBloodGroup() {
        return bloodGroup;
    }
    void setAddress(string address) {
        this->address = address;
    }
    string getAddress() {
        return address;
    }
    void setContact(string contact) {
        this->contact = contact;
    }
    string getContact() {
        return contact;
    }
    void setEmergencyContact(string emergencyContact) {
        this->emergencyContact = emergencyContact;
    }
    string getEmergencyContact() {
        return emergencyContact;
    }
    void setDisease(string disease) {
        this->disease = disease;
    }
    string getDisease() {
        return disease;
    }
    void setDoctorAssigned(string doctorAssigned) {
        this->doctorAssigned = doctorAssigned;
    }
    string getDoctorAssigned() {
        return doctorAssigned;
    }
 
    // Here I made a Function for displaying Patient data
    void viewPatientDetails() {
        cout << "\n----------------------------------------" << endl;
        cout << "Patient ID: " << patientId << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Blood Group: " << bloodGroup << endl;
        cout << "Address: " << address << endl;
        cout << "Contact: " << contact << endl;
        cout << "Emergency Contact: " << emergencyContact << endl;
        cout << "Disease/Symptoms: " << disease << endl;
        cout << "Doctor Assigned: " << doctorAssigned << endl;
        cout << "----------------------------------------" << endl;
    }
};

void loader(string msg) {
    cout << msg;
    for(int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(600); // Pause for 600 milliseconds
    }
    cout << endl;
}

void pauseWithMessage(string msg) {
    cout << endl; 
    cout << msg;
    cin.ignore();
    getchar(); // for enter 
}

void validChoice(int &choice) { // 'f'
    if (choice > 0) {
        return;
    } else {
        cout << "Please Enter a Valid Number" << endl;
        cin.clear(); // to remove
        cin.ignore(); // \n
        choice = 100;
    }
}

void patientManagement(vector<Patient> &patients) {
    int choice;
    do {
        system("cls");
        cout << "========================================" << endl;
        cout << "          PATIENT MANAGEMENT            " << endl;
        cout << "========================================" << endl;
        cout << "1. Register New Patient" << endl;
        cout << "2. View Patient Details" << endl;
        cout << "3. Update Patient Info" << endl;
        cout << "4. Delete Patient Record" << endl;
        cout << "5. View All Patients Details" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        validChoice(choice);
        switch (choice) {
            case 1: {
                cout << "----------------------------------------" << endl;
                cout << "           REGISTER NEW PATIENT         " << endl;
                cout << "----------------------------------------" << endl;
                cout << "Enter Patient Details:" << endl << endl;
                Patient p;
                string id, name, gender, bloodGroup, address, contact, emergencyContact, disease, doctorAssigned;
                int age;
                cout << "Enter Patient ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Gender (M/F): ";
                cin >> gender;
                cout << "Enter Blood Group: ";
                cin >> bloodGroup;
                cout << "Enter Address: ";
                cin.ignore();
                getline(cin, address);
                cout << "Enter Contact: ";
                cin >> contact;
                cout << "Enter Emergency Contact: ";
                cin >> emergencyContact;
                cout << "Enter Disease/Symptoms: ";
                cin.ignore();
                getline(cin, disease);
                cout << "Enter Doctor Assigned: ";
                cin >> doctorAssigned;

                p.setId(id);
                p.setName(name);
                p.setAge(age);
                p.setGender(gender);
                p.setBloodGroup(bloodGroup);
                p.setAddress(address);
                p.setContact(contact);
                p.setEmergencyContact(emergencyContact);
                p.setDisease(disease);
                p.setDoctorAssigned(doctorAssigned);
                patients.push_back(p);
                loader("Registering Patient");
                cout << "Patient Registered Successfully!" << endl;
                pauseWithMessage("Press Enter to go back to the menu...");
                break;
            }
            case 2: {
                cout << "----------------------------------------" << endl;
                cout << "             PATIENT DETAILS            " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Patient ID: ";
                cin >> id;
                bool found = false;
                loader("Searching");
                for (Patient &p : patients) {
                    if (p.getId() == id) {
                        cout << "Patient Found" << endl;
                        p.viewPatientDetails();
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Patient ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 3: {
                cout << "----------------------------------------" << endl;
                cout << "           UPDATE PATIENT INFO          " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Patient ID: ";
                cin >> id;
                bool found = false;
                for (Patient &p : patients) {
                    if (p.getId() == id) {
                        string name, gender, bloodGroup, address, contact, emergencyContact, disease, doctorAssigned;
                        int age;
                        cout << "What do you want to update?" << endl;
                        cout << "1. Update Patient Name" << endl;
                        cout << "2. Update Patient Age" << endl;
                        cout << "3. Update Patient Gender" << endl;
                        cout << "4. Update Patient Blood Group" << endl;
                        cout << "5. Update Patient Address" << endl;
                        cout << "6. Update Patient Contact" << endl;
                        cout << "7. Update Patient Emergency Contact" << endl;
                        cout << "8. Update Patient Disease/Symptoms" << endl;
                        cout << "9. Update Patient Doctor Assigned" << endl;
                        int update;
                        cout << "Enter Your Choice: ";
                        cin >> update;
                        cin.ignore();
                        validChoice(update);
                        switch (update) {
                            case 1:
                                cout << "Enter New Name: ";
                                getline(cin, name);
                                p.setName(name);
                                break;

                            case 2:
                                cout << "Enter New Age: ";
                                cin >> age;
                                p.setAge(age);
                                break;

                            case 3:
                                cout << "Enter New Gender (M/F): ";
                                cin >> gender;
                                p.setGender(gender);
                                break;

                            case 4:
                                cout << "Enter New Blood Group: ";
                                cin >> bloodGroup;
                                p.setBloodGroup(bloodGroup);
                                break;

                            case 5:
                                cout << "Enter New Address: ";
                                getline(cin, address);
                                p.setAddress(address);
                                break;

                            case 6:
                                cout << "Enter New Contact: ";
                                cin >> contact;
                                p.setContact(contact);
                                break;

                            case 7:
                                cout << "Enter New Emergency Contact: ";
                                cin >> emergencyContact;
                                p.setEmergencyContact(emergencyContact);
                                break;
                            
                            case 8:
                                cout << "Enter New Disease/Symptoms: ";
                                getline(cin, disease);
                                p.setDisease(disease);
                                break;
                            
                            case 9:
                                cout << "Enter New Doctor Assigned: ";
                                cin >> doctorAssigned;
                                p.setDoctorAssigned(doctorAssigned);
                                break;
                            
                            default:
                            cout << "Invalid choice! Try again." << endl;
                            pauseWithMessage("Press Enter to retry");
                        }

                        loader("Updating");
                        cout << "Patient Information Updated Successfully!" << endl;
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Patient ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 4: {
                cout << "----------------------------------------" << endl;
                cout << "         DELETE PATIENT RECORD          " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Patient ID to Delete: "; cin >> id;
                bool found = false;
                for (auto it = patients.begin(); it != patients.end(); ++it) {
                    if (it->getId() == id) {
                        patients.erase(it);
                        loader("Deleting Patient Data");
                        cout << "Patient Record Deleted Successfully!" << endl;
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Patient ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 5: {
                cout << "----------------------------------------" << endl;
                cout << "         VIEW ALL PATIENT RECORD        " << endl;
                cout << "----------------------------------------" << endl;
                string password;
                cout << "Enter Password: ";
                cin >> password;
                if (password == "Admin@1234") {
                    cout << "Verification Successful" << endl;
                    loader("Fetching Data");
                    for (Patient &p : patients) {
                        p.viewPatientDetails();
                    }

                    if (patients.empty()) {
                        cout << "Error: Patient Records Not Found" << endl;
                    }
                }
                pauseWithMessage("Hit Enter to proceed");
                break;
            }
            case 6:
                loader("Returning to Main Menu");
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
        }
    } while (choice != 6);
}

bool logout() {
    string s;
    cout << "========================================" << endl;
    cout << "                LOGOUT                  " << endl;
    cout << "========================================" << endl;
    cout << "Are you sure you want to logout? (Y/N): ";
    cin >> s;
    if (s == "Y" || s == "y") {
        loader("Logging out");
        return true;
    } else {
        return false;
    }
}

void dashboard() {
    vector<Patient> patients;
    // vector<Doctor> doctors;
    // vector<Appointment> appointments;
    // vector<Bill> bills;
    // vector<MedicalRecord> records;
    // vector<Medicine> medicines;
    // vector<Staff> staff;

    int choice;
    bool isLogout = false;
    do { // at least 1 time print hobe
        system("cls"); // too clear the terminal screen
        cout << "========================================" << endl;
        cout << "  HOSPITAL MANAGEMENT SYSTEM DASHBOARD  " << endl;
        cout << "========================================" << endl;
        cout << "1. Patient Management" << endl;
        cout << "2. Doctor Management" << endl;
        cout << "3. Appointment Management" << endl;
        cout << "4. Billing & Payments" << endl;
        cout << "5. Medical Records" << endl;
        cout << "6. Pharmacy & Inventory" << endl;
        cout << "7. Staff & Admin Management" << endl;
        cout << "8. Reports & Statistics" << endl;
        cout << "9. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // '\n'
        validChoice(choice);
        switch (choice) {
            case 1:
                patientManagement(patients);
                break;
            case 2:
                cout << "Development in Progress" << endl;
                // doctorManagement(doctors);
                break;
            case 3:
                cout << "Development in Progress" << endl;
                // appointmentManagement(appointments, patients, doctors);
                break;
            case 4:
                cout << "Development in Progress" << endl;
                // billingManagement(bills, patients);
                break;
            case 5:
                cout << "Development in Progress" << endl;
                // medicalRecordsManagement(records, patients);
                break;
            case 6:
                cout << "Development in Progress" << endl;
                // pharmacyManagement(medicines);
                break;
            case 7:
                cout << "Development in Progress" << endl;
                // staffManagement(staff);
                break;
            case 8:
                cout << "Development in Progress" << endl;
                // reportsManagement(patients, doctors, bills);
                break;
            case 9:
                system("cls");
                if(logout()) {
                    isLogout = true;
                }
                break;
            default: 
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
            }
            if (choice != 1 && choice != 9) {
                getchar();
            }
    } while (isLogout == false);
}



int main() {
    if (login() == true) {
        // Redirect to the main dashboard
        dashboard();
    } else {
        cout << "Access Denied!" << endl;
    }
    return 0;
}