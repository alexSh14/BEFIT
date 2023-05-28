#pragma once

#include "iostream"
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//���������� ������ ������
void add_client(const std::string& filename) {
    string full_name, phone, email, start_date, end_date;
    cout << "������� ������ �������:\n";
    cout << "���: ";
    getline(std::cin >> std::ws, full_name);
    cout << "�������: ";
    getline(std::cin >> std::ws, phone);
    cout << "Email: ";
    getline(std::cin >> std::ws, email);
    cout << "���� ������ ����������: ";
    getline(std::cin >> std::ws, start_date);
    cout << "���� ��������� ����������: ";
    getline(std::cin >> std::ws, end_date);

    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << full_name << "\n" << "���.: " << phone << "\n" << "��.����� : " << email << "\n" << "���� ����������: " << start_date << "-" << end_date << "\n" << std::endl;
        file.close();
        std::cout << "������ ��������\n";
    }
    else {
        std::cout << "Unable to open file\n";
    }
}
// ���������� �����
bool open_file_for_reading(ifstream& file, const string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ���� " << filename << endl;
        return false;
    }
    // ������ ���� �����...
  
    return true;
}
//���������� � ����
bool add_to_file(const string& filename, const string& data) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "�� ������� ������� ���� " << filename << endl;
        return false;
    }
    file << data << "\n";
    file.close();
    return true;
}

std::vector<std::string> readLinesFromFile(const std::string& filePath) {
    std::vector<std::string> lines; // ������� ������ ����� ��� �������� ����� �� �����
    std::ifstream file(filePath); // ��������� ���� ��� ������

    if (file.is_open()) { // ���������, �������� �� ����
        std::string line;
        while (getline(file, line)) { // ��������� ������ �� �����
            lines.push_back(line); // ��������� ��������� ������ � ������ �����
        }
        file.close(); // ��������� ����
    }

    return lines; // ���������� ������ ����� � ���������� �����
}
