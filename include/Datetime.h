#ifndef DATETIME_H
#define DATETIME_H
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Date
{
  int year;
  int month;
  int day;
  string dayName;

  static Date getCurrentDate()
  {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int year = 1900 + localTime->tm_year;
    int month = 1 + localTime->tm_mon;
    int day = localTime->tm_mday;
    string dayName = getDayName(year, month, day);

    return Date{ year, month, day, dayName };
  }

  static string getDayName(int y, int m, int d)
  {
    tm timeStruct = {};
    timeStruct.tm_year = y - 1900;
    timeStruct.tm_mon = m - 1;
    timeStruct.tm_mday = d;

    mktime(&timeStruct);

    string daysOfWeek[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    return daysOfWeek[timeStruct.tm_wday];
  }
};

struct Time
{
  int hour;
  int minute;
  int second;

  static Time getCurrentTime()
  {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;
    
    return Time{ hour, minute, second };
  }
};

struct Datetime: Date, Time
{
  static Datetime getCurrentDatetime()
  {
    Date d = getCurrentDate();
    Time t = getCurrentTime();
    
    return Datetime{ d.year, d.month, d.day, d.dayName, t.hour, t.minute, t.second }; 
  }

  static Datetime sToDatetime(string datetimeString)
  {
    stringstream ss(datetimeString);
    string d;
    int ds[6];
    int i = 0;
    while(getline(ss, d, '/'))
    {
      ds[i++] = stoi(d);
    }
    return Datetime{
      ds[2],
      ds[1],
      ds[0],
      getDayName(ds[0], ds[1], ds[2]),
      ds[3],
      ds[4],
      ds[5]
    };
  }

  static string datetimeToS(Datetime dt)
  {
    return to_string(dt.day) + "/" + to_string(dt.month) + "/" + to_string(dt.year) + "/" + to_string(dt.hour) + "/" + to_string(dt.minute) + "/" + to_string(dt.second);
  }

  bool operator>=(Date dt)
  {
    return year >= dt.year && month >= dt.month && day >= dt.day;
  }

  bool operator<=(Date dt)
  {
    return year <= dt.year && month <= dt.month && day <= dt.day;
  }
};

#endif
