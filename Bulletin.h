#ifndef BULLETIN_H
#define BULLETIH_H
#include "News.h"
#include "Publisher.h"
using namespace std;

class Bulletin: public News, public Publisher
{
  private:

  public:
    /** Loads `Publishers` and `News` from database. */
    Bulletin();

    /** Get all `News` published by a `Publisher` with specified `id`. */
    vector<News> getNewsByPublisher(int id) const;

    /** Get total likes from the `Publisher` with specified `id`. */
    int getTotalLikes(int id) const;

    /** Get total dislikes from the `Publisher` with specified `id`. */
    int getTotalDislikes(int id) const;

    /** Get total `News` published by `Publisher` with specified `id`.  */
    int getTotalNewsPublished(int id) const;

    /** Get total `Publishers` registered inside the database. */
    int getTotalPublishers() const;

    /** Get total `News` created inside the database. */
    int getTotalNews() const;

    /** Get popularity rank of `Publishers`. */
    vector<Publisher> getPopularityRankings() const;

    /** Writes `Publishers` and `News` into database and deletes DMA inside the program. */
    ~Bulletin();
};


#endif