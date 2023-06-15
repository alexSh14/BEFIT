#include "Function.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    cout << "Журнал учета клиентов и тренеров: \n";
    cout << "Выберите действие:\n";

    cout << "1 - Добавить персональные данные в файл\n";
    cout << "2 - Добавить клиента в файл\n";
    cout << "3 - Добавить тренера в файл\n";
    cout << "4 - Удалить запись из файла по имени\n";
    cout << "5 - Вывести содержимое файла на экран\n";
    cout << "6 - Вывести информацию по имени из файла на экран\n";
    cout << "7 - Записать на тренировку\n";

    int command;
    cin >> command;
    cin.ignore();
    switch (command) {
    case 1: {
        string filename = "persons";
        Person person;
        person.Read(cin);
        AddPersonToFile(filename, person);
        break;
    }
    case 2: {
        string filename = "clients";
        Client client;
        client.Read(cin);
        AddPersonToFile(filename, client);
        break;
    }
    case 3: {
        string filename = "trainers";
        Trainer trainer;
        trainer.Read(cin);
        AddPersonToFile(filename, trainer);
        break;
    }
    case 4: {
        string filename;
        cout << "Введите имя файла: ";
        getline(cin, filename);
        string name;
        cout << "Введите имя, которое нужно удалить: ";
        getline(cin, name);
        if (FindNameInFile(filename, name)) {
            DeletePersonFromFile(filename, name);
        }
        else {
            cout << "Имя не найдено в файле." << endl;
        }
        break;
    }
    case 5: {
        string filename;
        cout << "Введите имя файла: ";
        getline(cin, filename);
        DisplayFileContents(filename);
        break;
    }
    case 6: {
        string filename;
        cout << "Введите имя файла: ";
        getline(cin, filename);
        string name;
        cout << "Введите имя, которое нужно найти: ";
        getline(cin, name);
        DisplayPersonInfo(filename, name);
        break;
    }
    case 7: {
        string full_name, workout_name, workout_date, workout_time;
        cout << "Введите данные тренировки:\n";
        cout << "ФИО клиента: ";
        getline(cin >> ws, full_name);
        ifstream file("clients"); // открыть файл для чтения
        if (!file.is_open()) // проверяем, удалось ли открыть файл
        {
            cout << "Не удалось открыть файл!" << endl;
            return 1;
        }
        string search_string = full_name; // зададим поиcк введенного ФИО клиента в файле client.txt
        string line;
        bool found = false;
        while (getline(file, line)) // считываем строки из файла
        {
            if (line == search_string) // ищем ФИО
            {
                found = true;
                ofstream file("Journal_training", ios::app); // открываем файл для добавления ФИО в журнал тренировок
                if (file.is_open()) { // проверяем, открылся ли файл
                    file << full_name << "\n";// добавляем строку в файл
                }
                file.close(); // закрываем файл
                cout << "Выберите тренировку: " << endl;
                cout << "1 - Йога\n";
                cout << "2 - Зумба\n";
                int training_name;
                cin >> training_name;
                switch (training_name) {
                case 1: {

                    ifstream file("sheduleYoga"); // открываем файл для чтения
                    if (file.is_open()) { // проверяем, открылся ли файл
                        string line;
                        while (getline(file, line)) { // считываем строки из файла
                            cout << line << endl; // выводим их на экран
                        }
                        file.close(); // закрываем файл
                        cout << "Выберите дату тренировки: " << endl;
                        int training_date;
                        cin >> training_date;
                        switch (training_date) {
                        case 1: {
                            ifstream file("sheduleYoga");
                            if (file.is_open()) {
                                string line;
                                if (getline(file, line)) {
                                    if (getline(file, line)) { // считываем вторую строку
                                    }
                                    ofstream file("Journal_training", ios::app); // открываем файл для добавления ФИО в журнал тренировок
                                    if (file.is_open()) { // проверяем, открылся ли файл
                                        file << line << "\n";// добавляем строку в файл
                                    }
                                    file.close(); // закрываем файл
                                    break;
                                }
                            }

                        }
                        case 2: {
                            ifstream file("sheduleYoga");
                            if (file.is_open()) {
                                string line;
                                if (getline(file, line)) {
                                    if (getline(file, line)) { // считываем вторую строку
                                        if (getline(file, line)) { // считываем вторую строку
                                        }
                                        ofstream file("Journal_training", ios::app); // открываем файл для добавления ФИО в журнал тренировок
                                        if (file.is_open()) { // проверяем, открылся ли файл
                                            file << line << "\n";// добавляем строку в файл
                                        }
                                        file.close(); // закрываем файл
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        }
                        file.close(); // закрываем файл
                    }
                    else {
                        cout << "Unable to open file" << endl;
                    }
                    break;

                }
                case 2: {

                    ifstream file("sheduleZumba"); // открываем файл для чтения
                    if (file.is_open()) { // проверяем, открылся ли файл
                        string line;
                        while (getline(file, line)) { // считываем строки из файла
                            cout << line << endl; // выводим их на экран
                        }
                        file.close(); // закрываем файл
                        cout << "Выберите дату тренировки: " << endl;
                        int training_date;
                        cin >> training_date;
                        switch (training_date) {
                        case 1: {

                            ifstream file("sheduleZumba");
                            if (file.is_open()) {
                                string line;
                                if (getline(file, line)) {
                                    if (getline(file, line)) { // считываем вторую строку

                                    }
                                    ofstream file("Journal_training.txt", ios::app); // открываем файл для добавления ФИО в журнал тренировок
                                    if (file.is_open()) { // проверяем, открылся ли файл

                                        file << line << "\n";// добавляем строку в файл
                                    }
                                    file.close(); // закрываем файл
                                    break;
                                }
                            }

                        }

                        case 2: {
                            ifstream file("sheduleZumba");
                            if (file.is_open()) {
                                string line;
                                if (getline(file, line)) {
                                    if (getline(file, line)) { // считываем вторую строку
                                        if (getline(file, line)) { // считываем вторую строку

                                        }
                                        ofstream file("Journal_training", ios::app); // открываем файл для добавления ФИО в журнал тренировок
                                        if (file.is_open()) { // проверяем, открылся ли файл

                                            file << line << "\n";// добавляем строку в файл
                                        }
                                        file.close(); // закрываем файл
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        }

                        file.close(); // закрываем файл
                    }
                    else {
                        cout << "Unable to open file" << endl;
                    }
                    break;
                }
                }

                cout << "Запись на тренировку добавлена\n";








                break;
            }
        }
        if (!found) // если ФИО не найдено
        {
            cout << "ФИО не найдено!" << endl;
            cout << "Хотите добавить клиента? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y') {
                string full_name, phone, email, start_date, end_date;
                cout << "Введите данные клиента:\n";
                cout << "ФИО: ";
                getline(cin >> ws, full_name);
                cout << "Телефон: ";
                getline(cin >> ws, phone);
                cout << "Email: ";
                getline(cin >> ws, email);
                cout << "Дата начала абонемента: ";
                getline(cin >> ws, start_date);
                cout << "Дата окончания абонемента: ";
                getline(cin >> ws, end_date);
                Client client{ full_name, phone, email, start_date, end_date };
                //journal.add_client(client);
                cout << "Клиент добавлен\n";
                //Сохраним информацию в файл
                ofstream file("clients", ios::app); // открываем файл для добавления
                if (file.is_open()) { // проверяем, открылся ли файл
                    file << full_name << "\n" << "тел.: " << phone << "\n" << "эл.почта : " << email << "\n" << "срок абонемента: " << start_date << "-" << end_date << "\n" << endl; // добавляем строку в файл
                    file.close(); // закрываем файл
                }
                else {
                    cout << "Unable to open file" << endl;
                }
                break;
            }
        }
        file.close(); // закрываем файл
        break;
    }
    default:
        cout << "Неправильный ввод команды." << endl;
        break;
    }

    return 0;
}