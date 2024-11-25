#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#define DEFAULT_INTERVAL 40
using namespace std;
int ROW = 1;

void clear()
{
  system("clear");
  ROW = 1;
}

void center(int offset)
{
  int rows, cols;
  if (FILE *fp = popen("stty size", "r")) {
      fscanf(fp, "%d %d", &rows, &cols);
      pclose(fp);
  }

  // Calculate center position
  int centerCol = (cols - offset) / 2;

  // Move the cursor to the center
  cout << "\033[" << ROW++ << ";" << centerCol << "H";
}

void slowPrint(string msg, int intervalMs = DEFAULT_INTERVAL)
{
  center(msg.size());
  for (int i = 0; i < msg.size(); i++)
  {
    cout << msg[i];
    this_thread::sleep_for(chrono::milliseconds(intervalMs));
  }
}

void slowPrint(const char* msg, int intervalMs = DEFAULT_INTERVAL)
{
  string m = msg;
  slowPrint(m, intervalMs);
}

void print(string msg)
{
  center(msg.size());
  cout << msg << endl;
}

void print(const char* msg)
{
  string m = msg;
  print(m);
}

#endif