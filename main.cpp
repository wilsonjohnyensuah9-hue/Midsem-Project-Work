#include <iostream>
#include <vector>
using namespace std;

class Student {
private:
    string name;
    string indexNumber;

public:
    Student(string n, string i) {
        name = n;
        indexNumber = i;
    }

    string getName() {
        return name;
    }

    string getIndex() {
        return indexNumber;
    }

    void display() {
        cout << "Name: " << name << " | Index: " << indexNumber << endl;
    }
};

vector<Student> students;

void registerStudent() {
    string name, index;

    cout << "Enter student name: ";
    cin >> name;

    cout << "Enter index number: ";
    cin >> index;

    Student newStudent(name, index);
    students.push_back(newStudent);

    cout << "Student registered successfully!\n";
}

void viewStudents() {
    cout << "\n--- Registered Students ---\n";

    for (int i = 0; i < students.size(); i++) {
        students[i].display();
    }
}

int main() {
    int choice;

    do {
        cout << "\n===== DIGITAL ATTENDANCE SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. View Students\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while(choice != 3);

    return 0;
}