# Student Report Card Management System

A console-based C++ application for managing student academic records — marks, grades, and report cards — with binary file persistence.

---

## Features

- Add new student records
- Display all student records
- Search for a student by roll number
- Modify an existing student record
- Delete a student record
- View class-wide grade report (tabular)
- View individual student report card
- Input validation: marks enforced in range 0–100, roll numbers must be positive

---

## Tech Stack

- **Language:** C++ (standard C++11 or later)
- **File handling:** Binary file I/O via `<fstream>`
- **I/O:** `<iostream>`, `<iomanip>`
- **Build tool:** Any modern C++ compiler (`g++`, `clang++`, MSVC)

---

## Getting Started

### Requirements

- A C++11-compatible compiler (`g++`, `clang++`, or MSVC)
- Linux, macOS, or Windows

### Compile

```bash
g++ -std=c++11 -o student_report schoolproject.cpp
```

### Run

```bash
./student_report
```

---

## Usage

On launch you will see the **Main Menu**:

```
MAIN MENU

  01. RESULT MENU
  02. ENTRY/EDIT MENU
  03. EXIT
```

| Menu | Options |
|---|---|
| Result Menu | Class Result, Student Report Card |
| Entry/Edit Menu | Create, Display All, Search, Modify, Delete |

Student data is stored in `student.dat` in the working directory and persists between runs.

---

## Grading Scale

| Grade | Percentage |
|---|---|
| A | 60% and above |
| B | 50% – 59% |
| C | 33% – 49% |
| F | Below 33% |

Percentage is the average of five subjects: Physics, Chemistry, Maths, English, and Computer Science.

---

## Project Info

**Authors:** Hamza Ahmed Khan & Aaditya Senthilkumar  
**School:** DPS-Modern Indian School
