#pragma once
#include "Header.h"
#include "FunctionSchedule.h"
#include <fstream>
#include <sstream>

// Функция принимает имя файла, из которого нужно прочитать данные, а также ссылки на два вектора, в которые будут записаны расписания 
// тренировок по йоге и зумбе соответственно.Функция возвращает true, если чтение файла прошло успешно, и false в противном случае:
bool readScheduleFromFile(const std::string& file_name, std::vector<YogaTraining>& yoga_schedule, std::vector<ZumbaTraining>& zumba_schedule) {
    std::ifstream input_file(file_name);
    if (!input_file) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return false;
    }

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

    return true;
}
void printSchedule(const std::vector<YogaTraining>& yoga_schedule, const std::vector<ZumbaTraining>& zumba_schedule) {
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
}
