# 📁 File Management System

A **C++ Windows GUI application** that simulates core file system operations — create, read, write, delete, rename files and directories — through a clean, interactive interface.

---

## 📸 Overview

The File Management System is built using **C++17** and the **Win32 API**, providing a native Windows GUI without any third-party frameworks. It follows a layered architecture and covers all fundamental file management concepts found in modern operating systems.

---

## ✨ Features

| Category | Operations |
|---|---|
| 📄 File Operations | Create, Read, Write, Append, Delete, Rename, Info |
| 📂 Directory Operations | Create, Delete (recursive), Navigate, Go to Parent |
| 🖥️ Interface | File browser list, sidebar buttons, activity log panel |
| 🔀 Navigation | Double-click folder to enter · Double-click file to read |

---

## 🏗️ Architecture

The system is designed using a **5-layer architecture**:

```
┌─────────────────────────────────────────┐
│         Presentation Layer              │  ← GUI (buttons, list, log)
├─────────────────────────────────────────┤
│            Logic Layer                  │  ← C++ file/directory logic
├─────────────────────────────────────────┤
│      Application Execution Layer        │  ← FMS.exe (compiled binary)
├─────────────────────────────────────────┤
│        Operating System Layer           │  ← Windows Kernel (I/O, permissions)
├─────────────────────────────────────────┤
│       Database & Storage Layer          │  ← SSD / HDD (local disk)
└─────────────────────────────────────────┘
```

---

## 🛠️ Technologies Used

| Tool | Purpose |
|---|---|
| C++17 | Core programming language |
| Win32 API | Native Windows GUI framework |
| `<filesystem>` | Directory and file path management |
| `<fstream>` | File reading and writing |
| `<iostream>` | Standard I/O operations |
| GCC / MinGW | Compiler |

---

## ⚙️ How to Compile

### Option 1 — MinGW / GCC (Recommended)

Make sure MinGW is installed, then open **Command Prompt** in the project folder and run:

```bash
g++ -std=c++17 main.cpp -o FMS.exe -mwindows -lcomctl32 -lshell32 -lgdi32
```

Then double-click `FMS.exe` to launch.

---

### Option 2 — Visual Studio

1. Create a new **Empty C++ Project**
2. Add `main.cpp` to Source Files
3. Go to **Project Properties**:
   - C/C++ → Language → C++ Standard → **ISO C++17**
   - Linker → System → SubSystem → **Windows**
4. Press **Ctrl + F5** to build and run

---

### Option 3 — VS Code + MinGW

Create `.vscode/tasks.json`:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Build FMS",
      "type": "shell",
      "command": "g++",
      "args": [
        "-std=c++17", "main.cpp", "-o", "FMS.exe",
        "-mwindows", "-lcomctl32", "-lshell32", "-lgdi32"
      ],
      "group": { "kind": "build", "isDefault": true }
    }
  ]
}
```

Press **Ctrl + Shift + B** to build.

---

## 🖱️ How to Use

| Action | How |
|---|---|
| Browse files & folders | Scroll the list on the left |
| Enter a folder | Double-click it |
| Read a file | Double-click it, or select + click **\[R\] Read** |
| Create a new file | Click **\[+\] Create File** → type name → OK |
| Write to a file | Select file → **\[W\] Write / Append** → enter content |
| Append to a file | Same as write → choose **YES** (Append) when prompted |
| Delete a file | Select file → **\[X\] Delete File** |
| Rename anything | Select item → **\[~\] Rename** |
| View file details | Select item → **\[i\] File Info** |
| Create a directory | **\[+\] Create Directory** → enter name |
| Delete a directory | Select folder → **\[X\] Delete Directory** |
| Go up one level | Click **\[^\] Go to Parent** or double-click the `[..]` row |
| Refresh the list | **\[*\] Refresh List** |
| Clear the log | **\[ \] Clear Log** |

---

## 📋 Requirements

- **OS:** Windows 7 / 10 / 11
- **Compiler:** GCC 9+ or MSVC 2019+
- **C++ Standard:** C++17
- **Libraries:** `comctl32`, `shell32`, `gdi32` (included with Windows SDK — no extra installs needed)

---


## 👥 Authors

- **Ajmal**

---

## 📄 License

This project is open source and free to use for educational purposes.
