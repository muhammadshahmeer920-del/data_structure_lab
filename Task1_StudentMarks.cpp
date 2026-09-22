#include <iostream>
using namespace std;

int main() {
    const int STUDENTS = 6;
    const int SUBJECTS = 4;
    string subjectNames[SUBJECTS] = {"English", "Mathematics", "Programming", "AI"};

    int marks[STUDENTS][SUBJECTS] = {
        {78, 85, 90, 88},
        {65, 70, 75, 60},
        {92, 88, 95, 91},
        {55, 60, 58, 62},
        {80, 76, 82, 79},
        {70, 68, 74, 73}
    };

    
    cout << " Marks Table \n";
    cout << "Student\t";
    for (int j = 0; j < SUBJECTS; j++)
        cout << subjectNames[j] << "\t";
    cout << "\n";

    for (int i = 0; i < STUDENTS; i++) {
        cout << "S" << (i + 1) << "\t";
        for (int j = 0; j < SUBJECTS; j++)
            cout << marks[i][j] << "\t\t";
        cout << "\n";
    }

    
    int totals[STUDENTS];
    double averages[STUDENTS];
    cout << "\n Totals and Average\n";
    for (int i = 0; i < STUDENTS; i++) {
        int sum = 0;
        for (int j = 0; j < SUBJECTS; j++)
            sum += marks[i][j];
        totals[i] = sum;
        averages[i] = (double)sum / SUBJECTS;
        cout << "Student " << (i + 1) << " -> Total: " << totals[i]
             << ", Average: " << averages[i] << "\n";
    }

    cout << "\n Highest Marks per Subject \n";
    for (int j = 0; j < SUBJECTS; j++) {
        int highest = marks[0][j];
        for (int i = 1; i < STUDENTS; i++)
            if (marks[i][j] > highest)
                highest = marks[i][j];
        cout << subjectNames[j] << ": " << highest << "\n";
    }

    
    int topStudent = 0;
    for (int i = 1; i < STUDENTS; i++)
        if (totals[i] > totals[topStudent])
            topStudent = i;

    cout << "\nStudent with highest total marks: Student " << (topStudent + 1)
         << " with total " << totals[topStudent] << "\n";

    return 0;
}
