#ifndef NEWS_H
#define NEWS_H
#include <string>
#include <vector>
#include "Datetime.h"

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
    vector<News>* news;

    /** Keeps total number of news */
    static int totalNews;

    /** Tracks next unique value for `News.id` */
    static int nextNewsId;

  public:
    /** Returns a constant vector containing all `News`. */
    const vector<News>* getAllNews() const;

    /** Creates a `News`, then return the index of the `News`.  */
    int createNews(int publisherId, string title, string content);
    
    /** Modifies data inside a `News` with specified `id`. */
    void editNews(int id, string newTitle = "", string newContent = "");

    /** Deletes a `News` with specified `id`. */
    void deleteNews(int id);



    /** Saves `News` inside the database. */
    void saveNews() const;

    /** Stores `News` inside database and deletes DMA inside `News` class. */
    ~NewsManager();

    /** Searches title of `News`, then return a constant vector. */
    const vector<News> searchTitle(string title) const;

    /** Searches news published between `dt_start` and `dt_end`. */
    const vector<News> searchDate(Datetime dt_start, Datetime dt_end) const;
};

#endif