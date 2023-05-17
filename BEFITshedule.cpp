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
    client.first_name = "John";
    client.last_name = "Doe";
    client.phone_number = "+123456789";

    yoga_class.SetClient(client);

    yoga_class.Print();

    return 0;
}


