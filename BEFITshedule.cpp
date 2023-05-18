// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Client {
public:
    Client(std::string name, std::string phone, std::string email, std::string birthday,
        std::string start_date, std::string end_date)
        : name_(name), phone_(phone), email_(email), birthday_(birthday),
        start_date_(start_date), end_date_(end_date) {}

    std::string name() const { return name_; }
    std::string phone() const { return phone_; }
    std::string email() const { return email_; }
    std::string birthday() const { return birthday_; }
    std::string start_date() const { return start_date_; }
    std::string end_date() const { return end_date_; }

private:
    std::string name_;
    std::string phone_;
    std::string email_;
    std::string birthday_;
    std::string start_date_;
    std::string end_date_;
};

class FitnessJournal {
public:
    void AddClient(Client client) { clients_.push_back(client); }
    void RemoveClient(std::string name);
    void AddTrainingRecord(std::string name, std::string date, std::string workout,
        std::string trainer);
    void RemoveTrainingRecord(std::string name, std::string date);
    std::vector<Client> FindClient(std::string name) const;
    std::vector<Client> FindClientByPhone(std::string phone) const;
    std::vector<Client> GetAllClients() const { return clients_; }
    std::vector<std::string> GetTrainingRecords(std::string name) const;

private:
    std::vector<Client> clients_;
    std::map<std::string, std::vector<std::string>> training_records_;
};

void FitnessJournal::RemoveClient(std::string name) {
    for (auto it = clients_.begin(); it != clients_.end(); ++it) {
        if (it->name() == name) {
            clients_.erase(it);
            break;
        }
    }
}

void FitnessJournal::AddTrainingRecord(std::string name, std::string date, std::string workout,
    std::string trainer) {
    training_records_[name].push_back(date + " " + workout + " " + trainer);
}

void FitnessJournal::RemoveTrainingRecord(std::string name, std::string date) {
    auto& records = training_records_[name];
    for (auto it = records.begin(); it != records.end(); ++it) {
        if (it->find(date) == 0) {
            records.erase(it);
            break;
        }
    }
}

std::vector<Client> FitnessJournal::FindClient(std::string name) const {
    std::vector<Client> result;
    for (const auto& client : clients_) {
        if (client.name() == name) {
            result.push_back(client);
        }
    }
    return result;
}

std::vector<Client> FitnessJournal::FindClientByPhone(std::string phone) const {
    std::vector<Client> result;
    for (const auto& client : clients_) {
        if (client.phone() == phone) {
            result.push_back(client);
        }
    }
    return result;
}

std::vector<std::string> FitnessJournal::GetTrainingRecords(std::string name) const {
    auto it = training_records_.find(name);
    if (it == training_records_.end()) {
        return {};
    }
    return it->second;
}


int main() {
    FitnessJournal journal;

    int choice;
    do {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Add client" << std::endl;
        std::cout << "2. Remove client" << std::endl;
        std::cout << "3. Find client by name" << std::endl;
        std::cout << "4. Find client by phone number" << std::endl;
        std::cout << "5. Add training record for a client" << std::endl;
        std::cout << "6. Get training records for a client" << std::endl;
        std::cout << "7. Remove training record for a client" << std::endl;
        std::cout << "8. Get all clients" << std::endl;
        std::cout << "9. Quit" << std::endl;

        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, phone, email, birthday, start_date, end_date;
            std::cout << "Enter client name: ";
            std::cin >> name;
            std::cout << "Enter client phone number: ";
            std::cin >> phone;
            std::cout << "Enter client email: ";
            std::cin >> email;
            std::cout << "Enter client birthday: ";
            std::cin >> birthday;
            std::cout << "Enter client start date: ";
            std::cin >> start_date;
            std::cout << "Enter client end date: ";
            std::cin >> end_date;

            Client client(name, phone, email, birthday, start_date, end_date);
            journal.AddClient(client);
            break;
        }

        case 2: {
            std::string name;
            std::cout << "Enter client name: ";
            std::cin >> name;
            journal.RemoveClient(name);
            break;
        }

        case 3: {
            std::string name;
            std::cout << "Enter client name: ";
            std::cin >> name;
            std::vector<Client> found_clients = journal.FindClient(name);
            if (!found_clients.empty()) {
                std::cout << "Found " << found_clients.size() << " clients with name " << name << std::endl;
                for (const auto& client : found_clients) {
                    std::cout << "Client name: " << client.name() << ", phone number: " << client.phone() << std::endl;
                }
            }
            else {
                std::cout << "No clients found with name " << name << std::endl;
            }
            break;
        }

        case 4: {
            std::string phone;
            std::cout << "Enter client phone number: ";
            std::cin >> phone;
            std::vector<Client> found_clients = journal.FindClientByPhone(phone);
            if (!found_clients.empty()) {
                std::cout << "Found " << found_clients.size() << " clients with phone number " << phone << std::endl;
                for (const auto& client : found_clients) {
                    std::cout << "Client name: " << client.name() << ", phone number: " << client.phone() << std::endl;
                }
            }
            else {
                std::cout << "No clients found with phone number " << phone << std::endl;
            }
            break;
        }

        case 5: {
            std::string client_name, date, workout, trainer;
            std::cout << "Enter client name: ";
            std::cin >> client_name;
            std::cout << "Enter date: ";
            std::cin >> date;
            std::cout << "Enter workout: ";
            std::cin >> workout;
            std::cout << "Enter trainer: ";
            std::cin >> trainer;

            journal.AddTrainingRecord(client_name, date, workout, trainer);
            break;
        }

        case 6: {
            std::string client_name;
            std::cout << "Enter client name: ";
            std::cin >> client_name;

            std::vector<std::string> records = journal.GetTrainingRecords(client_name);
            std::cout << "Training records for client " << client_name << ":" << std::endl;
            for (const auto& record : records) {
                std::cout << "  " << record << std::endl;
            }
            break;
        }

        case 7: {
            std::string client_name, date;
            std::cout << "Enter client name: ";
            std::cin >> client_name;
            std::cout << "Enter date: ";
            std::cin >> date;

            journal.RemoveTrainingRecord(client_name, date);
            break;
        }

        case 8: {
            std::vector<Client> clients = journal.GetAllClients();
            for (const auto& client : clients) {
                std::cout << "Client name: " << client.name() << ", phone number: " << client.phone() << std::endl;
            }
            break;
        }

        case 9:
            break;

        default:
            std::cout << "Invalid choice, please try again." << std::endl;
            break;
        }
    } while (choice != 9);

    return 0;
}