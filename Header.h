#pragma once
#include "Persons.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void DeletePersonFromFile(string filename, string name) {
    ifstream infile(filename);
    ofstream outfile("temp.txt");

    if (infile.good() && outfile.good()) {
        string line;
        bool found = false;

        while (getline(infile, line)) {
            if (line.find("Name: ") == 0 && line.substr(6) == name) {
                found = true;

                // skip lines until the next name is found
                while (getline(infile, line)) {
                    if (line.find("Name: ") == 0) {
                        infile.seekg(-static_cast<int>(line.length()) - 1, ios::cur);
                        break;
                    }
                }
            }
            else {
                outfile << line << endl;
            }
        }

        if (found) {
            cout << "Person deleted from file." << endl;
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }
        else {
            cout << "Error: name not found in file." << endl;
            remove("temp.txt");
        }
    }
    else {
        cout << "Error: could not open file." << endl;
    }

    infile.close();
    outfile.close();
}

void DisplayFileContents(string filename) {
    ifstream infile(filename);

    if (infile.good()) {
        string line;

        while (getline(infile, line)) {
            cout << line << endl;
        }
    }
    else {
        cout << "Error: could not open file." << endl;
    }

    infile.close();
}

void DisplayPersonInfo(string filename, string name) {
    ifstream infile(filename);

    if (infile.good()) {
        string line;
        bool found = false;

        while (getline(infile, line)) {
            if (line.find("Name: ") == 0 && line.substr(6) == name) {
                found = true;

                cout << line << endl;

                while (getline(infile, line)) {
                    if (line.find("Name: ") == 0) {
                        infile.seekg(-static_cast<int>(line.length()) - 1, ios::cur);
                        break;
                    }
                    else {
                        cout << line << endl;
                    }
                }

                break;
            }
        }

        if (!found) {
            cout << "Error: name not found in file." << endl;
        }
    }
    else {
        cout << "Error: could not open file." << endl;
    }

    infile.close();
}

bool FindNameInFile(string filename, string name_) {
    ifstream infile(filename);

    if (infile.good()) {
        string line;

        while (getline(infile, line)) {
            if (line.find("Name: ") == 0 && line.find(name_) != string::npos) {
                return true;
            }
        }
    }

    return false;
}

void AddPersonToFile(string filename, const Person& person) {
    ofstream outfile(filename, ios_base::app);

    if (outfile.good()) {
        person.Print(outfile);
        cout << "Person added to file." << endl;
    }
    else {
        cout << "Error: could not open file." << endl;
    }

    outfile.close();
}

string SelectTrainingDate(const string& scheduleFile) {
    ifstream file(scheduleFile);

    if (!file.is_open()) {
        cout << "Failed to open file " << scheduleFile << endl;
        return "";
    }

    string line;

    while (getline(file, line)) {
        cout << line << endl;
    }

    file.clear();
    file.seekg(0, ios::beg);

    cout << "Select training date: ";
    string training_date;
    getline(cin >> ws, training_date);

    switch (stoi(training_date)) {
    case 1: {
        getline(file, line);
        getline(file, training_date);
        break;
    }
    case 2: {
        getline(file, line);
        getline(file, line);
        getline(file, training_date);
        break;
    }
    default: {
        cout << "Invalid date selection!" << endl;
        break;
    }
    }

    file.close();
    return training_date;
}
void AddPerson(const string& filename, const string& type) {
    string name;
    cout << "Поиск имени в файле:\n";
    cout << "Введите имя: ";
    getline(cin >> ws, name);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удается открыть файл " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find("Name: ") == 0 && line.substr(6) == name) {
            found = true;
            cout << "Введенное имя существует в файле: \n";
            DisplayPersonInfo(filename,name);
            if (type == "WorkoutRecords") {
                cout << "Хотите добавить запись? (y/n): ";
                char choice;
                cin >> choice;
                cin.ignore();
                if ((choice == 'y') || (choice == 'Y')) {
                    cout << "Выберите тренировку: " << std::endl;
                    cout << "1 - Йога\n";
                    cout << "2 - Зумба\n";
                    int training_name;
                    cin >> training_name;
                    cin.ignore();
                    switch (training_name) {
                    case 1: {
                        const string selected_date = SelectTrainingDate("sheduleYoga");
                        if (!selected_date.empty()) {
                            ofstream file("Journal_training", ios::app);
                            if (file.is_open()) {
                                file << "Name: " << name << "\n";
                                file << selected_date << "\n";
                                file.close();
                                cout << "Запись на тренировку добавлена!" << endl;
                            }
                            else {
                                cout << "Не удается открыть файл Journal_training" << endl;
                            }
                        }
                        break;
                    }
                    case 2: {
                        const string selected_date = SelectTrainingDate("sheduleZumba");
                        if (!selected_date.empty()) {
                            std::ofstream file("Journal_training", ios::app);
                            if (file.is_open()) {
                                file << "Name: " << name << "\n";
                                file << selected_date << "\n";
                                file.close();
                                cout << "Запись на тренировку добавлена!" << endl;
                            }
                            else {
                                cout << "Не удается открыть файл Journal_training" << endl;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Неверный выбор даты!" << endl;
                        break;
                    }
                    }
                }
            }

            break;
        }
    }
    file.close();

    if (!found) {
        cout << "Имя не найдено!" << endl;
        cout << "Хотите добавить запись? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if ((choice == 'y') || (choice == 'Y')) {
            if (type == "Client") {
                Client client;
                client.Read(cin);
                AddPersonToFile(filename, client);
            }
            else if (type == "Trainer") {
                Trainer trainer;
                trainer.Read(cin);
                AddPersonToFile(filename, trainer);
            }
            else if (type == "WorkoutRecords") {
                std::cout << "Введите имя: ";
                std::getline(cin >> ws, name);
                std::ofstream file("Journal_training", ios::app);
                if (file.is_open()) {
                    file << "Name: " << name << "\n";
                    file.close();
                    cout << "Выберите тренировку: " << endl;
                    cout << "1 - Йога\n";
                    cout << "2 - Зумба\n";
                    int training_name;
                    cin >> training_name;
                    cin.ignore();
                    switch (training_name) {
                    case 1: {
                        const string selected_date = SelectTrainingDate("sheduleYoga");
                        if (!selected_date.empty()) {
                            ofstream file("Journal_training", ios::app);
                            if (file.is_open()) {
                                file << "Name: " << name << "\n";
                                file << selected_date << "\n";
                                file.close();
                                cout << "Запись на тренировку добавлена!" << std::endl;
                            }
                            else {
                                cout << "Не удается открыть файл Journal_training" << endl;
                            }
                        }
                        break;
                    }
                    case 2: {
                        const string selected_date = SelectTrainingDate("sheduleZumba");
                        if (!selected_date.empty()) {
                            ofstream file("Journal_training", ios::app);
                            if (file.is_open()) {
                                file << "Name: " << name << "\n";
                                file << selected_date << "\n";
                                file.close();
                                cout << "Запись на тренировку добавлена!" << endl;
                            }
                            else {
                                cout << "Не удается открыть файл Journal_training" << endl;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Неверный выбор даты!" << endl;
                        break;
                    }
                    }
                }
                else {
                    cout << "Не удается открыть файл Journal_training" << endl;
                }
            }
        }
    }
};
