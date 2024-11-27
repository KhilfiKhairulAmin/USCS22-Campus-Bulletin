#ifndef NEWS_H
#define NEWS_H
#include "Datetime.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct News
{
  int id;
  int publisherId;
  Datetime createdAt;
  Datetime editedAt;
  Datetime publishedAt;

  string title;
  string content;
  int numOfLikes;
  int numOfDislikes;

  bool isPublished;
};

class NewsManager
{
  protected:
    /** Vector containing `News`. */
    vector<News>* news = new vector<News>();

    /** Keeps total number of news */
    static int totalNews;

    /** Tracks next unique value for `News.id` */
    static int nextNewsId;

  public:
    /** Returns a constant vector containing all `News`. */
    const vector<News>* getAllNews() const
    {
      return news;
    }

    /** Creates a `News`, then return the index of the `News`.  */
    int createNews(int publisherId, string title, string content)
    {
      Datetime now = Datetime::getCurrentDatetime();
      news->push_back(News {
        nextNewsId,
        publisherId,
        now,
        now,
        Datetime(),
        title,
        to_string(nextNewsId),
        0,
        0,
        false
      });

      ofstream nf(("news/" + to_string(nextNewsId) + ".txt").c_str());

      if (!nf.is_open())
      {
        cout << "NOT OPEN!";
      }
      nf << content;
      nf.close();

      totalNews++;
      nextNewsId++;
      saveNews();
      return totalNews-1;
    }

    /** Modifies data inside a `News` with specified `id`. */
    void editNews(int id, string newTitle = "", string newContent = "")
    {
      int index = searchNewsId(id);
      Datetime now = Datetime::getCurrentDatetime();
      News* n = &(news->at(index));
      if (newTitle != "")
        n->title = newTitle;
      if (newContent != "")
        n->content = newContent;
      n->editedAt = now;
      saveNews();
    }

    /** Deletes a `News` with specified `id`. */
    void deleteNews(int id)
    {
      int index = searchNewsId(id);
      news->erase(news->begin()+index);
      totalNews--;
      saveNews();
    }

    /** Loads `News` from database. */
    NewsManager()
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

    /** Saves `News` inside the database. */
    void saveNews() const
    {
      ofstream outNews("database/news.txt");

      if (!outNews.is_open())
        throw "Failed to open database/news.txt";

      outNews << "id^publisherId^createdAt^editedAt^publishedAt^title^content^numOfLikes^numOfDislikes^isPublished\n";

      for (auto it = news->begin(); it < news->end(); it++)
        outNews << it->id << "^" << it->publisherId << "^" << Datetime::datetimeToS(it->createdAt) << "^" << Datetime::datetimeToS(it->editedAt) << "^" << Datetime::datetimeToS(it->publishedAt) << "^" << it->title << "^" << it->content << "^" << it->numOfLikes << "^" << it->numOfDislikes << "^" << it->isPublished << "\n";
    }

    /** Stores `News` inside database and deletes DMA inside `News` class. */
    ~NewsManager()
    {
      saveNews();
      delete news;
      news = nullptr;
    }

    /** Returns index of `News` with specified `id`. */
    int searchNewsId(int id) const
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

    /** Searches title of `News`, then return a constant vector. */
    vector<News> searchTitle(string title) const
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

    /** Searches news published between `dt_start` and `dt_end`. */
    vector<News> searchDate(Datetime dt_start, Datetime dt_end) const
    {
      vector<News> res;
      for (auto it = news->begin(); it < news->end(); it++)
      {
        if (it->createdAt >= dt_start && it->createdAt <= dt_end)
          res.push_back(*it);
      }
      return res;
    }
};

#endif