#include <iostream>
#include <vector>
#include <string>
#include <fstream> // i used it for file handling
#include <sstream> // i used it for stringstreem it's okay if you don't know about it I will explain later or you can search it in google
#include <windows.h> // i used it for Sleep() and system("cls") function
using namespace std;

const string MASTER_KEY = "ADMIN@1234";

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

class User {
    string name, username, password;
    bool isLocked;
    int attempts;
public:
    User() {
        isLocked = false;
        attempts = 3;
    }
    void setName(string n) {
        name = n;
    }
    void setUsername(string u) { 
        username = u;
    }
    void setPassword(string p) { 
        password = p;
    }
    void setIsLocked(bool locked) { 
        isLocked = locked;
    }
    void setAttempts(int a) {
        attempts = a;
    }
    string getName() {
        return name;
    }
    string getUsername() { 
        return username;
    }
    string getPassword() { 
        return password;
    }
    bool getIsLocked() { 
        return isLocked;
    }
    int getAttempts() {
        return attempts;
    }
    void decrementAttempts() {
        attempts--;
    }

    // Reset attempts (after successful login or unlocking we are going to reset it)
    void resetAttempts() {
        attempts = 3;
    }

    // Unlock account
    void unlockAccount() {
        isLocked = false;
        resetAttempts(); // To Reset attempts when we unlock
    }

    void saveUsersToFile(string filename, vector<User> &users) {
        ofstream file(filename); // write
        for (User &user : users) {
            file << user.getName() << "|" << user.getUsername() << "|" << user.getPassword() << "|" 
                 << (user.getIsLocked() ? "1" : "0") << "|" << user.getAttempts() << "\n";
        }
    }

    // Admin Functions
    bool resetPassword(vector<User> &users, string masterKey) {
        if (masterKey != MASTER_KEY) {
            cout << "Invalid master key!" << endl;
            return false;
        }

        string targetUsername, newPassword;
        cout << "Enter the username of the account to reset: ";
        getline(cin, targetUsername);
        cout << "Enter the new password: ";
        getline(cin, newPassword);

        for (User &user : users) {
            if (user.getUsername() == targetUsername) {
                user.setPassword(newPassword);
                loader("Please Wait");
                saveUsersToFile("users.csv", users);
                cout << "Password reset successful!" << endl;
                return true;
            }
        }

        cout << "Username not found!" << endl;
        return false;
    }

    void unlockUserAccount(vector<User> &users, string masterKey) {
        if (masterKey != MASTER_KEY) {
            cout << "Invalid master key!" << endl;
            return;
        }

        string targetUsername;
        cout << "Enter the username of the account to unlock: ";
        getline(cin, targetUsername);

        for (User &user : users) {
            if (user.getUsername() == targetUsername) {
                if (user.getAttempts() > 0) {
                    cout << "Account is already active and not locked. No action needed." << endl;
                    return;
                }
                user.unlockAccount();
                loader("Unlocking");
                saveUsersToFile("users.csv", users);
                cout << "Account unlocked successfully!" << endl;
                return;
            }
        }

        cout << "Username not found!" << endl;
    }

    void removeUserAccount(vector<User> &users, string masterKey) {
        if (masterKey != MASTER_KEY) {
            cout << "Invalid master key!" << endl;
            return;
        }

        string targetUsername;
        cout << "Enter the username of the account to remove: ";
        getline(cin, targetUsername);

        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->getUsername() == targetUsername) {
                users.erase(it);
                loader("Removing");
                saveUsersToFile("users.csv", users);
                cout << "Account removed successfully!" << endl;
                return;
            }
        }

        cout << "Username not found!" << endl;
    }

};

vector<User> loadUsersFromFile(string filename) {
    vector<User> users;
    ifstream file(filename); 
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, username, password, locked, attemptsStr;
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, locked, '|');
        getline(ss, attemptsStr, '|');

        User user;
        user.setName(name);
        user.setUsername(username);
        user.setPassword(password);
        user.setIsLocked(locked == "1");
        user.setAttempts(stoi(attemptsStr)); // Set attempts from file string to integer "3" = 3
        users.push_back(user);
    }
    return users;
}

bool login(vector<User> &users) {
    string username, password;
    while (true) {
        system("cls");
        cout << "========================================" << endl;
        cout << "       HOSPITAL MANAGEMENT SYSTEM       " << endl;
        cout << "========================================" << endl << endl;
        cout << " LOGIN " << endl;
        cout << "----------------------------------------" << endl;
        if (users.empty()) {
            cout << "Currently No Account is Registered in the Hospital's DATABASE." << endl << "Please Register an account first" << endl;
            cout << "Thank you" << endl;
            pauseWithMessage("Click Enter to Continue");
            return false;
        }
        cout << "Enter Username: ";
        getline(cin, username);
        cout << "Enter Password: ";
        getline(cin, password);

        bool userExists = false;
        for (User &user : users) {
            if (user.getUsername() == username) {
                userExists = true;

                if (user.getIsLocked()) {
                    cout << "Account is locked. Please contact admin." << endl;
                    pauseWithMessage("Press Enter to continue...");
                    return false;
                }

                if (user.getPassword() == password) {
                    user.resetAttempts(); // Reset attempts on successful login
                    user.saveUsersToFile("users.csv", users);
                    loader("Please Wait");
                    cout << "\nLogin Successful! Redirecting to Dashboard." << endl;
                    Sleep(700);
                    return true;
                } else {
                    user.decrementAttempts(); // attempts--;
                    user.saveUsersToFile("users.csv", users);
                    if (user.getAttempts() <= 0) {
                        user.setIsLocked(true); // Lock the account
                        cout << "Your Account Has Been Locked Because Of Too Many Attempts." << endl;
                        cout << "[Please Contact The Administration If You Have Forgot Your Password Or Think This Is An Error]" << endl << endl;
                        Sleep(700);
                        return false;
                    } else {
                        cout << "\n----------------------------------------" << endl;
                        cout << "Invalid credentials! Try again. (" << user.getAttempts() << " attempts left)\n";
                        cout << "----------------------------------------" << endl;
                        Sleep(2000);
                        break; // Break out of the loop to retry
                    }
                }
            }
        }

        if (!userExists) {
            // Username does not exist
            cout << "\n----------------------------------------" << endl;
            cout << "Invalid User! Try again.\n";
            cout << "----------------------------------------" << endl;
            cout << "Do you want to retry? (Y/N): ";
            char choice;
            cin >> choice;
            cin.ignore(); // Used this to Clear the input buffer
            if (choice == 'N' || choice == 'n') {
                loader("Exiting Login");
                return false; // Return to the main menu
            }
        }
    }
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

void registerUser(vector<User> &users) {
    system("cls");
    cout << "========================================" << endl;
    cout << "       HOSPITAL MANAGEMENT SYSTEM       " << endl;
    cout << "========================================" << endl << endl;
    cout << " REGISTER " << endl;
    cout << "----------------------------------------" << endl;
    string name, username, password;
    cout << "Enter Your Full Name: ";
    getline(cin, name);
    cout << "Enter a username: ";
    getline(cin, username);
    cout << "Enter a password: ";
    getline(cin, password);

    User user;
    user.setName(name);
    user.setUsername(username);
    user.setPassword(password);
    users.push_back(user);

    user.saveUsersToFile("users.csv", users);
    cout << "Registration successful!" << endl;
    pauseWithMessage("Press Enter to continue...");
}

void unlockAccount(vector<User> &users) {
    string username, masterKey;
    cout << "Enter the username of the account to unlock: ";
    getline(cin, username);
    cout << "Enter the master key: ";
    getline(cin, masterKey);

    if (masterKey == MASTER_KEY) {
        for (User &user : users) {
            if (user.getUsername() == username) {
                user.unlockAccount();
                user.saveUsersToFile("users.csv", users);
                cout << "Account unlocked successfully!" << endl;
                pauseWithMessage("Press Enter to continue...");
                return;
            }
        }
        cout << "Username not found!" << endl;
    } else {
        cout << "Invalid master key!" << endl;
    }
    pauseWithMessage("Press Enter to continue...");
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

void savePatientsToFile(string filename, vector<Patient> &patients) {
    ofstream file(filename); // Write
    for (Patient &patient : patients) {
        file << patient.getId() << "|" << patient.getName() << "|" << patient.getAge() << "|" << patient.getGender() << "|" << patient.getBloodGroup() << "|" << patient.getAddress() << "|" << patient.getContact() << "|" << patient.getEmergencyContact() << "|" << patient.getDisease() << "|" << patient.getDoctorAssigned() << "\n";
    }
}

vector<Patient> loadPatientsFromFile(string filename) {
    vector<Patient> patients;
    ifstream file(filename); // read
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, ageStr, gender, bloodGroup, address, contact, emergencyContact, disease, doctorAssigned;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, ageStr, '|');
        getline(ss, gender, '|');
        getline(ss, bloodGroup, '|');
        getline(ss, address, '|');
        getline(ss, contact, '|');
        getline(ss, emergencyContact, '|');
        getline(ss, disease, '|');
        getline(ss, doctorAssigned, '|');

        Patient patient;
        patient.setId(id);
        patient.setName(name);
        patient.setAge(stoi(ageStr)); // string to integer
        patient.setGender(gender);
        patient.setBloodGroup(bloodGroup);
        patient.setAddress(address);
        patient.setContact(contact);
        patient.setEmergencyContact(emergencyContact);
        patient.setDisease(disease);
        patient.setDoctorAssigned(doctorAssigned);

        patients.push_back(patient);
    }
    return patients;
}

void patientManagement(vector<Patient> &patients) {
    int choice = 0;
    while (choice != 6) {
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
                getline(cin, doctorAssigned);

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
                savePatientsToFile("patients.csv", patients); // Save to file
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
                                getline(cin, doctorAssigned);
                                p.setDoctorAssigned(doctorAssigned);
                                break;
                            
                            default:
                            cout << "Invalid choice! Try again." << endl;
                            pauseWithMessage("Press Enter to retry");
                        }

                        loader("Updating");
                        savePatientsToFile("patients.csv", patients); // Save to file
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
                //  pointer arr[1] address
                for (auto it = patients.begin(); it != patients.end(); ++it) {
                    if (it->getId() == id) {
                        patients.erase(it);
                        savePatientsToFile("patients.csv", patients); // Save to file
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
                string masterKey;
                cout << "Enter MASTER KEY: ";
                cin >> masterKey;
                if (masterKey == MASTER_KEY) {
                    cout << "Verification Successful" << endl;
                    loader("Fetching Data");
                    for (Patient &p : patients) {
                        p.viewPatientDetails();
                    }

                    if (patients.empty()) {
                        cout << "Error: Patient Records Not Found" << endl;
                    }
                } else {
                    cout << "\n----------------------------------------" << endl;
                    cout << "           Invalid MASTER KEY!\n";
                    cout << "----------------------------------------" << endl;
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
    }
}

void adminManagement(vector<User> &users) {
    system("cls");
    string masterKey;
    cout << "========================================" << endl;
    cout << "         ADMINISTRATOR ACCESS           " << endl;
    cout << "========================================" << endl;
    cout << "You are not a superuser. Enter the Master Key to gain access." << endl;
    cout << "Enter Master Key: ";
    getline(cin, masterKey);

    if (masterKey != MASTER_KEY) {
        cout << "\n----------------------------------------" << endl;
        cout << "Invalid master key! Access denied." << endl;
        cout << "Please contact the system administrator if you believe this is an error." << endl;
        cout << "----------------------------------------" << endl;
        pauseWithMessage("Press Enter to return to the main menu...");
        return;
    }

    loader("Verifying Master Key. Please wait");
    cout << "Verified" << endl;
    loader("Entering Admin Menu");
    int choice = 0;
    while (choice != 5) {
        system("cls");
        cout << "========================================" << endl;
        cout << "           ADMINISTRATOR MENU           " << endl;
        cout << "========================================" << endl;
        cout << "1. Reset User Password" << endl;
        cout << "2. Unlock User Account" << endl;
        cout << "3. Remove User Account" << endl;
        cout << "4. View All Users" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                User admin;
                admin.resetPassword(users, masterKey);
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 2: {
                User admin;
                admin.unlockUserAccount(users, masterKey);
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 3: {
                User admin;
                admin.removeUserAccount(users, masterKey);
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 4: {
                cout << "\n----------------------------------------" << endl;
                cout << "           ALL USER ACCOUNTS            " << endl;
                cout << "----------------------------------------" << endl;
                for (User &user : users) {
                    cout << "Name: " << user.getName() << endl;
                    cout << "Username: " << user.getUsername() << endl;
                    cout << "Status: " << (user.getIsLocked() ? "Locked" : "Active") << endl;
                    cout << "----------------------------------------" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 5:
                loader("Returning to Main Menu");
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
        }
    }
}

void dashboard(vector<User> &users) {
    vector<Patient> patients = loadPatientsFromFile("patients.csv"); // Load patients from file

    // vector<Doctor> doctors;
    // vector<Appointment> appointments;
    // vector<Bill> bills;
    // vector<MedicalRecord> records;
    // vector<Medicine> medicines;
    // vector<Staff> staff;

    int choice;
    bool isLogout = false;
    while (isLogout == false) {
        system("cls"); // too clear the terminal screen
        cout << "========================================" << endl;
        cout << "  HOSPITAL MANAGEMENT SYSTEM DASHBOARD  " << endl;
        cout << "========================================" << endl;
        cout << "1. Patient Management" << endl;
        cout << "2. Doctor Management" << endl;
        cout << "3. Appointment Management" << endl;
        cout << "4. Pharmacy & Inventory" << endl;
        cout << "5. Admin Management" << endl; // I have removed Staff Management We will Discuss it with our teacher about it
        cout << "6. Reports & Statistics" << endl;
        cout << "7. Logout" << endl;
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
                // pharmacyManagement(medicines);
                break;
            case 5:
                adminManagement(users);
                break;
            case 6:
                cout << "Development in Progress" << endl;
                // reportsManagement(patients, doctors, bills);
                break;
            case 7:
                system("cls");
                if(logout()) {
                    isLogout = true;
                }
                break;
            default: 
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
        }
        if (choice != 1 && choice != 7 && choice != 5) {
            getchar();
        }
    }
}

void initialMenu(vector<User> &users) {
    int choice;
    while (true) {
        system("cls");
        cout << "========================================" << endl;
        cout << "       HOSPITAL MANAGEMENT SYSTEM       " << endl;
        cout << "========================================" << endl << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                if (login(users)) {
                    dashboard(users);
                }
                break;
            case 3:
                loader("Exiting");
                return;
            default:
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
        }
    }
}

int main() {
    vector<User> users = loadUsersFromFile("users.csv");
    initialMenu(users);
    return 0;
}
