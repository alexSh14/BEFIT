#include "Function.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
        
        cout << "Журнал учета клиентов: \n";
        cout << "Выберите действие:\n";
        cout << "1 - Добавить клиента в файл\n";
        cout << "2 - Удалить клиента из файла\n";
        cout << "3 - Найти клиента в файле\n";
        cout << "4 - Вывести на экран содержимое файла\n";
        cout << "5 - Добавить персональные данные\n";
       
        int command;
        cin >> command;
        cin.ignore();

        switch (command) {
        case 1: {
            Client client("", "", "", "", "");//Добавить Client в файл
            client.AddClient("persons.txt");
            break;
        }
        case 2: {
            Client client("", "", "", "", ""); //Удалить client из файла
            cout << "Enter the name of the client to remove: ";
            client.RemoveClientFromFile("clients.txt");
            cout << "Client removed from file." << endl;
            break;
        }
        case 3: {
            Client client("", "", "", "", "");//Найти клиента в файле
            client.FindClientFromFile("clients.txt");
            break;
        }
        case 4: {
            Client client("", "", "", "", "");//Вывести список клиентов
            client.printFileContents("clients.txt");
            break;
        }
        case 5: {
            Person person("", "", "");//Добавить Person
            person.addPersonToFile("persons.txt");
            break;
        }

            default:
            break;
        } 
         
    return 0;
}