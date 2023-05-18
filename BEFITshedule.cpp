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

    // Add some clients
    Client client1("John Smith", "555-1234", "jsmith@example.com", "01/01/1980", "05/01/2023", "05/31/2023");
    Client client2("Jane Doe", "555-5678", "jdoe@example.com", "02/02/1985", "05/01/2023", "05/31/2023");
    journal.AddClient(client1);
    journal.AddClient(client2);

    // Get all clients
    std::vector<Client> clients = journal.GetAllClients();
    for (const auto& client : clients) {
        std::cout << "Client name: " << client.name() << ", phone number: " << client.phone() << std::endl;
    }

    // Find a client by name
    std::string name = "John Smith";
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

    // Find a client by phone number
    std::string phone = "555-5678";
    found_clients = journal.FindClientByPhone(phone);
    if (!found_clients.empty()) {
        std::cout << "Found " << found_clients.size() << " clients with phone number " << phone << std::endl;
        for (const auto& client : found_clients) {
            std::cout << "Client name: " << client.name() << ", phone number: " << client.phone() << std::endl;
        }
    }
    else {
        std::cout << "No clients found with phone number " << phone << std::endl;
    }

    // Add training record for a client
    std::string client_name = "John Smith";
    std::string date = "05/18/2023";
    std::string workout = "Cardio";
    std::string trainer = "Trainer A";
    journal.AddTrainingRecord(client_name, date, workout, trainer);

    // Get training records for a client
    std::vector<std::string> records = journal.GetTrainingRecords(client_name);
    std::cout << "Training records for client " << client_name << ":" << std::endl;
    for (const auto& record : records) {
        std::cout << "  " << record << std::endl;
    }

    // Remove a training record for a client
    journal.RemoveTrainingRecord(client_name, date);

    // Remove a client
    journal.RemoveClient(client_name);

    return 0;
}