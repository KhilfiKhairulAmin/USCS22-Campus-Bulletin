#include "Publisher.h"
#include "News.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int PublisherManager::totalPublishers = 0;
int PublisherManager::nextId = 1;

PublisherManager::PublisherManager()
{
  ifstream file("database/publishers.txt");
  
  if (!file.is_open())
  {
    throw "Failed to open database/publishers.txt";
  }
  
  string line;
  getline(file, line);  // Skip first line as it is header of the file
  while (getline(file, line))
  {
    string id, email, password, name, about, phone;
    stringstream ss(line);
    vector<string> fields;

    // Split by ^ (the delimiter)
    while (getline(ss, id, '^'))
    {
      fields.push_back(id);
    }
    
    if (fields.size() == 6)
    {
      publishers.push_back(Publisher
      {
        stoi(fields[0]),
        fields[1],
        fields[2], 
        fields[3],
        fields[4],
        fields[5]
      });
    }

    totalPublishers++;
    nextId++;
  }
}

vector<Publisher> PublisherManager::getPublishers()
{
  return publishers;
}

Publisher PublisherManager::createPublisher(string email, string password, string name, string phone, string about)
{
  publishers.push_back(Publisher{nextId, email, password, name, phone, about});
  totalPublishers++;
  nextId++;
  return publishers.back();
}

Publisher PublisherManager::searchId(int id)
{ 
  for (auto it = publishers.begin(); it < publishers.end(); it++)
  {
    if (it->id == id)
    {
      return *it;
    }
  }
  throw "ID doesn't exist";
}

Publisher PublisherManager::searchEmail(string email)
{
  for (auto it = publishers.begin(); it < publishers.end(); it++)
  {
    if (it->email == email)
    {
      return *it;
    }
  }
  throw "Email doesn't exist";
}

int main()
{
  PublisherManager publisherManager = PublisherManager();
  vector<Publisher> publishers = publisherManager.getPublishers();
  publishers[0].about = "Hello World";
  for (auto it = publishers.begin(); it < publishers.end(); it++)
  {
    cout << it->id << " " << it->email << " " << it->password << " " << it->name << " " << it->phone << " " << it->about << endl;
  }
  vector<Publisher> publishers2 = publisherManager.getPublishers();
  publishers2[0].name = "Hello World";
    for (auto it = publishers2.begin(); it < publishers2.end(); it++)
  {
    cout << it->id << " " << it->email << " " << it->password << " " << it->name << " " << it->phone << " " << it->about << endl;
  }
    for (auto it = publishers.begin(); it < publishers.end(); it++)
  {
    cout << it->id << " " << it->email << " " << it->password << " " << it->name << " " << it->phone << " " << it->about << endl;
  }
}
