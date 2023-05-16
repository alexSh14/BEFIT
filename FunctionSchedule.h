#pragma once
#include "Header.h"
#include "FunctionSchedule.h"
#include <fstream>
#include <sstream>
void printSchedule(const std::vector<YogaTraining>& yoga_schedule, const std::vector<ZumbaTraining>& zumba_schedule) {
    // ����� ���������� ���������� �� ����
    std::cout << "���������� ���������� �� ����:" << std::endl;
    for (const auto& training : yoga_schedule) {
        std::cout << "����: " << training.date.day << "." << training.date.month << "." << training.date.year << std::endl;
        std::cout << "�����: " << training.time.hour << ":" << training.time.minute << std::endl;
        std::cout << "�����: " << training.place.name << ", " << training.place.address << std::endl;
        std::cout << std::endl;
    }

    // ����� ���������� ���������� �� �����
    std::cout << "���������� ���������� �� �����:" << std::endl;
    for (const auto& training : zumba_schedule) {
        std::cout << "����: " << training.date.day << "." << training.date.month << "." << training.date.year << std::endl;
        std::cout << "�����: " << training.time.hour << ":" << training.time.minute << std::endl;
        std::cout << "�����: " << training.place.name << ", " << training.place.address << std::endl;
        std::cout << std::endl;
    }
}
// ������� ��������� ��� �����, �� �������� ����� ��������� ������, � ����� ������ �� ��� �������, � ������� ����� �������� ���������� 
// ���������� �� ���� � ����� ��������������.������� ���������� true, ���� ������ ����� ������ �������, � false � ��������� ������.
bool readScheduleFromFile(const std::string& file_name, std::vector<YogaTraining>& yoga_schedule, std::vector<ZumbaTraining>& zumba_schedule) {
    std::ifstream input_file(file_name);
    if (!input_file) {
        std::cerr << "������ �������� �����" << std::endl;
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