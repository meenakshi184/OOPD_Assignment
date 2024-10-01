#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Faculty {
public:
    std::string name;
    std::string department;
    std::string designation;
    std::string roomNumber;
    std::string phoneNumber;
    std::string emailId;
};

// Function to split a CSV line while ignoring commas inside parentheses
void splitCSV(const std::string &line, std::string tokens[], int &tokenCount) {
    std::string token;
    int parenthesesCount = 0;
    tokenCount = 0;

    for (char c : line) {
        if (c == ',') {
            if (parenthesesCount == 0) {
                if (tokenCount < 6) { // Ensure we do not exceed the token array size
                    tokens[tokenCount++] = token;
                }
                token.clear();
            } else {
                token += c;  // Keep the comma inside parentheses
            }
        } else {
            if (c == '(') {
                parenthesesCount++;
            } else if (c == ')') {
                parenthesesCount--;
            }
            token += c;
        }
    }
    if (!token.empty() && tokenCount < 6) {
        tokens[tokenCount++] = token; // Add the last token if there's space
    }
}

void searchFaculty(Faculty faculties[], int facultyCount, const std::string &query) {
    bool found = false;
    for (int i = 0; i < facultyCount; ++i) {
        if (faculties[i].name.find(query) != std::string::npos) {
            std::cout << "Name: " << faculties[i].name << "\n";
            std::cout << "Department: " << faculties[i].department << "\n";
            std::cout << "Designation: " << faculties[i].designation << "\n";
            std::cout << "Room Number: " << faculties[i].roomNumber << "\n";
            std::cout << "Phone Number: " << faculties[i].phoneNumber << "\n";
            std::cout << "Email ID: " << faculties[i].emailId << "\n";
            std::cout << "-------------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "No faculty member found with the name: " << query << "\n";
    }
}

int main() {
    const int MAX_FACULTY = 100;
    Faculty faculties[MAX_FACULTY];
    int facultyCount = 0;

    std::ifstream inputFile("faculty_data.csv");
    std::string line;

    std::getline(inputFile, line); // Skip header

    while (std::getline(inputFile, line) && facultyCount < MAX_FACULTY) {
        std::string tokens[6]; // Fixed size for expected tokens
        int tokenCount = 0;
        splitCSV(line, tokens, tokenCount);

        // Only assign if we have enough tokens
        if (tokenCount >= 6) {
            faculties[facultyCount].name = tokens[0];
            faculties[facultyCount].department = tokens[1];
            faculties[facultyCount].designation = tokens[2];
            faculties[facultyCount].roomNumber = tokens[3];
            faculties[facultyCount].phoneNumber = tokens[4];
            faculties[facultyCount].emailId = tokens[5];
            facultyCount++;
        } else {
            std::cerr << "Error: Not enough tokens in line: " << line << "\n";
        }
    }
    inputFile.close();

    std::string query;
    std::cout << "Enter the name (or partial name) of the faculty member to search for: ";
    std::getline(std::cin, query);

    searchFaculty(faculties, facultyCount, query);

    return 0;
}