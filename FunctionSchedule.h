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
        cout << "Клиент добавлен\n";
    }
    else {
        std::cout << "Unable to open file\n";
    }
}
// Вывести на экран текст из файла
void printFileContents(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}
// 
void appendLinesToFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (inputFile.is_open()) {
        string line1, line2;
        if (getline(inputFile, line1) && getline(inputFile, line2)) {
            ofstream outputFile(outputFilename, std::ios::app);
            if (outputFile.is_open()) {
                outputFile << line1 << ",";
                outputFile << line2 <<endl;
                
            }
            outputFile.close();
        }
        inputFile.close();
    }
}
//
void appendLinesToFile2(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (inputFile.is_open()) {
        string line1, line2, line3;
        if (getline(inputFile, line1) && getline(inputFile, line2) && getline(inputFile, line3)) {
            ofstream outputFile(outputFilename, ios::app);
            if (outputFile.is_open()) {
                outputFile << line1 << ",";
                outputFile << line3 <<endl;
                

            }
            outputFile.close();
        }
        inputFile.close();
    }
}
//
void get_client_workouts(const string& full_name) {
    ifstream file("Journal_training.txt"); // открываем файл для чтения
    if (!file.is_open()) { // проверяем, удалось ли открыть файл
        cout << "Не удалось открыть файл!" << endl;
        return;
    }
    string search_string = full_name; // зададим поиск введенного ФИО клиента в файле workouts.txt
    string line;
    bool found = false;
    while (getline(file, line)) { // считываем строки из файла
        if (line == search_string) { // ищем ФИО
            found = true;
            cout << "Записи на тренировки для клиента " << full_name << ":" << endl;
            getline(file, line); // пропустим строку с ФИО клиента
            while (getline(file, line)) { // считываем строки с записями на тренировки для этого клиента
                if (line.empty()) { // если строка пустая, то все записи на тренировки для данного клиента были прочитаны
                    break;
                }
                cout << line << endl; // выводим строку на экран
            }
            break;
        }
    }
    if (!found) { // если ФИО не найдено
        cout << "ФИО не найдено!" << endl;
    }
    file.close(); // закрываем файл
}
