#include <Publisher.h>
#include <News.h>
using namespace std;

const vector<Publisher>& PublisherManager::getPublishers() const
{
  return publishers;
}

const Publisher& PublisherManager::createPublisher(string email, string password, string name, string phone, string about) const
{
    this->
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
