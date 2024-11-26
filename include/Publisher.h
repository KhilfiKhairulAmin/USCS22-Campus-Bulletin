#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "Utility.h"
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

struct Publisher
{
  int id;
  string email;
  string password;
  string name;
  string about;
  string phone;
};

class PublisherManager
{
  protected:
    /** Vector containing `Publishers`. */
    vector<Publisher>* publishers = new vector<Publisher>();

    /** Keeps total number of publishers */
    static int totalPublishers;

    /** Tracks next unique value for `Publisher.id` */
    static int nextPublisherId;

  public:
    /** Loads `Publishers` from database. */
    PublisherManager()
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
    };

    /** Returns constant pointer vector storing all `Publishers`. */
    const vector<Publisher>* getAllPublishers() const
    {
      return publishers;
    }
    
    /** Creates a new `Publisher`, then returns its index inside the `Publisher` vector.  */
    int createPublisher(string email, string password, string name, string about, string phone)
    {
      publishers->push_back(Publisher{ nextPublisherId, email, password, name, about, phone });
      nextPublisherId++;
      totalPublishers++;
      return totalPublishers-1;
    }

    /** Modifies data of a `Publisher` with specified `id`. */
    void editPublisher(int id, string newEmail = "", string newPassword = "", string newName = "", string newAbout = "", string newPhone = "")
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

    /** Deletes a `Publisher` with specified `id`. */
    void deletePublisher(int id)
    {
      int index = searchPublisherId(id);
      publishers->erase(publishers->begin()+index);
    }

    /** Save `Publishers` to database. */
    void savePublishers() const
    {
      ofstream outPub("database/publishers.txt");

      if (!outPub.is_open())
        throw "Failed to open database/publishers.txt";
      
      outPub << "id^email^password^name^about^phone\n";
      for (auto it = publishers->begin(); it < publishers->end(); it++)
        outPub << it->id << "^" << it->email << "^" << it->password << "^" << it->name << "^" << it->about << "^" << it->phone << "\n";

      outPub.close();
    }

    /** Stores `Publisher` inside database and deletes DMA inside `Publisher` class. */
    ~PublisherManager()
    {
      savePublishers();
      delete publishers;
      publishers = nullptr;
    }

    /** Returns the index of a `Publisher` with specified `id`. */
    int searchPublisherId(int id) const
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

    /** Returns the index of a `Publisher` based on given `email`. */
    int searchEmail(string email) const
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

    /** Searches names of `Publishers`, then return a constant vector. */
    vector<Publisher> searchName(string name) const
    {
      vector<Publisher> res;
      for (auto it = publishers->begin(); it < publishers->end(); it++)
      {
        string t = toLowerCase(it->name);
        string search = toLowerCase(name);

        if (t.find(search) != string::npos)
          res.push_back(*it);
      }
      return res;
    }
};

#endif