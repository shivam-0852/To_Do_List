#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Task {
    string taskName;
    string dueDate;
    string priority; // High, Medium, Low
    bool isCompleted;
    Task* next;
};

class ToDoList {
private:
    Task* head;

public:
    ToDoList() {
        head = nullptr;
        loadFromFile();
    }

    void addTask(string name, string due, string prio) {
        Task* newTask = new Task();
        newTask->taskName = name;
        newTask->dueDate = due;
        newTask->priority = prio;
        newTask->isCompleted = false;
        newTask->next = nullptr;

        if (head == nullptr) {
            head = newTask;
        } else {
            Task* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newTask;
        }
        cout << "Task Added Successfully!\n";
    }

    void displayTasks() {
        if (head == nullptr) {
            cout << "No tasks found!\n";
            return;
        }
        Task* temp = head;
        int count = 1;
        cout << left << setw(5) << "No." << setw(25) << "Task Name" 
             << setw(15) << "Due Date" << setw(10) << "Priority" << "Status\n";
        cout << "--------------------------------------------------------------\n";
        while (temp != nullptr) {
            cout << left << setw(5) << count++ 
                 << setw(25) << temp->taskName 
                 << setw(15) << temp->dueDate 
                 << setw(10) << temp->priority 
                 << (temp->isCompleted ? "Completed" : "Pending") << endl;
            temp = temp->next;
        }
    }

    void markCompleted(int taskNumber) {
        Task* temp = head;
        int count = 1;
        while (temp != nullptr && count < taskNumber) {
            temp = temp->next;
            count++;
        }
        if (temp != nullptr) {
            temp->isCompleted = true;
            cout << "Task marked as Completed!\n";
        } else {
            cout << "Invalid Task Number!\n";
        }
    }

    void deleteTask(int taskNumber) {
        if (head == nullptr) {
            cout << "No tasks to delete!\n";
            return;
        }
        Task* temp = head;
        if (taskNumber == 1) {
            head = head->next;
            delete temp;
            cout << "Task deleted!\n";
            return;
        }

        int count = 1;
        Task* prev = nullptr;
        while (temp != nullptr && count < taskNumber) {
            prev = temp;
            temp = temp->next;
            count++;
        }
        if (temp == nullptr) {
            cout << "Invalid Task Number!\n";
        } else {
            prev->next = temp->next;
            delete temp;
            cout << "Task deleted!\n";
        }
    }

    void sortByPriority() {
        if (head == nullptr || head->next == nullptr)
            return;

        for (Task* i = head; i != nullptr; i = i->next) {
            for (Task* j = i->next; j != nullptr; j = j->next) {
                if (priorityValue(i->priority) > priorityValue(j->priority)) {
                    swapTasks(i, j);
                }
            }
        }
        cout << "Tasks sorted by Priority!\n";
    }

    void sortByDueDate() {
        if (head == nullptr || head->next == nullptr)
            return;

        for (Task* i = head; i != nullptr; i = i->next) {
            for (Task* j = i->next; j != nullptr; j = j->next) {
                if (i->dueDate > j->dueDate) {
                    swapTasks(i, j);
                }
            }
        }
        cout << "Tasks sorted by Due Date!\n";
    }

    void saveToFile() {
        ofstream fout("tasks.txt");
        Task* temp = head;
        while (temp != nullptr) {
            fout << temp->taskName << "|" 
                 << temp->dueDate << "|"
                 << temp->priority << "|"
                 << temp->isCompleted << "\n";
            temp = temp->next;
        }
        fout.close();
    }

    void loadFromFile() {
        ifstream fin("tasks.txt");
        if (!fin.is_open())
            return;

        string line;
        while (getline(fin, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            string name = line.substr(0, pos1);
            string due = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string prio = line.substr(pos2 + 1, pos3 - pos2 - 1);
            bool completed = line.substr(pos3 + 1) == "1";

            Task* newTask = new Task();
            newTask->taskName = name;
            newTask->dueDate = due;
            newTask->priority = prio;
            newTask->isCompleted = completed;
            newTask->next = nullptr;

            if (head == nullptr) {
                head = newTask;
            } else {
                Task* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newTask;
            }
        }
        fin.close();
    }

  

private:
    int priorityValue(string prio) {
        if (prio == "High") return 1;
        else if (prio == "Medium") return 2;
        else return 3; // Low
    }

    void swapTasks(Task* a, Task* b) {
        swap(a->taskName, b->taskName);
        swap(a->dueDate, b->dueDate);
        swap(a->priority, b->priority);
        swap(a->isCompleted, b->isCompleted);
    }
};

int main() {
    ToDoList todo;
    int choice;
    do {
        cout << "\n--- To-Do List Menu ---\n";
        cout << "1. Add Task\n";
        cout << "2. Display Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Delete Task\n";
        cout << "5. Sort by Priority\n";
        cout << "6. Sort by Due Date\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore();
                string name, due, prio;
                cout << "Enter Task Name: ";
                getline(cin, name);
            
                // Due Date Validation
                bool validDate = false;
                while (!validDate) {
                    cout << "Enter Due Date (YYYY-MM-DD): ";
                    getline(cin, due);
                    if (due.length() == 10 && due[4] == '-' && due[7] == '-') {
                        string yearStr = due.substr(0, 4);
                        string monthStr = due.substr(5, 2);
                        string dayStr = due.substr(8, 2);
                        int year = stoi(yearStr);
                        int month = stoi(monthStr);
                        int day = stoi(dayStr);
                        if (year >= 1900 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                            validDate = true;
                        } else {
                            cout << "Invalid date components!\n";
                        }
                    } else {
                        cout << "Invalid date format! Please use YYYY-MM-DD.\n";
                    }
                }
            
                // Priority Validation
                while (true) {
                    cout << "Enter Priority (High/Medium/Low): ";
                    getline(cin, prio);
                    if (prio == "High" || prio == "Medium" || prio == "Low") {
                        break;
                    } else {
                        cout << "Invalid priority! Please enter only High, Medium, or Low.\n";
                    }
                }
            
                todo.addTask(name, due, prio);
                break;
            }
            
        case 2:
            todo.displayTasks();
            break;
        case 3: {
            int num;
            cout << "Enter Task Number to mark completed: ";
            cin >> num;
            todo.markCompleted(num);
            break;
        }
        case 4: {
            int num;
            cout << "Enter Task Number to delete: ";
            cin >> num;
            todo.deleteTask(num);
            break;
        }
        case 5:
            todo.sortByPriority();
            break;
        case 6:
            todo.sortByDueDate();
            break;
        case 7:
            cout << "Saving tasks and Exiting...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 7);

    return 0;
}
