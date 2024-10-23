#ifndef PUBLISHER_H
#define PUBLISHER_H
#include <string>
#include <ctime>
using namespace std;


struct Post
{

};


class Publisher
{
  private:
    // Account related information
    int id;
    string email;
    string password;
    
    // Profile related information
    string name;
    string about;
    Post posts[200];

    // Metadata
    time_t timeRegistered;

  public:
    Publisher();
};

#endif