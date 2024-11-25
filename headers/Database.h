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
    Database::Database(): NewsManager(), PublisherManager() {};

    /** Get all `News` published by a `Publisher` with specified `id`. */
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

    /** Get total likes from the `Publisher` with specified `id`. */
    int Database::getTotalLikes(int publisherId) const
    {
      int total = 0;
      for (auto it = news->begin(); it < news->end();it++)
        if (it->publisherId == publisherId)
          total += it->numOfLikes;
      return total;
    }

    /** Get total dislikes from the `Publisher` with specified `id`. */
    int Database::getTotalDislikes(int publisherId) const
    {
      int total = 0;
      for (auto it = news->begin(); it < news->end();it++)
        if (it->publisherId == publisherId)
          total += it->numOfDislikes;
      return total;
    }

    /** Get total `News` published by `Publisher` with specified `id`.  */
    int Database::getTotalNewsPublished(int publisherId) const
    {
      int total = 0;
      for (auto it = news->begin(); it < news->end();it++)
        if (it->publisherId == publisherId)
          total++;
      return total;
    }

    /** Get total `Publishers` registered inside the database. */
    int Database::getTotalPublishers() const
    {
      return totalPublishers;
    }

    /** Get total `News` created inside the database. */
    int Database::getTotalNews() const
    {
      return totalPublishers;
    }

    /** Get popularity rank of `Publishers`. */
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

    /** Writes `Publishers` and `News` into database and deletes DMA inside the program. */
    Database::~Database() {};
};


#endif