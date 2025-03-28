#include <bits/stdc++.h>

int cid = 0;


class Task {
    private:
        int id;
        std::string description;
        int status; // 0 - new, 1 - in progress, 2 - done(deleted)
        std::time_t createdAt;
        std::time_t updatedAt;
    public:
        Task(std::string description) {    
            id = cid++;
            this->description = description;
            status = 0;
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
        void changeStatus(int status) {
            this->status = status;
            auto now = std::chrono::system_clock::now();
            updatedAt = std::chrono::system_clock::to_time_t(now);
        }
        int getStatus() {
            return status;
        }
        void changeTask(std::string description) {
            this->description = description;
        }
        std::string getCreatedAt() {
            std::string createdStr = std::ctime(&createdAt);
            if (!createdStr.empty() && createdStr.back() == '\n') {
                createdStr.pop_back();
            }
            return createdStr;
        }
        std::string getUpdatedAt() {
            std::string createdStr = std::ctime(&updatedAt);
            if (!createdStr.empty() && createdStr.back() == '\n') {
                createdStr.pop_back();
            }
            return createdStr;
        }
};
void printLine(int index, std::vector<Task> &tasks) {
    auto i = tasks[index];
    std::cout << std::left
          << std::setw(5) << i.getID() << " | "
          << std::setw(16) << i.getDescription() << " | "
          << std::setw(3)  << i.getStatus() << " | "
          << std::setw(24) << i.getCreatedAt() << " | "
          << i.getUpdatedAt() << std::endl;
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
}
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
        }   else if (input == "help") {
            std::cout << "Available commands:\n"
                      << "  help  - Show this help menu\n"
                      << "  add <task> - Add a new task\n"
                      << "  exit  - Quit the application\n";
        }   else if (input.rfind("add ", 0) == 0) {
            std::string taskID = input.substr(4); // Получаем часть строки после "add "
            tasks.emplace_back(taskID);
            std::cout << "Task added: " << taskID << std::endl;
        }   else if (input.rfind("delete ", 0) == 0) {
            std::string taskID = input.substr(7);
            int index = std::stoi(taskID); // так как индексация внутри класса совпадает с индексацией массив чиллим
            if (index >= 0 && index < tasks.size()) {
                tasks[index].changeStatus(2);
            } else {
                std::cout << "Invalid task index: " << taskID << std::endl;
            }
        }   else if (input.rfind("update ", 0) == 0) {
            std::string taskID = input.substr(7);
            size_t pos = taskID.find(' ');
            std::string idx = taskID.substr(0, pos);
            int ID = std::stoi(taskID.substr(0, pos));
            std::string taskName = taskID.substr(pos + 1);
            tasks[ID].changeTask(taskName);
            tasks[ID].changeStatus(1);
        }   else if (input == "list") {
            std::cout << "ID\tDescription\tStatus\tCreated At\t\tUpdated At" << std::endl;
            std::cout << "----------------------------------------------------------------------------------------" << std::endl;
            for (auto i : tasks) {
                printLine(i.getID(), tasks);
            }
        }   else if (input == "list done") {
            std::cout << "ID\tDescription\tStatus\tCreated At\t\tUpdated At" << std::endl;
            std::cout << "----------------------------------------------------------------------------------------" << std::endl;
            for (auto i : tasks) {
                if(i.getStatus() == 2)
                    printLine(i.getID(), tasks);
                
            }
        }   else if (input == "list todo") {
            std::cout << "ID\tDescription\tStatus\tCreated At\t\tUpdated At" << std::endl;
            for (auto i : tasks) {
                if(i.getStatus() == 0)
                    printLine(i.getID(), tasks);
                
            }
        }   else if (input == "list in-progress") {
            std::cout << "ID\tDescription\tStatus\tCreated At\t\tUpdated At" << std::endl;
            for (auto i : tasks) {
                if(i.getStatus() == 1)
                    printLine(i.getID(), tasks);
            }
            
        }   else {
            std::cout << "Unrecognized command: " << input << std::endl;
        }
    }
    for (auto i : tasks) {
        std::cout << i.getDescription() << " " << i.getStatus() << std::endl;
    }
    return 0;
}
