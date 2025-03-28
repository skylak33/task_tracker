#include <bits/stdc++.h>

int cid = 0;

enum class progress {
    toDo,
    inPogress,
    done
};

class Task {
    private:
        int id;
        std::string description;
        progress status;
        std::time_t createdAt;
        std::time_t updatedAt;
    public:
        Task(std::string description) {    
            id = cid++;
            this->description = description;
            status = progress::toDo;
            auto now = std::chrono::system_clock::now();
            createdAt = std::chrono::system_clock::to_time_t(now);
            updatedAt = std::chrono::system_clock::to_time_t(now);
        }
        std::string getDescription() {
            return description;
        }
        int getID() {
            return id;
        }
};

int main(int argc, char *argv[]) {
    std::string input;

    std::vector<Task> tasks;

    while (true) {
        std::cout << "task-tracker> ";
        if (!std::getline(std::cin, input)) {
            // Обработка конца ввода или ошибок
            break;
        }
        if (input == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        } else if (input == "help") {
            std::cout << "Available commands:\n"
                      << "  help  - Show this help menu\n"
                      << "  add <task> - Add a new task\n"
                      << "  exit  - Quit the application\n";
        } 
        else if (input.rfind("add ", 0) == 0) {
            std::string taskName = input.substr(4); // Получаем часть строки после "add "
            tasks.emplace_back(taskName);
            std::cout << "Task added: " << taskName << std::endl;}
        else {
            std::cout << "Unrecognized command: " << input << std::endl;
        }
    }
    for (auto i : tasks) {
        std::cout << i.getDescription() << std::endl;
    }
    return 0;
}