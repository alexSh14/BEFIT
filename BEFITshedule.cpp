#include "Header.h"
#include "Persons.h"

using namespace std;
int main() {
    setlocale(LC_ALL, "rus");
    cout << "Журнал учета клиентов,тренеров и тренировок: \n";
    cout << "Выберите действие:\n";
    cout << "1 - Добавить клиента в файл\n";
    cout << "2 - Добавить тренера в файл\n";
    cout << "3 - Добавить запись на тренировку\n";
    cout << "4 - Удалить запись из файла по имени\n";
    cout << "5 - Вывести содержимое файла на экран\n";
    cout << "6 - Вывести информацию по имени из файла на экран\n";
   


    int command;
    cin >> command;
    cin.ignore();
    switch (command) {
    case 1: {
        Add("clients", "Client");//Добавить клиента в файл
        break;
    }
    case 2: {
        Add("trainers", "Trainer");//Добавить тренера в файл
        break;
    }
    case 3: {
        Add("Journal_training", "WorkoutRecords");//Добавить запись на тренировку
        break;
    }
    case 4: {//Удалить запись из файла по имени
        string filename;
        cout << "Введите имя файла (clients/trainers/Journal_training): ";
        getline(cin, filename);
        string name;
        cout << "Введите имя, которое нужно удалить: ";
        getline(cin, name);
        
            DeletePersonFromFile(filename, name);
       
        
        break;
    }
    case 5: {//Вывести содержимое файла на экран
        string filename;
        cout << "Введите имя файла (clients/trainers/Journal_training): ";
        getline(cin, filename);
        DisplayFileContents(filename);
        break;
    }
    case 6: {//Вывести информацию по имени из файла на экран
        string filename;
        cout << "Введите имя файла (clients/trainers/Journal_training): ";
        getline(cin, filename);
        string name;
        cout << "Введите имя, которое нужно найти: ";
        getline(cin, name);
        DisplayPersonInfo(filename, name);
        break;
    }
       
    default:
        cout << "Неправильный ввод команды." << endl;
        break;
    }

    return 0;
}