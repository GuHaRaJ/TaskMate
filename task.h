#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

class Task {
private:
    std::string description;
    std::string priority;  // Low, Medium, High
    int daysRemaining;  // Days to complete the task
    std::string deadline;  // Calculated deadline (e.g., "2024-11-15")
    
public:
    Task(const std::string& desc, const std::string& prio, int days)
        : description(desc), priority(prio), daysRemaining(days) {
        calculateDeadline();
    }

    void calculateDeadline() {
        // Get the current date
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Add daysRemaining to current date
        ltm->tm_mday += daysRemaining;
        mktime(ltm);

        // Format the deadline date
        char deadlineStr[100];
        strftime(deadlineStr, sizeof(deadlineStr), "%Y-%m-%d", ltm);
        deadline = std::string(deadlineStr);
    }

    void displayTask() const {
        std::string priorityColor;
        std::string priorityEmoji;
        
        if (priority == "High") {
            priorityColor = "\033[1;31m"; // Red
            priorityEmoji = "🔥";
        } else if (priority == "Medium") {
            priorityColor = "\033[1;33m"; // Yellow
            priorityEmoji = "⚠️";
        } else {
            priorityColor = "\033[1;32m"; // Green
            priorityEmoji = "✅";
        }

        std::cout << priorityColor << "Task: " << description 
                  << "\033[0m\nPriority: " << priority << " " << priorityEmoji
                  << "\nDeadline: " << deadline << " ⏰" << std::endl;
    }

    std::string getDescription() const {
        return description;
    }

    std::string getPriority() const {
        return priority;
    }

    int getDaysRemaining() const {
        return daysRemaining;
    }

    std::string getDeadline() const {
        return deadline;
    }
};

// Function declarations
void addTask(const std::string& taskDescription, const std::string& priority, int days);
void loadTasks();
void viewTasks();
void deleteTask(const std::string& taskDescription);
void sortTasksByPriority();

#endif
