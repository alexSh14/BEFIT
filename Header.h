#pragma once
#include "Persons.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void DeletePersonFromFile(string filename, string name) {
    setlocale(LC_ALL, "rus");
    ifstream infile(filename);
    ofstream outfile("temp.txt");

    if (!infile.good() || !outfile.good()) {
        cout << "Error: could not open file." << endl;
        return;
    }

    string line;
    bool found = false;
    bool deleted = false;

    while (getline(infile, line)) {
        if (line.find("Name: ") == 0 && line.substr(6) == name) {
            found = true;
            deleted = true;
          
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
        if (deleted) {
            cout << "Person deleted from file." << endl;
            infile.close();
            outfile.close();
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }
        else {
            cout << "Error: name not found in file." << endl;
            remove("temp.txt");
        }
    }
    else {
        cout << "Error: name not found in file." << endl;
        remove("temp.txt");
    }
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
void Add(const string& filename, const string& type) {
    string name;
    cout << "Searching for a name in a file: \n";
    cout << "Enter name: ";
    getline(cin >> ws, name);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file. " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find("Name: ") == 0 && line.substr(6) == name) {
            found = true;
            cout << "The entered name exists in the file: \n";
            DisplayPersonInfo(filename,name);
            if (type == "WorkoutRecords") {
                cout << "Want to add an entry? (y/n): ";
                char choice;
                cin >> choice;
                cin.ignore();
                if ((choice == 'y') || (choice == 'Y')) {
                    cout << "Choose a workout: " << std::endl;
                    cout << "1 - Yoga\n";
                    cout << "2 - Zumba\n";
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
                                cout << "Training record added!" << endl;
                            }
                            else {
                                cout << "Unable to open file Journal_training" << endl;
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
                                cout << "Training record added!" << endl;
                            }
                            else {
                                cout << "Unable to open file Journal_training" << endl;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Wrong date selection!" << endl;
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
        cout << "Name not found!" << endl;
        cout << "Want to add an entry? (y/n): ";
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
                cout << "Enter name: ";
                getline(cin >> ws, name);
                ofstream file("Journal_training", ios::app);
                    if (file.is_open()) {
                    file << "Name: " << name << "\n";
                    file.close();
                    cout << "Choose a workout: " << endl;
                    cout << "1 - Yoga\n";
                    cout << "2 - Zumba\n";
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
                                cout << "Training record added!" << std::endl;
                            }
                            else {
                                cout << "Unable to open file Journal_training" << endl;
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
                                cout << "Training record added!" << endl;
                            }
                            else {
                                cout << "Unable to open file Journal_training" << endl;
                            }
                        }
                        break;
                    }
                    default: {
                        cout << "Wrong date selection!!" << endl;
                        break;
                    }
                    }
                }
                else {
                    cout << "Unable to open file Journal_training" << endl;
                }
            }
        }
    }
};
