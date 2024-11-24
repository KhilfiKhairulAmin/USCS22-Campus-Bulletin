#ifndef DATABASE_H
#define DATABASE_H
#include "News.h"
#include "Publisher.h"
#include <vector>
#include <unordered_map>
#include <array>
using namespace std;

class Database: public NewsManager, public PublisherManager
{
  private:
    static string version;
    
  public:
    /** Loads `Publishers` and `News` from database. */
    Database();

    /** Get all `News` published by a `Publisher` with specified `id`. */
    vector<int> getNewsByPublisher(int publisherId) const;

    /** Get total likes from the `Publisher` with specified `id`. */
    int getTotalLikes(int publisherId) const;

    /** Get total dislikes from the `Publisher` with specified `id`. */
    int getTotalDislikes(int publisherId) const;

    /** Get total `News` published by `Publisher` with specified `id`.  */
    int getTotalNewsPublished(int publisherId) const;

    /** Get total `Publishers` registered inside the database. */
    int getTotalPublishers() const;

    /** Get total `News` created inside the database. */
    int getTotalNews() const;

    /** Get popularity rank of `Publishers`. */
    vector<array<int, 2>> getPopularityRankings() const;

    /** Writes `Publishers` and `News` into database and deletes DMA inside the program. */
    ~Database();
};


#endif