// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header.h"
#include "FunctionSchedule.h"
#include <fstream>
#include <sstream>

int main() {
    setlocale(LC_ALL, "Rus");

    std::vector<YogaTraining> yoga_schedule;
    std::vector<ZumbaTraining> zumba_schedule;

    if (!readScheduleFromFile("schedule.txt", yoga_schedule, zumba_schedule)) {
        return 1;
    }

    printSchedule(yoga_schedule, zumba_schedule);

    return 0;
}


