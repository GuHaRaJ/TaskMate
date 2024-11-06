#include "task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>

std::vector<Task> tasks;

void addTask(const std::string& taskDescription, const std::string& priority, int days) {
    Task newTask(taskDescription, priority, days);
    tasks.push_back(newTask);

    std::ofstream outFile("tasks.txt", std::ios::app);
    outFile << taskDescription << "|" << priority << "|" << days << "\n";
    outFile.close();
}

void loadTasks() {
    std::ifstream inFile("tasks.txt");
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string description, priority;
        int days;
        std::getline(ss, description, '|');
        std::getline(ss, priority, '|');
        ss >> days;
        tasks.push_back(Task(description, priority, days));
    }
    inFile.close();
}

void viewTasks() {
    if (tasks.empty()) {
        std::cout << "No tasks available. 📝\n";
        return;
    }

    for (const Task& task : tasks) {
        task.displayTask();
        std::cout << "-----------------------\n";
    }
}

void deleteTask(const std::string& taskDescription) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&taskDescription](const Task& task) {
        return task.getDescription() == taskDescription;
    });

    if (it == tasks.end()) {
        std::cout << "Error: Task '" << taskDescription << "' not found. ❌\n";
    } else {
        tasks.erase(it, tasks.end());

        // Update file
        std::ofstream outFile("tasks.txt");
        for (const Task& task : tasks) {
            outFile << task.getDescription() << "|" << task.getPriority() << "|" << task.getDaysRemaining() << "\n";
        }
        outFile.close();
        std::cout << "Task '" << taskDescription << "' deleted successfully! 🗑️\n";
    }
}

void sortTasksByPriority() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& t1, const Task& t2) {
        std::vector<std::string> priorityOrder = {"High", "Medium", "Low"};
        return std::find(priorityOrder.begin(), priorityOrder.end(), t1.getPriority()) < 
               std::find(priorityOrder.begin(), priorityOrder.end(), t2.getPriority());
    });
}
