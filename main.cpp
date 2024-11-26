/*------------------------------------------------[ CREDITS ]-----------------------------------------------------------------*/

// TODO: Siapkan different parts of UI and flow
// TODO: Dominate all the other groups by introducing some absurd feature (sound effects, image, data analytics)
// TODO: configuration, calendar view, link opener, text-to-speech, system information

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


const vector<Publisher>* publishers;  // Stores all publishers data
const vector<News>* news;             // Stores all news data

int PID = 0;   // Publisher ID of current user
int MENU = 0;  // Current Menu number the user is interacting with

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
  Database db = Database();
  publishers = db.getAllPublishers();
  loadSounds();
  mainMenu();
}


/*----------------------------------------[ FUNCTION DEFINITIONS ]-------------------------------------------------------------*/


void entryMenu()
{
  vector<string> opts = { "Sign Up", "Sign In" };
  int selected = 0;
  bool flag = true;
  int key = 0;
  while (true) {
    while (flag)
    {
      if (key == 224 || key == 0)
      {
        clear();
        sidebar(opts, selected);
        setCursor(10, 1);
        if (selected == 0)
        {
          slowPrint("SIGN UP");
        }
        else
        {
          slowPrint("SIGN IN");
        }
      }

      int key = _getch(); // Get a single character input

      // Detect arrow keys: in Windows, arrow keys start with a 224 or 0 followed by the specific keycode
      if (key == 224 || key == 0)
      {
        key = _getch();  // Get the actual key code after 224/0

        if (key == 75 || key == 77)
        {
          selected = (selected+1) % 2;

          if (selected == 0)
            MENU = SIGN_UP;
          else  
            MENU = SIGN_IN;
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
}

void mainMenu()
{
  clear();
  entryMenu();
  clear();
}
