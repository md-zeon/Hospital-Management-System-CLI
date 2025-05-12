# Hospital Management CLI

```
Hospital Management CLI

========================================
        HOSPITAL MANAGEMENT SYSTEM
========================================

🛡️ LOGIN 
----------------------------------------
Username: ________
Password: ________

----------------------------------------
Invalid credentials! Try again. (3 attempts max)
----------------------------------------

✅ Login Successful!
Press any key to continue...



========================================
        🏥 MAIN MENU
========================================
1️⃣  Patient Management
2️⃣  Doctor Management
3️⃣  Appointment Management
4️⃣  Billing & Payments
5️⃣  Medical Records
6️⃣  Pharmacy & Inventory
7️⃣  Staff & Admin Management
8️⃣  Reports & Statistics
9️⃣  Logout

Enter your choice: _


========================================
        📂 PATIENT MANAGEMENT
========================================
1️⃣  Register New Patient
2️⃣  View Patient Details
3️⃣  Update Patient Info
4️⃣  Delete Patient Record
5️⃣  Back to Main Menu

Enter your choice: _

1️⃣  Register New Patient
----------------------------------------
        🆕 REGISTER NEW PATIENT
----------------------------------------
Enter Patient Details:

Patient ID: P1001
Full Name: John Doe
Age: 30
Gender (M/F): M
Blood Group: O+
Address: 123 Main St, City
Contact No.: +1234567890
Emergency Contact: +0987654321
Disease/Symptoms: Fever, Cough
Doctor Assigned: Dr. Smith

✅ Patient Registered Successfully!
Press any key to continue...


2️⃣  View Patient Details
----------------------------------------
        👤 PATIENT DETAILS
----------------------------------------
Enter Patient ID: _ P1001

----------------------------------------
Patient ID: P1001
Full Name: John Doe
Age: 30
Gender: Male
Blood Group: O+
Address: 123 Main St, City
Contact No.: +1234567890
Emergency Contact: +0987654321
Disease/Symptoms: Fever, Cough
Doctor Assigned: Dr. Smith
Last Visit: 2025-02-20

Press any key to continue...

If patient ID is not found:
⚠️ Error: Patient ID not found!
Press any key to go back...


3️⃣  Update Patient Info
----------------------------------------
        ✏️ UPDATE PATIENT INFO
----------------------------------------
Enter Patient ID: _ P1001

----------------------------------------
Patient ID: P1001
Current Name: John Doe
Current Age: 30
Current Address: 123 Main St, City

Enter new details (leave blank to keep unchanged):
New Name: John Doe
New Age: 31
New Address: 456 Maple Ave, City
New Contact No.: +1234567899

✅ Patient Information Updated Successfully!
Press any key to continue...

If patient ID is not found:
⚠️ Error: Patient ID not found!
Press any key to go back...


4️⃣  Delete Patient Record
----------------------------------------
        ❌ DELETE PATIENT RECORD
----------------------------------------
Enter Patient ID to Delete: _ P1001

⚠️ Warning: This action cannot be undone!
Are you sure you want to delete this patient? (Y/N): _ Y

✅ Patient Record Deleted Successfully!
Press any key to continue...

If patient ID is not found:
⚠️ Error: Patient ID not found!
Press any key to go back...


5️⃣ Back to Main Menu
Returning to Main Menu...


========================================
        👨‍⚕️ DOCTOR MANAGEMENT
========================================
1️⃣  Add New Doctor
2️⃣  View Doctor List
3️⃣  Assign Doctor to Patient
4️⃣  Remove Doctor
5️⃣  Back to Main Menu

Enter your choice: _

1️⃣  Add New Doctor
----------------------------------------
        🆕 ADD NEW DOCTOR
----------------------------------------
Enter Doctor Details:

Doctor ID: D101
Full Name: Dr. Smith
Specialization: Cardiologist
Experience (Years): 10
Availability (Yes/No): Yes
Contact No.: +1234567890

✅ Doctor Added Successfully!
Press any key to continue...


2️⃣  View Doctor List
----------------------------------------
        👨‍⚕️ LIST OF DOCTORS
----------------------------------------
ID     Name        Specialization   Experience  Available
--------------------------------------------------------
D101   Dr. Smith    Cardiologist      10 Yrs       Yes
D102   Dr. Allen    Neurologist       8 Yrs        No
D103   Dr. Taylor   Dermatologist     6 Yrs        Yes
D104   Dr. Evans    Orthopedic        12 Yrs       Yes

Press any key to continue...


3️⃣  Assign Doctor to Patient
----------------------------------------
        🔄 ASSIGN DOCTOR TO PATIENT
----------------------------------------
Enter Patient ID: _ P1001
Current Doctor Assigned: Dr. Allen

Available Doctors:
----------------------------------------
ID     Name        Specialization   
----------------------------------------
D101   Dr. Smith    Cardiologist    
D103   Dr. Taylor   Dermatologist  
D104   Dr. Evans    Orthopedic     

Enter Doctor ID to Assign: _ D103

✅ Doctor Dr. Taylor Assigned to Patient P1001 Successfully!
Press any key to continue...


If patient ID is not found:

⚠️ Error: Patient ID not found!
Press any key to go back...


If Doctor ID is not found:
⚠️ Error: Doctor ID is invalid or unavailable!
Press any key to go back...


4️⃣  Remove Doctor
----------------------------------------
        ❌ REMOVE DOCTOR
----------------------------------------
Enter Doctor ID to Remove: _ D102

⚠️ Warning: Removing this doctor will unassign them from all patients.
Are you sure you want to proceed? (Y/N): _ Y

✅ Doctor Removed Successfully!
Press any key to continue...


If Doctor ID not found:

⚠️ Error: Doctor ID not found!
Press any key to go back...


5️⃣ Back to Main Menu

Returning to Main Menu...

========================================
        📅 APPOINTMENT MANAGEMENT
========================================
1️⃣  Schedule New Appointment
2️⃣  View Upcoming Appointments
3️⃣  Cancel Appointment
4️⃣  Back to Main Menu

Enter your choice: _

1️⃣  Schedule New Appointment
----------------------------------------
        🆕 SCHEDULE NEW APPOINTMENT
----------------------------------------
Enter Patient ID: _ P1001
Enter Doctor ID: _ D101

Available Slots for Dr. Smith:
----------------------------------------
1️⃣  10:00 AM - 10:30 AM
2️⃣  11:00 AM - 11:30 AM
3️⃣  02:00 PM - 02:30 PM

Select Slot (1/2/3): _ 2

✅ Appointment Scheduled Successfully!
----------------------------------------
🆔 Appointment ID: A2001
👤 Patient: John Doe (P1001)
👨‍⚕️ Doctor: Dr. Smith (D101)
📅 Date: 2025-02-26
⏰ Time: 11:00 AM - 11:30 AM
----------------------------------------

Press any key to continue...

If patient or doctor ID is invalid:

⚠️ Error: Invalid Patient ID or Doctor ID!
Press any key to go back...


If selected time slot is unavailable:

⚠️ Error: Selected time slot is unavailable!
Press any key to go back...


2️⃣  View Upcoming Appointments
----------------------------------------
        📅 UPCOMING APPOINTMENTS
----------------------------------------
Appointment ID  Patient      Doctor        Date       Time      
--------------------------------------------------------------
A2001           John Doe     Dr. Smith     2025-02-26 11:00 AM  
A2002           Alex Brown   Dr. Taylor    2025-02-26 02:00 PM  
A2003           Emma Davis   Dr. Evans     2025-02-27 10:30 AM  

Press any key to continue...

If no upcoming appointments:
⚠️ No upcoming appointments found!
Press any key to go back...


3️⃣  Cancel Appointment
----------------------------------------
        ❌ CANCEL APPOINTMENT
----------------------------------------
Enter Appointment ID: _ A2001

⚠️ Warning: Are you sure you want to cancel this appointment? (Y/N): _ Y

✅ Appointment Cancelled Successfully!
Press any key to continue...

If appointment ID is not found:

⚠️ Error: Appointment ID not found!
Press any key to go back...


4️⃣ Back to Main Menu

Returning to Main Menu...

========================================
        💳 BILLING & PAYMENTS
========================================
1️⃣  Generate Bill
2️⃣  View Payment History
3️⃣  Process Payment
4️⃣  Back to Main Menu

Enter your choice: _

1️⃣  Generate Bill
----------------------------------------
        🧾 GENERATE BILL
----------------------------------------
Enter Patient ID: _ P1001

Fetching patient details...

----------------------------------------
🆔 Patient ID: P1001
👤 Name: John Doe
🩺 Doctor Assigned: Dr. Smith
----------------------------------------

Services Availed:
----------------------------------------
1. Consultation Fee     - $50
2. X-ray Scan          - $40
3. Blood Test          - $30

Total Amount: $120

✅ Bill Generated Successfully!
🧾 Bill ID: B3001
📅 Date: 2025-02-26
💰 Amount Due: $120

Press any key to continue...

If patient ID is invalid:
⚠️ Error: Patient ID not found!
Press any key to go back...


2️⃣  View Payment History
----------------------------------------
        📜 PAYMENT HISTORY
----------------------------------------
Enter Patient ID: _ P1001

Fetching payment records...

----------------------------------------
🆔 Patient ID: P1001
👤 Name: John Doe
----------------------------------------

Bill ID      Date        Amount   Status  
----------------------------------------
B2001    2025-02-10    $150      Paid    
B2002    2025-02-15    $80       Paid    
B3001    2025-02-26    $120      Pending  

Press any key to continue...

If no payment history found:
⚠️ No payment history available for this patient.
Press any key to go back...


3️⃣  Process Payment
----------------------------------------
        💵 PROCESS PAYMENT
----------------------------------------
Enter Bill ID: _ B3001

Fetching bill details...

----------------------------------------
🧾 Bill ID: B3001
👤 Patient: John Doe (P1001)
💰 Amount Due: $120
----------------------------------------

Select Payment Method:
1️⃣  Cash
2️⃣  Credit/Debit Card
3️⃣  Online Payment

Enter choice: _ 2

Processing payment...
✅ Payment of $120 completed successfully via Credit/Debit Card!

🆔 Transaction ID: T5001
📅 Date: 2025-02-26

Press any key to continue...


If bill ID is not found:
⚠️ Error: Bill ID not found or already paid!
Press any key to go back...


4️⃣ Back to Main Menu

Returning to Main Menu...



========================================
        📜 MEDICAL RECORDS
========================================
1️⃣  Add Medical Record
2️⃣  View Patient History
3️⃣  Update Medical Record
4️⃣  Back to Main Menu

Enter your choice: _

1️⃣  Add Medical Record
----------------------------------------
        📝 ADD MEDICAL RECORD
----------------------------------------
Enter Patient ID: _ P1001

Fetching patient details...

----------------------------------------
🆔 Patient ID: P1001
👤 Name: John Doe
🩺 Doctor Assigned: Dr. Smith
----------------------------------------

Enter Diagnosis: _ Pneumonia
Enter Medications Prescribed: _ Azithromycin, Cough Syrup
Enter Treatment Plan: _ 7 days bed rest, Hydration, Antibiotics

✅ Medical Record Added Successfully!
🆔 Record ID: MR4001
📅 Date: 2025-02-26

Press any key to continue...

If patient ID is invalid:
⚠️ Error: Patient ID not found!
Press any key to go back...


2️⃣  View Patient History
----------------------------------------
        📖 PATIENT MEDICAL HISTORY
----------------------------------------
Enter Patient ID: _ P1001

Fetching medical history...

----------------------------------------
🆔 Patient ID: P1001
👤 Name: John Doe
----------------------------------------

Record ID   Date        Diagnosis     Doctor        Status
----------------------------------------------------------
MR3001    2025-02-10    Flu          Dr. Taylor    Recovered
MR3502    2025-02-20    Fever        Dr. Evans     Ongoing  
MR4001    2025-02-26    Pneumonia    Dr. Smith     Ongoing  

Press any key to continue...


If no history found:
⚠️ No medical history available for this patient.
Press any key to go back...


3️⃣  Update Medical Record
----------------------------------------
        ✏️ UPDATE MEDICAL RECORD
----------------------------------------
Enter Record ID: _ MR4001

Fetching record details...

----------------------------------------
🆔 Record ID: MR4001
📅 Date: 2025-02-26
👤 Patient: John Doe (P1001)
🩺 Doctor: Dr. Smith
📝 Diagnosis: Pneumonia
💊 Medications: Azithromycin, Cough Syrup
💡 Treatment: 7 days bed rest, Hydration, Antibiotics
----------------------------------------

Select Field to Update:
1️⃣  Diagnosis
2️⃣  Medications
3️⃣  Treatment Plan
4️⃣  Mark as Recovered
5️⃣  Cancel

Enter choice: _ 4

✅ Medical Record Updated Successfully! Status: **Recovered**
Press any key to continue...


If record ID is not found:
⚠️ Error: Record ID not found!
Press any key to go back...


4️⃣ Back to Main Menu

Returning to Main Menu...


========================================
        💊 PHARMACY & INVENTORY
========================================
1️⃣  View Medicine Stock
2️⃣  Add New Medicine
3️⃣  Update Medicine Details
4️⃣  Remove Medicine
5️⃣  Back to Main Menu

Enter your choice: _

1️⃣  View Medicine Stock
----------------------------------------
        📋 MEDICINE STOCK
----------------------------------------
Fetching inventory details...

----------------------------------------
ID      Name              Quantity   Price   Expiry Date
--------------------------------------------------------
M1001   Paracetamol       100        $5      2025-12-31
M1002   Azithromycin      50         $15     2025-09-30
M1003   Cough Syrup      200        $8      2026-02-15
M1004   Ibuprofen         75         $10     2025-08-20

Press any key to continue...

If no stock available:

⚠️ No medicine in stock!
Press any key to go back...


2️⃣  Add New Medicine
----------------------------------------
        ➕ ADD NEW MEDICINE
----------------------------------------
Enter Medicine ID: _ M1005
Enter Medicine Name: _ Amoxicillin
Enter Quantity: _ 120
Enter Price: _ 20
Enter Expiry Date (YYYY-MM-DD): _ 2026-05-30

✅ Medicine Added Successfully!
🆔 Medicine ID: M1005
💊 Name: Amoxicillin
📦 Quantity: 120
💵 Price: $20
📅 Expiry Date: 2026-05-30

Press any key to continue...


If medicine ID already exists:
⚠️ Error: Medicine ID already exists!
Press any key to go back...


3️⃣  Update Medicine Details
----------------------------------------
        ✏️ UPDATE MEDICINE DETAILS
----------------------------------------
Enter Medicine ID: _ M1003

Fetching medicine details...

----------------------------------------
🆔 Medicine ID: M1003
💊 Name: Cough Syrup
📦 Quantity: 200
💵 Price: $8
📅 Expiry Date: 2026-02-15
----------------------------------------

Select Field to Update:
1️⃣  Name
2️⃣  Quantity
3️⃣  Price
4️⃣  Expiry Date
5️⃣  Cancel

Enter choice: _ 2

Enter New Quantity: _ 180

✅ Medicine Details Updated Successfully!
Press any key to continue...

If medicine ID is invalid:
⚠️ Error: Medicine ID not found!
Press any key to go back...


4️⃣  Remove Medicine
----------------------------------------
        ❌ REMOVE MEDICINE
----------------------------------------
Enter Medicine ID to Remove: _ M1002

⚠️ Warning: Removing this medicine will delete it from the inventory. Are you sure? (Y/N): _ Y

✅ Medicine Removed Successfully!
Press any key to continue...

If medicine ID is not found:
⚠️ Error: Medicine ID not found!
Press any key to go back...


5️⃣ Back to Main Menu

Returning to Main Menu...


========================================
        👨‍💼 STAFF MANAGEMENT
========================================
1️⃣  Add New Staff Member
2️⃣  View Staff Details
3️⃣  Update Staff Information
4️⃣  Remove Staff Member
5️⃣  Back to Main Menu

Enter your choice: _


1️⃣  Add New Staff Member
----------------------------------------
        ➕ ADD NEW STAFF MEMBER
----------------------------------------
Enter Staff ID: _ S1001
Enter Name: _ Alice Johnson
Enter Role (Doctor/Receptionist/Nurse/Admin): _ Doctor
Enter Department: _ Cardiology
Enter Salary: _ $5000
Enter Joining Date (YYYY-MM-DD): _ 2025-01-15

✅ Staff Member Added Successfully!
🆔 Staff ID: S1001
👤 Name: Alice Johnson
💼 Role: Doctor
🏥 Department: Cardiology
💵 Salary: $5000
📅 Joining Date: 2025-01-15

Press any key to continue...


If staff ID already exists:
⚠️ Error: Staff ID already exists!
Press any key to go back...


2️⃣  View Staff Details
----------------------------------------
        👥 VIEW STAFF DETAILS
----------------------------------------
Enter Staff ID: _ S1001

Fetching staff details...

----------------------------------------
🆔 Staff ID: S1001
👤 Name: Alice Johnson
💼 Role: Doctor
🏥 Department: Cardiology
💵 Salary: $5000
📅 Joining Date: 2025-01-15
----------------------------------------

Press any key to continue...

If staff ID is invalid:
⚠️ Error: Staff ID not found!
Press any key to go back...


3️⃣  Update Staff Information
----------------------------------------
        ✏️ UPDATE STAFF INFORMATION
----------------------------------------
Enter Staff ID: _ S1001

Fetching staff details...

----------------------------------------
🆔 Staff ID: S1001
👤 Name: Alice Johnson
💼 Role: Doctor
🏥 Department: Cardiology
💵 Salary: $5000
📅 Joining Date: 2025-01-15
----------------------------------------

Select Field to Update:
1️⃣  Name
2️⃣  Role
3️⃣  Department
4️⃣  Salary
5️⃣  Cancel

Enter choice: _ 3

Enter New Department: _ Neurology

✅ Staff Information Updated Successfully!
Press any key to continue...

If staff ID is invalid:
⚠️ Error: Staff ID not found!
Press any key to go back...



4️⃣  Remove Staff Member
----------------------------------------
        ❌ REMOVE STAFF MEMBER
----------------------------------------
Enter Staff ID to Remove: _ S1001

⚠️ Warning: Removing this staff member will delete their record permanently. Are you sure? (Y/N): _ Y

✅ Staff Member Removed Successfully!
Press any key to continue...


If staff ID is not found:
⚠️ Error: Staff ID not found!
Press any key to go back...


5️⃣ Back to Main Menu

Returning to Main Menu...


========================================
        📊 REPORTS & STATISTICS
========================================
1️⃣  Generate Patient Reports
2️⃣  Doctor & Staff Reports
3️⃣  Financial Statistics
4️⃣  Hospital Performance Analysis
5️⃣  Back to Main Menu

Enter your choice: _

1️⃣  Generate Patient Reports
----------------------------------------
        📑 GENERATE PATIENT REPORT
----------------------------------------
Enter Report Type:
1️⃣  All Patients
2️⃣  Patients by Department
3️⃣  Patients by Diagnosis
4️⃣  Patients by Treatment Status

Enter choice: _ 2

Enter Department Name: _ Cardiology

Generating report...

----------------------------------------
🆔 Report ID: R1001
📝 Department: Cardiology
📅 Date: 2025-02-26

Patient ID    Name            Age    Diagnosis      Treatment Status
---------------------------------------------------------------------
P1001         John Doe        45     Heart Disease   Ongoing
P1002         Jane Smith      50     Hypertension    Recovered
P1003         Mark Johnson    60     Arrhythmia      Ongoing

Press any key to continue...

If invalid department:
⚠️ Error: Department not found!
Press any key to go back...


2️⃣  Doctor & Staff Reports
----------------------------------------
        📑 DOCTOR & STAFF REPORTS
----------------------------------------
Enter Report Type:
1️⃣  All Doctors
2️⃣  Doctors by Department
3️⃣  All Staff Members
4️⃣  Staff by Role

Enter choice: _ 2

Enter Department Name: _ Neurology

Generating report...

----------------------------------------
🆔 Report ID: R2001
📝 Department: Neurology
📅 Date: 2025-02-26

Staff ID    Name            Role         Salary
--------------------------------------------------
S1001       Alice Johnson   Doctor       $5000
S1002       Bob Williams    Nurse        $3000

Press any key to continue...


If no doctors in department:
⚠️ No doctors found in this department!
Press any key to go back...


3️⃣  Financial Statistics
----------------------------------------
        💰 FINANCIAL STATISTICS
----------------------------------------
Enter Report Type:
1️⃣  Total Revenue
2️⃣  Expenses Report
3️⃣  Profit/Loss Analysis

Enter choice: _ 1

Generating report...

----------------------------------------
🆔 Report ID: R3001
📝 Report Type: Total Revenue
📅 Date: 2025-02-26

Total Revenue: $150,000
Revenue from Patient Payments: $100,000
Revenue from Services: $50,000

Press any key to continue...

If no data available:
⚠️ Error: No financial data available for this period!
Press any key to go back...


4️⃣  Hospital Performance Analysis
----------------------------------------
        🏥 HOSPITAL PERFORMANCE
----------------------------------------
Enter Report Type:
1️⃣  Patient Satisfaction
2️⃣  Treatment Effectiveness
3️⃣  Staff Efficiency

Enter choice: _ 2

Generating report...

----------------------------------------
🆔 Report ID: R4001
📝 Report Type: Treatment Effectiveness
📅 Date: 2025-02-26

Treatment Type    Success Rate    Ongoing Treatments    Failed Treatments
----------------------------------------------------------------------
Cardiology        90%             10                    2
Neurology         85%             12                    3
General Surgery   92%             8                     1

Press any key to continue...

If no data available:
⚠️ Error: No performance data available for this period!
Press any key to go back...


5️⃣ Back to Main Menu

Returning to Main Menu...


========================================
        🚪 LOGOUT
========================================
Are you sure you want to logout? (Y/N): _ Y

✅ Successfully Logged Out!
```
