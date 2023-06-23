#include "Header.h"
#include "Persons.h"

using namespace std;
int main() {
    setlocale(LC_ALL, "rus");
    cout << "Журнал учета клиентов,тренеров и тренеровок: \n";
    cout << "Выберите действие:\n";
    cout << "1 - Добавить клиента в файл\n";
    cout << "2 - Добавить тренера в файл\n";
    cout << "3 - Записать на тренировку\n";
    cout << "4 - Удалить запись из файла по имени\n";
    cout << "6 - Вывести содержимое файла на экран\n";
    cout << "7 - Вывести информацию по имени из файла на экран\n";
   


    int command;
    cin >> command;
    cin.ignore();
    switch (command) {
    case 1: {
        AddPerson("clients", "Client");
        break;
    }
    case 2: {
        AddPerson("trainers", "Trainer");
        break;
    }
    case 3: {
        AddPerson("Journal_training", "WorkoutRecords");
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
        cout << "Введите имя файла (clients/trainers/Journal_training): ";
        getline(cin, filename);
        string name;
        cout << "Введите имя, которое нужно найти: ";
        getline(cin, name);
        DisplayPersonInfo(filename, name);
        break;
    }
    case 7: {
        string filename;
        cout << "Введите имя файла (clients/trainers/Journal_training): ";
        getline(cin, filename);
        DisplayFileContents(filename);
        break;
    }
    
    default:
        cout << "Неправильный ввод команды." << endl;
        break;
    }

    return 0;
}