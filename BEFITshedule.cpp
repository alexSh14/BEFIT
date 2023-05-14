// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class FitnessClass {
public:
    std::string name;
    std::string instructor;
    std::string time;
    int capacity;
    int enrolled;

    FitnessClass(std::string name, std::string instructor, std::string time, int capacity) {
        this->name = name;
        this->instructor = instructor;
        this->time = time;
        this->capacity = capacity;
        this->enrolled = 0;
    }

    bool isFull() {
        return enrolled >= capacity;
    }

    void enroll() {
        if (!isFull()) {
            enrolled++;
            std::cout << "You have successfully enrolled in " << name << std::endl;
        }
        else {
            std::cout << "Sorry, " << name << " is already full." << std::endl;
        }
    }
};

class FitnessSchedule {
public:
    std::vector<FitnessClass> classes;

    void addClass(FitnessClass fitnessClass) {
        classes.push_back(fitnessClass);
    }

    void displayClasses() {
        std::cout << "Fitness classes schedule:" << std::endl;
        for (FitnessClass fitnessClass : classes) {
            std::cout << fitnessClass.name << " with " << fitnessClass.instructor << " at " << fitnessClass.time << std::endl;
        }
    }

    FitnessClass* findClassByName(std::string name) {
        for (FitnessClass& fitnessClass : classes) {
            if (fitnessClass.name == name) {
                return &fitnessClass;
            }
        }
        return nullptr;
    }

    void loadScheduleFromFile(std::string filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                std::string name, instructor, time;
                int capacity;
                std::istringstream iss(line);
                if (!(iss >> name >> instructor >> time >> capacity)) {
                    continue;
                }
                addClass(FitnessClass(name, instructor, time, capacity));
            }
            file.close();
        }
        else {
            std::cout << "Unable to open file " << filename << std::endl;
        }
    }

    void enrollClient(std::string className, std::string clientName, std::string clientEmail) {
        FitnessClass* fitnessClass = findClassByName(className);
        if (fitnessClass == nullptr) {
            std::cout << "Sorry, we couldn't find a fitness class with that name." << std::endl;
        }
        else {
            fitnessClass->enroll();
            std::ofstream outfile;
            outfile.open(className + ".txt", std::ios_base::app);
            outfile << clientName << " " << clientEmail << std::endl;
            outfile.close();
        }
    }
};

int main() {
    FitnessSchedule schedule;

    // Load fitness classes from file
    schedule.loadScheduleFromFile("fitness_classes.txt");

    // Display the schedule
    schedule.displayClasses();

    // Prompt the user to enroll in a fitness class
    std::string className;
    std::string clientName;
    std::string clientEmail;
    std::cout << "Enter the name of the fitness class you want to enroll in: ";
    std::cin >> className;
    std::cout << "Enter your name: ";
    std::cin >> clientName;
    std::cout << "Enter your email address: ";
    std::cin >> clientEmail;

    // Enroll the client in the fitness class
    schedule.enrollClient(className, clientName, clientEmail);

    return 0;
}