// BEFITshedule.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class YogaClass {
public:
    std::string name;
    std::string instructor;
    std::string time;
    int capacity;
    int enrolled;

    YogaClass(std::string name, std::string instructor, std::string time, int capacity) {
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
class YogaSchedule {
public:
    std::vector<YogaClass> classes;

    void addClass(YogaClass yogaClass) {
        classes.push_back(yogaClass);
    }

    void displayClasses() {
        for (YogaClass yogaClass : classes) {
            std::cout << yogaClass.name << " with " << yogaClass.instructor << " at " << yogaClass.time << std::endl;
        }
    }

    YogaClass* findClassByName(std::string name) {
        for (YogaClass& yogaClass : classes) {
            if (yogaClass.name == name) {
                return &yogaClass;
            }
        }
        return nullptr;
    }
};
int main() {
    YogaSchedule schedule;

    // Add yoga classes to the schedule
    YogaClass hatha("Hatha Yoga", "John Doe", "Monday 10:00", 10);
    YogaClass vinyasa("Vinyasa Yoga", "Jane Doe", "Tuesday 18:00", 15);
    YogaClass ashtanga("Ashtanga Yoga", "Mike Smith", "Wednesday 14:00", 8);
    schedule.addClass(hatha);
    schedule.addClass(vinyasa);
    schedule.addClass(ashtanga);

    // Display the schedule
    std::cout << "Yoga classes schedule:" << std::endl;
    schedule.displayClasses();

    // Prompt the user to enroll in a yoga class
    std::string className;
    std::cout << "Enter the name of the yoga class you want to enroll in: ";
    std::cin >> className;

    // Find the yoga class by name and enroll in it
    YogaClass* yogaClass = schedule.findClassByName(className);
    if (yogaClass == nullptr) {
        std::cout << "Sorry, we couldn't find a yoga class with that name." << std::endl;
    }
    else {
        yogaClass->enroll();
    }

    return 0;
}