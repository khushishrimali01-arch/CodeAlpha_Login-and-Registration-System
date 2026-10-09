#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <functional>
using namespace std;

const string FILE_NAME = "users.txt";

string hashPassword(string password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

bool usernameExists(string username) {
    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        string storedUsername;
        string storedPassword;

        stringstream ss(line);
        getline(ss, storedUsername, ':');
        getline(ss, storedPassword, ':');

        if (storedUsername == username) {
            return true;
        }
    }

    return false;
}

string registerUser(string username, string password) {
    if (username.empty() || password.empty()) {
        return "Registration failed: Username and password cannot be empty.";
    }

    if (password.length() < 6) {
        return "Registration failed: Password must contain at least 6 characters.";
    }

    if (usernameExists(username)) {
        return "Registration failed: Username already exists.";
    }

    ofstream file(FILE_NAME, ios::app);

    file << username << ":" << hashPassword(password) << "\n";

    file.close();

    return "Registration successful.";
}

string loginUser(string username, string password) {
    if (username.empty() || password.empty()) {
        return "Login failed: Username and password cannot be empty.";
    }

    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        string storedUsername;
        string storedPassword;

        stringstream ss(line);

        getline(ss, storedUsername, ':');
        getline(ss, storedPassword, ':');

        if (storedUsername == username) {
            if (storedPassword == hashPassword(password)) {
                return "Login successful.";
            }

            return "Login failed: Invalid username or password.";
        }
    }

    return "Login failed: Invalid username or password.";
}

int main() {
    ofstream clearFile(FILE_NAME);
    clearFile.close();

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string operation, username, password;

        cin >> operation >> username >> password;

        if (operation == "REGISTER") {
            cout << registerUser(username, password) << endl;
        }
        else if (operation == "LOGIN") {
            cout << loginUser(username, password) << endl;
        }
        else {
            cout << "Invalid operation." << endl;
        }
    }

    return 0;
}
