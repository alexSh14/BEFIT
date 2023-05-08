// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

// Функция отображения расписания занятий
void printSchedule(const std::map<std::string, std::vector<std::string>>& schedule) {
    std::cout << "Fitness Class Schedule:\n";
    for (const auto& entry : schedule) {
        std::cout << entry.first << ":\n";
        for (const auto& day : entry.second) {
            std::cout << "  " << day << '\n';
        }
    }
}

// Функция для записи клиента на занятие
void signUp(const std::string& class_name, const std::string& day) {
    // Открытие файла для записи, добавление записи в конец файла
    std::ofstream outfile(class_name + "_" + day + ".txt", std::ios_base::app);
    if (!outfile.is_open()) {
        std::cout << "Unable to open file for writing\n";
        return;
    }

    std::string name;
    std::cout << "Enter your name:\n";
    std::cin >> name;

    outfile << name << '\n';
    outfile.close();

    std::cout << "You have successfully signed up for " << class_name << " on " << day << ".\n";
}

int main() {
    std::ifstream file("schedule.txt");
    std::string line;
    std::string current_day = "";
    std::map<std::string, std::vector<std::string>> schedule;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (line.back() == ':') {
                current_day = line;
            }
            else if (line.find("yoga") != std::string::npos || line.find("zumba") != std::string::npos) {
                schedule[line].push_back(current_day);
            }
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file\n";
        return 1;
    }

    int choice = 0;
    while (choice != 3) {
        std::cout << "Select an option:\n";
        std::cout << "1. View Fitness Class Schedule\n";
        std::cout << "2. Sign up for a Fitness Class\n";
        std::cout << "3. Exit\n";

        std::cin >> choice;

        switch (choice) {
        case 1:
            printSchedule(schedule);
            break;
        case 2: {
            std::cout << "Enter the number of the Fitness Class you would like to sign up for:\n";
            std::cout << "1. yoga\n";
            std::cout << "2. zumba\n";
            int class_choice;
            std::cin >> class_choice;
            if (class_choice == 1) {
                std::cout << "Available yoga classes:\n";
                for (const auto& day : schedule["yoga"]) {
                    std::cout << "  " << day << '\n';
                }
                std::cout << "Enter the day you would like to sign up for (e.g. 'Monday'):\n";
                std::string day;
                std::cin >> day;
                signUp("yoga", day);
            }
            else if (class_choice == 2) {
                std::cout << "Available zumba classes:\n";
                for (const auto& day : schedule["zumba"]) {
                    std::cout << "  " << day << '\n';
                }
                std::cout << "Enter the day you would like to sign up for (e.g. 'Monday'):\n";
                std::string day;
                std::cin >> day;
                signUp("zumba", day);
            }
            else {
                std::cout << "Invalid choice. Please enter 1 or 2.\n";
            }
            break;
        }
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
            break;
        }
    }

    return 0;
}