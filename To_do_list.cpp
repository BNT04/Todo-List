#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int Id;
// Them kieu du lieu
struct To_do {
    int id;
    string task;
};

void Add() {
    system("cls");
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "                           TO_DO_LIST                             " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;

    To_do Todo;

    cout << "\n\t Enter new task: ";
    cin.get();
    getline(cin, Todo.task);
    Id++;
    // Mở file todolist
    ofstream write;
    write.open("Todolist.txt", ios::app);
    write << "\n" << Id;
    write << "\n" << Todo.task;
    write.close();

    // Mở file id
    write.open("Id.txt");
    write << Id;
    write.close();

    char ch;
    cout << "Do you want to add more tasks? (y/n)" << endl;
    cin >> ch;

    // Nếu người dùng muốn thêm task, nhấp kí tự yes or no
    if (ch == 'y') {
        Add();
    }
    else {
        cout << "\n\t Task has been added successfully";
        return;
    }
}

// In lên màn hình
void Print(To_do s) {
    cout << "\n\t ID is: " << s.id << endl;
    cout << "\n\t Task is: " << s.task << endl;
}

// Đọc data và in ra màn hình
void readData() {
    system("cls");
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "                           TO_DO_LIST                             " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;

    int id;
    cout << "\n\t Enter task id: ";
    cin >> id;
    To_do Todo;

    ifstream read;
    read.open("Todolist.txt");
    while (read >> Todo.id) {
        read.ignore();
        getline(read, Todo.task);
        if (Todo.id == id) {
            Print(Todo);
        }
    }
    read.close();
}

int searchData() {
    system("cls");
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "                           TO_DO_LIST                             " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;

    int id;
    cout << "\n\t Enter task id: ";
    cin >> id;
    To_do Todo;
    ifstream read;
    read.open("Todolist.txt");
    while (read >> Todo.id) {
        read.ignore();
        getline(read, Todo.task);
        if (Todo.id == id) {
            Print(Todo);
            return id;
        }
    }
    read.close();
    return -1;
}

// Xóa dữ liệu
void deleteData() {
    system("cls");
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "                           TO_DO_LIST                             " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;

    int id = searchData();
    if (id == -1) {
        cout << "\n\t Task not found";
        return;
    }

    cout << "\n\t Do you want to delete this task? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y') {
        To_do Todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("Todolist.txt");

        // Xóa dữ liệu trong data
        while (read >> Todo.id) {
            read.ignore();
            getline(read, Todo.task);
            if (Todo.id != id) {
                tempFile << "\n" << Todo.id;
                tempFile << "\n" << Todo.task;
            }
        }
        read.close();
        tempFile.close();
        remove("Todolist.txt");
        rename("temp.txt", "Todolist.txt");
        cout << "\n\t Task deleted successfully";
    }
    else {
        cout << "\n\t Task not deleted";
    }
}

// Cập nhật các task
void updateData() {
    system("cls");
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "                           TO_DO_LIST                             " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;

    int id = searchData();
    if (id == -1) {
        cout << "\n\t Task not found";
        return;
    }

    cout << "\n\t Do you want to update this task? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y') {
        To_do newData;
        cout << "\n\t Enter new task: ";
        cin.get();
        getline(cin, newData.task);

        To_do Todo;
        ofstream tempFile;
        tempFile.open("temp.txt");
        ifstream read;
        read.open("Todolist.txt");

        while (read >> Todo.id) {
            read.ignore();
            getline(read, Todo.task);
            if (Todo.id != id) {
                tempFile << "\n" << Todo.id;
                tempFile << "\n" << Todo.task;
            }
            else {
                tempFile << "\n" << Todo.id;
                tempFile << "\n" << newData.task;
            }
        }
        read.close();
        tempFile.close();
        remove("Todolist.txt");
        rename("temp.txt", "Todolist.txt");
        cout << "\n\t Task updated successfully ";
    }
    else {
        cout << "\n\t Task not updated";
    }
}

int main() {
    system("cls");
    cout << "\t\t\t------------------------------------------------------------" << endl;
    cout << "                           TO_DO_LIST                             " << endl;
    cout << "\t\t\t------------------------------------------------------------" << endl;

    ifstream read;
    read.open("Id.txt");
    if (!read.fail()) {
        read >> Id;
    }
    else {
        Id = 0;
    }
    read.close();

    while (true) {
        cout << endl << endl;
        cout << "\n\t1. Add task";
        cout << "\n\t2. See task";
        cout << "\n\t3. Search task";
        cout << "\n\t4. Delete task";
        cout << "\n\t5. Update task";

        int choice;
        cout << "\n\t Enter choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            Add();
            break;
        case 2:
            readData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            updateData();
            break;
        default:
            cout << "\n\t Invalid choice";
            break;
        }
    }

    return 0;
}
