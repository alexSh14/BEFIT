#pragma once
#include "iostream"
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
    //Функция добавления данных в Person
void addPersonToFile(string filename) {
    string name, phone, email;
    cout << "Enter person name: ";
    getline(cin, name);
    cout << "Enter person phone number: ";
    getline(cin, phone);
    cout << "Enter person email address: ";
    getline(cin, email);
    Person person(name, phone, email);
    ofstream outfile;
        outfile.open(filename, ios_base::app);
        if (outfile.good()) {
            outfile << person.name_
                << "\n" << "Phone: " << person.phone_
                << "\n" << "Email: " << person.email_
                << "\n" << endl;
            cout << "Person added to file." << endl;
        }
        else {
            cout << "Error: could not open file." << endl;
        }
        outfile.close();
    }
};

class Client : public Person {
public:
    Client(string name, string phone, string email, string start_date, string end_date) : Person(name, phone, email), start_date_(start_date), end_date_(end_date) {}
    string start_date_;
    string end_date_;

    //Функция добавления клиента из базы данных "persons.txt" в журнал учета клиентов
void AddClient(string filename) {
    string name, phone, email;
    cout << "Find the person's name ";
    getline(cin, name);
    ifstream in_file(filename);
        if (!in_file.is_open()) { 
            cout << "Error: could not open file " << filename << endl;
            return;
        }
        string line;
        bool found = false;
        while (getline(in_file, line)) { 
            if (line == name) {
                found = true;
                getline(in_file, phone); 
                getline(in_file, email); 
                Client client("", "", "", "", "");
                cout << name << endl;
                cout << phone << endl;
                cout << email << endl << endl;
                cout << "Enter client start date: ";
                getline(cin, client.start_date_);
                cout << "Enter client end date: ";
                getline(cin, client.end_date_);
                ofstream outfile;
                string filename = "clients.txt";
                outfile.open(filename, ios_base::app);
                if (outfile.good()) {
                    outfile << name
                        << "\n" << phone
                        << "\n" << email
                        << "\n" << "Subscription period: " << client.start_date_ << "-" << client.end_date_
                        << "\n"
                        << endl;
                    cout << "Client added to file." << endl;
                }
                else {
                    cout << "Error: could not open file." << endl;
                }
                outfile.close();

                break;
            }
        }

        if (!found) { // Искомый клиент не найден в файле
            cout << "Error: person not found in file." << endl;
            addPersonToFile("persons.txt");
        }
        in_file.close(); // Закрываем файл

    }
    // Функция для удаления клиента из файла
void RemoveClientFromFile(string filename) const {
     string name;
     getline(cin, name);
     ifstream infile(filename);
     ofstream outfile("temp.txt");
        if (!infile.is_open()) {
            cerr << "Error: could not open input file." << endl;
            return;
        }
        if (!outfile.is_open()) {
            cerr << "Error: could not open output file." << endl;
            infile.close();
            return;
        }
        string line;
        bool found = false;
        while (getline(infile, line)) {
            if (line == name) {
               found = true;
               while (getline(infile, line)) {
                    if (line.empty()) {
                        break;
                    }
                }
            }
            else {
                outfile << line << endl;
            }
        }
        infile.close();
        outfile.close();
        if (found) {
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }
        else {
            cout << "Error: client not found in file." << endl;
            remove("temp.txt");
        }
    }
// Функция для поиска клиента в файле
void FindClientFromFile(string filename) {
     string name, phone, email, start_date, end_date;
     cout << "Enter a name to search for: ";
     getline(cin, name);
     ifstream in_file(filename); 
        if (!in_file.is_open()) { 
            cout << "Error: could not open file." << filename << endl;
            return;
        }
        string line;
        bool found = false;
        while (getline(in_file, line)) { 
            if (line == name) { 
                found = true;
                cout << line << endl;
                getline(in_file, line); 
                cout << "Phone: " << line.substr(line.find(":") + 2) << endl;
                getline(in_file, line); 
                cout << "Email: " << line.substr(line.find(":") + 2) << endl;
                getline(in_file, line); 
                cout << "Subscription period: " << line.substr(line.find(":") + 2) << endl;
                break;
            }
        }
        if (!found) { 
            cout << "Error: client not found in file." << endl;
        }
        in_file.close(); 
    }
//Вывод списка клиентов:
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