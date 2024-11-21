#include <Publisher.h>
#include <News.h>
#include <fstream>
#include <sstream>
using namespace std;

// TODO Settle file operations


int PublisherManager::totalPublishers = 0;
int PublisherManager::nextId = 1;

PublisherManager::PublisherManager()
{
  ifstream inPub("data/publishers.txt");

  if (!inPub.is_open())
  {
    ofstream outPub("data/publishers.txt");
    outPub << "id^email^password^name^about^phone\n";
    outPub.close();
  }
  else
  {
    string line;
    getline(inPub, line);
    while (getline(inPub, line))
    {
      stringstream ss(line);
      string data[6];
      int i = 0;
      while (getline(ss, line, '^'))
      {
        data[i++] = line;
      }

      publishers.push_back(Publisher{
        stoi(data[0]), data[1], data[2], data[3], data[4], data[5]
      });

      totalPublishers++;
    }
    
    nextId = publishers[totalPublishers-1].id + 1;
  }
}

vector<Publisher>& PublisherManager::getPublishers()
{
  return publishers;
}

Publisher PublisherManager::createPublisher(string email, string password, string name, string phone, string about)
{
  publishers.push_back(Publisher{ nextId, email, password, name, phone, about });
  nextId++;
  totalPublishers++;
}

Publisher editPublisher(int id, string newEmail = "", string newPassword = "", string newName = "", string newPhone = "", string about = "")
{
  
  if (newEmail)
  {
    
  }
}

const Publisher& PublisherManager::searchId(int id) const
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

const Publisher& PublisherManager::searchEmail(string email) const
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
