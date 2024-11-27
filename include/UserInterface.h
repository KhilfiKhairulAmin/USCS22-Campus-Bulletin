#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include "Sound.h"
#include "Colors.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdlib.h>
#include <csignal>                  // For handling special input
#include <conio.h>                  // For handling custom input (Windows only; Compiler G++ v11.0.0+)
#include <cctype>
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

void slowPrint(string msg, int intervalMs = DEFAULT_INTERVAL, string color = Color_Off)
{
  thread soundThread(clickSound, intervalMs*(msg.size()+1));
  center(msg.size());
  cout << color;
  for (int i = 0; i < msg.size(); i++)
  {
    cout << msg[i];
    this_thread::sleep_for(chrono::milliseconds(intervalMs));
  }
  soundThread.join();
  cout << Color_Off;
}

void slowPrint(const char* msg, int intervalMs = DEFAULT_INTERVAL, string color = Color_Off)
{
  string m = msg;
  slowPrint(m, intervalMs, color);
}

void print(string msg, string color = Color_Off)
{
  center(msg.size());
  cout << color;
  cout << msg;
  cout << Color_Off;
}

void print(const char* msg, string color = Color_Off)
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
  int interval = (x-5) / (options.size()+1);
  cout << "+" << string(length, '-') << "+\n";
  cout << "|" << space << "|\n";
  cout << "|    Welcome to" << string(length-14, ' ') << "|\n";
  cout << BYellow << "|    INTEC HUB" << string(length-13, ' ') << Color_Off << "|\n";
  cout << "|" << space << "|\n";
  cout << "+" << string(length, '-') << "+\n";
  for (int j = 0; j < interval - 1; j++)
  {
    cout << "|" << space << "|\n";
  }

  cout << "|   ";
  if (0 == selected)
    setColor(1, 33);
  cout << " " << options[0] << " ";
  resetColor();
  cout << string(length-5-options[0].size(), ' ') << "|\n";

  for (int i = 1; i < options.size(); i++)
  {
    for (int j = 0; j < interval - 1; j++)
    {
      cout << "|" << space << "|\n";
      ROW++;
    }
    cout << "|   ";
    if (i == selected)
      setColor(1, 33);
    cout << " " << options[i] << " ";
    resetColor();
    cout << string(length-5-options[i].size(), ' ')<< "|\n";
  }
  
  for (int j = 0; j < interval - 1; j++)
  {
    cout << "|" << space << "|\n";
  }
  cout << "+" << string(length, '-') << "+\n";
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

// TODO: Input error handling
// Input auto centralized + limit
// Add sounds to all button press
// Add more menu in main menu

string inputText(int maxSize, int minSize = 1, string def = "")
{
  cout << Cyan;
  string s = def;
  int key = 0;
  while (true)
  {
    center(s.length());
    ROW--;
    cout << flush << s;
    key = _getch();
    center(s.length());
    ROW--;
    cout << string(s.length(), ' ');
    
    if (key == 27) {} // ESC key

    // Handle the Enter key
    if (s.length() > minSize && key == 13)
    {
      break;
    }
    else if (key == 8)
    { // Handle Backspace key
      if (!s.empty()) {
          s.pop_back();
      }
    }
    else if (s.length() < maxSize && isalnum(char(key)))
    {
      // Handle other keys (add to input)
      s += char(key);
    }
  }
  center(s.length());
  ROW--;
  cout << s;
  ROW += 2;
  cout << Color_Off;
  return s;
}

string inputEmail(int maxSize, int minSize = 1, string def = "")
{
  cout << Cyan;
  string s = def;
  int key = 0;
  while (true)
  {
    center(s.length());
    ROW--;
    cout << flush << s;
    key = _getch();
    center(s.length());
    ROW--;
    cout << string(s.length(), ' ');
    
    if (key == 27) {} // ESC key

    // Handle the Enter key
    if (s.length() > minSize && s.find('@') != string::npos && key == 13)
    {
      break;
    }
    else if (key == 8)
    { // Handle Backspace key
      if (!s.empty()) {
          s.pop_back();
      }
    }
    else if (s.length() < maxSize && (isalnum(char(key)) || char(key) == '@' || char(key) == '.' || char(key) == '_' || char(key) == '-'))
    {
      // Handle other keys (add to input)
      s += char(key);
    }
  }
  center(s.length());
  ROW--;
  cout << s;
  ROW += 2;
  cout << Color_Off;
  return s;
}

string inputPhone(int maxSize, int minSize = 1, string def = "")
{
  cout << Cyan;
  string s = def;
  int key = 0;
  while (true)
  {
    center(s.length());
    ROW--;
    cout << flush << s;
    key = _getch();
    center(s.length());
    ROW--;
    cout << string(s.length(), ' ');
    
    if (key == 27) {} // ESC key

    // Handle the Enter key
    if (s.length() > minSize && key == 13)
    {
      break;
    }
    else if (key == 8)
    { // Handle Backspace key
      if (!s.empty()) {
          s.pop_back();
      }
    }
    else if (s.length() < maxSize && isdigit(char(key)))
    {
      // Handle other keys (add to input)
      s += char(key);
    }
  }
  center(s.length());
  ROW--;
  cout << s;
  ROW += 2;
  cout << Color_Off;
  return s;
}

string inputPassword(int maxSize, int minSize = 1, string def = "")
{
  string s = def;
  int key = 0;
  while (true)
  {
    center(s.length());
    ROW--;
    cout << flush << string(s.length(), '*');
    key = _getch();
    center(s.length());
    ROW--;
    cout << string(s.length(), ' ');
    
    if (key == 27) {} // ESC key

    // Handle the Enter key
    if (s.length() > minSize && key == 13)
    {
      break;
    }
    else if (key == 8)
    { // Handle Backspace key
      if (!s.empty()) {
          s.pop_back();
      }
    }
    else if (s.length() < maxSize && isalnum(char(key)))
    {
      // Handle other keys (add to input)
      s += char(key);
    }
  }
  center(s.length());
  ROW--;
  cout << s;
  ROW += 2;
  return s;
}

#endif