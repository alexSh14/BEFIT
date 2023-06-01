#include <vector>
#include <fstream>
#include "FunctionSchedule.h"
using namespace std;
int main() {
    setlocale(LC_ALL, "rus");
    
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
        cout << endl;
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
    { string filename = "Journal_training.txt";
    string client_name;
    cout << "Введите имя клиента:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, client_name);
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
        
            break;
        
    }
    case 6: {
       
        break;
    }
    case 7: {
        
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






   
  