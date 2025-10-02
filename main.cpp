#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_STUDENTS = 120;
const int MAX_COURSES = 12;

struct StudentCourse {
    string courseCode;
    float degree;
};

struct Student {
    string name;
    string id;
    int level;
    string group;
    float gpa;
    StudentCourse courses[5];
    int courseCount;
};

struct Course {
    string name;
    string code;
    int creditHours;
};

Student studentList[MAX_STUDENTS];
Course courseList[MAX_COURSES];
int studentCount = 0;
int courseCount = 0;

void addStudent();
void updateStudent();
void deleteStudent();
void addCourse();
void updateCourse();
void deleteCourse();
void assignCourse();
void displayStudents();
void displayTopStudents();
void listByLevel();
void searchStudent();
void searchCourse();
void line();
int getValidInt(string, int, int);
float getValidFloat(string, float, float);
string getValidName(string);
string getValidID(string);
string getValidString(string);

int main() {
    int choice;
    do {
        cout << "\n========= Student Management System ==========\n";
        cout << endl;
        cout << "          1. Add Student\n";
        line();
        cout << "          2. Update Student\n";
        line();
        cout << "          3. Delete Student\n";
        line();
        cout << "          4. Add Course\n";
        line();
        cout << "          5. Update Course\n";
        line();
        cout << "          6. Delete Course\n";
        line();
        cout << "          7. Assign Course to Student\n";
        line();
        cout << "          8. Display All Students\n";
        line();
        cout << "          9. Display Top Students by Course\n";
        line();
        cout << "          10. List Students by Level\n";
        line();
        cout << "          11. Search for a Student\n";
        line();
        cout << "          12. Search for a Course\n";
        line();
        cout << "          0. Exit\n";
        line();
        choice = getValidInt("Enter your choice: ", 0, 12);
        cout << endl;

        switch (choice) {
        case 1: addStudent(); break;
        case 2: updateStudent(); break;
        case 3: deleteStudent(); break;
        case 4: addCourse(); break;
        case 5: updateCourse(); break;
        case 6: deleteCourse(); break;
        case 7: assignCourse(); break;
        case 8: displayStudents(); break;
        case 9: displayTopStudents(); break;
        case 10: listByLevel(); break;
        case 11: searchStudent(); break;
        case 12: searchCourse(); break;
        case 0: cout << "Thank you for using the students management system of sphinx university Goodbye!\n"; break;
        default: cout << "Invalid choice. Please try again!\n";
        }

    } while (choice != 0);

    return 0;
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum student limit reached!\n";
        return;
    }

    studentList[studentCount].name = getValidName("Enter Name: ");
    studentList[studentCount].id = getValidID("Enter ID: ");
    studentList[studentCount].level = getValidInt("Enter Level (1-4): ", 1, 4);
    studentList[studentCount].group = getValidString("Enter Group: ");
    studentList[studentCount].gpa = getValidFloat("Enter GPA (0.0 - 4.0): ", 0.0, 4.0);

    studentList[studentCount].courseCount = 0;
    studentCount++;
    cout << "Student added successfully!\n";
}

void updateStudent() {
    string id = getValidID("Enter ID to update: ");
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].id == id) {
            studentList[i].name = getValidName("Enter New Name: ");
            studentList[i].level = getValidInt("Enter New Level (1-4): ", 1, 4);
            studentList[i].group = getValidString("Enter New Group: ");
            studentList[i].gpa = getValidFloat("Enter New GPA (0.0 - 4.0): ", 0.0, 4.0);
            cout << "Student updated successfully!\n";
            return;
        }
    }
    cout << "No student found with that ID.\n";
}

void deleteStudent() {
    string id = getValidID("Enter ID to delete: ");
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].id == id) {
            for (int j = i; j < studentCount - 1; j++)
                studentList[j] = studentList[j + 1];
            studentCount--;
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "No student found with that ID.\n";
}

void addCourse() {
    if (courseCount >= MAX_COURSES) {
        cout << "Maximum course limit reached!\n";
        return;
    }

    courseList[courseCount].name = getValidString("Enter Course Name: ");
    courseList[courseCount].code = getValidString("Enter Course Code: ");
    courseList[courseCount].creditHours = getValidInt("Enter Credit Hours (1-6): ", 1, 6);

    courseCount++;
    cout << "Course added successfully!\n";
}

void updateCourse() {
    string code = getValidString("Enter Course Code to update: ");
    for (int i = 0; i < courseCount; i++) {
        if (courseList[i].code == code) {
            courseList[i].name = getValidString("Enter New Name: ");
            courseList[i].creditHours = getValidInt("Enter New Credit Hours (1-6): ", 1, 6);
            cout << "Course updated successfully!\n";
            return;
        }
    }
    cout << "No course found with that code.\n";
}

void deleteCourse() {
    string code = getValidString("Enter Course Code to delete: ");
    for (int i = 0; i < courseCount; i++) {
        if (courseList[i].code == code) {
            for (int j = i; j < courseCount - 1; j++)
                courseList[j] = courseList[j + 1];
            courseCount--;
            cout << "Course deleted successfully!\n";
            return;
        }
    }
    cout << "No course found with that code.\n";
}

void assignCourse() {
    string id = getValidID("Enter Student ID: ");
    int sIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].id == id) {
            sIndex = i;
            break;
        }
    }
    if (sIndex == -1) {
        cout << "No student found with that ID.\n";
        return;
    }
    if (studentList[sIndex].courseCount >= 5) {
        cout << "This student has reached the maximum of 5 courses.\n";
        return;
    }
    cout << "\nAvailable Courses:\n";
    for (int i = 0; i < courseCount; i++) {
        cout << "Code: " << courseList[i].code << ", Name: " << courseList[i].name << "\n";
    }
    string code = getValidString("Enter Course Code: ");
    int cIndex = -1;
    for (int i = 0; i < courseCount; i++) {
        if (courseList[i].code == code) {
            cIndex = i;
            break;
        }
    }
    if (cIndex == -1) {
        cout << "No course found with that code.\n";
        return;
    }
    for (int i = 0; i < studentList[sIndex].courseCount; i++) {
        if (studentList[sIndex].courses[i].courseCode == code) {
            cout << "This student is already enrolled in this course.\n";
            return;
        }
    }
    float degree = getValidFloat("Enter Degree (0.0-100.0): ", 0.0, 100.0);
    StudentCourse sc;
    sc.courseCode = code;
    sc.degree = degree;
    studentList[sIndex].courses[studentList[sIndex].courseCount++] = sc;
    cout << "Course assigned successfully!\n";
}

void displayStudents() {
    if (studentCount == 0) {
        cout << "No students to display.\n";
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        cout << "Name: " << studentList[i].name
            << ", ID: " << studentList[i].id
            << ", Level: " << studentList[i].level
            << ", GPA: " << studentList[i].gpa << "\n";
        for (int j = 0; j < studentList[i].courseCount; j++) {
            cout << "  Course: " << studentList[i].courses[j].courseCode
                << ", Degree: " << studentList[i].courses[j].degree << "\n";
        }
    }
}

void displayTopStudents() {
    if (courseCount == 0) {
        cout << "No courses to display.\n";
        return;
    }
    for (int i = 0; i < courseCount; i++) {
        float maxDegree = -1;
        string topStudent = "None";
        for (int j = 0; j < studentCount; j++) {
            for (int k = 0; k < studentList[j].courseCount; k++) {
                if (studentList[j].courses[k].courseCode == courseList[i].code) {
                    if (studentList[j].courses[k].degree > maxDegree) {
                        maxDegree = studentList[j].courses[k].degree;
                        topStudent = studentList[j].name;
                    }
                }
            }
        }
        cout << "Highest scoring student in " << courseList[i].code << ": " << topStudent << " with " << maxDegree << "\n";
    }
}

void listByLevel() {
    int level = getValidInt("Please enter the level to display students (1-4): ", 1, 4);
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].level == level) {
            cout << studentList[i].name << " (" << studentList[i].id << ")\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No students found in level " << level << ".\n";
    }
}

void searchStudent() {
    string input = getValidString("Enter Student Name or ID: ");
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].name == input || studentList[i].id == input) {
            cout << "Student located: " << studentList[i].name << " - " << studentList[i].id << "\n";
            return;
        }
    }
    cout << "No student found with that ID or name.\n";
}

void searchCourse() {
    string input = getValidString("Enter Course Name or Code: ");
    for (int i = 0; i < courseCount; i++) {
        if (courseList[i].name == input || courseList[i].code == input) {
            cout << "Matching course located: " << courseList[i].name << " - " << courseList[i].code << "\n";
            for (int j = 0; j < studentCount; j++) {
                for (int k = 0; k < studentList[j].courseCount; k++) {
                    if (studentList[j].courses[k].courseCode == input)
                        cout << "  Student: " << studentList[j].name << ", Degree: " << studentList[j].courses[k].degree << "\n";
                }
            }
            return;
        }
    }
    cout << "No course found with that code or name.\n";
}


string getValidName(string prompt) {
    string input;
    bool valid;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. ";
            continue;
        }
        valid = true;
        for (char c : input) {
            if (!isalpha(c) && !isspace(c)) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "Name must contain only letters and spaces. ";
        }
    } while (input.empty() || !valid);
    return input;
}

string getValidID(string prompt) {
    string input;
    bool valid;
    do {
        cout << prompt;
        getline(cin, input);
        if (input.empty()) {
            cout << "Input cannot be empty. ";
            continue;
        }
        valid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "ID must contain only digits. ";
        }
    } while (input.empty() || !valid);
    return input;
}

string getValidString(string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    while (input.empty()) {
        cout << "Input cannot be empty. " << prompt;
        getline(cin, input);
    }
    return input;
}

int getValidInt(string prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float getValidFloat(string prompt, float min, float max) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input! Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void line() {
    cout << "==============================================\n";
}
