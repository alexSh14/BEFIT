#pragma once
#include "iostream"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Person {
public:
    Person() {}
    Person(string name, string phone, string email) : name_(name), phone_(phone), email_(email) {}
    virtual void Print(ostream& os) const {
        os << "Name: " << name_
            << "\n" << "Phone: " << phone_
            << "\n" << "Email: " << email_
            << "\n" << endl;
    }
    virtual void Read(istream& is) {
        cout << "Enter name: ";
        getline(is, name_);
        cout << "Enter phone: ";
        getline(is, phone_);
        cout << "Enter email: ";
        getline(is, email_);
    }
    string name_;
    string phone_;
    string email_;
};

class Client : public Person {
public:
    Client() {}
    Client(string name, string phone, string email, string start_date, string end_date) : Person(name, phone, email), start_date_(start_date), end_date_(end_date) {}
    void Print(ostream& os) const override {
        Person::Print(os);
        os << "Subscription period: " << start_date_ << "-" << end_date_ << "\n" << endl;
    }
    void Read(istream& is) override {
        Person::Read(is);
        cout << "Enter start date (YYYY-MM-DD): ";
        getline(is, start_date_);
        cout << "Enter end date (YYYY-MM-DD): ";
        getline(is, end_date_);
    }
    string GetName() const {
        return name_;
    }
    string start_date_;
    string end_date_;
};

class Trainer : public Person {
public:
    Trainer() {}
    Trainer(string name, string phone, string email, string status, string specialisation) : Person(name, phone, email), status_(status), specialisation_(specialisation) {}
    void Print(ostream& os) const override {
        Person::Print(os);
        os << "Status: " << status_
            << "\n" << "Specialisation: " << specialisation_
            << "\n" << endl;
    }
    void Read(istream& is) override {
        Person::Read(is);
        cout << "Enter status (active/not active): ";
        getline(is, status_);
        cout << "Enter specialisation (Yoga/Zumba): ";
        getline(is, specialisation_);
    }
    string GetName() const {
        return name_;
    }
    string status_;
    string specialisation_;
};
class TrainingRecord {
public:
    TrainingRecord() {}
    TrainingRecord(std::shared_ptr<Client> client, std::shared_ptr<Trainer> trainer,
        std::string date, std::string time)
        : client_(client), trainer_(trainer), date_(date), time_(time) {}

    void Print(std::ostream& os) const {
        os << "Training Record:\n"
            << "Date: " << date_ << "\n"
            << "Time: " << time_ << "\n"
            << "Client: " << client_->GetName() << "\n"
            << "Trainer: " << trainer_->GetName() << "\n";
    }

private:
    std::shared_ptr<Client> client_;
    std::shared_ptr<Trainer> trainer_;
    std::string date_;
    std::string time_;
};

void AddPersonToFile(string filename, const Person& person) {
    ofstream outfile;
    outfile.open(filename, ios_base::app);
    if (outfile.good()) {
        person.Print(outfile);
        cout << "Person added to file." << endl;
    }
    else {
        cout << "Error: could not open file." << endl;
    }
    outfile.close();
}

bool FindNameInFile(string filename, string name_) {
    ifstream infile(filename);
    if (infile.good()) {
        string line;
        while (getline(infile, line)) {
            if (line.find("Name: ") == 0 && line.find(name_) != string::npos) {
                return true;
            }
        }
    }
    return false;
}

void DeletePersonFromFile(string filename, string name) {
    ifstream infile(filename);
    ofstream outfile("temp.txt");
    if (infile.good() && outfile.good()) {
        string line;
        bool found = false;
        while (getline(infile, line)) {
            if (line.find("Name: ") == 0 && line.substr(6) == name) {
                found = true;
                // skip lines until the next name is found
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
            cout << "Person deleted from file." << endl;
            remove(filename.c_str());
            rename("temp.txt", filename.c_str());
        }
        else {
            cout << "Error: name not found in file." << endl;
            remove("temp.txt");
        }
    }
    else {
        cout << "Error: could not open file." << endl;
    }
    infile.close();
    outfile.close();
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