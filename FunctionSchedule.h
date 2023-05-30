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
// ������� �� ����� ����� �� �����
void printFileContents(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
}
// 
void appendLinesToFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (inputFile.is_open()) {
        string line1, line2;
        if (getline(inputFile, line1) && getline(inputFile, line2)) {
            ofstream outputFile(outputFilename, std::ios::app);
            if (outputFile.is_open()) {
                outputFile << line1 << "\n";
                outputFile << line2 << "\n";
            }
            outputFile.close();
        }
        inputFile.close();
    }
}
//
void appendLinesToFile2(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename);
    if (inputFile.is_open()) {
        string line1, line2, line3;
        if (getline(inputFile, line1) && getline(inputFile, line2) && getline(inputFile, line3)) {
            ofstream outputFile(outputFilename, ios::app);
            if (outputFile.is_open()) {
                outputFile << line1 << "\n";
                outputFile << line3 << "\n";
            }
            outputFile.close();
        }
        inputFile.close();
    }
}
