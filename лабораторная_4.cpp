//Прокопьева Марина НБИбд-02-23 4 Лабораторная 

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Student {
  string id;
  string name;
  string surname;
  string grade;
  string age;
};

const int MAX_STUDENTS = 1000; // Максимальное количество записей
Student students[MAX_STUDENTS];
int studentCount = 0;

void loadFromFile(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return;
  }
  studentCount = 0;
  string line;
  while (getline(file, line)) {
    if (studentCount >= MAX_STUDENTS)
      break;
    stringstream ss(line);
    getline(ss, students[studentCount].id, ',');
    getline(ss, students[studentCount].name, ',');
    getline(ss, students[studentCount].surname, ',');
    getline(ss, students[studentCount].grade, ',');
    getline(ss, students[studentCount].age, ',');
    studentCount++;
  }
  file.close();
}

void saveToFile(const string &filename) {
  ofstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening file" << endl;
    return;
  }
  for (int i = 0; i < studentCount; i++) {
    file << students[i].id << "," << students[i].name << ","
         << students[i].surname << "," << students[i].grade << ","
         << students[i].age << endl;
  }
  file.close();
}

void addStudent() {
  if (studentCount >= MAX_STUDENTS) {
    cerr << "Cannot add more students" << endl;
    return;
  }
  cout << "Enter ID: ";
  cin >> students[studentCount].id;
  cout << "Enter Name: ";
  cin >> students[studentCount].name;
  cout << "Enter Surname: ";
  cin >> students[studentCount].surname;
  cout << "Enter Grade: ";
  cin >> students[studentCount].grade;
  cout << "Enter Age: ";
  cin >> students[studentCount].age;
  studentCount++;
}

void editStudent() {
  string id;
  cout << "Enter ID of student to edit: ";
  cin >> id;
  for (int i = 0; i < studentCount; i++) {
    if (students[i].id == id) {
      cout << "Editing student with ID: " << id << endl;
      cout << "Enter new Name: ";
      cin >> students[i].name;
      cout << "Enter new Surname: ";
      cin >> students[i].surname;
      cout << "Enter new Grade: ";
      cin >> students[i].grade;
      cout << "Enter new Age: ";
      cin >> students[i].age;
      return;
    }
  }
  cout << "Student with ID " << id << " not found." << endl;
}

void deleteStudent() {
  string id;
  cout << "Enter ID of student to delete: ";
  cin >> id;
  for (int i = 0; i < studentCount; i++) {
    if (students[i].id == id) {
      for (int j = i; j < studentCount - 1; j++) {
        students[j] = students[j + 1];
      }
      studentCount--;
      cout << "Student with ID " << id << " deleted." << endl;
      return;
    }
  }
  cout << "Student with ID " << id << " not found." << endl;
}

void searchStudent() {
  string id;
  cout << "Enter ID of student to search: ";
  cin >> id;
  for (int i = 0; i < studentCount; i++) {
    if (students[i].id == id) {
      cout << "Student found:" << endl;
      cout << "ID: " << students[i].id << endl;
      cout << "Name: " << students[i].name << endl;
      cout << "Surname: " << students[i].surname << endl;
      cout << "Grade: " << students[i].grade << endl;
      cout << "Age: " << students[i].age << endl;
      return;
    }
  }
  cout << "Student with ID " << id << " not found." << endl;
}

void displayAllStudents() {
  if (studentCount == 0) {
    cout << "No students in the database." << endl;
    return;
  }
  for (int i = 0; i < studentCount; i++) {
    cout << "ID: " << students[i].id << endl;
    cout << "Name: " << students[i].name << endl;
    cout << "Surname: " << students[i].surname << endl;
    cout << "Grade: " << students[i].grade << endl;
    cout << "Age: " << students[i].age << endl;
    cout << "---------------------" << endl;
  }
}

int main() {
  string filename = "students.txt";
  loadFromFile(filename);
  while (true) {
    cout << "1. Add Student" << endl;
    cout << "2. Edit Student" << endl;
    cout << "3. Delete Student" << endl;
    cout << "4. Search Student" << endl;
    cout << "5. Display All Students" << endl;
    cout << "6. Save and Exit" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
      addStudent();
      break;
    case 2:
      editStudent();
      break;
    case 3:
      deleteStudent();
      break;
    case 4:
      searchStudent();
      break;
    case 5:
      displayAllStudents();
      break;
    case 6:
      saveToFile(filename);
      return 0;
    default:
      cout << "Invalid choice. Try again." << endl;
    }
  }
  return 0;
}