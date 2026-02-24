#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// ================= STUDENT CLASS =================
class Student {
public:
    string indexNumber;
    string name;

    Student(string idx = "", string nm = "") {
        indexNumber = idx;
        name = nm;
    }
};

// ================= ATTENDANCE SESSION CLASS =================
class AttendanceSession {
public:
    string courseCode;
    string date;
    string startTime;
    int duration;

    void createSession() {
        cout << "Enter Course Code: ";
        cin >> courseCode;
        cout << "Enter Date (YYYY_MM_DD): ";
        cin >> date;
        cout << "Enter Start Time: ";
        cin >> startTime;
        cout << "Enter Duration (minutes): ";
        cin >> duration;
    }
};

// ================= FILE FUNCTIONS =================
void saveStudentToFile(Student s) {
    ofstream file("students.txt", ios::app);
    if (file.is_open()) {
        file << s.indexNumber << "," << s.name << endl;
        file.close();
    }
}

vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string idx, name;

        getline(ss, idx, ',');
        getline(ss, name);

        students.push_back(Student(idx, name));
    }

    file.close();
    return students;
}

// ================= STUDENT MANAGEMENT =================
void registerStudent() {
    string idx, name;

    cout << "Enter Index Number: ";
    cin >> idx;

    cout << "Enter Full Name: ";
    cin.ignore();
    getline(cin, name);

    Student s(idx, name);
    saveStudentToFile(s);

    cout << "Student Registered Successfully!\n";
}

void viewStudents() {
    vector<Student> students = loadStudents();

    cout << "\n--- Registered Students ---\n";
    for (size_t i = 0; i < students.size(); i++) {
        cout << students[i].indexNumber << " - "
             << students[i].name << endl;
    }
}

void searchStudent() {
    string searchIdx;
    cout << "Enter Index Number to Search: ";
    cin >> searchIdx;

    vector<Student> students = loadStudents();
    bool found = false;

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].indexNumber == searchIdx) {
            cout << "Student Found: "
                 << students[i].name << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student Not Found.\n";
    }
}

// ================= ATTENDANCE + CSV =================
void createAttendance() {
    AttendanceSession session;
    session.createSession();

    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No students registered!\n";
        return;
    }

    string filename = "session_" +
                      session.courseCode + "_" +
                      session.date + ".csv";

    ofstream file(filename.c_str());

    file << "Index Number,Name,Status\n";

    int present = 0, absent = 0, late = 0;
    int choice;
    string status;

    for (size_t i = 0; i < students.size(); i++) {

        cout << "\nMark attendance for "
             << students[i].name << endl;
        cout << "1. Present\n2. Absent\n3. Late\nChoose: ";
        cin >> choice;

        if (choice == 1) {
            status = "Present";
            present++;
        }
        else if (choice == 2) {
            status = "Absent";
            absent++;
        }
        else {
            status = "Late";
            late++;
        }

        file << students[i].indexNumber << ","
             << students[i].name << ","
             << status << endl;
    }

    file.close();

    cout << "\nAttendance Saved to " << filename << endl;

    cout << "\n--- Attendance Summary ---\n";
    cout << "Present: " << present << endl;
    cout << "Absent : " << absent << endl;
    cout << "Late   : " << late << endl;
}

// ================= MAIN =================
int main() {
    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Create Attendance Session\n";
        cout << "5. Exit\n";
        cout << "Choose Option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            createAttendance();
            break;
        case 5:
            cout << "Exiting Program...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}