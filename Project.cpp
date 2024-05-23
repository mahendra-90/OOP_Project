#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Student {
private:
    string name;
    int roll;
    string level;
    string programme;
    char gender;
    char section;
    string address;
    int age;

public:
    void ShowOptions();
    void addRecords();
    void displayRecord(const string &studName);
    void modify(const string &studName);
    void deleteRecord(const string &studName);
    void displayAll();
};

void Student::ShowOptions() {
    cout << "\nChoose your option\n";
    cout << "1. Add new record\n";
    cout << "2. Modify record\n";
    cout << "3. Display specific record\n";
    cout << "4. Delete record\n";
    cout << "5. Display all the records\n";
    cout << "6. Exit\n";
}

void Student::addRecords() {
    cout << "\nEnter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter roll number: ";
    cin >> roll;
    cin.ignore();
    cout << "Enter level: ";
    getline(cin, level);
    cout << "Enter the programme: ";
    getline(cin, programme);
    cout << "Enter the gender (M/F): ";
    cin >> gender;
    cout << "\nEnter section: ";
    cin >> section;
    cin.ignore();
    cout << "\nEnter address: ";
    getline(cin, address);
    cout << "Enter age: ";
    cin >> age;
    cin.ignore();

    ofstream outFile("students.txt", ios::app);
    outFile << name << "\n" << roll << "\n" << level << "\n" << programme << "\n" << gender << "\n" << section << "\n" << address << "\n" << age << "\n";
    outFile.close();
    cout << "\nRecord has been added successfully.\n";
}

void Student::displayRecord(const string &studName) {
    ifstream inFile("students.txt");
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line == studName) {
            for (int i = 0; i < 7; ++i) {
                getline(inFile, line);
                cout << line << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Record not found." << endl;
    }
    inFile.close();
}

void Student::modify(const string &studName) {
    fstream file("students.txt");
    string line;
    bool found = false;
    ofstream tempFile("temp.txt");

    while (getline(file, line)) {
        if (line == studName) {
            found = true;
            tempFile << line << endl;
            for (int i = 0; i < 7; ++i) {
                getline(file, line);
                cout << "Enter new " << line << ": ";
                getline(cin, line);
                tempFile << line << endl;
            }
        } else {
            tempFile << line << endl;
        }
    }

    file.close();
    tempFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nRecord has been modified successfully." << endl;
    } else {
        cout << "\nRecord not found." << endl;
    }
}

void Student::deleteRecord(const string &studName) {
    ifstream inFile("students.txt");
    string line;
    bool found = false;
    ofstream tempFile("temp.txt");

    while (getline(inFile, line)) {
        if (line == studName) {
            found = true;
            for (int i = 0; i < 7; ++i) {
                getline(inFile, line);
            }
        } else {
            tempFile << line << endl;
            for (int i = 0; i < 7; ++i) {
                getline(inFile, line);
            }
        }
    }

    inFile.close();
    tempFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nRecord has been deleted successfully." << endl;
    } else {
        cout << "\nRecord not found." << endl;
    }
}

void Student::displayAll() {
    ifstream inFile("students.txt");
    string line;

    cout << "Name\t | Roll no. | Level | Programme | Gender | Section | Address\t | Age\n";
    cout << "-----------------------------------------------------------------\n";

    while (getline(inFile, line)) {
        cout << line << "\n";
    }
    cout << "-----------------------------------------------------------------\n";
    inFile.close();
}

int main() {
    Student student;
    int choice;
    string name;

    while (true) {
        cout << "\n..........Welcome to Student Record Keeping System...........\n";
        student.ShowOptions();
        cin >> choice;

        switch (choice) {
            case 1:
                student.addRecords();
                break;
            case 2:
                cout << "Enter the name of the student to modify: ";
                cin.ignore();
                getline(cin, name);
                student.modify(name);
                break;
            case 3:
                cout << "Enter the name of student whose record is to be displayed: ";
                cin.ignore();
                getline(cin, name);
                student.displayRecord(name);
                break;
            case 4:
                cout << "Enter the name of student whose record is to be deleted: ";
                cin.ignore();
                getline(cin, name);
                student.deleteRecord(name);
                break;
            case 5:
                student.displayAll();
                break;
            case 6:
                cout << "\nExiting..." << endl;
                return 0;
            default:
                cout << "Invalid option" << endl;
        }
    }

    return 0;
}
