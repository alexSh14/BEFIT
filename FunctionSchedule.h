#pragma once

#include "iostream"
#include <fstream>
#include <string>
#include <vector>

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
// Считывание файла
bool open_file_for_reading(ifstream& file, const string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return false;
    }
    // читаем файл здесь...
  
    return true;
}
//Добавление в файл
bool add_to_file(const string& filename, const string& data) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return false;
    }
    file << data << "\n";
    file.close();
    return true;
}

std::vector<std::string> readLinesFromFile(const std::string& filePath) {
    std::vector<std::string> lines; // создаем вектор строк для хранения строк из файла
    std::ifstream file(filePath); // открываем файл для чтения

    if (file.is_open()) { // проверяем, открылся ли файл
        std::string line;
        while (getline(file, line)) { // считываем строки из файла
            lines.push_back(line); // добавляем считанную строку в вектор строк
        }
        file.close(); // закрываем файл
    }

    return lines; // возвращаем вектор строк с содержимым файла
}
