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
    vector<News> news;
    /** Keeps total number of news */
    static int totalPublishers;
    /** Tracks next unique value for `News.id` */
    static int nextId;
  public:
    /** Returns a constant vector containing all `News`. */
    const vector<News>& getNews() const;
    /** Returns a constant vector containing only published `News` or only non-published `News`. */
    const vector<News>& getNews(bool onlyPublished) const;
    /** Returns one `News` based on given `id`. */
    const News& getOneNews(int id) const;
    /** Creates a new `News`, then returns its constant pointer.  */
    const News& createNews(int publisherId, string title, string content) const;
    /** Modifies data inside a `Publisher`, then return its constant pointer. */
    const News& editNews(int id, string newTitle = "", string newContent = "") const;
    /** Sets a `News` to be published (allow it to be viewed by users). */
    const News& setPublished(int id) const;
    /** Deletes a `News`. */
    void deleteNews(int id) const;
    /** Lazily searches title of `News`, then return a constant vector. */
    const vector<News>& searchTitle(string title) const;
    /** Searches news published between `dt_start` and `dt_end`. */
    const vector<News>& searchDate(Datetime dt_start, Datetime dt_end) const;
};

#endif