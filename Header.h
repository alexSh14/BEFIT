#pragma once
#include <string>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person {
    string first_name;
    string last_name;
};

struct Instructor {
    Person person;
    string specialization;
    string service;
   
};

struct Client {
    Person person;
    string phone_number;
    string email;

};

struct Date {
    int day;
    int month;
    int year;
};

struct Time {
    int hour;
    int minute;
};

struct Place {
    string name;
    string address;
};

struct YogaTraining {
    Date date;
    Time time;
    Place place;
};

struct ZumbaTraining {
    Date date;
    Time time;
    Place place;
};

