#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Person {
protected:
    string name;
    string room;
    string phone;
    string email;

public:
    Person(string n, string r, string p, string e)
        : name(n), room(r), phone(p), email(e) {}

    virtual void displayDetails() const {
        cout << "Name: " << name << endl;
        cout << "Room: " << room << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
    }

    string getName() const {
        return name;
    }
};

class Position : public Person {
protected:
    string position;
    string department;
    Position* next;

public:
    Position(string dept, string pos, string n, string r, string p, string e)
        : Person(n, r, p, e), department(dept), position(pos), next(nullptr) {}

    void displayDetails() const override {
        cout << "Department: " << department << endl;
        cout << "Position: " << position << endl;
        Person::displayDetails(); 
    }

    void setNext(Position* nextPos) {
        next = nextPos;
    }

    Position* getNext() const {
        return next;
    }
};

class Dean : public Position {
public:
    Dean(string dept, string n, string r, string p, string e)
        : Position(dept, "Dean", n, r, p, e) {}
};

class AdministrativeOfficer : public Position {
public:
    AdministrativeOfficer(string dept, string pos, string n, string r, string p, string e)
        : Position(dept, pos, n, r, p, e) {}
};

class Administration {
private:
    Position* head;

public:
    Administration() : head(nullptr) {}

    void addPerson(Position* newPerson) {
        if (head == nullptr) {
            head = newPerson;
        } else {
            Position* current = head;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newPerson);
        }
    }

void readCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);  

    while (getline(file, line)) {
        stringstream ss(line);
        string department, position, name, room, phone, email;

        getline(ss, department, ',');
        getline(ss, position, ',');
        getline(ss, name, ',');
        getline(ss, room, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');

        Position* newPerson;
        if (position == "Dean") {
            newPerson = new Dean(department, name, room, phone, email);
        } else {
            newPerson = new AdministrativeOfficer(department, position, name, room, phone, email);
        }

        addPerson(newPerson);
    }

    file.close();

    // printAllPeople();
}

    void printAllPeople() const {
        Position* current = head;
        while (current != nullptr) {
            current->displayDetails();
            cout << "-----------------------" << endl;
            current = current->getNext();
        }
    }

    void fetchDetailsByName(const string& name) const {
        Position* current = head;
        bool found = false;
        while (current != nullptr) {
            if (current->getName() == name) {
                current->displayDetails();
                found = true;
                break;
            }
            current = current->getNext();
        }
        if (!found) {
            cout << "Person with name '" << name << "' not found." << endl;
        }
    }

    ~Administration() {
        Position* current = head;
        while (current != nullptr) {
            Position* next = current->getNext();
            delete current;
            current = next;
        }
    }
};

int main() {
    Administration admin;

    admin.readCSV("data.csv");

    string name;
    cout << "Enter the name of the person to fetch details: ";
    getline(cin, name);

    admin.fetchDetailsByName(name);

    return 0;
}