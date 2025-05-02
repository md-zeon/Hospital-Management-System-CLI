#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream> // i used it for file handling
#include <sstream> // i used it for stringstreem it's okay if you don't know about it I will explain later or you can search it in google
#include <windows.h> // i used it for Sleep() and system("cls") function
using namespace std;

const string MASTER_KEY = "ADMIN@1234";

int safeStoi(const string& str) {
    try {
        return stoi(str);
    } catch (...) {
        return 0; // Return default value if conversion fails
    }
}

void loader(string msg) {
    cout << msg;
    for(int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(600); // Pause for 600 milliseconds
    }
    cout << endl;
}

void pauseWithMessage(string msg) {
    cout << endl << msg;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // No getchar() needed! cin.ignore() already waits for Enter if buffer is empty.
}

void validChoice(int &choice) {
    while (choice <= 0 || cin.fail()) {
        cout << "Please enter a valid number: ";
        cin.clear();             // Clear error flag on the cin stream
        cin.ignore(1000, '\n');  // Discard invalid input from buffer
        cin >> choice;           // Try to get valid input again
    }
    cin.ignore(); // <- This helps when a string (with getline) follows
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
    void setName(string n) { name = n; }
    void setUsername(string u) {  username = u; }
    void setPassword(string p) {  password = p; }
    void setIsLocked(bool locked) {  isLocked = locked; }
    void setAttempts(int a) { attempts = a; }
    string getName() { return name; }
    string getUsername() {  return username; }
    string getPassword() {  return password; }
    bool getIsLocked() {  return isLocked; }
    int getAttempts() { return attempts; }
    void decrementAttempts() { attempts--; }

    // Reset attempts (after successful login or unlocking we are going to reset it)
    void resetAttempts() { attempts = 3; }

    // Unlock account
    void unlockAccount() {
        isLocked = false;
        resetAttempts(); // To Reset attempts when we unlock
    }

    void saveUsersToFile(string filename, vector<User> &users) {
        ofstream file(filename); // write
        for (User &user : users) {
            file << user.getName() << "," << user.getUsername() << "," << user.getPassword() << "," 
                 << (user.getIsLocked() ? "1" : "0") << "," << user.getAttempts() << "\n";
        }
    }

    // Admin Functions
    bool resetPassword(vector<User> &users, string masterKey) {
        if (masterKey != MASTER_KEY) {
            cout << "Invalid master key!" << endl;
            return false;
        }

        string targetUsername, newPassword, confirmPassword;
        cout << "Enter the username of the account to reset: ";
        getline(cin, targetUsername);

        for (User &user : users) {
            if (user.getUsername() == targetUsername) {
                cout << "Enter the new password: ";
                getline(cin, newPassword);
                cout << "Re enter new password: ";
                getline(cin, confirmPassword);
        
                if (newPassword != confirmPassword) {
                    cout << "Incorrect Password!" << endl;
                    return false;
                }
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

        for (auto it = users.begin(); it != users.end(); it++) {
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
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, locked, ',');
        getline(ss, attemptsStr, ',');

        User user;
        user.setName(name);
        user.setUsername(username);
        user.setPassword(password);
        user.setIsLocked(locked == "1");
        user.setAttempts(safeStoi(attemptsStr)); // Set attempts from file string to integer "3" = 3
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

        bool userExists = false;
        for (User &user : users) {
            if (user.getUsername() == username) {
                userExists = true;

                if (user.getIsLocked()) {
                    cout << "Account is locked. Please contact admin." << endl;
                    pauseWithMessage("Press Enter to continue...");
                    return false;
                }

                cout << "Enter Password: ";
                getline(cin, password);

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
    for (User &user : users) {
        if (user.getUsername() == username) {
            cout << "User Already Exist! Please use another username :)" << endl;
            pauseWithMessage("Hit Enter To Proceed");
            return;
        }
    }
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
    void setId(string id) { patientId = id; }
    string getId() { return patientId; }
    void setName(string name) { this->name = name; }
    string getName() { return name; }
    void setAge(int age) { this->age = age; }
    int getAge() { return age; }
    void setGender(string gender) { this->gender = gender; }
    string getGender() { return gender; }
    void setBloodGroup(string bloodGroup) { this->bloodGroup = bloodGroup; }
    string getBloodGroup() { return bloodGroup; }
    void setAddress(string address) { this->address = address; }
    string getAddress() { return address; }
    void setContact(string contact) { this->contact = contact; }
    string getContact() { return contact; }
    void setEmergencyContact(string emergencyContact) { this->emergencyContact = emergencyContact; }
    string getEmergencyContact() { return emergencyContact; }
    void setDisease(string disease) { this->disease = disease; }
    string getDisease() { return disease; }
    void setDoctorAssigned(string doctorAssigned) { this->doctorAssigned = doctorAssigned; }
    string getDoctorAssigned() { return doctorAssigned; }
 
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
    ofstream file(filename); // write
    for (Patient &patient : patients) {
        file << "\"" << patient.getId() << "\","
             << "\"" << patient.getName() << "\","
             << "\"" << patient.getAge() << "\","
             << "\"" << patient.getGender() << "\","
             << "\"" << patient.getBloodGroup() << "\","
             << "\"" << patient.getAddress() << "\","
             << "\"" << patient.getContact() << "\","
             << "\"" << patient.getEmergencyContact() << "\","
             << "\"" << patient.getDisease() << "\","
             << "\"" << patient.getDoctorAssigned() << "\"\n";
    }
}

// Helper Function
vector<string> parseQuotedCSVLine(string &line) {
    vector<string> result;
    string part;
    bool insideQuotes = false;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == '"') {
            insideQuotes = !insideQuotes;
        } else if (c == ',' && !insideQuotes) {
            result.push_back(part);
            part.clear();
        } else {
            part += c;
        }
    }
    result.push_back(part); // last part
    return result;
}

vector<Patient> loadPatientsFromFile(string filename) {
    vector<Patient> patients;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> parts = parseQuotedCSVLine(line);
        if (parts.size() != 10) continue; // skip malformed lines

        Patient patient;
        patient.setId(parts[0]);
        patient.setName(parts[1]);
        patient.setAge(safeStoi(parts[2]));
        patient.setGender(parts[3]);
        patient.setBloodGroup(parts[4]);
        patient.setAddress(parts[5]);
        patient.setContact(parts[6]);
        patient.setEmergencyContact(parts[7]);
        patient.setDisease(parts[8]);
        patient.setDoctorAssigned(parts[9]);

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
                cin.ignore();
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
                        p.viewPatientDetails();
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
                        cin >> update;
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
                                cin.ignore();
                                break;

                            case 3:
                                cout << "Enter New Gender (M/F): ";
                                getline(cin, gender);
                                p.setGender(gender);
                                break;

                            case 4:
                                cout << "Enter New Blood Group: ";
                                getline(cin, bloodGroup);
                                p.setBloodGroup(bloodGroup);
                                break;

                            case 5:
                                cout << "Enter New Address: ";
                                getline(cin, address);
                                p.setAddress(address);
                                break;

                            case 6:
                                cout << "Enter New Contact: ";
                                getline(cin, contact);
                                p.setContact(contact);
                                break;

                            case 7:
                                cout << "Enter New Emergency Contact: ";
                                getline(cin, emergencyContact);
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
                cin.ignore();
                bool found = false;
                for (auto it = patients.begin(); it != patients.end(); it++) {
                    if (it->getId() == id) {
                        patients.erase(it);
                        loader("Deleting Patient Data");
                        savePatientsToFile("patients.csv", patients); // Save to file
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
                getline(cin, masterKey);
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

class Doctor {
    string id, name, specialization, contact, experience, availability, degrees, institutions;
public:
    void setId(string id) { 
        this->id = id;
    } 
    string getId() { return id; }
    void setName(string name) { this->name = name; }
    string getName() { return name; }
    void setSpecialization(string specialization) { this->specialization = specialization; }
    string getSpecialization() { return specialization; }
    void setExperience(string experience) { this->experience = experience; }
    string getExperience() { return experience; }
    void setAvailability(string availability) { this->availability = availability; }
    string getAvailability() { return availability; }
    void setContact(string contact) { this->contact = contact; }
    string getContact() { return contact; }
    void setDegrees(string degrees) { this->degrees = degrees; }
    string getDegrees() { return degrees; }
    void setInstitutions(string institutions) { this->institutions = institutions; }
    string getInstitutions() { return institutions; }

    void viewDoctorDetails() {
        cout << "\n----------------------------------------" << endl;
        cout << "Doctor ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Degrees: " << degrees << endl;
        cout << "Institutions: " << institutions << endl;
        cout << "Experience: " << experience << " years" << endl;
        cout << "Available: " << (availability == "true" ? "Yes" : "No") << endl;
        cout << "Contact: " << contact << endl;
        cout << "----------------------------------------" << endl;
    }
};

void saveDoctorsToFile(string filename, vector<Doctor> &doctors) {
    ofstream file(filename);
    for (Doctor &doctor : doctors) {
        file << "\"" << doctor.getId() << "\","
             << "\"" << doctor.getName() << "\","
             << "\"" << doctor.getSpecialization() << "\","
             << "\"" << doctor.getDegrees() << "\","
             << "\"" << doctor.getInstitutions() << "\","
             << "\"" << doctor.getContact() << "\","
             << "\"" << doctor.getExperience() << "\","
             << "\"" << doctor.getAvailability() << "\"\n";
    }
}

vector<Doctor> loadDoctorsFromFile(string filename) {
    vector<Doctor> doctors;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> parts = parseQuotedCSVLine(line);
        if (parts.size() != 8) continue; // skip if malformed

        Doctor doctor;
        doctor.setId(parts[0]);
        doctor.setName(parts[1]);
        doctor.setSpecialization(parts[2]);
        doctor.setDegrees(parts[3]);
        doctor.setInstitutions(parts[4]);
        doctor.setContact(parts[5]);
        doctor.setExperience(parts[6]);
        doctor.setAvailability(parts[7]);

        doctors.push_back(doctor);
    }

    return doctors;
}

void doctorManagement(vector<Doctor> &doctors) {
    int choice = 0;
    while (choice != 6) {
        system("cls");
        cout << "========================================" << endl;
        cout << "          DOCTOR MANAGEMENT            " << endl;
        cout << "========================================" << endl;
        cout << "1. Register New Doctor" << endl;
        cout << "2. View Doctor Details" << endl;
        cout << "3. Update Doctor Info" << endl;
        cout << "4. Delete Doctor Record" << endl;
        cout << "5. View All Doctor Details" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        validChoice(choice);
        switch (choice) {
            case 1: {
                cout << "----------------------------------------" << endl;
                cout << "           REGISTER NEW DOCTOR         " << endl;
                cout << "----------------------------------------" << endl;
                cout << "Enter Doctor Details:" << endl << endl;
                Doctor d;
                string id, name, specialization, degrees, institutions, contact, experience, availability;
                cout << "Enter Doctor ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Specialization: ";
                getline(cin, specialization);
                cout << "Enter Degrees: ";
                getline(cin, degrees);
                cout << "Enter Institutions: ";
                getline(cin, institutions);
                cout << "Enter Experience: ";
                cin >> experience;
                cout << "Enter Contact: ";
                cin.ignore();
                getline(cin, contact);
                cout << "Is Available(true/false): ";
                cin >> availability;
                cin.ignore();
                d.setId(id);
                d.setName(name);
                d.setSpecialization(specialization);
                d.setDegrees(degrees);
                d.setInstitutions(institutions);
                d.setExperience(experience);
                d.setAvailability(availability);
                d.setContact(contact);
                doctors.push_back(d);

                saveDoctorsToFile("doctors.csv", doctors); // Save to file
                loader("Registering Doctor");
                cout << "Doctor Registered Successfully!" << endl;
                pauseWithMessage("Press Enter to go back to the menu...");
                break;
            }
            case 2: {
                cout << "----------------------------------------" << endl;
                cout << "             DOCTOR DETAILS            " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter DOCTOR ID: ";
                cin >> id;
                cin.ignore();
                bool found = false;
                loader("Searching");
                for (Doctor &d : doctors) {
                    if (d.getId() == id) {
                        cout << "Doctor Found" << endl;
                        d.viewDoctorDetails();
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Doctor ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 3: {
                cout << "----------------------------------------" << endl;
                cout << "           UPDATE DOCTOR INFO          " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Doctor ID: ";
                cin >> id;
                cin.ignore();
                bool found = false;
                for (Doctor &d : doctors) {
                    if (d.getId() == id) {
                        string id, name, specialization, degrees, institutions, contact, experience, availability;
                        cout << "What do you want to update?" << endl;
                        cout << "1. Update Doctor Name" << endl;
                        cout << "2. Update Doctor Specialization" << endl;
                        cout << "3. Update Doctor Degrees" << endl;
                        cout << "4. Update Doctor Institutions" << endl;
                        cout << "5. Update Doctor Experience" << endl;
                        cout << "6. Update Doctor Contact" << endl;
                        cout << "7. Update Doctor Availability" << endl;
                        cout << "8. Go Back" << endl;
                        int update;
                        cout << "Enter Your Choice: ";
                        cin >> update;
                        validChoice(update);
                        switch (update) {
                            case 1:
                                cout << "Enter New Name: ";
                                getline(cin, name);
                                d.setName(name);
                                break;

                            case 2:
                                cout << "Enter New Specialization: ";
                                getline(cin, specialization);
                                d.setSpecialization(specialization);
                                break;

                            case 3:
                                cout << "Enter New Degrees: ";
                                getline(cin, degrees);
                                d.setDegrees(degrees);
                                break;

                            case 4:
                                cout << "Enter New Institutions: ";
                                getline(cin, institutions);
                                d.setInstitutions(institutions);
                                break;

                            case 5:
                                cout << "Enter New Experience: ";
                                cin >> experience;
                                cin.ignore();
                                d.setExperience(experience);
                                break;

                            case 6:
                                cout << "Enter New Contact: ";
                                getline(cin, contact);
                                d.setContact(contact);
                                break;

                            case 7:
                                cout << "Enter New Availability: ";
                                getline(cin, availability);
                                d.setAvailability(availability);
                                break;

                            case 8:
                                loader("Going Back");
                                break;
                            
                            default:
                                cout << "Invalid choice! Try again." << endl;
                                pauseWithMessage("Press Enter to retry");
                        }

                        if (update != 8) {
                            loader("Updating");
                            saveDoctorsToFile("doctors.csv", doctors); // Save to file
                            cout << "Doctor Information Updated Successfully!" << endl;
                        }
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Doctor ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 4: {
                cout << "----------------------------------------" << endl;
                cout << "         DELETE DOCTOR RECORD          " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Doctor ID to Delete: "; cin >> id;
                cin.ignore();
                bool found = false;
                for (auto it = doctors.begin(); it != doctors.end(); it++) {
                    if (it->getId() == id) {
                        doctors.erase(it);
                        loader("Deleting Doctor Data");
                        saveDoctorsToFile("doctors.csv", doctors); // Save to file
                        cout << "Doctor Record Deleted Successfully!" << endl;
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Doctor ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 5: {
                cout << "----------------------------------------" << endl;
                cout << "         VIEW ALL DOCTOR RECORD        " << endl;
                cout << "----------------------------------------" << endl;
                string masterKey;
                cout << "Enter MASTER KEY: ";
                getline(cin, masterKey);
                if (masterKey == MASTER_KEY) {
                    cout << "Verification Successful" << endl;
                    loader("Fetching Data");
                    for (Doctor &d : doctors) {
                        d.viewDoctorDetails();
                    }

                    if (doctors.empty()) {
                        cout << "Error: Doctor Records Not Found" << endl;
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
        validChoice(choice);

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
                    cout << "Status: " << (user.getIsLocked() ? "Disabled" : "Active") << endl; // fixed
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

class Appointment {
    string appointmentId, patientId, doctorId, date, time, status;
public:
    void setAppointmentId(string id) { appointmentId = id; }
    string getAppointmentId() { return appointmentId; }
    void setPatientId(string id) { patientId = id; }
    string getPatientId() { return patientId; }
    void setDoctorId(string id) { doctorId = id; }
    string getDoctorId() { return doctorId; }
    void setDate(string d) { date = d; }
    string getDate() { return date; }
    void setTime(string t) { time = t; }
    string getTime() { return time; }
    void setStatus(string s) { status = s; }
    string getStatus() { return status; }

    void viewAppointmentDetails(vector<Patient>& patients, vector<Doctor>& doctors) {
        string patientName = "Unknown", doctorName = "Unknown";
        
        // Find patient name
        for (Patient &p : patients) {
            if (p.getId() == patientId) {
                patientName = p.getName();
                break;
            }
        }
        
        // Find doctor name
        for (Doctor &d : doctors) {
            if (d.getId() == doctorId) {
                doctorName = d.getName();
                break;
            }
        }
        
        cout << "\n----------------------------------------" << endl;
        cout << "Appointment ID: " << appointmentId << endl;
        cout << "Patient: " << patientName << " (" << patientId << ")" << endl;
        cout << "Doctor: " << doctorName << " (" << doctorId << ")" << endl;
        cout << "Date: " << date << endl;
        cout << "Time: " << time << endl;
        cout << "Status: " << status << endl;
        cout << "----------------------------------------" << endl;
    }
};

void saveAppointmentsToFile(string filename, vector<Appointment> &appointments) {
    ofstream file(filename);
    for (Appointment &app : appointments) {
        file << "\"" << app.getAppointmentId() << "\","
             << "\"" << app.getPatientId() << "\","
             << "\"" << app.getDoctorId() << "\","
             << "\"" << app.getDate() << "\","
             << "\"" << app.getTime() << "\","
             << "\"" << app.getStatus() << "\"\n";
    }
}

vector<Appointment> loadAppointmentsFromFile(string filename) {
    vector<Appointment> appointments;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        vector<string> parts = parseQuotedCSVLine(line);
        if (parts.size() != 6) continue; // skip malformed lines
        
        Appointment app;
        app.setAppointmentId(parts[0]);
        app.setPatientId(parts[1]);
        app.setDoctorId(parts[2]);
        app.setDate(parts[3]);
        app.setTime(parts[4]);
        app.setStatus(parts[5]);
        
        appointments.push_back(app);
    }
    return appointments;
}

bool isDoctorAvailable(vector<Appointment>& appointments, string doctorId, string date, string time) {
    for (Appointment &app : appointments) {
        if (app.getDoctorId() == doctorId && app.getDate() == date && 
            app.getTime() == time && app.getStatus() != "Cancelled") {
            return false;
        }
    }
    return true;
}

void scheduleAppointment(vector<Appointment>& appointments, vector<Patient>& patients, vector<Doctor>& doctors) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "        SCHEDULE NEW APPOINTMENT       " << endl;
    cout << "----------------------------------------" << endl;
    
    string patientId, doctorId;
    cout << "Enter Patient ID: ";
    cin >> patientId;
    cin.ignore();
    
    // Check if patient exists
    bool patientExists = false;
    for (Patient &p : patients) {
        if (p.getId() == patientId) {
            patientExists = true;
            break;
        }
    }
    
    if (!patientExists) {
        cout << "Error: Patient ID not found!" << endl;
        pauseWithMessage("Press Enter to go back...");
        return;
    }
    
    cout << "Enter Doctor ID: ";
    cin >> doctorId;
    cin.ignore();
    
    // Check if doctor exists
    bool doctorExists = false;
    for (Doctor &d : doctors) {
        if (d.getId() == doctorId) {
            doctorExists = true;
            break;
        }
    }
    
    if (!doctorExists) {
        cout << "Error: Doctor ID not found!" << endl;
        pauseWithMessage("Press Enter to go back...");
        return;
    }
    
    string date;
    cout << "Enter Date (YYYY-MM-DD): ";
    getline(cin, date);
    
    // Show available time slots
    vector<string> timeSlots = {"09:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", 
                               "02:00 PM", "03:00 PM", "04:00 PM"};
    vector<string> availableSlots;
    
    for (string slot : timeSlots) {
        if (isDoctorAvailable(appointments, doctorId, date, slot)) {
            availableSlots.push_back(slot);
        }
    }
    
    if (availableSlots.empty()) {
        cout << "No available slots for this doctor on " << date << endl;
        pauseWithMessage("Press Enter to go back...");
        return;
    }
    
    cout << "\nAvailable Slots:" << endl;
    for (int i = 0; i < availableSlots.size(); i++) {
        cout << i+1 << ". " << availableSlots[i] << endl;
    }
    
    int slotChoice;
    cout << "Select Slot (1-" << availableSlots.size() << "): ";
    cin >> slotChoice;
    cin.ignore();
    
    if (slotChoice < 1 || slotChoice > availableSlots.size()) {
        cout << "Invalid slot selection!" << endl;
        pauseWithMessage("Press Enter to go back...");
        return;
    }
    
    string time = availableSlots[slotChoice-1];
    
    // Change Start
    cout<<"Enter appointment id : ";
    string appointmentId;
    getline(cin,appointmentId);
    bool duplicateId = false;
    for (Appointment &app: appointments) {
        if (app.getAppointmentId() == appointmentId) {
            duplicateId = true;
            break;
        }
    }

    if(duplicateId) {
        cout << "Appointment ID already Exist!" << endl;
        pauseWithMessage("Press Enter to go back...");
        return;
    }

    // Change End
    
    Appointment newApp;
    newApp.setAppointmentId(appointmentId);
    newApp.setPatientId(patientId);
    newApp.setDoctorId(doctorId);
    newApp.setDate(date);
    newApp.setTime(time);
    newApp.setStatus("Scheduled");
    
    appointments.push_back(newApp);
    loader("Scheduling appointment");
    saveAppointmentsToFile("appointments.csv", appointments);
    
    cout << "\nAppointment Scheduled Successfully!" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Appointment ID: " << appointmentId << endl;
    cout << "Patient: " << patientId << endl;
    cout << "Doctor: " << doctorId << endl;
    cout << "Date: " << date << endl;
    cout << "Time: " << time << endl;
    cout << "----------------------------------------" << endl;
    
    pauseWithMessage("Press Enter to continue...");
}

void viewUpcomingAppointments(vector<Appointment>& appointments, vector<Patient>& patients, vector<Doctor>& doctors) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "        UPCOMING APPOINTMENTS           " << endl;
    cout << "----------------------------------------" << endl;
    
    if (appointments.empty()) {
        cout << "No appointments found!" << endl;
        pauseWithMessage("Press Enter to go back...");
        return;
    }
    
    bool found = false;
    cout << "Appointment ID  Patient      Doctor        Date       Time      " << endl;
    cout << "--------------------------------------------------------------" << endl;
    
    for (Appointment &app : appointments) {
        if (app.getStatus() == "Scheduled") {
            found = true;
            
            string patientName = "Unknown", doctorName = "Unknown";
            for (Patient &p : patients) {
                if (p.getId() == app.getPatientId()) {
                    patientName = p.getName();
                    break;
                }
            }
            
            for (Doctor &d : doctors) {
                if (d.getId() == app.getDoctorId()) {
                    doctorName = d.getName();
                    break;
                }
            }
            
            // Format output in columns
            printf("%-15s %-12s %-12s %-10s %-8s\n", 
                   app.getAppointmentId().c_str(),
                   patientName.substr(0, 10).c_str(),
                   doctorName.substr(0, 10).c_str(),
                   app.getDate().c_str(),
                   app.getTime().c_str());
        }
    }
    
    if (!found) {
        cout << "No upcoming appointments found!" << endl;
    }
    
    pauseWithMessage("\nPress Enter to continue...");
}

void cancelAppointment(vector<Appointment>& appointments) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "         CANCEL APPOINTMENT             " << endl;
    cout << "----------------------------------------" << endl;
    
    string appointmentId;
    cout << "Enter Appointment ID: ";
    cin >> appointmentId;
    cin.ignore();
    
    bool found = false;
    for (Appointment &app : appointments) {
        if (app.getAppointmentId() == appointmentId) {
            found = true;
            
            if (app.getStatus() == "Cancelled") {
                cout << "This appointment is already cancelled!" << endl;
                pauseWithMessage("Press Enter to continue...");
                return;
            }
            
            cout << "Warning: Are you sure you want to cancel this appointment? (Y/N): ";
            char confirm;
            cin >> confirm;
            cin.ignore();
            
            if (confirm == 'Y' || confirm == 'y') {
                loader("Cancelling");
                app.setStatus("Cancelled");
                saveAppointmentsToFile("appointments.csv", appointments);
                cout << "Appointment cancelled successfully!" << endl;
            } else {
                cout << "Cancellation aborted." << endl;
            }
            
            break;
        }
    }
    
    if (!found) {
        cout << "Error: Appointment ID not found!" << endl;
    }
    
    pauseWithMessage("Press Enter to continue...");
}

void appointmentManagement(vector<Appointment>& appointments, vector<Patient>& patients, vector<Doctor>& doctors) {
    int choice = 0;
    while (choice != 4) {
        system("cls");
        cout << "========================================" << endl;
        cout << "        APPOINTMENT MANAGEMENT          " << endl;
        cout << "========================================" << endl;
        cout << "1.  Schedule New Appointment" << endl;
        cout << "2.  View Upcoming Appointments" << endl;
        cout << "3.  Cancel Appointment" << endl;
        cout << "4.  Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        validChoice(choice);
        
        switch (choice) {
            case 1:
                scheduleAppointment(appointments, patients, doctors);
                break;
            case 2:
                viewUpcomingAppointments(appointments, patients, doctors);
                break;
            case 3:
                cancelAppointment(appointments);
                break;
            case 4:
                loader("Returning to Main Menu");
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
        }
    }
}

class Medicine {
    string id, name, expiryDate;
    int quantity;
    double price;
public:
    void setId(string id) { this->id = id; }
    string getId() { return id; }
    void setName(string name) { this->name = name; }
    string getName() { return name; }
    void setExpiryDate(string expiryDate) { this->expiryDate = expiryDate; }
    string getExpiryDate() { return expiryDate; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    int getQuantity() { return quantity; }
    void setPrice(double price) { this->price = price; }
    double getPrice() { return price; }

    void viewMedicineDetails() {
        cout << "\n----------------------------------------" << endl;
        cout << "Medicine ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Quantity: " << quantity << endl;
        printf("Price: %.2f\n", price);
        cout << "Expiry Date: " << expiryDate << endl;
        cout << "----------------------------------------" << endl;
    }
};

void saveMedicinesToFile(string filename, vector<Medicine> &medicines) {
    ofstream file(filename);
    for (Medicine &med : medicines) {
        file << med.getId() << "," 
             << med.getName() << ","
             << med.getQuantity() << ","
             << med.getPrice() << ","
             << med.getExpiryDate() << "\n";
    }
}

vector<Medicine> loadMedicinesFromFile(string filename) {
    vector<Medicine> medicines;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, quantityStr, priceStr, expiryDate;
        
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, expiryDate);

        Medicine med;
        med.setId(id);
        med.setName(name);
        med.setQuantity(safeStoi(quantityStr));
        med.setPrice(stod(priceStr));
        med.setExpiryDate(expiryDate);

        medicines.push_back(med);
    }
    return medicines;
}

void viewMedicineStock(vector<Medicine> &medicines) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "         MEDICINE STOCK              " << endl;
    cout << "----------------------------------------" << endl;
    
    if (medicines.empty()) {
        cout << " No medicine in stock!" << endl;
        pauseWithMessage("Press any key to go back...");
        return;
    }

    loader("Fetching inventory details"); // changed
    cout << "----------------------------------------" << endl;
    cout << "ID      Name              Quantity   Price   Expiry Date" << endl;
    cout << "--------------------------------------------------------" << endl;
    
    for (Medicine &med : medicines) {
        printf("%-8s%-18s%-10d$%-8.2f%s\n", 
               med.getId().c_str(),
               med.getName().c_str(),
               med.getQuantity(),
               med.getPrice(),
               med.getExpiryDate().c_str());
    }
    
    pauseWithMessage("\nPress any key to continue...");
}

void addNewMedicine(vector<Medicine> &medicines) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "         ADD NEW MEDICINE             " << endl;
    cout << "----------------------------------------" << endl;
    
    Medicine newMed;
    string id, name, expiryDate;
    int quantity;
    double price;
    
    cout << "Enter Medicine ID: ";
    cin >> id;
    cin.ignore();
    
    // Check if medicine ID already exists
    for (Medicine &med : medicines) {
        if (med.getId() == id) {
            cout << "Error: Medicine ID already exists!" << endl;
            pauseWithMessage("Press any key to go back...");
            return;
        }
    }
    
    cout << "Enter Medicine Name: ";
    // cin.ignore();
    getline(cin, name);
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Expiry Date (YYYY-MM-DD): ";
    cin >> expiryDate;
    cin.ignore(); // added
    
    newMed.setId(id);
    newMed.setName(name);
    newMed.setQuantity(quantity);
    newMed.setPrice(price);
    newMed.setExpiryDate(expiryDate);
    medicines.push_back(newMed);
    
    saveMedicinesToFile("medicines.csv", medicines);
    loader("Adding medicine");
    
    cout << "\n Medicine Added Successfully!" << endl;
    cout << " Medicine ID: " << id << endl;
    cout << " Name: " << name << endl;
    cout << " Quantity: " << quantity << endl;
    printf(" Price: $%.2f\n", price);
    cout << " Expiry Date: " << expiryDate << endl;
    
    pauseWithMessage("\nPress any key to continue...");
}

void updateMedicineDetails(vector<Medicine> &medicines) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "         UPDATE MEDICINE DETAILS      " << endl;
    cout << "----------------------------------------" << endl;
    
    string id;
    cout << "Enter Medicine ID: ";
    cin >> id;
    cin.ignore();
    
    bool found = false;
    for (Medicine &med : medicines) {
        if (med.getId() == id) {
            found = true;
            loader("Fetching medicine details");
            
            cout << "\n----------------------------------------" << endl;
            cout << " Medicine ID: " << med.getId() << endl;
            cout << " Name: " << med.getName() << endl;
            cout << " Quantity: " << med.getQuantity() << endl;
            printf(" Price: $%.2f\n", med.getPrice());
            cout << " Expiry Date: " << med.getExpiryDate() << endl;
            cout << "----------------------------------------" << endl;
            
            cout << "\nSelect Field to Update:" << endl;
            cout << "1.  Name" << endl;
            cout << "2.  Quantity" << endl;
            cout << "3.  Price" << endl;
            cout << "4.  Expiry Date" << endl;
            cout << "5.  Cancel" << endl;
            
            int choice;
            cout << "Enter choice: ";
            cin >> choice;
            validChoice(choice);
            
            if (choice == 5) {
                loader("Cancelling update");
                pauseWithMessage("Press any key to continue...");
                return;
            }
            
            switch (choice) {
                case 1: {
                    string newName;
                    cout << "Enter New Name: ";
                    getline(cin, newName);
                    med.setName(newName);
                    break;
                }
                case 2: {
                    int newQty;
                    cout << "Enter New Quantity: ";
                    cin >> newQty;
                    cin.ignore();
                    med.setQuantity(newQty);
                    break;
                }
                case 3: {
                    double newPrice;
                    cout << "Enter New Price: ";
                    cin >> newPrice;
                    med.setPrice(newPrice);
                    break;
                }
                case 4: {
                    string newExpiry;
                    cout << "Enter New Expiry Date (YYYY-MM-DD): ";
                    cin >> newExpiry;
                    med.setExpiryDate(newExpiry);
                    break;
                }
                default:
                    cout << "Invalid choice!" << endl;
            }
            
            if (choice >= 1 && choice <= 4) {
                saveMedicinesToFile("medicines.csv", medicines);
                loader("Updating medicine");
                cout << " Medicine Details Updated Successfully!" << endl;
            }
            
            pauseWithMessage("Press any key to continue...");
            return;
        }
    }
    
    if (!found) {
        cout << " Error: Medicine ID not found!" << endl;
        pauseWithMessage("Press any key to go back...");
    }
}

void removeMedicine(vector<Medicine> &medicines) {
    system("cls");
    cout << "----------------------------------------" << endl;
    cout << "         REMOVE MEDICINE              " << endl;
    cout << "----------------------------------------" << endl;
    
    string id;
    cout << "Enter Medicine ID to Remove: ";
    cin >> id;
    cin.ignore();
    bool found = false;
    for (auto it = medicines.begin(); it != medicines.end(); it++) {
        if (it->getId() == id) {
            found = true;
            
            cout << "Warning: Removing this medicine will delete it from the inventory. Are you sure? (Y/N): ";
            char confirm;
            cin >> confirm;
            
            if (confirm == 'Y' || confirm == 'y') {
                medicines.erase(it);
                saveMedicinesToFile("medicines.csv", medicines);
                loader("Removing medicine");
                cout << "Medicine Removed Successfully!" << endl;
            } else {
                cout << "Operation cancelled." << endl;
            }
            cin.ignore(); // changed
            pauseWithMessage("Press any key to continue...");
            return;
        }
    }
    
    if (!found) {
        cout << "Error: Medicine ID not found!" << endl;
        pauseWithMessage("Press any key to go back...");
    }
}

void pharmacyManagement(vector<Medicine> &medicines) {
    int choice = 0;
    while (choice != 5) {
        system("cls");
        cout << "========================================" << endl;
        cout << "        PHARMACY & INVENTORY        " << endl;
        cout << "========================================" << endl;
        cout << "1.  View Medicine Stock" << endl;
        cout << "2.  Add New Medicine" << endl;
        cout << "3.  Update Medicine Details" << endl;
        cout << "4.  Remove Medicine" << endl;
        cout << "5.  Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        validChoice(choice);
        
        switch (choice) {
            case 1:
                viewMedicineStock(medicines);
                break;
            case 2:
                addNewMedicine(medicines);
                break;
            case 3:
                updateMedicineDetails(medicines);
                break;
            case 4:
                removeMedicine(medicines);
                break;
            case 5:
                loader("Returning to Main Menu");
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
                pauseWithMessage("Press Enter to retry");
        }
    }
}

class Staff {
    string id, name, role, shift, salary, joiningDate;
public:
    void setId(string id) { this->id = id; }
    string getId() { return id; }
    void setName(string name) { this->name = name; }
    string getName() { return name; }
    void setRole(string role) { this->role = role; }
    string getRole() { return role; }
    void setShift(string shift) { this->shift = shift; }
    string getShift() { return shift; }
    void setSalary(string salary) { this->salary = salary; }
    string getSalary() { return salary; }
    void setJoiningDate(string joiningDate) { this->joiningDate = joiningDate; }
    string getJoiningDate() { return joiningDate; }

    void viewStaffDetails() {
        cout << "\n----------------------------------------" << endl;
        cout << "Staff ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Role: " << role << endl;
        cout << "Shift: " << shift << endl;
        cout << "Salary: " << salary << "TK" << endl;
        cout << "Joining Date: " << joiningDate << endl;
        cout << "----------------------------------------" << endl;
    }
};

void saveStaffsToFile(string filename, vector<Staff> &staffs) {
    ofstream file(filename);
    for (Staff &staff : staffs) {
        file << staff.getId() << "," << staff.getName() << "," << staff.getRole() << "," << staff.getShift() << "," << staff.getSalary() << "," << staff.getJoiningDate() << endl;
    }
}

vector<Staff> loadStaffsFromFile(string filename) {
    vector<Staff> staffs;
    ifstream file(filename); // read
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, role, shift, salary, joiningDate;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, role, ',');
        getline(ss, shift, ',');
        getline(ss, salary, ',');
        getline(ss, joiningDate);

        Staff staff;
        staff.setId(id);
        staff.setName(name);
        staff.setRole(role);
        staff.setShift(shift);
        staff.setSalary(salary);
        staff.setJoiningDate(joiningDate);

        staffs.push_back(staff);
    }
    return staffs;
}

void staffManagement(vector<Staff> &staffs) {
    int choice = 0;
    while (choice != 6) {
        system("cls");
        cout << "========================================" << endl;
        cout << "          STAFF MANAGEMENT" << endl;
        cout << "========================================" << endl;
        cout << "1. Add New Staff Member" << endl;
        cout << "2. View Staff Details" << endl;
        cout << "3. Update Staff Information" << endl;
        cout << "4. Remove Staff Member" << endl;
        cout << "5. View All Staffs Details" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        validChoice(choice);
        switch (choice) {
            case 1: {
                cout << "----------------------------------------" << endl;
                cout << "           REGISTER NEW STAFF         " << endl;
                cout << "----------------------------------------" << endl;
                cout << "Enter Staff Details:" << endl << endl;
                Staff s;
                string id, name, role, shift, joiningDate;
                string salary;
                cout << "Enter Staff ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Role(Receptionist/Nurse/Cleaner/Electrician): ";
                cin >> role;
                cout << "Enter Shift(Day/Night): ";
                cin >> shift;
                cout << "Enter Salary: ";
                cin >> salary;
                cout << "Enter Joining Date (DD-MM-YYYY): ";
                cin.ignore();
                getline(cin, joiningDate);

                s.setId(id);
                s.setName(name);
                s.setRole(role);
                s.setShift(shift);
                s.setSalary(salary);
                s.setJoiningDate(joiningDate);

                staffs.push_back(s);
                saveStaffsToFile("staffs.csv", staffs);
                loader("Registering Staff");
                cout << "Staff Registered Successfully!" << endl;
                pauseWithMessage("Press Enter to go back to the menu...");
                break;
            }
            case 2: {
                cout << "----------------------------------------" << endl;
                cout << "             STAFF DETAILS            " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Staff ID: ";
                cin >> id;
                cin.ignore();
                bool found = false;
                loader("Searching");
                for (Staff &s : staffs) {
                    if (s.getId() == id) {
                        cout << "Staff Found" << endl;
                        s.viewStaffDetails();
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Staff ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 3: {
                cout << "----------------------------------------" << endl;
                cout << "           UPDATE STAFF INFO          " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Staff ID: ";
                cin >> id;
                bool found = false;
                for (Staff &s : staffs) {
                    if (s.getId() == id) {
                        string name, role, shift, joiningDate, salary;
                        cout << "Select Field to Update:" << endl;
                        cout << "1. Name" << endl;
                        cout << "2. Role" << endl;
                        cout << "3. Shift" << endl;
                        cout << "4. Salary" << endl;
                        cout << "5. Joining Date" << endl;
                        cout << "6. Cancel" << endl;
                        int update;
                        cout << "Enter Your Choice: ";
                        cin >> update;
                        validChoice(update);
                        switch (update) {
                            case 1:
                                cout << "Enter New Name: ";
                                getline(cin, name);
                                s.setName(name);
                                break;

                            case 2:
                                cout << "Enter New Role: ";
                                getline(cin, role);
                                s.setRole(role);
                                break;

                            case 3:
                                cout << "Enter New Shift(Day/Night)";
                                getline(cin, shift);
                                s.setShift(shift);
                                break;

                            case 4:
                                cout << "Enter New Salary";
                                getline(cin, salary);
                                s.setSalary(salary);
                                break;

                            case 5:
                                cout << "Enter New Joining Date (DD-MM-YYYY): ";
                                getline(cin, joiningDate);
                                s.setJoiningDate(joiningDate);
                                break;

                            case 6:
                                loader("Going Back");
                                break;
                            
                            default:
                                cout << "Invalid choice! Try again." << endl;
                                pauseWithMessage("Press Enter to retry");
                        }

                        if (update != 6) {
                            loader("Updating");
                            saveStaffsToFile("staffs.csv", staffs); // Save to file
                            cout << "Staff Information Updated Successfully!" << endl;
                        }
                        found = true;
                        break;
                    }
                }

                if (found == false) {
                    cout << "Error: Staff ID not found!" << endl;
                }
                
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 4: {
                cout << "----------------------------------------" << endl;
                cout << "         DELETE STAFF RECORD          " << endl;
                cout << "----------------------------------------" << endl;
                string id;
                cout << "Enter Staff ID to Remove: "; cin >> id;
                cin.ignore();
                bool found = false;
                for (auto it = staffs.begin(); it != staffs.end(); it++) {
                    if (it->getId() == id) {
                        staffs.erase(it);
                        saveStaffsToFile("staffs.csv", staffs); // Save to file
                        loader("Deleting Staff Data");
                        cout << "Staff Record Deleted Successfully!" << endl;
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    cout << "Error: Staff ID not found!" << endl;
                }
                pauseWithMessage("Press Enter to continue...");
                break;
            }
            case 5: {
                cout << "----------------------------------------" << endl;
                cout << "         VIEW ALL STAFFS DETAILS        " << endl;
                cout << "----------------------------------------" << endl;
                string masterKey;
                cout << "Enter MASTER KEY: ";
                getline(cin, masterKey);
                if (masterKey == MASTER_KEY) {
                    cout << "Verification Successful" << endl;
                    loader("Fetching Data");
                    for (Staff &s : staffs) {
                        s.viewStaffDetails();
                    }

                    if (staffs.empty()) {
                        cout << "Error: Staff Records Not Found" << endl;
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

void dashboard(vector<User> &users) {
    vector<Patient> patients = loadPatientsFromFile("patients.csv");
    vector<Doctor> doctors = loadDoctorsFromFile("doctors.csv");
    vector<Appointment> appointments = loadAppointmentsFromFile("appointments.csv");
    vector<Medicine> medicines= loadMedicinesFromFile("medicines.csv");
    vector<Staff> staffs = loadStaffsFromFile("staffs.csv");

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
        cout << "5. Admin Management" << endl;
        cout << "6. Staff Management" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        validChoice(choice);
        switch (choice) {
            case 1:
                patientManagement(patients);
                break;
            case 2:
                doctorManagement(doctors);
                break;
            case 3:
                appointmentManagement(appointments, patients, doctors);
                break;
            case 4:
                pharmacyManagement(medicines);
                break;
            case 5:
                adminManagement(users);
                break;
            case 6:
                staffManagement(staffs);
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
        validChoice(choice);
        switch (choice) {
            case 1:
                registerUser(users);
                break;
            case 2:
                if (login(users)) { // true / false
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
