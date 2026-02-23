#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// ================= STUDENT =================
class Student {
public:
    string name;
    string index;

    Student(string n, string i) {
        name = n;
        index = i;
    }

    void display() {
        cout << name << " (" << index << ")" << endl;
    }
};

vector<Student> students;

// ================= SESSION =================
class AttendanceSession {
public:
    string course;
    string date;
    string time;
    int duration;

    vector<string> attendanceStatus; // P, A, L

    AttendanceSession(string c, string d, string t, int dur) {
        course = c;
        date = d;
        time = t;
        duration = dur;

        attendanceStatus.resize(students.size(), "Not Marked");
    }

    void display() {
        cout << "Course: " << course
             << " | Date: " << date
             << " | Time: " << time << endl;
    }
};

vector<AttendanceSession> sessions;

// ================= STUDENT FUNCTIONS =================
void addStudent() {
    string name, index;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter index: ";
    cin >> index;

    students.push_back(Student(name, index));
    cout << "Student added!\n";
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students.\n";
        return;
    }

    for (int i = 0; i < students.size(); i++) {
        cout << i + 1 << ". ";
        students[i].display();
    }
}

// ================= SESSION =================
void createSession() {
    if (students.empty()) {
        cout << "Add students first!\n";
        return;
    }

    string course, date, time;
    int duration;

    cout << "Course code: ";
    cin >> course;

    cout << "Date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Time (HH:MM): ";
    cin >> time;

    cout << "Duration: ";
    cin >> duration;

    sessions.push_back(AttendanceSession(course, date, time, duration));
    cout << "Session created!\n";
}

void viewSessions() {
    if (sessions.empty()) {
        cout << "No sessions.\n";
        return;
    }

    for (int i = 0; i < sessions.size(); i++) {
        cout << i + 1 << ". ";
        sessions[i].display();
    }
}

// ================= ATTENDANCE =================
void markAttendance() {
    if (sessions.empty()) {
        cout << "No sessions available.\n";
        return;
    }

    viewSessions();
    int s;
    cout << "Select session: ";
    cin >> s;

    if (s < 1 || s > sessions.size()) {
        cout << "Invalid session.\n";
        return;
    }

    AttendanceSession &session = sessions[s - 1];

    session.attendanceStatus.resize(students.size());

    cout << "\nMark Attendance (P=Present, A=Absent, L=Late)\n";

    for (int i = 0; i < students.size(); i++) {
        cout << students[i].name << ": ";
        string status;
        cin >> status;

        if (status != "P" && status != "A" && status != "L") {
            cout << "Invalid input, set to Absent.\n";
            status = "A";
        }

        session.attendanceStatus[i] = status;
    }

    cout << "Attendance marked!\n";
}

// ================= REPORT =================
void viewReport() {
    if (sessions.empty()) {
        cout << "No sessions.\n";
        return;
    }

    viewSessions();
    int s;
    cout << "Select session: ";
    cin >> s;

    if (s < 1 || s > sessions.size()) {
        cout << "Invalid.\n";
        return;
    }

    AttendanceSession &session = sessions[s - 1];

    int present = 0, absent = 0, late = 0;

    cout << "\n--- Attendance Report ---\n";

    for (int i = 0; i < students.size(); i++) {
        cout << students[i].name << " - " << session.attendanceStatus[i] << endl;

        if (session.attendanceStatus[i] == "P") present++;
        else if (session.attendanceStatus[i] == "A") absent++;
        else if (session.attendanceStatus[i] == "L") late++;
    }

    cout << "\nSummary:\n";
    cout << "Present: " << present << endl;
    cout << "Absent: " << absent << endl;
    cout << "Late: " << late << endl;
}

// ================= FILE HANDLING =================
void saveStudents() {
    ofstream file("students.txt");
    for (auto &s : students) {
        file << s.name << "," << s.index << endl;
    }
    file.close();
}

void loadStudents() {
    ifstream file("students.txt");
    string line;

    while (getline(file, line)) {
        int comma = line.find(",");
        string name = line.substr(0, comma);
        string index = line.substr(comma + 1);
        students.push_back(Student(name, index));
    }
}

void saveSessions() {
    ofstream file("sessions.txt");

    for (auto &s : sessions) {
        file << s.course << "," << s.date << "," << s.time << "," << s.duration;

        for (auto &a : s.attendanceStatus) {
            file << "," << a;
        }

        file << endl;
    }

    file.close();
}

void loadSessions() {
    ifstream file("sessions.txt");
    string line;

    while (getline(file, line)) {
        vector<string> parts;
        string temp = "";

        for (char c : line) {
            if (c == ',') {
                parts.push_back(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        parts.push_back(temp);

        AttendanceSession s(parts[0], parts[1], parts[2], stoi(parts[3]));

        for (int i = 4; i < parts.size(); i++) {
            s.attendanceStatus.push_back(parts[i]);
        }

        sessions.push_back(s);
    }
}

// ================= MENU =================
int main() {
    loadStudents();
    loadSessions();

    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Create Session\n";
        cout << "4. View Sessions\n";
        cout << "5. Mark Attendance\n";
        cout << "6. View Report\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            saveStudents();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            createSession();
            saveSessions();
            break;
        case 4:
            viewSessions();
            break;
        case 5:
            markAttendance();
            saveSessions();
            break;
        case 6:
            viewReport();
            break;
        case 7:
            saveStudents();
            saveSessions();
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid!\n";
        }

    } while (choice != 7);

    return 0;
}
