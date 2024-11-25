/* ------------------------------------------------------------- AUTHOR ---------------------------------------------------------------- */
// CREATED BY: Khilfi bin Khairul Amin
/* ---------------------------------------------------------- DESCRIPTION -------------------------------------------------------------- */
//
// This file is created by Khilfi to simulate the sign up and login feature.
// This file does not relate to main.cpp and other files, can run this file independently and it will work.
// Created at 22.10.2024
//
/* -------------------------------------------------------- CLASS DECLARATION --------------------------------------------------------- */
#include <iostream>
#include <string>
using namespace std;


class Publisher
{
    private:
        int id;
        string name;
        string username;
        string password;

        static int totalPublishers;
        static int curId;
    public:
        Publisher(string name, string username, string password)
        {
            this->id = curId;
            this->name = name;
            this->username = username;
            this->password = password;
            totalPublishers++;
            curId++;
        }
        Publisher()
        {
            
        }
        string getUsername()
        {
            return username;
        }
        bool comparePassword(string password)
        {
            return password == this->password;
        }
        void displayInfo()
        {
            cout << "Publisher #" << id << endl;
            cout << "Name: " << name << endl;
            cout << "Username: " << username << endl;
        }
        int getId()
        {
            return id;
        }
};

int Publisher::totalPublishers = 0;  // Default value for totalPublisher is 0
int Publisher::curId = 1;  // Starting value for current ID is 1
int sessionId = 0;

/* -------------------------------------------------------- MAIN PROGRAM -------------------------------------------------------------- */
Publisher publisher1("MyVolunteer", "myvo", "myvo123");
Publisher publisher2("PEERS", "peers", "peers123");
Publisher publishers[3] = { publisher1, publisher2 };


int main()
{
    cout << "Welcome to INTEC Campus Bulletin!" << endl << endl;
    cout << "[1] Log in" << endl << "[2] Sign up" << endl << endl;
    cout << "Choose your action: ";

    // Get input from user
    char option;
    cin >> option;
    cin.ignore();
    
    cout << endl;
    if (option == '1')
    {
        // Login option

        string username, password;  // Store username and password input

        cout << "Login" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        cout << endl;

        Publisher* currentPublisher = nullptr;
        for (int i = 0; i < 3; i++)
        {
            // Search for a user with the provided username
            if (username == publishers[i].getUsername())
            {
                currentPublisher = &publishers[i];
                break;
            }
        }

        if (currentPublisher != nullptr)
        {
            if (currentPublisher->comparePassword(password))
            {
                cout << "User logged in successfully! User INFO is:" << endl;
                sessionId = currentPublisher->getId();
            }
            else
            {
                cout << "Password is wrong." << endl;
            }
        }
        else
        {
            cout << "User not found." << endl;
        }
    }
    else if (option == '2')
    {
        // Sign up option

        string name, username, password;

        cout << "Sign up" << endl;
        cout << "Publisher Name (public): ";
        getline(cin, name);
        cout << "Publisher Username (private): ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        Publisher newPublisher(name, username, password);
        publishers[2] = newPublisher;
        cout << endl << "New user created successfully!" << endl;
        cout << endl << "New Publisher Info" << endl;
        sessionId = publishers[2].getId();
    }
    else
    {
        // Invalid option
        cout << "Invalid action." << endl;
    }
    publishers[sessionId-1].displayInfo();
    cout << endl << "Exiting application..." << endl;

    return 0;
}
