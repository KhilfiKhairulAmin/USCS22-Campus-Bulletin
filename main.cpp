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
  
  mainMenu();

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

void createNews() {
    cout << "Create News functionality is not yet implemented.\n";
}

void editNews() {
    cout << "Edit News functionality is not yet implemented.\n";
}

void deleteNews() {
    cout << "Delete News functionality is not yet implemented.\n";
}

void editProfile() {
    cout << "Edit Profile functionality is not yet implemented.\n";
}


void slowPrint(const string& text, int delay = 50) {
    // Simulate slow printing of text
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void mainMenu() {
    while (true) { // Loop until the user chooses to exit
        // Clear the console for a clean menu interface
        system("clear");

        // Display the title with a dramatic animation
        slowPrint("========================================\n");
        slowPrint("        WELCOME TO THE NEWS HUB\n");
        slowPrint("========================================\n");

        // Provide an overview of options
        cout << "\nMAIN MENU OPTIONS:\n";
        cout << "1. Create News\n";
        cout << "2. Edit News\n";
        cout << "3. Delete News\n";
        cout << "4. Edit Profile\n";
        cout << "5. View Calendar\n";
        cout << "6. Sign Out\n";

        // Simulate sound effect for user input readiness
        cout << "\n*Ding* Please select an option: ";

        // Get the user's choice
        int choice;
        cin >> choice;

        // Use a switch-case for menu navigation
        switch (choice) {
        case 1:
            cout << "\nRedirecting to Create News...\n";
            slowPrint("Loading...\n");
            createNews(); // Calls the Create News function
            break;
        case 2:
            cout << "\nRedirecting to Edit News...\n";
            slowPrint("Loading...\n");
            editNews(); // Calls the Edit News function
            break;
        case 3:
            cout << "\nRedirecting to Delete News...\n";
            slowPrint("Loading...\n");
            deleteNews(); // Calls the Delete News function
            break;
        case 4:
            cout << "\nRedirecting to Edit Profile...\n";
            slowPrint("Loading...\n");
            editProfile(); // Calls the Edit Profile function
            break;
        case 5:
            cout << "\nOpening Calendar...\n";
            slowPrint("Loading...\n");
            calendar(); // Calls the Calendar function
            break;
        case 6:
            cout << "\nSigning Out...\n";
            slowPrint("Goodbye!\n");
            MENU = ENTRY; // Reset to the entry menu
            return;       // Exit the menu loop
        default:
            cout << "\nInvalid choice! Please try again.\n";
            slowPrint("Returning to menu...\n");
            break;
        }
    }
}
