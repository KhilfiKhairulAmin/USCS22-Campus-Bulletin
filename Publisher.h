#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <string>
#include <ctime>
#include <vector>
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
    vector<Publisher> publishers;
    /** Keeps total number of publishers */
    static int totalPublishers;
    /** Tracks next unique value for `Publisher.id` */
    static int nextId;
  public:
    /** Loads `Publishers` from database. */
    PublisherManager();
    /** Returns a vector containing all `Publishers`. */
    vector<Publisher> getPublishers();
    /** Creates a new `Publisher`, then returns its constant pointer.  */
    Publisher createPublisher(string email, string password, string name, string phone, string about);
    /** Modifies data inside a `Publisher`, then return its constant pointer. */
    Publisher editPublisher(int id, string newEmail = "", string newPassword = "", string newName = "", string newPhone = "", string about = "");
    /** Deletes a `Publisher`. */
    void deletePublisher(int id);
    /** Returns one `Publisher` based on given `id`. */
    Publisher searchId(int id);
    /** Returns one `Publisher` based on given `email`. */
    Publisher searchEmail(string email);
    /** Lazily searches names of `Publishers`, then return a constant vector. */
    vector<Publisher>& searchName(string name);
    /** Lazily searches phone numbers of `Publishers`, then return a constant vector. */
    vector<Publisher>& searchPhone(string phone);
    /** Returns a constant vector containing all `Publishers` sorted ascendingly/descendingly based on `Publisher.name` attribute. */
    vector<Publisher>& sortPublishers(bool ascending = true);
    
};

#endif