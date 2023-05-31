﻿
#include <vector>
#include <fstream>
#include "FunctionSchedule.h"


using namespace std;

class Client {
public:
    string full_name;
    string phone_number;
    string email;
    string subscription_start_date;
    string subscription_end_date;
};
class WorkoutRecord {
public:
    string workout_date;
    string workout_time;
    string workout_name;
    string trainer_name;
    string client_full_name;
};
class ClientJournal {
public:
    // Добавление нового клиента в журнал
    void add_client(const Client& client);

    // Удаление клиента из журнала
    void remove_client(const string& full_name);

    // Добавление записи на тренировку для конкретного клиента
    void add_workout_record(const string& full_name, const WorkoutRecord& record);

    // Удаление записи на тренировку для конкретного клиента
    void remove_workout_record(const string& full_name, const string& workout_date, const string& workout_time);

    // Поиск клиента по ФИ или номеру телефона
    Client find_client(const string& search_param);

    // Получение списка всех клиентов в журнале
    std::vector<Client> get_all_clients();

    // Получение списка всех записей на тренировки для конкретного клиента
    std::vector<WorkoutRecord> get_workout_records(const string& full_name);

    // Получение списка всех записей на тренировки за определенный период времени
    std::vector<WorkoutRecord> get_workout_records_by_period(const string& start_date, const string& end_date);

private:
    vector<Client> clients_;
    vector<WorkoutRecord> workout_records_;

    // Вспомогательная функция для поиска клиента
    bool matches_search_param(const Client& client, const string& search_param);
};
void ClientJournal::add_client(const Client& client) {
    clients_.push_back(client);
}

void ClientJournal::remove_client(const string& full_name) {
    auto it = find_if(clients_.begin(), clients_.end(), [full_name](const Client& client) {
        return client.full_name == full_name;
        });
    if (it != clients_.end()) {
        clients_.erase(it);
    }
}

void ClientJournal::add_workout_record(const string& full_name, const WorkoutRecord& record) {
    auto it = find_if(clients_.begin(), clients_.end(), [full_name](const Client& client) {
        return client.full_name == full_name;
        });
    if (it != clients_.end()) {
        workout_records_.push_back(record);
    }
}

void ClientJournal::remove_workout_record(const string& full_name, const string& workout_date, const string& workout_time) {
    auto it = find_if(workout_records_.begin(), workout_records_.end(), [full_name, workout_date, workout_time](const WorkoutRecord& record) {
        return record.client_full_name == full_name && record.workout_date == workout_date && record.workout_time == workout_time;
        });
    if (it != workout_records_.end()) {
        workout_records_.erase(it);
    }
}

Client ClientJournal::find_client(const string& search_param) {
    auto it = find_if(clients_.begin(), clients_.end(), [this, search_param](const Client& client) {
        return matches_search_param(client, search_param);
        });
    if (it != clients_.end()) {
        return *it;
    }
    else {
        // Возвращаем пустой объект Client, если клиент не найден
        return Client();
    }
}

vector<Client> ClientJournal::get_all_clients() {
    return clients_;
}

vector<WorkoutRecord> ClientJournal::get_workout_records(const string& full_name) {
    vector<WorkoutRecord> records;
    for (const auto& record : workout_records_) {
        if (record.client_full_name == full_name) {
            records.push_back(record);
        }
    }
    return records;
}

vector<WorkoutRecord> ClientJournal::get_workout_records_by_period(const string& start_date, const string& end_date) {
    vector<WorkoutRecord> records;
    for (const auto& record : workout_records_) {
        if (record.workout_date >= start_date && record.workout_date <= end_date) {
            records.push_back(record);
        }
    }
    return records;
}

bool ClientJournal::matches_search_param(const Client& client, const string& search_param) {
    return client.full_name == search_param || client.phone_number == search_param;
}



int main() {
    setlocale(LC_ALL, "rus");
    ClientJournal journal;
    cout << "Выберите действие:\n";
    cout << "1 - добавить клиента\n";
    cout << "2 - добавить запись на тренировку\n";
    cout << "3 - получить всех клиентов\n";
    cout << "4 - получить записи на тренировки для конкретного клиента\n";
    cout << "5 - получить записи на тренировки за определенный период времени\n";
    cout << "6 - удалить запись на тренировку для конкретного клиента\n";
    cout << "7 - удалить клиента из журнала\n";
    cout << "8 - найти клиента";
    cout << "0 - выход\n";

    int command;
    cin >> command;
    switch (command) {
    case 1: {
        add_client("client.txt");//Добавляем нового клиента
        break;
    }
    case 2: {
        string full_name, workout_name, workout_date, workout_time;
        cout << "Введите данные тренировки:\n";
        cout << "ФИО клиента: ";
        getline(cin >> ws, full_name);
        ifstream file("client.txt"); // открыть файл для чтения
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
                ofstream file("Journal_training.txt", ios::app); // открываем файл для добавления ФИО в журнал тренировок
                if (file.is_open()) { // проверяем, открылся ли файл
                    file << full_name << ",";// добавляем строку в файл
                }
                file.close(); // закрываем файл
                cout << "Выберите тренировку: " << endl;
                cout << "1 - Йога\n";
                cout << "2 - Зумба\n";
                int training_name;
                cin >> training_name;
                switch (training_name) {
                case 1: {

                    ifstream file("sheduleYoga.txt"); // открываем файл для чтения
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
                            appendLinesToFile("sheduleYoga.txt", "Journal_training.txt");
                          
                            break;
                        }
                        case 2: {
                            appendLinesToFile2("sheduleYoga.txt", "Journal_training.txt");
                            
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
                    ifstream file("sheduleZumba.txt"); // открываем файл для чтения
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
                            appendLinesToFile("sheduleZumba.txt", "Journal_training.txt");
                            break;
                                                           
                        }
                        case 2: {
                            appendLinesToFile2("sheduleZumba.txt", "Journal_training.txt");
                                    break;
                                
                            }
                            break;
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
                journal.add_client(client);
                cout << "Клиент добавлен\n";
                //Сохраним информацию в файл
                ofstream file("client.txt", ios::app); // открываем файл для добавления
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
    case 3: {
        printFileContents("client.txt");
        break;
    }

    case 4: 
    {
        string filename = "Journal_training.txt";
        string client_name = "Shtadler Andrey Andreech";

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Ошибка открытия файла" << endl;
            return 1;
        }

        vector<string> records;
        string line;
        while (getline(file, line)) {
            string name, training, date;
            size_t pos1 = 0, pos2 = 0;
            pos1 = line.find(',');
            if (pos1 != string::npos) {
                name = line.substr(0, pos1);
                pos2 = line.find(',', pos1 + 1);
                if (pos2 != string::npos) {
                    training = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    date = line.substr(pos2 + 1);
                    if (name == client_name) {
                        records.push_back(line);
                    }
                }
            }
        }

        file.close();

        if (records.empty()) {
            cout << "Записей для клиента " << client_name << " не найдено" << endl;
        }
        else {
            cout << "Записи для клиента " << client_name << ":" << endl;
            for (const string& record : records) {
                cout << record << endl;
            }
        }

        
    
        break;

    }

    case 5: {
        string start_date, end_date;
        cout << "Введите период времени (ДД.ММ.ГГГГ):\n";
        cout << "Начальная дата: ";
        getline(cin >> ws, start_date);
        cout << "Конечная дата: ";
        getline(cin >> ws, end_date);
        vector<WorkoutRecord> period_records = journal.get_workout_records_by_period(start_date, end_date);
        for (const auto& record : period_records) {
            cout << "Запись на тренировку: " << record.workout_name << " (" << record.workout_date << " " << record.workout_time << ")" << std::endl;
            break;
        }
    }
    case 6: {
        string client_name, workout_date, workout_time;
        cout << "Введите данные записи на тренировку:\n";
        cout << "ФИО клиента: ";
        getline(cin >> ws, client_name);
        cout << "Дата тренировки (ДД.ММ.ГГГГ): ";
        getline(cin >> ws, workout_date);
        cout << "Время тренировки (ЧЧ:ММ): ";
        getline(cin >> ws, workout_time);
        journal.remove_workout_record(client_name, workout_date, workout_time);
        cout << "Запись на тренировку удалена\n";
        break;
    }
    case 7: {
        string client_name;
        cout << "Введите ФИО клиента: ";
        getline(cin >> ws, client_name);
        journal.remove_client(client_name);
        cout << "Клиент удален\n";
        break;
    }
    case 8: {
        string name;
        ifstream file("client.txt"); // открыть файл на чтение
        string line;
        string currentName; // текущее имя клиента
        cin >> currentName;
        bool found = false; // флаг, указывающий, был ли найден клиент
        while (getline(file, line)) { // читать файл построчно
            if (line.empty()) { // если строка пустая (конец предыдущего клиента или начало файла)
                currentName = ""; // сбросить имя текущего клиента
                found = false; // сбросить флаг
            }
            else if (name.empty()) { // если имя текущего клиента не задано
                currentName = line; // задать имя текущего клиента
                if (currentName == name) { // если имя текущего клиента совпадает с искомым именем
                    found = true; // установить флаг
                }
            }
            else if (found) { // если клиент был найден
                cout << line << endl; // вывести информацию о клиенте
            }
        }
        if (!found) { // если клиент не был найден
            cout << "Client not found." << endl;
        }
            

        break;
    }
    case 0: {
        return 0;
    }
    default: {
        cout << "Некорректная команда\n";
        break;
    }
    }
}











   
  