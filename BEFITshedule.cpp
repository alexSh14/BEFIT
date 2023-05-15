// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"
int main() {
    setlocale(LC_ALL, "Rus");
    // Загрузка расписания тренировок по йоге
    std::vector<YogaTraining> yoga_schedule = {
        { {1, 6, 2023}, {9, 0}, {"Йога-центр", "ул. Пушкина, 10"} },
        { {3, 6, 2023}, {15, 0}, {"Студия йоги", "ул. Лермонтова, 5"} },
        { {5, 6, 2023}, {11, 0}, {"Фитнес-клуб", "ул. Гоголя, 20"} }
    };

    // Загрузка расписания тренировок по зумбе
    std::vector<ZumbaTraining> zumba_schedule = {
        { {2, 6, 2023}, {10, 0}, {"Танцевальный зал", "ул. Толстого, 15"} },
        { {4, 6, 2023}, {16, 0}, {"Студия танцев", "ул. Пушкина, 5"} },
        { {6, 6, 2023}, {12, 0}, {"Фитнес-центр", "ул. Чехова, 12"} }
    };

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

