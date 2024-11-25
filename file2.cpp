#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Datetime
{

};

struct Publisher
{
  int id;
  string email;
  string password;
  string name;
  string about;
  const char* phone;
};

struct News
{
  int id;
  int publisherId;
  Datetime datetime;
  string title;
  string content;
  string tags;
};

class DataManager
{
  private:
    const int SIZE_P = 200;
    const int SIZE_N = 400;
    Publisher* const publishers = new Publisher[SIZE_P]();
    News* const news = new News[SIZE_N]();
    static int nextPublisherId;
    static int nextNewsId;
    static int totalPublishers;
    static int totalNews;
  public:
    Publisher* getAllPublishers() { return publishers; }
    
    News* getAllNews() { return news; }
    
    int createNewPublisher(string email, string password, string name, string about, string phone)
    {
      Publisher newP;
      newP.id = nextPublisherId;
      newP.email = email;
      newP.password = password;
      newP.name = name;
      newP.about = about;
      newP.phone = phone.c_str();
      
      publishers[totalPublishers] = newP;
      
      nextPublisherId++;
      totalPublishers++;

      return newP.id;
    }

    int createNewNews(int publisherId, Datetime datetime, string title, string content, string tags)
    {
      News newN;
      newN.id = nextNewsId;

      nextNewsId++;
      totalNews++;

      return newN.id;
    }
};


int main()
{

}
