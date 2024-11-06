#include <iostream>
#include <string>
#include "task.h"

int main() {
    loadTasks();  // Load tasks from file when the program starts

    while (true) {
        std::cout << "\nTaskMate CLI 💻\n";
        std::cout << "1. Add Task 📝\n2. View Tasks 👀\n3. Delete Task ❌\n4. Sort Tasks by Priority 🔽\n5. Exit 🚪\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();  // To ignore newline character after entering choice

        if (choice == 1) {
            std::string description, priority;
            int days;
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            std::cout << "Enter priority (Low/Medium/High): ";
            std::getline(std::cin, priority);
            std::cout << "Enter number of days to complete the task: ";
            std::cin >> days;
            std::cin.ignore();  // To ignore newline after entering days

            addTask(description, priority, days);
            std::cout << "Task added successfully! 🎉\n";
        } 
        else if (choice == 2) {
            viewTasks();
        }
        else if (choice == 3) {
            std::string descriptionToDelete;
            std::cout << "Enter task description to delete: ";
            std::getline(std::cin, descriptionToDelete);
            deleteTask(descriptionToDelete);
        }
        else if (choice == 4) {
            sortTasksByPriority();
            std::cout << "Tasks sorted by priority. 🔝\n";
        }
        else if (choice == 5) {
            std::cout << "Exiting TaskMate. See you next time! 👋\n";
            break;
        } 
        else {
            std::cout << "Invalid choice. Please try again. ❌\n";
        }
    }

    return 0;
}


//g++ -std=c++11 taskmate.cpp task.cpp -o taskmate && ./taskmate
