// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"
#include <fstream>
#include <sstream>

int main() {
    setlocale(LC_ALL, "Rus");
    std::ifstream input_file("schedule.txt");
    if (!input_file) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::vector<YogaTraining> yoga_schedule;
    std::vector<ZumbaTraining> zumba_schedule;

    std::string line;
    std::string category;

    while (std::getline(input_file, line)) {
        std::istringstream iss(line);

        if (line == "YOGA") {
            category = "YOGA";
            continue;
        }
        else if (line == "ZUMBA") {
            category = "ZUMBA";
            continue;
        }

        Date date;
        Time time;
        Place place;

        char delimiter;
        iss >> date.day >> delimiter >> date.month >> delimiter >> date.year >> time.hour >> delimiter >> time.minute >> place.name >> place.address;

        if (category == "YOGA") {
            yoga_schedule.push_back({ date, time, place });
        }
        else if (category == "ZUMBA") {
            zumba_schedule.push_back({ date, time, place });
        }
    }

    // Вывод расписания тренировок по йоге
    std::cout << "Расписание тренировок по йоге:" << std::endl;
    for (const auto& training : yoga_schedule) {
        std::cout << "Дата: " << training.date.day << "." << training.date.month << "." << training.date.year << std::endl;
        std::cout << "Время: " << training.time.hour << ":" << training.time.minute << std::endl;
        std::cout << "Место: " << training.place.name << ", " << training.place.address << std::endl;
        std::cout << std::endl;
    }

    // Вывод расписания тренировок по зумбе
    std::cout << "Расписание тренировок по зумбе:" << std::endl;
    for (const auto& training : zumba_schedule) {
        std::cout << "Дата: " << training.date.day << "." << training.date.month << "." << training.date.year << std::endl;
        std::cout << "Время: " << training.time.hour << ":" << training.time.minute << std::endl;
        std::cout << "Место: " << training.place.name << ", " << training.place.address << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

