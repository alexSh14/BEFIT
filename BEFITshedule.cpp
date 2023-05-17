﻿// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>
#include <fstream>

struct Client {
    std::string first_name;
    std::string last_name;
    std::string phone_number;
};

class YogaClass {
public:
    YogaClass(const std::string& date, const std::string& time) : date_(date), time_(time) {}

    void SetClient(const Client& client) {
        client_ = client;
    }

    void Print() const {
        std::cout << "Yoga class on " << date_ << " at " << time_ << std::endl;
        std::cout << "Client: " << client_.first_name << " " << client_.last_name << ", phone number: " << client_.phone_number << std::endl;
    }
    void SaveClientToFile(const std::string& fileclient) const {
        std::fstream outfile;
        outfile.open(fileclient, std::ios::out | std::ios::app);
        outfile << client_.first_name << " " << client_.last_name << " " << client_.phone_number << std::endl;
        outfile.close();
    }
    void SaveToFile(const std::string& filename) const {
        std::fstream outfile;
        outfile.open(filename, std::ios::out | std::ios::app);
        outfile << date_ << " " << time_ << " " << client_.first_name << " " << client_.last_name << " " << client_.phone_number << std::endl;
        outfile.close();
    }

private:
    std::string date_;
    std::string time_;
    Client client_;
};

void PrintFileContents(const std::string& filename) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::cout << line << std::endl;
    }
    infile.close();
}

int main() {
    std::string filename = "yoga_classes.txt";
    PrintFileContents(filename);
    
    std::string date;
    std::string time;
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> date;
    std::cout << "Enter time (HH:MM): ";
    std::cin >> time;

    YogaClass yoga_class(date, time);

    Client client;
    std::cout << "Enter first name: ";
    std::cin >> client.first_name;
    std::cout << "Enter last name: ";
    std::cin >> client.last_name;
    std::cout << "Enter phone number: ";
    std::cin >> client.phone_number;

    yoga_class.SetClient(client);

    yoga_class.Print();
    std::string fileclient = "client.txt";
    yoga_class.SaveClientToFile(fileclient);
    std::cout << "Client saved to file: " << fileclient << std::endl;
    yoga_class.SaveToFile(filename);
    std::cout << "Yoga class saved to file: " << filename << std::endl;

    return 0;
}


