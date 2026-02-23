#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* =========================
   STUDENT CLASS
   ========================= */
class Student {
public:
    string indexNumber;
    string fullName;
    string programme;

    void inputStudent() {
        cout << "Enter Index Number: ";
        cin >> indexNumber;
        cin.ignore();

        cout << "Enter Full Name: ";
        getline(cin, fullName);

        cout << "Enter Programme: ";
        getline(cin, programme);
    }

    void displayStudent(int count) const {
        cout << count << ". "
             << indexNumber << " - "
             << fullName << " - "
             << programme << endl;
    }
};

/* =========================
   ATTENDANCE SESSION CLASS
   ========================= */
class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;

    vector<string> attendanceStatus;

    void inputSession() {
        cout << "Enter Course Code: ";
        cin >> courseCode;

        cout << "Enter Date (YYYY-MM-DD): ";
        cin >> date;

        cout << "Enter Start Time (HH:MM): ";
        cin >> startTime;

        cout << "Enter Duration (hours): ";
        cin >> duration;
    }

    void initializeAttendance(int numberOfStudents) {
        attendanceStatus.resize(numberOfStudents, "Absent");
    }
};

/* =========================
   FILE FUNCTIONS
   ========================= */
void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt");
    for (const auto& s : students) {
        file << s.indexNumber << ","
             << s.fullName << ","
             << s.programme << endl;
    }
    file.close();
}

void loadStudents(vector<Student>& students) {
    ifstream file("students.txt");
    if (!file.is_open()) return;

    Student s;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, s.indexNumber, ',');
        getline(ss, s.fullName, ',');
        getline(ss, s.programme, ',');
        students.push_back(s);
    }

    file.close();
}

/* =========================
   MENU
   ========================= */
void showMenu() {
    cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
    cout << "1. Register Student\n";
    cout << "2. View Students\n";
    cout << "3. Create Attendance Session\n";
    cout << "4. Mark Attendance\n";
    cout << "5. View Attendance Report\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

/* =========================
   MAIN FUNCTION
   ========================= */
int main() {

    vector<Student> students;
    vector<AttendanceSession> sessions;

    loadStudents(students);

    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {

        case 1: {
            Student s;
            s.inputStudent();
            students.push_back(s);
            cout << "Student registered successfully!\n";
            break;
        }

        case 2:
            if (students.empty()) {
                cout << "No students registered yet.\n";
            } else {
                for (size_t i = 0; i < students.size(); i++) {
                    students[i].displayStudent(i + 1);
                }
            }
            break;

        case 3: {
            if (students.empty()) {
                cout << "Register students first.\n";
                break;
            }

            AttendanceSession s;
            s.inputSession();
            s.initializeAttendance(students.size());
            sessions.push_back(s);
            cout << "Attendance session created successfully!\n";
            break;
        }

        case 4:
            if (sessions.empty() || students.empty()) {
                cout << "No sessions or students available.\n";
                break;
            }

            cout << "Select Session:\n";
            for (size_t i = 0; i < sessions.size(); i++) {
                cout << i + 1 << ". "
                     << sessions[i].courseCode
                     << " - "
                     << sessions[i].date << endl;
            }

            int sessionChoice;
            cin >> sessionChoice;
            sessionChoice--;

            for (size_t i = 0; i < students.size(); i++) {
                cout << "Mark attendance for "
                     << students[i].fullName << endl;
                cout << "1. Present  2. Late  3. Absent: ";

                int statusChoice;
                cin >> statusChoice;

                if (statusChoice == 1)
                    sessions[sessionChoice].attendanceStatus[i] = "Present";
                else if (statusChoice == 2)
                    sessions[sessionChoice].attendanceStatus[i] = "Late";
                else
                    sessions[sessionChoice].attendanceStatus[i] = "Absent";
            }

            cout << "Attendance marked successfully.\n";
            break;

        case 5:
            if (sessions.empty()) {
                cout << "No sessions available.\n";
                break;
            }

            cout << "Select Session:\n";
            for (size_t i = 0; i < sessions.size(); i++) {
                cout << i + 1 << ". "
                     << sessions[i].courseCode
                     << " - "
                     << sessions[i].date << endl;
            }

            cin >> sessionChoice;
            sessionChoice--;

            int present = 0, late = 0, absent = 0;

            for (size_t i = 0; i < students.size(); i++) {
                cout << students[i].fullName << " - "
                     << sessions[sessionChoice].attendanceStatus[i] << endl;

                if (sessions[sessionChoice].attendanceStatus[i] == "Present")
                    present++;
                else if (sessions[sessionChoice].attendanceStatus[i] == "Late")
                    late++;
                else
                    absent++;
            }

            cout << "\nSummary:\n";
            cout << "Present: " << present << endl;
            cout << "Late: " << late << endl;
            cout << "Absent: " << absent << endl;
            break;

        case 6:
            saveStudents(students);
            cout << "Data saved. Exiting...\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}