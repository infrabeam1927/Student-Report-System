//************************************************
//                   HEADER FILES USED IN PROJECT
//***********************************************

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <limits>

using namespace std;

void clrscr() { system("clear"); }

void pause()
{
    cout << "\n\tPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

//************************************************
//                   CLASS USED IN PROJECT
//************************************************

class student
{
  private:
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    float per;
    char grade;
    void calculate();
  public:
    void getdata();
    void showdata();
    void show_tabular();
    int retrollno();
};

void student::calculate()
{
    per = (p_marks + c_marks + m_marks + e_marks + cs_marks) / 5.0;
    if (per >= 60)      grade = 'A';
    else if (per >= 50) grade = 'B';
    else if (per >= 33) grade = 'C';
    else                grade = 'F';
}

static int readMark(const char* subject)
{
    int val;
    while (true) {
        cout << "\nEnter marks in " << subject << " (0-100): ";
        if (cin >> val && val >= 0 && val <= 100) break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid! Marks must be between 0 and 100.\n";
    }
    return val;
}

void student::getdata()
{
    cout << "\nEnter roll number: ";
    while (!(cin >> rollno) || rollno <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid! Enter a positive integer: ";
    }
    cin.ignore();
    cout << "Enter student name: ";
    cin.getline(name, 50);

    p_marks  = readMark("Physics");
    c_marks  = readMark("Chemistry");
    m_marks  = readMark("Maths");
    e_marks  = readMark("English");
    cs_marks = readMark("Computer Science");
    calculate();
}

void student::showdata()
{
    cout << "\nRoll Number     : " << rollno;
    cout << "\nName            : " << name;
    cout << "\nPhysics         : " << p_marks;
    cout << "\nChemistry       : " << c_marks;
    cout << "\nMaths           : " << m_marks;
    cout << "\nEnglish         : " << e_marks;
    cout << "\nComputer Science: " << cs_marks;
    cout << "\nPercentage      : " << fixed << setprecision(2) << per << "%";
    cout << "\nGrade           : " << grade;
}

void student::show_tabular()
{
    cout << left
         << setw(6)  << rollno
         << setw(20) << name
         << setw(5)  << p_marks
         << setw(5)  << c_marks
         << setw(5)  << m_marks
         << setw(5)  << e_marks
         << setw(5)  << cs_marks
         << setw(9)  << fixed << setprecision(1) << per
         << grade << "\n";
}

int student::retrollno()
{
    return rollno;
}


//**********************************************************
//    	function declarations
//**********************************************************

void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();


//**********************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//**********************************************************

int main()
{
    char ch;
    intro();
    do {
        clrscr();
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. RESULT MENU";
        cout << "\n\n\t02. ENTRY/EDIT MENU";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        cin >> ch;
        clrscr();
        switch (ch) {
            case '1': result();     break;
            case '2': entry_menu(); break;
            case '3': break;
            default:  cout << "\a";
        }
    } while (ch != '3');
    return 0;
}

//**********************************************************
//    	function to write in file
//**********************************************************

void write_student()
{
    student st;
    ofstream fout;
    fout.open("student.dat", ios::binary | ios::app);
    if (!fout) {
        cout << "File could not be opened!";
        pause();
        return;
    }
    st.getdata();
    fout.write((char *)&st, sizeof(student));
    fout.close();
    cout << "\n\nStudent record has been created.";
    pause();
}

//**********************************************************
//    	function to read all records from file
//**********************************************************

void display_all()
{
    student st;
    ifstream fin;
    fin.open("student.dat", ios::binary);
    if (!fin) {
        cout << "File could not be opened!";
        pause();
        return;
    }
    cout << "\n\n\n\t\tDISPLAY ALL RECORDS\n\n";
    bool any = false;
    while (fin.read((char *)&st, sizeof(student))) {
        st.showdata();
        cout << "\n\n====================================\n";
        any = true;
    }
    if (!any) cout << "\tNo records found.\n";
    fin.close();
    pause();
}

//**********************************************************
//    	function to read specific record from file
//**********************************************************

void display_sp(int n)
{
    student st;
    ifstream fin;
    fin.open("student.dat", ios::binary);
    if (!fin) {
        cout << "File could not be opened!";
        pause();
        return;
    }
    bool found = false;
    while (fin.read((char *)&st, sizeof(student))) {
        if (st.retrollno() == n) {
            st.showdata();
            found = true;
        }
    }
    fin.close();
    if (!found)
        cout << "\n\nRecord not found.";
    pause();
}

//**********************************************************
//    	function to modify record of file
//**********************************************************

void modify_student(int n)
{
    bool found = false;
    student st;
    fstream File;
    File.open("student.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened!";
        pause();
        return;
    }
    while (File.read((char *)&st, sizeof(student)) && !found) {
        if (st.retrollno() == n) {
            st.showdata();
            cout << "\n\nEnter new details:\n";
            st.getdata();
            int pos = -1 * (int)sizeof(st);
            File.seekp(pos, ios::cur);
            File.write((char *)&st, sizeof(student));
            cout << "\n\n\tRecord updated.";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "\n\nRecord not found.";
    pause();
}

//**********************************************************
//    	function to delete record of file
//**********************************************************

void delete_student(int n)
{
    student st;
    ifstream fin;
    fin.open("student.dat", ios::binary);
    if (!fin) {
        cout << "File could not be opened!";
        pause();
        return;
    }
    ofstream fout;
    fout.open("Temp.dat", ios::binary | ios::out);
    bool found = false;
    while (fin.read((char *)&st, sizeof(student))) {
        if (st.retrollno() != n)
            fout.write((char *)&st, sizeof(student));
        else
            found = true;
    }
    fout.close();
    fin.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    if (found)
        cout << "\n\n\tRecord deleted.";
    else
        cout << "\n\n\tRecord not found.";
    pause();
}

//**********************************************************
//    	function to display all students grade report
//**********************************************************

void class_result()
{
    student st;
    ifstream fin;
    fin.open("student.dat", ios::binary);
    if (!fin) {
        cout << "File could not be opened!";
        pause();
        return;
    }
    cout << "\n\n\t\tALL STUDENTS RESULT\n\n";
    cout << string(65, '=') << "\n";
    cout << left
         << setw(6)  << "R.No"
         << setw(20) << "Name"
         << setw(5)  << "P"
         << setw(5)  << "C"
         << setw(5)  << "M"
         << setw(5)  << "E"
         << setw(5)  << "CS"
         << setw(9)  << "%age"
         << "Grade\n";
    cout << string(65, '=') << "\n";
    while (fin.read((char *)&st, sizeof(student)))
        st.show_tabular();
    fin.close();
    pause();
}

//**********************************************************
//    	function to display result menu
//**********************************************************

void result()
{
    char ch;
    int rno;
    cout << "\n\n\n\tRESULT MENU";
    cout << "\n\n\n\t1. Class Result";
    cout << "\n\n\t2. Student Report Card";
    cout << "\n\n\t3. Back to Main Menu";
    cout << "\n\n\n\tEnter Choice (1/2/3)? ";
    cin >> ch;
    clrscr();
    switch (ch) {
        case '1': class_result(); break;
        case '2':
            cout << "\n\n\tEnter Roll Number: ";
            cin >> rno;
            display_sp(rno);
            break;
        case '3': break;
        default:  cout << "\a";
    }
}

//**********************************************************
//    	INTRODUCTION FUNCTION
//**********************************************************

void intro()
{
    clrscr();
    cout << "\n\n\n\t\t  STUDENT";
    cout << "\n\n\t\tREPORT CARD";
    cout << "\n\n\t\t  PROJECT";
    cout << "\n\n\n\tMADE BY : HAMZA AHMED KHAN AND AADITYA SENTHILKUMAR";
    cout << "\n\tSCHOOL : DPS-MODERN INDIAN SCHOOL";
    pause();
}

//**********************************************************
//    	ENTRY / EDIT MENU FUNCTION
//**********************************************************

void entry_menu()
{
    char ch;
    int num;
    clrscr();
    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1. CREATE STUDENT RECORD";
    cout << "\n\n\t2. DISPLAY ALL STUDENTS RECORDS";
    cout << "\n\n\t3. SEARCH STUDENT RECORD";
    cout << "\n\n\t4. MODIFY STUDENT RECORD";
    cout << "\n\n\t5. DELETE STUDENT RECORD";
    cout << "\n\n\t6. BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter Your Choice (1-6) ";
    cin >> ch;
    clrscr();
    switch (ch) {
        case '1': write_student(); break;
        case '2': display_all(); break;
        case '3':
            cout << "\n\n\tEnter Roll Number: ";
            cin >> num;
            display_sp(num);
            break;
        case '4':
            cout << "\n\n\tEnter Roll Number: ";
            cin >> num;
            modify_student(num);
            break;
        case '5':
            cout << "\n\n\tEnter Roll Number: ";
            cin >> num;
            delete_student(num);
            break;
        case '6': break;
        default:  cout << "\a"; entry_menu();
    }
}

//**********************************************************
//    			END OF PROJECT
//**********************************************************
