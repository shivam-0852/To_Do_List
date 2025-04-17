# 📝 ToDo List (C++ Console Application)

A simple and clean **To-Do List** application built using C++.  
This is a console-based app that uses a **linked list** to manage tasks. You can add, view, complete, delete, and sort your tasks easily!

---

## 🚀 Features

- ✅ Add new tasks
- 📋 Display all tasks
- ✔️ Mark any task as completed
- ❌ Delete any task
- 🔽 Sort tasks by **Priority** (High > Medium > Low)
- 📅 Sort tasks by **Due Date**
- 💾 Save & Load tasks from a file (`tasks.txt`)

---

## 📂 Project Structure

```
ToDoList/
│
├── main.cpp        → Main source code (C++)
├── tasks.txt       → Auto-generated file for saving tasks
└── README.md       → This documentation file
```

---

## 🛠️ How to Compile & Run

### ▶️ Using g++ (Linux / Windows with MinGW)

```bash
g++ main.cpp -o ToDoList
./ToDoList
```

### ▶️ Using Any C++ IDE (Code::Blocks / Visual Studio / DevC++)

- Create a new project
- Add the `main.cpp` file
- Build and Run the project

---

## 🧾 Task File Format

Filename: `tasks.txt`

```txt
Complete Assignment|2025-04-15|High|0
Buy Groceries|2025-04-20|Medium|1
```

Each line format:  
```
TaskName|DueDate|Priority|isCompleted
```

Where:
- `isCompleted = 0` means **Pending**
- `isCompleted = 1` means **Completed**

