#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
class Person {
private:
    string name;
    int telephone;
    string email;

public:
    Person(string name, int telephone, string email)
        : name(name), telephone(telephone), email(email) {}

    string GetName() {
        return name;
    }

    string GetTelephone() {
        return to_string(telephone);
    }

    string GetEmail() {
        return email;
    }
};
class Client {
public:
    Client(string name, string phone, string email, string start_date, string end_date) :
        name_(name), phone_(phone), email_(email), start_date_(start_date), end_date_(end_date) {}

    string GetName() const { return name_; }
    string GetPhone() const { return phone_; }
    string GetEmail() const { return email_; }
    string GetStartDate() const { return start_date_; }
    string GetEndDate() const { return end_date_; }

    // Функция добавления клиента
    void AddClientToFile() const {
        // Открываем файл для записи в конец
        ofstream out_file("clients.txt", ios::app);
        // Записываем данные в файл
        out_file << "\n" << GetName() << "\n" << "тел.: " << GetPhone() << "\n" << "эл.почта : " << GetEmail() << "\n" << "срок абонемента: " << GetStartDate() << "-" << GetEndDate() << "\n" << endl;
        out_file.close();
        cout << "Клиент " << GetName() << " успешно добавлен в файл.\n\n";
    }
    // Функция для удаления клиента из файла
    void RemoveClientFromFile(string name) const {
        ifstream in_file("clients.txt");
        ofstream out_file("temp.txt");
        string line;

        while (getline(in_file, line)) {
            if (line.empty() || line == "\n") {
                // Если строка пустая или содержит только символ переноса строки,
                // то пропускаем её и не записываем в выходной файл
                continue;
            }

            if (line.find(name) == 0) {
                // Если строка начинается с указанной фамилии клиента,
                // то пропускаем её и пропускаем все последующие строки до символа переноса строки
                while (getline(in_file, line)) {
                    if (line.empty() || line == "\n") {
                        // Если строка пустая или содержит только символ переноса строки,
                        // то пропускаем её и не записываем в выходной файл
                        break;
                    }
                }

                continue;
            }

            // Иначе записываем строку в выходной файл
            out_file << line << endl;
            // Если строка содержит информацию о клиенте, то записываем отступ
            if (line.find("срок абонемента:") == 0) {
                out_file << endl;
            }
        }

        in_file.close();
        out_file.close();

        // Заменяем исходный файл на файл с удаленными данными
        remove("clients.txt");
        rename("temp.txt", "clients.txt");
        cout << "Клиент " << name << " удален\n";
    }
    // Функция для обновления данных клиента в файле
    static void Update_client(string name, string phone, string email, string start_date, string end_date) {
        cout << "Введите ФИО клиента, данные которого нужно обновить: ";
        getline(cin, name);
        ifstream in_file("clients.txt");
        ofstream out_file("temp.txt");
        string line;
        bool found = false;

        while (getline(in_file, line)) {
            if (line.empty() || line == "\n") {
                // Если строка пустая или содержит только символ переноса строки,
                // то пропускаем её и не записываем в выходной файл
                continue;
            }

            size_t name_pos = line.find(name);
            if (name_pos == 0) {
                // Если строка начинается с указанной фамилии клиента,
                // то считываем информацию о клиенте и обновляем нужные поля
                string name = line.substr(0, name_pos + name.length());
                string phone, email, start_date, end_date;

                getline(in_file, phone);
                getline(in_file, email);
                getline(in_file, start_date);
                getline(in_file, end_date);

                // Обновляем поля
                cout << "Введите новый номер телефона: ";
                getline(cin, phone);
                cout << "Введите новый email: ";
                getline(cin, email);
                cout << "Введите новую дату начала абонемента: ";
                getline(cin, start_date);
                cout << "Введите новую дату окончания абонемента: ";
                getline(cin, end_date);

                // Записываем обновленную информацию о клиенте в выходной файл
                out_file << "\n" << name << "\n" << "тел.: " << phone << "\n" << "эл.почта : " << email << "\n" << "срок абонемента: " << start_date << "-" << end_date << "\n" << endl;;
                found = true;
                continue;
            }

            // Иначе записываем строку в выходной файл
            out_file << line << endl;
            // Если строка содержит информацию о клиенте, то записываем отступ
            if (line.find("срок абонемента:") == 0) {
                out_file << endl;
            }
        }

        in_file.close();
        out_file.close();

        if (!found) {
            cout << "Клиент с указанным ФИО не найден" << endl;
        }
        else {
            // Заменяем исходный файл на файл с обновленными данными
            remove("clients.txt");
            rename("temp.txt", "clients.txt");
            cout << "Данные о клиенте успешно обновлены" << endl;
        }
    }
private:
    string name_;
    string phone_;
    string email_;
    string start_date_;
    string end_date_;
};

// Функция для поиска клиента в файле
void print_client_info_from_file() {
    string name, phone, email, start_date, end_date;
    string filename = "clients.txt";
    cout << "Введите ФИО клиента, данные которого нужно обновить: ";
    getline(cin, name);
    ifstream in_file(filename); // Открываем файл для чтения

    if (!in_file.is_open()) { // Проверяем, удалось ли открыть файл
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in_file, line)) { // Считываем содержимое файла построчно
        if (line == name) { // Строка с ФИО соответствует искомому клиенту
            found = true;
            cout << "Клиент: " << line << endl;
            getline(in_file, line); // Считываем следующую строку (с телефоном)
            cout << "Телефон: " << line.substr(line.find(":") + 2) << endl;
            getline(in_file, line); // Считываем следующую строку (с email)
            cout << "Email: " << line.substr(line.find(":") + 2) << endl;
            getline(in_file, line); // Считываем следующую строку (с датами начала и окончания абонемента)
            cout << "Срок абонемента: " << line.substr(line.find(":") + 2) << endl;
            break;
        }
    }

    if (!found) { // Искомый клиент не найден в файле
        cout << "Клиент с ФИО " << name << " не найден в файле " << filename << endl;
    }

    in_file.close(); // Закрываем файл
}

// Функция для вывода содержимого файла на экран
void print_clients_from_file() {
    string filename = "clients.txt";
    ifstream in_file(filename); // Открываем файл для чтения

    if (!in_file.is_open()) { // Проверяем, удалось ли открыть файл
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    cout << "Информация о клиентах:\n";
    string line;
    while (getline(in_file, line)) { // Считываем содержимое файла построчно
        // Ожидаем, что содержимое файла имеет определенный формат. В данном случае
        // мы ожидаем, что каждый клиент записан в файле в следующем формате:
        // ФИО
        // тел.: <телефон>
        // эл.почта : <email>
        // срок абонемента: <дата начала> - <дата окончания>
        // (пустая строка)
        // Поэтому мы извлекаем необходимую информацию из каждой строки с помощью методов
        // класса string и выводим ее на экран в удобном формате.
        if (line.empty()) { // Пустая строка разделяет записи о клиентах в файле
            cout << endl;
        }
        else if (line.find("тел.:", 0) != string::npos) { // Строка с телефоном
            cout << line.substr(line.find(":") + 2) << ", ";
        }
        else if (line.find("эл.почта :", 0) != string::npos) { // Строка с email
            cout << line.substr(line.find(":") + 2) << endl;
        }
        else if (line.find("срок абонемента:", 0) != string::npos) { // Строка с датами начала и окончания абонемента
            cout << "Срок абонемента: " << line.substr(line.find(":") + 2) << endl;
        }
        else { // Строка с ФИО
            cout << line << ", ";
        }
    }

    in_file.close(); // Закрываем файл
}
// Функция вывода расписания
void print_schedule_from_file(string filename) {

    ifstream in_file(filename);
    if (!in_file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    cout << "Расписание занятий:\n";
    string line;
    while (getline(in_file, line)) {
        if (!line.empty() && line[0] != '#') { // игнорируем пустые строки и строки, начинающиеся с символа '#'
            string date = line.substr(0, 10);
            string time = line.substr(11, 5);
            string yoga_class = line.substr(17);
            cout << date << " " << time << " - " << yoga_class << endl;
        }
    }

    in_file.close();
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
                outputFile << line2 << endl;

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
                outputFile << line3 << endl;


            }
            outputFile.close();
        }
        inputFile.close();
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Выберите журнал:\n";
    cout << "1 - Журнал учета клиентов\n";
    cout << "2 - Журнал записи на тренировку\n";
    int command;
    cin >> command;
    cin.ignore();

    switch (command) {
    case 1: {
        cout << "Журнал учета клиентов: \n";
        cout << "Выберите действие:\n";
        cout << "1 - Добавить клиента в файл\n";
        cout << "2 - Удалить клиента из файла\n";
        cout << "3 - Обновить данные клиента в файле\n";
        cout << "4 - Найти клиента в файле\n";
        cout << "5 - Вывести на экран содержимое файла\n";
        cout << "0 - выход\n";

        int command;
        cin >> command;
        cin.ignore();
        switch (command) {
        case 1: {
            string name, phone, email, start_date, end_date;
            cout << "Введите данные клиента:\n";
            cout << "ФИО: ";
            getline(cin, name);
            cout << "Телефон: ";
            getline(cin, phone);
            cout << "Email: ";
            getline(cin, email);
            cout << "Дата начала обслуживания: ";
            getline(cin, start_date);
            cout << "Дата окончания обслуживания: ";
            getline(cin, end_date);
            Client client(name, phone, email, start_date, end_date);
            // Вызываем метод AddClientToFile() у объекта client
            client.AddClientToFile();
            break;
        }
        case 2: {
            string name;
            cout << "Для удаления введите ФИО: ";
            getline(cin, name);
            Client client("", "", "", "", "");
            client.RemoveClientFromFile(name);
            break;
        }
        case 3: {
            string name, phone, email, start_date, end_date;
            Client::Update_client(name, phone, email, start_date, end_date);
            break;
        }
        case 4: {
            void print_client_info_from_file();
            break;
        }
        case 5: {
            print_clients_from_file();
            break;
        }
              break;
        }
        break; //TO DO  ПРЕДЛОЖИТЬ СНОВА МЕНЮ
    }

    case 2: {
        cout << "Журнал записи на тренировку: \n";
        cout << "Выберите действие:\n";
        cout << "1 - Расписание тренировок \n";
        cout << "2 - Добавить запись на тренировку\n";
        cout << "3 - Получить записи на тренировки для конкретного клиента\n";
        cout << "4 - Удалить запись на тренировку для конкретного клиента\n";
        cout << "0 - Выход\n";
        int command;
        cin >> command;
        cin.ignore();
        switch (command) {
        case 1: {
            print_schedule_from_file("sheduleYoga.txt");
            print_schedule_from_file("sheduleZumba.txt");
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

            break;
        }

        case 3: {
            string filename = "Journal_training.txt";
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

        case 4: {



            break;
        }

        }
        break;
    }
          break;


    }
    return 0;
}