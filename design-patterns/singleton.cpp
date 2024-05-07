#include <iostream>

class Database {
private:
    static Database* instance;
    int record;
    std::string name;

    // Private constructor so that no objects can be created.
    Database(std::string name) {
        this->name = name;
        record = 0;
    }

public:
    static Database* getInstance(std::string name) {
        if (instance == nullptr) {
            instance = new Database(name);
        }
        return instance;
    }

    void printDetails() {
        std::cout << "Database Name: " << name << " - Record: " << record << endl;
    }

    void addRecord() {
        record++;
    }

    void setName(std::string name) {
        this->name = name;
    }
};

// Initialize pointer to zero so that it can be initialized in first call to getInstance
Database* Database::instance = 0;
