#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "Sound.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdlib.h>
#define DEFAULT_INTERVAL 40
using namespace std;
int ROW = 1;

void clear()
{
  system("clear");
  ROW = 1;
}

void setColor(int attr = 0, int fore = 37, int back = 40)
{
  cout << "\033[" << attr << ";" << fore << ";" << back << "m";
}

void resetColor()
{
  cout << "\033[0m";
}

void setCursor(int r, int c)
{
  ROW = r;
  cout << "\033[" << ROW << ";" << c << "H";
}

void getMaxXY(int &x, int &y)
{
  if (FILE *fp = popen("stty size", "r")) {
      fscanf(fp, "%d %d", &x, &y);
      pclose(fp);
  }
}

void center(int offset)
{
  int rows, cols;
  getMaxXY(rows, cols);

  // Calculate center position
  int centerCol = (cols - offset) / 2;

  // Move the cursor to the center
  cout << "\033[" << ROW++ << ";" << centerCol << "H";
}

void slowPrint(string msg, int intervalMs = DEFAULT_INTERVAL, string color = "0")
{
  thread soundThread(clickSound, intervalMs*(msg.size()+1));
  center(msg.size());
  cout << "\033[" << color << "m";
  for (int i = 0; i < msg.size(); i++)
  {
    cout << msg[i];
    this_thread::sleep_for(chrono::milliseconds(intervalMs));
  }
  soundThread.join();
  cout << "\033[0m";
}

void slowPrint(const char* msg, int intervalMs = DEFAULT_INTERVAL, string color = "0")
{
  string m = msg;
  slowPrint(m, intervalMs, color);
}

void print(string msg, string color = "0")
{
  center(msg.size());
  cout << "\033[" << color << "m";
  cout << msg << endl;
  cout << "\033[0m";
}

void print(const char* msg, string color = "0")
{
  string m = msg;
  print(m, color);
}

void setPercentage(int r = 0, int c = 0)
{
  int x, y;
  getMaxXY(x, y);
  setCursor(x * r/100+1, y*c/100+1);
}

void sidebar(vector<string> options, int selected)
{
  int x, y;
  getMaxXY(x, y);
  x--;
  int length = y*20/100;
  string space = string(length, ' ');
  int interval = x / options.size() - options.size();
  cout << "\n";
  for (int j = 0; j < interval / 2; j++)
  {
    cout << "|" << space << "|\n";
  }

  cout << "|    ";
  if (0 == selected)
    setColor(1, 33);
  cout << options[0] << string(length-4-options[0].size(), ' ');
  resetColor();
  cout << "|\n";

  for (int i = 1; i < options.size(); i++)
  {
    for (int j = 0; j < interval; j++)
    {
      cout << "|" << space << "|\n";
      ROW++;
    }
    cout << "|    ";
    if (i == selected)
      setColor(1, 33);
    cout << options[i] << string(length-4-options[i].size(), ' ');
    resetColor();
    cout << "|\n";
  }
  
  for (int j = 0; j < interval / 2; j++)
  {
    cout << "|" << space << "|\n";
  }
}

void rowSet(int set)
{
  ROW = set;
}

int getRow()
{
  int x, y;
  return ROW;
}

#endif