#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class Task {
private:
    std::string title;
    std::string description;
    std::string dueDate;
    bool completed;

public:
    Task(std::string title, std::string description, std::string dueDate, bool completed = false)
        : title(title), description(description), dueDate(dueDate), completed(completed) {}

    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getDueDate() const { return dueDate; }
    bool isCompleted() const { return completed; }

    void markAsCompleted() { completed = true; }

    void displayTask() const {
        std::cout << "Title: " << title << "\nDescription: " << description
                  << "\nDue Date: " << dueDate << "\nCompleted: " << (completed ? "Yes" : "No") << std::endl;
    }

    // Function to compare tasks by due date (ascending)
    static bool compareByDate(const Task &a, const Task &b) {
        return a.dueDate < b.dueDate;
    }
};

class TaskManager {
private:
    std::vector<Task> tasks;
    std::string filename;

public:
    TaskManager(const std::string &filename) : filename(filename) {}

    // Add a new task
    void addTask(const Task &task) {
        tasks.push_back(task);
    }

    // Load tasks from file
    void loadTasks() {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "File could not be opened!" << std::endl;
            return;
        }

        std::string title, description, dueDate;
        bool completed;
        while (file >> std::ws && getline(file, title)) {
            getline(file, description);
            file >> dueDate >> completed;
            tasks.emplace_back(title, description, dueDate, completed);
        }

        file.close();
    }

    // Save tasks to file
    void saveTasks() const {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "File could not be opened for writing!" << std::endl;
            return;
        }

        for (const auto &task : tasks) {
            file << task.getTitle() << "\n" << task.getDescription() << "\n" 
                 << task.getDueDate() << "\n" << task.isCompleted() << std::endl;
        }

        file.close();
    }

    // Display all tasks
    void displayTasks() const {
        for (const auto &task : tasks) {
            task.displayTask();
            std::cout << "------------------" << std::endl;
        }
    }

    // Mark a task as completed by title
    void completeTask(const std::string &taskTitle) {
        for (auto &task : tasks) {
            if (task.getTitle() == taskTitle) {
                task.markAsCompleted();
                std::cout << "Task marked as completed." << std::endl;
                return;
            }
        }
        std::cerr << "Task not found!" << std::endl;
    }

    // Sort tasks by due date
    void sortTasksByDate() {
        std::sort(tasks.begin(), tasks.end(), Task::compareByDate);
    }
};

int main() {
    TaskManager manager("tasks.txt");

    // Load tasks from file
    manager.loadTasks();

    // Add a new task
    manager.addTask(Task("Finish Project", "Complete the coding assignment", "2024-11-01"));
    manager.addTask(Task("Job Application", "Apply to tech companies", "2024-10-25"));

    // Sort tasks by due date
    manager.sortTasksByDate();

    // Display tasks
    std::cout << "Tasks after sorting by due date:\n";
    manager.displayTasks();

    // Complete a task
    std::cout << "\nMarking 'Job Application' as completed.\n";
    manager.completeTask("Job Application");

    // Save tasks to file
    manager.saveTasks();

    return 0;
}
