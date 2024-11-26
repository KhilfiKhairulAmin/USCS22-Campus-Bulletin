/*------------------------------------------------[ CREDITS ]-----------------------------------------------------------------*/

// TODO: Siapkan different parts of UI and flow
// TODO: Dominate all the other groups by introducing some absurd feature (sound effects, image, data analytics)
// TODO: Add text sound effect, configuration, calendar view, link opener, text-to-speech, system information

/*-------------------------------------------[ HEADERS & INCLUDES ]------------------------------------------------------------*/


#include "include/Database.h"       // For connecting to the database of the application
#include "include/UserInterface.h"  // For reusing same UI components multiple times
#include "include/Calendar.h"       // Include calendar function to the main file
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
     editProfile();


/*---------------------------------------------[ MAIN PROGRAM ]----------------------------------------------------------------*/


int main()
{
  Database db = Database();
  publishers = db.getAllPublishers();
  
  calendar();

}


/*----------------------------------------[ FUNCTION DEFINITIONS ]-------------------------------------------------------------*/


void entryMenu()
{
  int s = 0;
  print("SIGN IN / UP");
  slowPrint("DNWUFIUBWIIBIUFBWIUBIUBFWUFWUBFIWBIWBFI");

  cin >> s;

  if (s == 0)
    MENU = 1;
  else
    MENU = 2;
}

void mainMenu()
{
  clear();
  entryMenu();
}
