#pragma once

#include "iostream"
#include <fstream>
#include <string>
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
