/* ------------------------------------------------------------- AUTHOR ---------------------------------------------------------------- */
// CREATED BY: Khilfi bin Khairul Amin
/* ---------------------------------------------------------- DESCRIPTION -------------------------------------------------------------- */
//
// This file is created by Khilfi to demonstrate file operation to read and write data about Publisher.
//
// The file `Publisher.h` and `publishers.txt` is related to this file.
//   - Publisher.h: store declaration of Publisher class
//   - publishers.txt: store data about Publisher in text format
//
// Created at 23.10.2024
//
/* -------------------------------------------------------- CLASS DEFINITION ----------------------------------------------------------- */
#include <iostream>
#include <fstream>
#include "Publisher.h"
using namespace std;


const int P_SIZE = 200;
Publisher publishers[P_SIZE];
int Publisher::nextId = 1;

Publisher::Publisher(int id, string email, string password, string name, time_t timeRegistered)
{
  this->id = id;
  this->email = email;
  this->password = password;
  this->name = name;
  this->timeRegistered = timeRegistered;

  if (this->id >= nextId)
  {
    nextId = this->id + 1;
  }
}

Publisher::Publisher(string newEmail, string newPassword, string newName)
{
  this->id = nextId;
  this->email = newEmail;
  this->password = newPassword;
  this->name = newName;
  this->timeRegistered = time(0);

  nextId += 1;
}

Publisher::Publisher()
{
  return;
}

int Publisher::getId()
{
  return id;
}

string Publisher::getEmail()
{
  return email;
}

string Publisher::getPassword()
{
  return password;
}

string Publisher::getName()
{
  return name;
}

time_t Publisher::getTimeRegistered()
{
  return timeRegistered;
}

void Publisher::displayInfo()
{
  cout << "Publisher Name: " << name << endl;
  cout << "ID: " << id << endl;
  cout << "Email: " << email << endl;
  cout << "Password: " << password << endl;
  cout << "Time Registered: " << timeRegistered << endl;
}

/* -------------------------------------------------------- FUNCTION DEFINITION ----------------------------------------------------------- */

// This function is cursed with complexity, read at your own sanity!
void readPublishers(Publisher* publishers)
{
  ifstream inPublishers("database/publishers.txt");

  if (!inPublishers)
  {
    cout << "Read Publishers failed." << endl;
  }

  // Parsing the text file form into C++ datatypes
  string line;
  getline(inPublishers, line);  // Skip line 1 (data header)
  int k = 0;
  while (getline(inPublishers, line))
  {
    int i = 0, temp;
    string id, email, password, name, timeRegistered;

    temp = line.find("|", i);
    while(i != temp) id += line[i++];
    temp = line.find("|", ++i);
    while(i != temp) email += line[i++];
    temp = line.find("|", ++i);
    while(i != temp) password += line[i++];
    temp = line.find("|", ++i);
    while(i != temp) name += line[i++];
    i++;
    while(i < line.length()) timeRegistered += line[i++];

    publishers[k++] = Publisher(stoi(id), email, password, name, stoi(timeRegistered));
  }
}

void printPublishers(Publisher* publishers)
{
  for (int j = 0; j < 3; j++)
  {
    if (publishers[j].getId() != 0)
    {
      publishers[j].displayInfo();
    }
    else
    {
      break;
    }
  }
}

void writePublishers(Publisher* publishers)
{
  ofstream outPublishers("database/publishers.txt");

  if (!outPublishers)
  {
    cout << "Write Publishers failed." << endl;
  }

  Publisher* pub = publishers;
  outPublishers << "id|email|password|name|timeRegistered\n";
  while(pub->getId() != 0)
  {
    outPublishers << pub->getId() << "|" << pub->getEmail() << "|" << pub->getPassword() << "|" << pub->getName() << "|" << pub->getTimeRegistered() << "\n";
    pub++;
  }
}

/* -------------------------------------------------------- MAIN FUNCTION ----------------------------------------------------------- */

int main()
{
  readPublishers(publishers);
  printPublishers(publishers);
  int i;
  cin >> i;
  publishers[1] = Publisher("myvo@gmail.com", "myvo123", "MyVolunteer");
  writePublishers(publishers);
}

/* ---------------------------------------------------------------------------------------------------------------------------------- */
