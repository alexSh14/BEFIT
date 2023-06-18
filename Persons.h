#pragma once
#include "Header.h"
#include <iostream>
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