#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <limits>

using namespace std;
namespace fs = std::filesystem;

// ============================================================
//  PRESENTATION LAYER  –  Menu & Input Validator
// ============================================================

// Clear the terminal screen (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pause and wait for the user to press Enter
void pressEnterToContinue() {
    cout << "\n  Press ENTER to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Print a styled separator line
void printLine(char ch = '-', int len = 55) {
    cout << "  ";
    for (int i = 0; i < len; i++) cout << ch;
    cout << "\n";
}

// Validate that the user entered a number in a given range
int getValidChoice(int minVal, int maxVal) {
    int choice;
    while (true) {
        cout << "  Enter your choice [" << minVal << "-" << maxVal << "]: ";
        if (cin >> choice && choice >= minVal && choice <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid input. Please try again.\n";
    }
}

// Display the main menu
void showMainMenu() {
    clearScreen();
    printLine('=');
    cout << "        THE FILE MANAGEMENT SYSTEM\n";
    cout << "     University of Kotli AJK  |  Session 2023-2027\n";
    printLine('=');
    cout << "\n";
    cout << "   ------- FILE OPERATIONS -------\n";
    cout << "   1.  Create a New File\n";
    cout << "   2.  Read / Display a File\n";
    cout << "   3.  Write / Update a File\n";
    cout << "   4.  Append Data to a File\n";
    cout << "   5.  Delete a File\n";
    cout << "   6.  Rename a File\n";
    cout << "\n";
    cout << "   ------- DIRECTORY OPERATIONS -------\n";
    cout << "   7.  Create a Directory\n";
    cout << "   8.  Delete a Directory\n";
    cout << "   9.  List Files in a Directory\n";
    cout << "\n";
    cout << "   ------- SYSTEM -------\n";
    cout << "   10. Display File Information\n";
    cout << "   0.  Exit\n";
    cout << "\n";
    printLine('-');
}

// ============================================================
//  LOGIC LAYER  –  File Operations  (uses fstream / iostream)
// ============================================================

// ---- 1. Create a New File ----------------------------------
void createFile() {
    clearScreen();
    printLine('=');
    cout << "        CREATE A NEW FILE\n";
    printLine('=');

    string filename;
    cout << "  Enter the file name (e.g. notes.txt): ";
    getline(cin, filename);

    if (filename.empty()) {
        cout << "  [!] File name cannot be empty.\n";
        pressEnterToContinue();
        return;
    }

    // Check for duplicate
    if (fs::exists(filename)) {
        cout << "  [!] File \"" << filename << "\" already exists.\n";
        pressEnterToContinue();
        return;
    }

    ofstream file(filename);
    if (file.is_open()) {
        file.close();
        cout << "  [OK] File \"" << filename << "\" created successfully.\n";
    } else {
        cout << "  [!] Error: Could not create file.\n";
    }
    pressEnterToContinue();
}

// ---- 2. Read / Display a File ------------------------------
void readFile() {
    clearScreen();
    printLine('=');
    cout << "        READ / DISPLAY FILE\n";
    printLine('=');

    string filename;
    cout << "  Enter the file name to read: ";
    getline(cin, filename);

    if (!fs::exists(filename)) {
        cout << "  [!] File \"" << filename << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    ifstream file(filename);
    if (file.is_open()) {
        printLine('-');
        cout << "  --- Contents of \"" << filename << "\" ---\n\n";
        string line;
        bool empty = true;
        while (getline(file, line)) {
            cout << "  " << line << "\n";
            empty = false;
        }
        if (empty) cout << "  (File is empty)\n";
        printLine('-');
        file.close();
    } else {
        cout << "  [!] Error: Could not open file.\n";
    }
    pressEnterToContinue();
}

// ---- 3. Write / Overwrite a File ---------------------------
void writeFile() {
    clearScreen();
    printLine('=');
    cout << "        WRITE / UPDATE FILE\n";
    printLine('=');
    cout << "  NOTE: This will OVERWRITE all existing content.\n";
    printLine('-');

    string filename;
    cout << "  Enter the file name: ";
    getline(cin, filename);

    if (!fs::exists(filename)) {
        cout << "  [!] File \"" << filename << "\" does not exist.\n"
             << "      Create the file first (Option 1).\n";
        pressEnterToContinue();
        return;
    }

    ofstream file(filename, ios::trunc);   // trunc = overwrite
    if (file.is_open()) {
        cout << "  Type your content below.\n"
             << "  Type \"DONE\" on a new line to finish.\n";
        printLine('-');

        string line;
        while (true) {
            getline(cin, line);
            if (line == "DONE") break;
            file << line << "\n";
        }
        file.close();
        cout << "  [OK] File \"" << filename << "\" updated successfully.\n";
    } else {
        cout << "  [!] Error: Could not open file for writing.\n";
    }
    pressEnterToContinue();
}

// ---- 4. Append Data to a File ------------------------------
void appendFile() {
    clearScreen();
    printLine('=');
    cout << "        APPEND DATA TO FILE\n";
    printLine('=');
    cout << "  NOTE: This will ADD content to the end of the file.\n";
    printLine('-');

    string filename;
    cout << "  Enter the file name: ";
    getline(cin, filename);

    if (!fs::exists(filename)) {
        cout << "  [!] File \"" << filename << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    ofstream file(filename, ios::app);    // app = append
    if (file.is_open()) {
        cout << "  Type your content below.\n"
             << "  Type \"DONE\" on a new line to finish.\n";
        printLine('-');

        string line;
        while (true) {
            getline(cin, line);
            if (line == "DONE") break;
            file << line << "\n";
        }
        file.close();
        cout << "  [OK] Data appended to \"" << filename << "\" successfully.\n";
    } else {
        cout << "  [!] Error: Could not open file for appending.\n";
    }
    pressEnterToContinue();
}

// ---- 5. Delete a File --------------------------------------
void deleteFile() {
    clearScreen();
    printLine('=');
    cout << "        DELETE A FILE\n";
    printLine('=');

    string filename;
    cout << "  Enter the file name to delete: ";
    getline(cin, filename);

    // Verify existence before deletion
    if (!fs::exists(filename)) {
        cout << "  [!] File \"" << filename << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    // Confirm before deleting
    char confirm;
    cout << "  Are you sure you want to delete \"" << filename << "\"? (y/n): ";
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        if (fs::remove(filename)) {
            cout << "  [OK] File \"" << filename << "\" deleted successfully.\n";
        } else {
            cout << "  [!] Error: Could not delete file.\n";
        }
    } else {
        cout << "  [--] Delete operation cancelled.\n";
    }
    pressEnterToContinue();
}

// ---- 6. Rename a File --------------------------------------
void renameFile() {
    clearScreen();
    printLine('=');
    cout << "        RENAME A FILE\n";
    printLine('=');

    string oldName, newName;
    cout << "  Enter the current file name: ";
    getline(cin, oldName);

    if (!fs::exists(oldName)) {
        cout << "  [!] File \"" << oldName << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    cout << "  Enter the new file name   : ";
    getline(cin, newName);

    if (newName.empty()) {
        cout << "  [!] New file name cannot be empty.\n";
        pressEnterToContinue();
        return;
    }

    if (fs::exists(newName)) {
        cout << "  [!] A file named \"" << newName << "\" already exists.\n";
        pressEnterToContinue();
        return;
    }

    try {
        fs::rename(oldName, newName);
        cout << "  [OK] File renamed from \"" << oldName
             << "\" to \"" << newName << "\" successfully.\n";
    } catch (const fs::filesystem_error& e) {
        cout << "  [!] Error: " << e.what() << "\n";
    }
    pressEnterToContinue();
}

// ============================================================
//  LOGIC LAYER  –  Directory Operations  (uses std::filesystem)
// ============================================================

// ---- 7. Create a Directory ---------------------------------
void createDirectory() {
    clearScreen();
    printLine('=');
    cout << "        CREATE A DIRECTORY\n";
    printLine('=');

    string dirName;
    cout << "  Enter the directory name: ";
    getline(cin, dirName);

    if (dirName.empty()) {
        cout << "  [!] Directory name cannot be empty.\n";
        pressEnterToContinue();
        return;
    }

    if (fs::exists(dirName)) {
        cout << "  [!] Directory \"" << dirName << "\" already exists.\n";
        pressEnterToContinue();
        return;
    }

    if (fs::create_directory(dirName)) {
        cout << "  [OK] Directory \"" << dirName << "\" created successfully.\n";
    } else {
        cout << "  [!] Error: Could not create directory.\n";
    }
    pressEnterToContinue();
}

// ---- 8. Delete a Directory ---------------------------------
void deleteDirectory() {
    clearScreen();
    printLine('=');
    cout << "        DELETE A DIRECTORY\n";
    printLine('=');

    string dirName;
    cout << "  Enter the directory name to delete: ";
    getline(cin, dirName);

    if (!fs::exists(dirName)) {
        cout << "  [!] Directory \"" << dirName << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    if (!fs::is_directory(dirName)) {
        cout << "  [!] \"" << dirName << "\" is not a directory.\n";
        pressEnterToContinue();
        return;
    }

    // Safety check: warn if not empty
    bool isEmpty = fs::is_empty(dirName);
    if (!isEmpty) {
        cout << "  [!] WARNING: Directory is NOT empty!\n";
    }

    char confirm;
    cout << "  Are you sure you want to delete \"" << dirName << "\"? (y/n): ";
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm == 'y' || confirm == 'Y') {
        try {
            uintmax_t removed = fs::remove_all(dirName);
            cout << "  [OK] Directory \"" << dirName
                 << "\" deleted (" << removed << " item(s) removed).\n";
        } catch (const fs::filesystem_error& e) {
            cout << "  [!] Error: " << e.what() << "\n";
        }
    } else {
        cout << "  [--] Delete operation cancelled.\n";
    }
    pressEnterToContinue();
}

// ---- 9. List Files in a Directory --------------------------
void listDirectory() {
    clearScreen();
    printLine('=');
    cout << "        LIST FILES IN DIRECTORY\n";
    printLine('=');

    string dirName;
    cout << "  Enter directory path (press ENTER for current directory): ";
    getline(cin, dirName);

    if (dirName.empty()) dirName = ".";

    if (!fs::exists(dirName)) {
        cout << "  [!] Directory \"" << dirName << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    printLine('-');
    cout << "  Listing: " << fs::absolute(dirName).string() << "\n";
    printLine('-');

    int fileCount = 0, dirCount = 0;
    cout << "  TYPE        SIZE (bytes)    NAME\n";
    printLine('-');

    for (const auto& entry : fs::directory_iterator(dirName)) {
        string type;
        uintmax_t size = 0;

        if (entry.is_regular_file()) {
            type = "  [FILE]   ";
            size = entry.file_size();
            fileCount++;
        } else if (entry.is_directory()) {
            type = "  [DIR ]   ";
            dirCount++;
        } else {
            type = "  [OTHER]  ";
        }

        cout << type;
        if (entry.is_regular_file())
            cout << "  " << size;
        else
            cout << "  ---";

        // Pad columns
        string sizeStr = entry.is_regular_file() ? to_string(size) : "---";
        int pad = 14 - (int)sizeStr.size();
        for (int i = 0; i < pad; i++) cout << " ";

        cout << entry.path().filename().string() << "\n";
    }

    if (fileCount == 0 && dirCount == 0) {
        cout << "  (Directory is empty)\n";
    }

    printLine('-');
    cout << "  Total: " << fileCount << " file(s),  "
         << dirCount << " directory(ies)\n";

    pressEnterToContinue();
}

// ============================================================
//  LOGIC LAYER  –  File Information Display
// ============================================================

// ---- 10. Display File Information --------------------------
void displayFileInfo() {
    clearScreen();
    printLine('=');
    cout << "        DISPLAY FILE INFORMATION\n";
    printLine('=');

    string filename;
    cout << "  Enter file or directory name: ";
    getline(cin, filename);

    if (!fs::exists(filename)) {
        cout << "  [!] \"" << filename << "\" does not exist.\n";
        pressEnterToContinue();
        return;
    }

    printLine('-');
    cout << "  Name          : " << fs::path(filename).filename().string() << "\n";
    cout << "  Absolute Path : " << fs::absolute(filename).string() << "\n";

    if (fs::is_regular_file(filename)) {
        cout << "  Type          : Regular File\n";
        cout << "  Size          : " << fs::file_size(filename) << " bytes\n";
    } else if (fs::is_directory(filename)) {
        cout << "  Type          : Directory\n";

        // Count items inside
        int items = 0;
        for (const auto& e : fs::directory_iterator(filename)) {
            (void)e;
            items++;
        }
        cout << "  Items Inside  : " << items << "\n";
    } else {
        cout << "  Type          : Other / Special File\n";
    }

    // Last write time
    auto ftime = fs::last_write_time(filename);
    auto sctp  = chrono::time_point_cast<chrono::system_clock::duration>(
                    ftime - fs::file_time_type::clock::now()
                    + chrono::system_clock::now());
    time_t cftime = chrono::system_clock::to_time_t(sctp);
    cout << "  Last Modified : " << ctime(&cftime);

    printLine('-');
    pressEnterToContinue();
}

// ============================================================
//  APPLICATION EXECUTION LAYER  –  Main (Core Controller)
// ============================================================

int main() {
    int choice;

    // System starts – initialize and display menu
    do {
        showMainMenu();
        choice = getValidChoice(0, 10);

        // Route user command to the correct module
        switch (choice) {
            case 1:  createFile();      break;
            case 2:  readFile();        break;
            case 3:  writeFile();       break;
            case 4:  appendFile();      break;
            case 5:  deleteFile();      break;
            case 6:  renameFile();      break;
            case 7:  createDirectory(); break;
            case 8:  deleteDirectory(); break;
            case 9:  listDirectory();   break;
            case 10: displayFileInfo(); break;
            case 0:
                clearScreen();
                printLine('=');
                cout << "  Thank you for using The File Management System.\n";
                cout << "  Developed by: Ajmal, Subhan Majeed, M. Ehtisham Ashfaq\n";
                cout << "  University of Kotli AJK  |  Session 2023-2027\n";
                printLine('=');
                cout << "\n";
                break;
            default:
                cout << "  [!] Invalid option.\n";
                break;
        }

    } while (choice != 0);   // Repeat until exit is selected

    // System terminates safely
    return 0;
}
