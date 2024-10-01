#include <iostream>
#include <map>
#include <string>

using namespace std;

class Position {
protected:
    string name;
    int seniorityLevel; 
    string email;

public:
    Position(string n, int level, string e) : name(n), seniorityLevel(level), email(e) {}

    virtual void handleComplaint(int daysPending) {
        if (daysPending <= 3) {
            cout << "Complaint handled by: " << name << " (Email: " << email << ")" << endl;
        } else {
            cout << name << " couldn't resolve the complaint. Escalating..." << endl;
        }
    }

    int getSeniorityLevel() const {
        return seniorityLevel;
    }

    virtual string getEmail() const {
        return email;
    }

    virtual ~Position() {}
};

class JuniorStaff : public Position {
public:
    JuniorStaff(string name, string email) : Position(name, 1, email) {}
};

class SeniorStaff : public Position {
public:
    SeniorStaff(string name, string email) : Position(name, 2, email) {}
};

class Manager : public Position {
public:
    Manager(string name, string email) : Position(name, 3, email) {}
};

class Dean : public Position {
public:
    Dean(string name, string email) : Position(name, 4, email) {}
};

class EscalationMatrix {
private:
    map<int, Position*> escalationMap; 

public:

    void addPosition(Position* pos) {
        escalationMap[pos->getSeniorityLevel()] = pos;
    }

    void escalateComplaint(int daysPending) {
        for (auto it = escalationMap.begin(); it != escalationMap.end(); ++it) {
            it->second->handleComplaint(daysPending);
            if (daysPending <= 3) {
                break; 
            }
            daysPending -= 3; 
        }
    }

    ~EscalationMatrix() {
        for (auto it = escalationMap.begin(); it != escalationMap.end(); ++it) {
            delete it->second;
        }
    }
};

int main() {

    JuniorStaff* junior = new JuniorStaff("Aakash Gupta", "aakash@iiitd.ac.in");
    SeniorStaff* senior = new SeniorStaff("Ashutosh Brahma", "ashutosh@iiitd.ac.in");
    Manager* manager = new Manager("Sumit J Darak", "sumit@iiitd.ac.in");
    Dean* dean = new Dean("Vivek Ashot Bohara", "vivek@iiitd.ac.in");

    EscalationMatrix matrix;
    matrix.addPosition(junior);
    matrix.addPosition(senior);
    matrix.addPosition(manager);
    matrix.addPosition(dean);

    int daysPending;
    cout << "Enter the number of days the complaint has been pending: ";
    cin >> daysPending;

    matrix.escalateComplaint(daysPending);

    return 0;
}