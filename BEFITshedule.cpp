#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class Person {
public:
    Person(string name, string phone, string email) : name_(name), phone_(phone), email_(email) {}
    string name_;
    string phone_;
    string email_;
};

class Client : public Person {
public:
    Client(string name, string phone, string email, string start_date, string end_date) : Person(name, phone, email), start_date_(start_date), end_date_(end_date) {}
    string start_date_;
    string end_date_;
    //Функция добавления клиента
    void addClientToFile(string filename) {
        string name, phone, email, start_date, end_date;
        cout << "Enter client name: ";
        getline(cin, name);
        cout << "Enter client phone number: ";
        getline(cin, phone);
        cout << "Enter client email address: ";
        getline(cin, email);
        cout << "Enter client start date: ";
        getline(cin, start_date);
        cout << "Enter client end date: ";
        getline(cin, end_date);
        Client client(name, phone, email, start_date, end_date);

        ofstream outfile;
        outfile.open(filename, ios_base::app);
        if (outfile.good()) {
            outfile << client.name_
                << "\n" << "Phone: " << client.phone_
                << "\n" << "Email: " << client.email_
                << "\n" << "Subscription period: " << client.start_date_ << "-" << client.end_date_
                << "\n"
                << endl;
            cout << "Client added to file." << endl;
        }
        else {
            cout << "Error: could not open file." << endl;
        }
        outfile.close();
    }
    // Функция для удаления клиента из файла
    void RemoveClientFromFile(string filename) const {
        // Введите имя клиента для удаления
        string name;

        getline(cin, name);

        // Открыть файлы для считывания и записи
        ifstream infile(filename);
        ofstream outfile("temp.txt");
        // Проверка файла для считывания
        if (!infile.is_open()) {
            cerr << "Error: could not open input file." << endl;
            return;
        }
        // Проверка файла для записи
        if (!outfile.is_open()) {
            cerr << "Error: could not open output file." << endl;
            infile.close();
            return;
        }

        // Считываем файл
        string line;
        bool found = false;
        while (getline(infile, line)) {
            // Содержит ли строка имя удаляемого клиента:
            if (line == name) {
                // Если строка содержит имя удаляемого клиента, то пропускаем ее и все последующие строки до пустой:
                found = true;

                while (getline(infile, line)) {
                    if (line.empty()) {
                        break;
                    }
                }
            }
            else {
                // Если строка не содержит имени удаляемого клиента, то запишем его во временный файл
                outfile << line << endl;
            }
        }

        // Закрываем файлы
        infile.close();
        outfile.close();

        // Check if the client was found
        if (found) {
            // Replace the input file with the output file
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());

        }
        else {
            cout << "Error: client not found in file." << endl;
            remove("temp.txt");
        }
    }
    // Функция для обновления данных клиента в файле
    void UpdateClientData(string filename) {
        RemoveClientFromFile("clients.txt");
        cout << "Enter the new update data: " << endl;
        addClientToFile("clients.txt");
    }
    // Функция для поиска клиента в файле
    void FindClientFromFile(string filename) {
        string name, phone, email, start_date, end_date;
        cout << "Enter a name to search for: ";
        getline(cin, name);
        ifstream in_file(filename); // Открываем файл для чтения

        if (!in_file.is_open()) { // Проверяем, удалось ли открыть файл
            cout << "Error: could not open file." << filename << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(in_file, line)) { // Считываем содержимое файла построчно
            if (line == name) { // Строка с ФИО соответствует искомому клиенту
                found = true;
                cout << line << endl;
                getline(in_file, line); // Считываем следующую строку (с телефоном)
                cout << "Phone: " << line.substr(line.find(":") + 2) << endl;
                getline(in_file, line); // Считываем следующую строку (с email)
                cout << "Email: " << line.substr(line.find(":") + 2) << endl;
                getline(in_file, line); // Считываем следующую строку (с датами начала и окончания абонемента)
                cout << "Subscription period: " << line.substr(line.find(":") + 2) << endl;
                break;
            }
        }

        if (!found) { // Искомый клиент не найден в файле
            cout << "Error: client not found in file." << endl;
        }

        in_file.close(); // Закрываем файл
    }

    void printFileContents(string filename) {
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

};
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
            Client client("", "", "", "", "");
            client.addClientToFile("clients.txt");
            break;
        }
        case 2: {// Call the RemoveClientFromFile() function to remove a client from the file
            Client client("", "", "", "", "");
            cout << "Enter the name of the client to remove: ";
            client.RemoveClientFromFile("clients.txt");
            cout << "The operation is completed" << endl;
            break;
        }
        case 3: { //Call update
            Client client("", "", "", "", "");
            cout << "Enter the name of the client to update: ";
            client.UpdateClientData("clients.txt");
            cout << "The operation is completed" << endl;
            break;
        }
        case 4: {
            Client client("", "", "", "", "");
            client.FindClientFromFile("clients.txt");
            break;
        }
        case 5: {//Call print clients from file
            Client client("", "", "", "", "");         
            client.printFileContents("clients.txt");
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