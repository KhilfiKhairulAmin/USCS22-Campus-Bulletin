#include "Bulletin.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
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

const vector<News>* NewsManager::getAllNews() const
{
  return news;
}

int NewsManager::createNews(int publisherId, string title, string content)
{
  Datetime now = Datetime::getCurrentDatetime();
  news->push_back(News {
    nextNewsId,
    publisherId,
    now,
    now,
    Datetime(),
    title,
    content,
    0,
    0,
    false
  });
  totalNews++;
  nextNewsId++;
  return totalNews-1;
}

void NewsManager::editNews(int id, string newTitle = "", string newContent = "")
{
  int index = searchNewsId(id);
  Datetime now = Datetime::getCurrentDatetime();
  News* n = &(news->at(index));
  if (newTitle != "")
    n->title = newTitle;
  if (newContent != "")
    n->content = newContent;
}

void NewsManager::deleteNews(int id)
{
  int index = searchNewsId(id);
  news->erase(news->begin()+index);
  totalNews--;
}

int NewsManager::searchNewsId(int id) const
{
  int index = 0;
  for (auto it = news->begin(); it < news->end(); it++)
  {
    if (it->id == id)
    {
      return index;
    }
    index++;
  }
  throw "ID doesn't exist";
}

NewsManager::NewsManager()
{
  ifstream file("database/news.txt");
  
  if (!file.is_open())
  {
    throw "Failed to open database/news.txt";
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

    news->push_back(News{
      stoi(fields[0]),
      stoi(fields[1]),
      Datetime::sToDatetime(fields[2]),
      Datetime::sToDatetime(fields[3]),
      Datetime::sToDatetime(fields[4]),
      fields[5],
      fields[6],
      stoi(fields[7]),
      stoi(fields[8]),
      stoi(fields[9]) == 1
    });
  
    totalNews++;
  }
  if (totalNews > 0)
    nextNewsId = (*news)[totalNews-1].id + 1;
}

void NewsManager::saveNews() const
{
  ofstream outNews("database/news.txt");

  if (!outNews.is_open())
    throw "Failed to open database/news.txt";

  outNews << "id^publisherId^createdAt^editedAt^publishedAt^title^content^numOfLikes^numOfDislikes^isPublished\n";

  for (auto it = news->begin(); it < news->end(); it++)
    outNews << it->id << "^" << it->publisherId << "^" << Datetime::datetimeToS(it->createdAt) << "^" << Datetime::datetimeToS(it->editedAt) << "^" << Datetime::datetimeToS(it->publishedAt) << "^" << it->title << "^" << it->content << "^" << it->numOfLikes << "^" << it->numOfDislikes << "^" << it->isPublished << "\n";
}

NewsManager::~NewsManager()
{
  saveNews();
  delete news;
  news = nullptr;
}

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

bool findSimilarTitle(const string& text, const string& pattern) {
    string lowerText = toLowerCase(text);
    string lowerPattern = toLowerCase(pattern);

    // Use string::find for substring search
    if (lowerText.find(lowerPattern) != string::npos) {
        return true; // Found a similar title
    }
    return false; // No similar title found
}

vector<News> NewsManager::searchTitle(string title) const
{
  vector<News> res;
  for (auto it = news->begin(); it < news->end(); it++)
  {
    string t = toLowerCase(it->title);
    string search = toLowerCase(title);

    if (t.find(search) != string::npos)
      res.push_back(*it);
  }
  return res;
}

vector<News> NewsManager::searchDate(Datetime dt_start, Datetime dt_end) const
{
  vector<News> res;

  for (auto it = news->begin(); it < news->end(); it++)
  {
    if (it->createdAt >= dt_start && it->createdAt <= dt_end)
      res.push_back(*it);
  }
  return res;
}

Bulletin::Bulletin(): NewsManager(), PublisherManager() {};

vector<int> Bulletin::getNewsByPublisher(int publisherId) const
{
  int cur = 0;
  vector<int> indexes;
  for (auto it = news->begin(); it < news->end();it++)
  {
    if (it->publisherId == publisherId)
      indexes.push_back(cur);
    cur++;
  }
  return indexes;
}

int Bulletin::getTotalLikes(int publisherId) const
{
  int total = 0;
  for (auto it = news->begin(); it < news->end();it++)
    if (it->publisherId == publisherId)
      total += it->numOfLikes;
  return total;
}

int Bulletin::getTotalDislikes(int publisherId) const
{
  int total = 0;
  for (auto it = news->begin(); it < news->end();it++)
    if (it->publisherId == publisherId)
      total += it->numOfDislikes;
  return total;
}

int Bulletin::getTotalNewsPublished(int publisherId) const
{
  int total = 0;
  for (auto it = news->begin(); it < news->end();it++)
    if (it->publisherId == publisherId)
      total++;
  return total;
}

int Bulletin::getTotalPublishers() const
{
  return totalPublishers;
}

int Bulletin::getTotalNews() const
{
  return totalPublishers;
}

Bulletin::~Bulletin() {};

int main()
{
  // PublisherManager publisherManager = PublisherManager();
  // const vector<Publisher>* publishers = publisherManager.getAllPublishers();
  // // publisherManager.deletePublisher(2);
  // int index = publisherManager.searchEmail("stfu@gmail.com");
  // cout << index;
  // for (auto it = publishers->begin(); it < publishers->end(); it++)
  // {
  //   cout << it->name << endl;
  // }
  NewsManager nm = NewsManager();
  const vector<News>* n = nm.getAllNews();
  Datetime dt = Datetime::getCurrentDatetime();
  vector<News> s = nm.searchDate(Datetime::sToDatetime("2/11/2024/21/11/5"), Datetime::sToDatetime("2/11/2024/21/11/5"));

  for (auto it = s.begin(); it < s.end(); it++)
    cout << it->title << it->isPublished << endl;
}
