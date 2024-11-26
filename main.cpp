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


Database db;
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
  db = Database();
  publishers = db.getAllPublishers();
  news = db.getAllNews();
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
    else if (MENU == )
  }
}


/*----------------------------------------[ FUNCTION DEFINITIONS ]-------------------------------------------------------------*/


void entryMenu()
{
  vector<string> opts = { "Log In", "Sign Up" };
  int selected = 0;
  bool flag = true;
  int key = 72;
  while (flag)
  {
    if (key == 72 || key == 80)
    {
      clear();
      sidebar(opts, selected);
      setPercentage(10);
      if (selected == 0)
      {
        print("LOG IN", "1;33;40");
        slowPrint("Sign in into your account");
      }
      else
      {
        print("SIGN UP", "1;33;40");
        slowPrint("Register as a Publisher for INTEC Insider");
      }
      print("");
      slowPrint("[ENTER]");
    }

    int key = _getch(); // Get a single character input

    // Detect arrow keys: in Windows, arrow keys start with a 224 or 0 followed by the specific keycode
    if (key == 224)
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
    // if (MENU == SIGN_UP)
    //   signUp();
    // else
    //   signIn();
}

void signUp()
{
  print("");
  print("");
  slowPrint("Enter your details as requested:");

  string email, pass, rPass, name, about, phone;

  print("Email:");
  center(15);
  getline(cin, email);
  print("Password:");
  center(15);
  getline(cin, pass);
  print("Repeat Password:");
  center(15);
  getline(cin, rPass);
  print("About:");
  center(15);
  getline(cin, about);
  print("Phone:");
  center(15);
  getline(cin, phone);

  db.createPublisher(email, pass, name, about, phone);

  MENU = MAIN_MENU;
}

void mainMenu()
{
  clear();
  print("MAIN MENU");
}
