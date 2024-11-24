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
    vector<Publisher>* publishers = new vector<Publisher>();

    /** Keeps total number of publishers */
    static int totalPublishers;

    /** Tracks next unique value for `Publisher.id` */
    static int nextPublisherId;

  public:
    /** Loads `Publishers` from database. */
    PublisherManager();

    /** Returns constant pointer vector storing all `Publishers`. */
    const vector<Publisher>* getAllPublishers() const;
    
    /** Creates a new `Publisher`, then returns its index inside the `Publisher` vector.  */
    int createPublisher(string email, string password, string name, string phone, string about);

    /** Modifies data of a `Publisher` with specified `id`. */
    void editPublisher(int id, string newEmail, string newPassword, string newName, string newAbout, string newPhone);

    /** Deletes a `Publisher` with specified `id`. */
    void deletePublisher(int id);



    /** Save `Publishers` to database. */
    void savePublishers() const;

    /** Stores `Publisher` inside database and deletes DMA inside `Publisher` class. */
    ~PublisherManager();

    /** Returns the index of a `Publisher` with specified `id`. */
    int searchPublisherId(int id) const;

    /** Returns the index of a `Publisher` based on given `email`. */
    int searchEmail(string email) const;

    /** Searches names of `Publishers`, then return a constant vector. */
    vector<Publisher> searchName(string name) const;
};

#endif