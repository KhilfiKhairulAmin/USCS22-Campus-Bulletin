/*------------------------------------------------[ CREDITS ]-----------------------------------------------------------------*/

// TODO Siapkan different parts of UI and flow
// TODO Dominate all the other groups by introducing some absurd feature (sound effects, image, data analytics)
// TODO configuration, calendar view, link opener, text-to-speech, system information
// TODO 

/*-------------------------------------------[ HEADERS & INCLUDES ]------------------------------------------------------------*/


#include "include/Database.h"       // For connecting to the database of the application
#include "include/UserInterface.h"  // For reusing same UI components multiple times
#include <iostream>                 // For handling input and output
#include <iomanip>                  // For formatting output
#include <csignal>                  // For handling special input
#include <conio.h>                  // For handling custom input (Windows only; Compiler G++ v11.0.0+)

#define ENTRY 0         // MENU NUMBER 0
#define SIGN_UP 1       // MENU NUMBER 1
#define SIGN_IN 2       // MENU NUMBER 2
#define MAIN_MENU 3     // MENU NUMBER 3
#define CREATE_NEWS 4   // MENU NUMBER 4
#define EDIT_NEWS 5     // MENU NUMBER 5
#define DELETE_NEWS 6   // MENU NUMBER 6
#define EDIT_PROFILE 7  // MENU NUMBER 7
#define CALENDAR 8      // MENU NUMBER 8

using namespace std;


/*--------------------------------[ GLOBAL VARIABLES & FUNCTION PROTOTYPES ]---------------------------------------------------*/


Database* db;
const vector<Publisher>* publishers;  // Stores all publishers data
const vector<News>* news;             // Stores all news data

int PID = 0;   // Publisher ID of current user
int MENU = ENTRY;  // Current Menu number the user is interacting with

void entryMenu(),     // Function prototypes for all menus
     signUp(),
     signIn(),
     mainMenu(),
     createNews(),
     editNews(),
     deleteNews(),
     editProfile(),
     calendar();


/*---------------------------------------------[ MAIN PROGRAM ]----------------------------------------------------------------*/


int main()
{
  db = new Database();
  publishers = db->getAllPublishers();
  news = db->getAllNews();
  loadSounds();

  clear();
  while (true)
  {
    if (MENU == ENTRY)
      entryMenu();
    else if (MENU == SIGN_UP)
      signUp();
    else if (MENU == SIGN_IN)
      signIn();
    else if (MENU == MAIN_MENU)
      mainMenu();
    else
      break;
  }
}


/*----------------------------------------[ FUNCTION DEFINITIONS ]-------------------------------------------------------------*/


void entryMenu()
{
  vector<string> opts = { "Sign In", "Sign Up" };
  int selected = 0;
  MENU = SIGN_IN;
  bool flag = true;
  int key = 72;
  while (flag)
  {
    if (key == 72 || key == 80)
    {
      // clear();
      thread th(clickButtonSound);
      sidebar(opts, selected);
      th.join();
      setPercentage(20);
      if (selected == 0)
      {
        slowPrint("SIGN IN");
        cout << endl;
        slowPrint("Sign in to your account");
      }
      else
      {
        slowPrint("SIGN UP");
        slowPrint("Register as a publisher");
      }
      print("\n");
      print("...");
    }

    int key = _getch(); // Get a single character input

    // Detect arrow keys: in Windows, arrow keys start with a 224 or 0 followed by the specific keycode
    if (key == 224 || key == 0)
    {
      key = _getch();  // Get the actual key code after 224/0

      if (key == 72 || key == 80)
      {
        selected = (selected+1) % 2;

        if (selected == 0)
          MENU = SIGN_IN;
        else
          MENU = SIGN_UP;
      }
    }
    else if (key == 13)
    {
      flag = false;
    }
  }
}

void signUp()
{
  print("");
  print("");
  slowPrint("Enter your information:");

  string email, pass, rPass, name, about, phone;

  print("Email:");
  email = inputEmail(30, 10);
  print("Password:");
  pass = inputPassword(20);  
  print("Organization Name:");
  name = inputText(30, 3);
  print("About:");
  about = inputText(250, 1);
  print("Phone:");
  phone = inputPhone(11, 9);

  PID = db->createPublisher(email, pass, name, about, phone);
  MENU = MAIN_MENU;
}

void signIn()
{
  print("");
  print("");
  slowPrint("Enter your information:");

  string email, password;
  int index = -1;
  print("");
  while (true)
  {
    print("Email:");
    email = inputEmail(30, 10);
    try
    {
      index = db->searchEmail(email);
      break;
    }
    catch(const char* c)
    {
      ROW -= 3;
      center(email.length());
      print(string(email.length(), ' '));
      ROW -= 2;
      center(7);
      print(string(7, ' '));
      ROW -= 3;
      print("Email doesn't exist", Red);
      continue;
    }    
  }

  print("");
  while (true)
  {
    print("Password");
    password = inputPassword(20);
    if (password != publishers->at(index).password)
    {
      ROW -= 3;
      center(password.length());
      print(string(password.length(), ' '));
      ROW -= 2;
      center(7);
      print(string(7, ' '));
      ROW -= 3;
      print("Password is wrong", Red);
      continue;
    }
    break;
  }
  PID = index;
  MENU = MAIN_MENU;
}

void mainMenu()
{
  clear();
  createNews();
  MENU = -1;
}

void createNews()
{
  string title, content;
  slowPrint("Title:");
  title = inputText(50, 3, "", Yellow);

  string p;

  slowPrint("Body:");
  slowPrint("Enter '$' to finish writing");
  print("");
  string t = "";
  while (true)
  {
    string t = inputText(50, 0, "", Yellow);
    ROW--;
    if (t == "$")
      break;
    
    p += t + "\n";
  }
  db->createNews(PID, title, p);
}

void editNews()
{
  int id, index;

  while (true)
  {
    print("News ID:");
    id = inputNumber(5);
    try
    {
      index = db->searchNewsId(id);
      break;
    }
    catch(const char* c)
    {
      ROW -= 3;
      center((to_string(id)).length());
      print(string((to_string(id)).length(), ' '));
      ROW -= 2;
      center(7);
      print(string(7, ' '));
      ROW -= 3;
      print("News with " + to_string(id) + " not found", Red);
      continue;
    }    
  }

  string title, content;
  News n = news->at(index);
  slowPrint("Title:");
  title = inputText(50, 3, n.title, Yellow);

  string p;

  slowPrint("Body:");
  slowPrint("Enter '$' to finish writing");
  print("");
  string t = "";
  while (true)
  {
    string t = inputText(50, 0, Yellow);
    ROW--;
    if (t == "$")
      break;
    
    p += t + "\n";
  }
  db->editNews(PID, title, p);
}
