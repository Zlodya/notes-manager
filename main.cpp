#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Функция для добавления записи в базу данных
void addRecord(const string& filename) {
    ofstream file(filename, ios::app); // Открываем файл для добавления данных
    if (!file) { // Проверяем, удалось ли открыть файл
        cerr << "Error!" << endl;
        return;
    }

    string record;
    cout << "Enter record: ";
    cin.ignore(); // Игнорируем предыдущий ввод
    getline(cin, record); // Считываем всю строку

    file << record << endl; // Записываем запись в файл
    file.close(); // Закрываем файл
    cout << "Record added." << endl;
}

// Функция для удаления записи из базы данных
void deleteRecord(const string& filename) {
    ifstream file(filename); // Открываем файл для чтения
    if (!file) { // Проверяем, удалось ли открыть файл
        cerr << "Error!" << endl;
        return;
    }

    vector<string> records; // Вектор для хранения записей
    string record;

    // Считываем все записи из файла
    while (getline(file, record)) {
        records.push_back(record);
    }
    file.close(); // Закрываем файл

    cout << "Enter the record number to delete (starting from 1): ";
    int index;
    cin >> index;

    // Проверяем, корректен ли индекс
    if (index < 1 || index > records.size()) {
        cout << "Incorrect record number!" << endl;
        return;
    }

    records.erase(records.begin() + index - 1); // Удаляем запись по индексу

    // Записываем оставшиеся записи обратно в файл
    ofstream outFile(filename);
    for (const auto& rec : records) {
        outFile << rec << endl;
    }
    outFile.close(); // Закрываем файл
    cout << "Record deleted." << endl;
}

// Функция для просмотра всех записей в базе данных
void viewRecords(const string& filename) {
    ifstream file(filename); // Открываем файл для чтения
    if (!file) { // Проверяем, удалось ли открыть файл
        cerr << "Error!" << endl;
        return;
    }

    string record;
    int lineNumber = 1;

    // Считываем и выводим все записи
    while (getline(file, record)) {
        cout << lineNumber++ << ": " << record << endl;
    }
    file.close(); // Закрываем файл
}

int main() {
    string filename = "database.txt"; // Имя файла базы данных

    while (true) {
        cout << "\nChoose action:\n";
        cout << "1. Add record\n";
        cout << "2. Delete record\n";
        cout << "3. View records\n";
        cout << "4. Quit\n";
        cout << "Your choise: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord(filename); // Добавляем запись
                break;
            case 2:
                deleteRecord(filename); // Удаляем запись
                break;
            case 3:
                viewRecords(filename); // Просматриваем записи
                break;
            case 4:
                return 0; // Выход из программы
            default:
                cout << "Incorrect choice! Try again." << endl; // Обработка некорректного выбора
        }
    }

    return 0; // Завершение программы
}
