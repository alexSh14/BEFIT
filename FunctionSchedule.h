#pragma once

#include "iostream"
#include <fstream>
#include <string>
using namespace std;


//Добавление нового клента
void add_client(const std::string& filename) {
    string full_name, phone, email, start_date, end_date;
    cout << "Введите данные клиента:\n";
    cout << "ФИО: ";
    getline(std::cin >> std::ws, full_name);
    cout << "Телефон: ";
    getline(std::cin >> std::ws, phone);
    cout << "Email: ";
    getline(std::cin >> std::ws, email);
    cout << "Дата начала абонемента: ";
    getline(std::cin >> std::ws, start_date);
    cout << "Дата окончания абонемента: ";
    getline(std::cin >> std::ws, end_date);

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << full_name << "\n" << "тел.: " << phone << "\n" << "эл.почта : " << email << "\n" << "срок абонемента: " << start_date << "-" << end_date << "\n" << std::endl;
        file.close();
        std::cout << "Клиент добавлен\n";
    }
    else {
        std::cout << "Unable to open file\n";
    }
}
