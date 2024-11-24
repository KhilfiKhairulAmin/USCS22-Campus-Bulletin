#include "../headers/Database.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

int PublisherManager::totalPublishers = 0;
int PublisherManager::nextPublisherId = 1;
int NewsManager::totalNews = 0;
int NewsManager::nextNewsId = 1;
string Database::version = "0.0.1";

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

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

vector<Publisher> PublisherManager::searchName(string name) const
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

vector<int> NewsManager::searchTitle(string title) const
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

Database::Database(): NewsManager(), PublisherManager() {};

vector<int> Database::getNewsByPublisher(int publisherId) const
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

int Database::getTotalLikes(int publisherId) const
{
  int total = 0;
  for (auto it = news->begin(); it < news->end();it++)
    if (it->publisherId == publisherId)
      total += it->numOfLikes;
  return total;
}

int Database::getTotalDislikes(int publisherId) const
{
  int total = 0;
  for (auto it = news->begin(); it < news->end();it++)
    if (it->publisherId == publisherId)
      total += it->numOfDislikes;
  return total;
}

int Database::getTotalNewsPublished(int publisherId) const
{
  int total = 0;
  for (auto it = news->begin(); it < news->end();it++)
    if (it->publisherId == publisherId)
      total++;
  return total;
}

int Database::getTotalPublishers() const
{
  return totalPublishers;
}

int Database::getTotalNews() const
{
  return totalPublishers;
}

vector<array<int, 2>> Database::getPopularityRankings() const
{
  struct IndexSum
  {
    int i = -1;
    int sum = 0;

    bool operator<(IndexSum is)
    {
      return sum < is.sum;
    }
  };

  unordered_map<int, IndexSum> m;
  int i = 0;
  for (auto it = publishers->begin(); it < publishers->end(); it++)
    m.insert(make_pair( it->id, IndexSum{ i++, 0 }));

  int j = 0;
  for (auto it = news->begin(); it < news->end(); it++)
    m[it->publisherId].sum += it->numOfLikes - it->numOfDislikes;
  
  vector<IndexSum> r;
  for (auto it = publishers->begin(); it < publishers->end(); it++)
    r.push_back(m[it->id]);

  sort(r.rbegin(), r.rend());

  vector<array<int, 2>> ids;
  for (auto it = r.begin(); it < r.end(); it++)
  {
    ids.push_back({ it->i, it->sum });
  }
  
  return ids;
}

Database::~Database() {};
