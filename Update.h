void UpdatePersonDataById(string filename) {
    // Prompt the user to enter the name of the person to update
    string name;
    cout << "Поиск имени в файле:\n";
    cout << "Введите имя: ";
    getline(cin >> ws, name);

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удается открыть файл " << filename << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find("Name: ") == 0 && line.substr(6) == name) {
            found = true;
            cout << "Введенное имя существует в файле: \n";
            DisplayFileContents(filename);
            cout << "Хотите обновить данные? (y/n): ";
            char choice;
            cin >> choice;
            cin.ignore();
            if ((choice == 'y') || (choice == 'Y')) {
                // Open a temporary output file for writing
                ofstream outfile("temp.txt");
                if (!outfile.good()) {
                    cout << "Error: could not open temporary file." << endl;
                    return;
                }

                // Close the input file stream before opening it again
                file.close();
                ifstream infile(filename);
                if (!infile.is_open()) {
                    cout << "Не удается открыть файл " << filename << endl;
                    outfile.close();
                    remove("temp.txt");
                    return;
                }

                // Loop through the input file line by line
                while (getline(infile, line)) {
                    // If we find a line that starts with "Name: " and the name matches the one we're looking for, update the person's data
                    if (line.find("Name: ") == 0 && line.substr(6) == name) {
                        found = true;
                        cout << "Select the field to update: " << endl;
                        cout << "1. Name" << endl;
                        cout << "2. Phone" << endl;
                        cout << "3. Email" << endl;
                        int choice;
                        cin >> choice;
                        cin.ignore();

                        // Update the selected field
                        string new_data;
                        switch (choice) {
                        case 1:
                            cout << "Enter new name: ";
                            getline(cin >> ws, new_data);
                            outfile << "Name: " << new_data << endl;
                            break;
                        case 2:
                            cout << "Enter new phone number: ";
                            getline(cin >> ws, new_data);
                            outfile << "Phone: " << new_data << endl;
                            break;
                        case 3:
                            cout << "Enter new email: ";
                            getline(cin >> ws, new_data);
                            outfile << "Email: " << new_data << endl;
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                        }
                    }
                    else {
                        // If the line doesn't match the person we're looking for, copy it to the output file as is
                        outfile << line << endl;
                    }
                }

                infile.close();
                outfile.close();

                // If we found the person and updated their data, replace the original file with the updated version
                if (found) {
                    remove(filename.c_str());
                    rename("temp.txt", filename.c_str());
                    cout << "Person data updated." << endl;
                }
                else {
                    // Otherwise, delete the temporary file
                    remove("temp.txt");
                    cout << "Person not found." << endl;
                }
            }
        }
    }
    if (!found) {
        cout << "Person not found." << endl;
    }
}