#include "Bulletin.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int PublisherManager::totalPublishers = 0;
int PublisherManager::nextPublisherId = 1;
int NewsManager::totalNews = 0;
int NewsManager::nextNewsId = 1;
string Bulletin::version = "0.0.1";

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
    string id;
    stringstream ss(line);
    vector<string> fields;

    // Split by ^ (the delimiter)
    while (getline(ss, id, '^'))
    {
      fields.push_back(id);
    }
    
      publishers->push_back(Publisher{
        stoi(fields[0]),
        fields[1],
        fields[2], 
        fields[3],
        fields[4],
        fields[5]
      });
    

    totalPublishers++;
  }
  if (totalPublishers > 0)
    nextPublisherId = (*publishers)[totalPublishers-1].id + 1;
}

const vector<Publisher>* PublisherManager::getAllPublishers() const
{
  return publishers;
}

int PublisherManager::createPublisher(string email, string password, string name, string about, string phone)
{
  publishers->push_back(Publisher{ nextPublisherId, email, password, name, about, phone });
  nextPublisherId++;
  totalPublishers++;
  return totalPublishers-1;
}

void PublisherManager::editPublisher(int id, string newEmail = "", string newPassword = "", string newName = "", string newAbout = "", string newPhone = "")
{
  int index = searchPublisherId(id);
  Publisher* p = &(publishers->at(index));
  
  if (newEmail != "")
    p->email = newEmail;
  if (newPassword != "")
    p->password = newPassword;
  if (newName != "")
    p->name = newName;
  if (newAbout != "")
    p->about = newAbout;
  if (newPhone != "")
    p->phone = newPhone;
}

void PublisherManager::deletePublisher(int id)
{
  int index = searchPublisherId(id);
  publishers->erase(publishers->begin()+index);
}

void PublisherManager::savePublishers() const
{
  ofstream outPub("database/publishers.txt");

  if (!outPub.is_open())
    throw "Failed to open database/publishers.txt";
  
  outPub << "id^email^password^name^about^phone\n";
  for (auto it = publishers->begin(); it < publishers->end(); it++)
    outPub << it->id << "^" << it->email << "^" << it->password << "^" << it->name << "^" << it->about << "^" << it->phone << "\n";

  outPub.close();
}

PublisherManager::~PublisherManager()
{
  savePublishers();
  delete publishers;
  publishers = nullptr;
}

int PublisherManager::searchPublisherId(int id) const
{ 
  int index = 0;
  for (auto it = publishers->begin(); it < publishers->end(); it++)
  {
    if (it->id == id)
    {
      return index;
    }
    index++;
  }
  throw "ID doesn't exist";
}

int PublisherManager::searchEmail(string email) const
{
  int index = 0;
  for (auto it = publishers->begin(); it < publishers->end(); it++)
  {
    if (it->email == email)
    {
      return index;
    }
    index++;
  }
  throw "Email doesn't exist";
}

int main()
{
  PublisherManager publisherManager = PublisherManager();
  const vector<Publisher>* publishers = publisherManager.getAllPublishers();
  // publisherManager.deletePublisher(2);
  int index = publisherManager.searchEmail("stfu@gmail.com");
  cout << index;
  // for (auto it = publishers->begin(); it < publishers->end(); it++)
  // {
  //   cout << it->name << endl;
  // }
}
