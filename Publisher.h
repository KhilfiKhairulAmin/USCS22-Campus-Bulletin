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
    /** Returns a constant vector containing all `Publishers`. */
    const vector<Publisher>& getPublishers() const;
    /** Creates a new `Publisher`, then returns its constant pointer.  */
    const Publisher& createPublisher(string email, string password, string name, string phone, string about) const;
    /** Modifies data inside a `Publisher`, then return its constant pointer. */
    const Publisher& editPublisher(int id, string newEmail = "", string newPassword = "", string newName = "", string newPhone = "", string about = "") const;
    /** Deletes a `Publisher`. */
    void deletePublisher(int id) const;
    /** Returns one `Publisher` based on given `id`. */
    const Publisher& searchId(int id) const;
    /** Returns one `Publisher` based on given `email`. */
    const Publisher& searchEmail(string email) const;
    /** Lazily searches names of `Publishers`, then return a constant vector. */
    const vector<Publisher>& searchName(string name);
    /** Lazily searches phone numbers of `Publishers`, then return a constant vector. */
    const vector<Publisher>& searchPhone(string phone);
    /** Returns a constant vector containing all `Publishers` sorted ascendingly/descendingly based on `Publisher.name` attribute. */
    const vector<Publisher>& sortPublishers(bool ascending = true);
};

#endif