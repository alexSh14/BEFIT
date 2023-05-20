#include <string>
#include <vector>
#include <iostream>


using namespace std;

class Client {
public:
    string full_name;
    string phone_number;
    string email;
    string subscription_start_date;
    string subscription_end_date;
};
class WorkoutRecord {
public:
    string workout_date;
    string workout_time;
    string workout_name;
    string trainer_name;
    string client_full_name;
};
class ClientJournal {
public:
    // Добавление нового клиента в журнал
    void add_client(const Client& client);

    // Удаление клиента из журнала
    void remove_client(const string& full_name);

    // Добавление записи на тренировку для конкретного клиента
    void add_workout_record(const string& full_name, const WorkoutRecord& record);

    // Удаление записи на тренировку для конкретного клиента
    void remove_workout_record(const string& full_name, const string& workout_date, const string& workout_time);

    // Поиск клиента по ФИ или номеру телефона
    Client find_client(const string& search_param);

    // Получение списка всех клиентов в журнале
    std::vector<Client> get_all_clients();

    // Получение списка всех записей на тренировки для конкретного клиента
    std::vector<WorkoutRecord> get_workout_records(const string& full_name);

    // Получение списка всех записей на тренировки за определенный период времени
    std::vector<WorkoutRecord> get_workout_records_by_period(const string& start_date, const string& end_date);

private:
    vector<Client> clients_;
    vector<WorkoutRecord> workout_records_;

    // Вспомогательная функция для поиска клиента
    bool matches_search_param(const Client& client, const string& search_param);
};
void ClientJournal::add_client(const Client& client) {
    clients_.push_back(client);
}

void ClientJournal::remove_client(const string& full_name) {
    auto it = find_if(clients_.begin(), clients_.end(), [full_name](const Client& client) {
        return client.full_name == full_name;
        });
    if (it != clients_.end()) {
        clients_.erase(it);
    }
}

void ClientJournal::add_workout_record(const string& full_name, const WorkoutRecord& record) {
    auto it = find_if(clients_.begin(), clients_.end(), [full_name](const Client& client) {
        return client.full_name == full_name;
        });
    if (it != clients_.end()) {
        workout_records_.push_back(record);
    }
}

void ClientJournal::remove_workout_record(const string& full_name, const string& workout_date, const string& workout_time) {
    auto it = find_if(workout_records_.begin(), workout_records_.end(), [full_name, workout_date, workout_time](const WorkoutRecord& record) {
        return record.client_full_name == full_name && record.workout_date == workout_date && record.workout_time == workout_time;
        });
    if (it != workout_records_.end()) {
        workout_records_.erase(it);
    }
}

Client ClientJournal::find_client(const string& search_param) {
    auto it = find_if(clients_.begin(), clients_.end(), [this, search_param](const Client& client) {
        return matches_search_param(client, search_param);
        });
    if (it != clients_.end()) {
        return *it;
    }
    else {
        // Возвращаем пустой объект Client, если клиент не найден
        return Client();
    }
}

vector<Client> ClientJournal::get_all_clients() {
    return clients_;
}

vector<WorkoutRecord> ClientJournal::get_workout_records(const string& full_name) {
    vector<WorkoutRecord> records;
    for (const auto& record : workout_records_) {
        if (record.client_full_name == full_name) {
            records.push_back(record);
        }
    }
    return records;
}

vector<WorkoutRecord> ClientJournal::get_workout_records_by_period(const string& start_date, const string& end_date) {
    vector<WorkoutRecord> records;
    for (const auto& record : workout_records_) {
        if (record.workout_date >= start_date && record.workout_date <= end_date) {
            records.push_back(record);
        }
    }
    return records;
}

bool ClientJournal::matches_search_param(const Client& client, const string& search_param) {
    return client.full_name == search_param || client.phone_number == search_param;
}
int main() {
    setlocale (LC_ALL, "rus");
    ClientJournal journal;

    // Добавляем несколько клиентов
    Client client1{ "Иванов Иван Иванович", "1234567890", "ivanov@mail.com", "01.01.2023", "31.12.2023" };
    Client client2{ "Петров Петр Петрович", "0987654321", "petrov@mail.com", "01.01.2023", "31.12.2023" };
    Client client3{ "Сидоров Сидор Сидорович", "5551234", "sidorov@mail.com", "01.01.2023", "31.12.2023" };
    journal.add_client(client1);
    journal.add_client(client2);
    journal.add_client(client3);

    // Добавляем записи на тренировки для клиентов
    WorkoutRecord record1{ "01.06.2023", "10:00", "Йога", "Иванов Иван Иванович" };
    WorkoutRecord record2{ "02.06.2023", "14:00", "Кроссфит", "Петров Петр Петрович" };
    WorkoutRecord record3{ "03.06.2023", "18:00", "Бокс", "Сидоров Сидор Сидорович" };
    journal.add_workout_record("Иванов Иван Иванович", record1);
    journal.add_workout_record("Петров Петр Петрович", record2);
    journal.add_workout_record("Сидоров Сидор Сидорович", record3);

    // Получаем всех клиентов в журнале
    vector<Client> all_clients = journal.get_all_clients();
    for (const auto& client : all_clients) {
        cout << "Клиент: " << client.full_name << endl;
    }

    // Получаем записи на тренировки для конкретного клиента
    vector<WorkoutRecord> ivanov_records = journal.get_workout_records("Иванов Иван Иванович");
    for (const auto& record : ivanov_records) {
        cout << "Запись на тренировку: " << record.workout_name << " (" << record.workout_date << " " << record.workout_time << ")" << endl;
    }

    // Получаем записи на тренировки за определенный период времени
    vector<WorkoutRecord> records_in_june = journal.get_workout_records_by_period("01.06.2023", "30.06.2023");
    for (const auto& record : records_in_june) {
        cout << "Запись на тренировку: " << record.workout_name << " (" << record.workout_date << " " << record.workout_time << ")" << std::endl;
    }

    // Удаляем запись на тренировку для конкретного клиента
    journal.remove_workout_record("Иванов Иван Иванович", "01.06.2023", "10:00");

    // Удаляем клиента из журнала
    journal.remove_client("Петров Петр Петрович");

    return 0;
}