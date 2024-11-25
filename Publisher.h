#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <string>
#include <ctime>
using namespace std;


class Publisher
{
  private:
    int id;  // Unique identifier for the publisher
    string email;  // Will be used for sign up and log in
    string password;  // Used for authentication
    string name;  // Publicly shown name
    time_t timeRegistered;  // Stored in time after epoch format (seconds)
    
    static int nextId;  // 
  public:
    Publisher(int, string, string, string, time_t);  // This one is default to load Publisher from file
    Publisher(string, string, string);  // This one is used when creating new Publisher
    Publisher();
    void displayInfo();
    int getId();
    string getEmail();
    string getPassword();
    string getName();
    time_t getTimeRegistered();
};


#endif