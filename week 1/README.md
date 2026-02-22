# Digital Attendance System

## Course Information
**Name:** Wilson John Yensuah
**ID No:** 01241570D
**Programme:** HND Electrical Engineering (Level 200)  
**Course Code:** EEE227  
**Institution:** Accra Technical University  
**Assessment:** Mid-Semester Capstone Project  

---

## Project Description

The Digital Attendance System is a console-based C++ application designed to replace paper-based attendance taking in lecture halls.  

The system allows lecturers to:
- Register students
- Create lecture sessions
- Mark attendance (Present, Absent, Late)
- Generate attendance reports
- Store data using text files

The application runs offline on Windows and uses file handling (fstream) for data persistence.

---

## Features

### 1. Student Management
- Register new students
- View all registered students
- Search student by index number

### 2. Attendance Session Management
- Create lecture session (course code, date, start time, duration)
- Mark attendance (P/A/L)
- Update attendance records

### 3. Reports and Summary
- Display attendance list for a session
- Show summary count of Present, Absent, and Late students

### 4. File Storage
- Saves students to `students.txt`
- Saves sessions to `session_<course>_<date>.txt`
- Data persists between program executions

---

## Technologies Used

- Programming Language: C++
- IDE: Visual Studio Code
- Version Control: GitHub
- Platform: Windows (Offline First)

---

## How to Compile and Run

1. Open the project folder in VS Code
2. Open terminal
3. Compile using:

   g++ main.cpp -o attendance

4. Run using:

   attendance

---

## Project Structure

digital-attendance-system/
│── main.cpp  
│── README.md  
│── students.txt  
│── session_<course>_<date>.txt  

---

## Author

Name: [Your Full Name]  
Index Number: [Your Index Number]  

---

## Notes

This project was developed as part of the EEE227 Mid-Semester Capstone Project.  
All work is original and developed using standard C++ programming practices.
