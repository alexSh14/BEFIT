// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <iostream>

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

private:
    std::string date_;
    std::string time_;
    Client client_;
};

int main() {
    YogaClass yoga_class("2023-05-17", "10:00");

    Client client;
    std::cout << "Enter first name: ";
    std::cin >> client.first_name;
    std::cout << "Enter last name: ";
    std::cin >> client.last_name;
    std::cout << "Enter phone number: ";
    std::cin >> client.phone_number;
    yoga_class.SetClient(client);

    yoga_class.Print();

    return 0;
}


