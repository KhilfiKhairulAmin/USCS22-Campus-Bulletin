/*------------------------------------------------[ CREDITS ]-----------------------------------------------------------------*/

// TODO Siapkan different parts of UI and flow
// TODO Dominate all the other groups by introducing some absurd feature (sound effects, image, data analytics)
// TODO configuration, calendar view, link opener, text-to-speech, system information
// TODO 

/*-------------------------------------------[ HEADERS & INCLUDES ]------------------------------------------------------------*/


#include "include/Database.h"       // For connecting to the database of the application
#include "include/UserInterface.h"  // For reusing same UI components multiple times
#include "include/Calendar.h"
#include "include/Colors.h"
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
vector<Publisher>* publishers;  // Stores all publishers data
vector<News>* news;             // Stores all news data

Publisher this_pub;
int PID = 0;   // Publisher ID of current user
int MENU = MAIN_MENU;  // Current Menu number the user is interacting with

void entryMenu(),     // Function prototypes for all menus
     signUp(),
     signIn(),
     mainMenu(),
     createNews(),
     editNews(),
     deleteNews(),
     editProfile(),
     readNews(),
     calendar(),
     readSingleNews();


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
  }
}


/*----------------------------------------[ FUNCTION DEFINITIONS ]-------------------------------------------------------------*/


void entryMenu()
{
  vector<string> opts = { "Sign In", "Sign Up", "Guest" };
  int selected = 0;
  MENU = SIGN_IN;
  bool flag = true;
  int key = 72;
  while (flag)
  {
    if (key == 72 || key == 80)
    {
      clear();
      thread th(clickButtonSound);
      sidebar(opts, selected);
      th.join();
      setPercentage(20);
      if (selected == 0)
      {
        slowPrint("SIGN IN", 40, UWhite);
        cout << endl;
        slowPrint("Sign in to your account", 40);
      }
      else
      {
        slowPrint("SIGN UP", 40, UWhite);
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

void mainMenu() {
  this_pub = publishers->at(PID);
  while (true) { // Loop until the user chooses to exit
    // Clear the console for a clean menu interface
    clear();

    // Display the title with a dramatic animation
    print("");
    fill('=', Purple);
    print("");
    print("WELCOME TO THE NEWS HUB", Yellow);
    print("");
    fill('=', Purple);
    print("");
    // Provide an overview of options
    // print("*************************", Cyan);
    slowPrint("MAIN MENU OPTIONS:", 40, BGreen);
    // print("*************************", Cyan);
    print("");
    print("1. Create News");
    print("2. Edit News");
    print("3. Delete News");
    print("4. Edit Profile");
    print("5. View Calendar");
    print("6. Read News");
    print("7. Sign Out");

    // TODO Create news, edit news, delete news, edit profile, view calendar, 

    // Simulate sound effect for user input readiness
    print("\a");
    slowPrint("Please select an option: ", 40, BIWhite);

    // Get the user's choice
    int choice = inputNumber(1, 1, "", On_IYellow);

    clear();

    // Use a switch-case for menu navigation
    string line;
    switch (choice) {
      case 1:
          cout << "\nRedirecting to Create News...\n";
          slowPrint("Loading...\n");
          createNews(); // Calls the Create News function
          break;
      case 2:
          // cout << "\nRedirecting to Edit News...\n";
          // slowPrint("Loading...\n");
          editNews(); // Calls the Edit News function
          break;
      case 3:
          // cout << "\nRedirecting to Delete News...\n";
          // slowPrint("Loading...\n");
          deleteNews(); // Calls the Delete News function
          break;
      case 4:
          // cout << "\nRedirecting to Edit Profile...\n";
          // slowPrint("Loading...\n");
          getline(cin, line);
          editProfile(); // Calls the Edit Profile function
          break;
      case 5:
          // cout << "\nOpening Calendar...\n";
          // slowPrint("Loading...\n");
          calendar(); // Calls the Calendar function
          getline(cin, line);
          break;
      case 6:
          // cout << "\nSigning Out...\n";
          // slowPrint("Goodbye!\n");
          readNews();
          getline(cin, line);
          break;
          // MENU = ENTRY; // Reset to the entry menu
          // return;       // Exit the menu loop
      case 7:
          cout << "\nSigning Out...\n";
          slowPrint("Goodbye!\n");
          MENU = ENTRY; // Reset to the entry menu
          return;       // Exit the menu loop
      case 8:
          readSingleNews();
      default:
          cout << "\nInvalid choice! Please try again.\n";
          slowPrint("Returning to menu...\n");
          break;
    }
  }
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

void readSingleNews()
{
  slowPrint("READ NEWS");
  slowPrint("Enter ID:");
  int id = inputNumber(5, 1);
  int index = db->searchNewsId(id);
  cout << news->at(index).content << endl;
  string line;
  getline(cin, line);
}

void deleteNews()
{
  int id, index;
  print("");
  while (true)
  {
    print("News ID:");
    id = inputNumber(5);
    try
    {
      index = db->searchNewsId(id);
      cout << news->at(index).publisherId << PID;

      if (news->at(index).publisherId != news->at(PID).publisherId)
        throw "News doesn't belong to you.";
      break;
    }
    catch(const char* c)
    {
      ROW -= 3;
      center(to_string(id).length());
      print(string(to_string(id).length(), ' '));
      ROW -= 2;
      center(9);
      print(string(7, ' '));
      ROW -= 3;
      print(c, Red);
      continue;
    }    
  }
  db->deleteNews(id);
}

void readNews()
{
  vector<string> opts = { "Recent", "Search", "Filter" };
  int selected = 0;
  bool flag = true;
  int key = 72;
  while (flag)
    {
    if (key == 72 || key == 80)
    {
      clear();
      thread th(clickButtonSound);
      sidebar2(opts, selected);
      th.join();
    }

    int key = _getch(); // Get a single character input

    // Detect arrow keys: in Windows, arrow keys start with a 224 or 0 followed by the specific keycode
    if (key == 224 || key == 0)
    {
      key = _getch();  // Get the actual key code after 224/0

      if (key == 72)
        selected = (selected + 2) % opts.size();
      else if (key == 80)
        selected = (selected+1) % opts.size();
    }
    else if (key == 13)
    {
      flag = false;
    }
  }

  int x, y;
  getMaxXY(x, y);
  int length = y*20/100;
  string space = string(length, ' ');

  vector<News> ns;
  if (selected == 0)
    ns = *db->getAllNews();
  else if (selected == 1)
  {
    string search;
    cout << space + "Search: " << On_IYellow;
    getline(cin, search);
    cout << Color_Off;
    ns = db->searchTitle(search);
  }
  else
  {
    cout << space + "Start Date (D/M/Y): " << On_IYellow;
    string inD;
    getline(cin, inD);
    stringstream ss(inD);

    int d, m, y;
    getline(ss, inD, '/');
    d = atoi(inD.c_str());
    getline(ss, inD, '/');
    m = atoi(inD.c_str());
    getline(ss, inD, '/');
    y = atoi(inD.c_str());

    cout << Color_Off;

    cout << space + "End Date (D/M/Y): " << On_IYellow;
    getline(cin, inD);
    stringstream ss2(inD);

    int d2, m2, y2;
    getline(ss2, inD, '/');
    d2 = atoi(inD.c_str());
    getline(ss2, inD, '/');
    m2 = atoi(inD.c_str());
    getline(ss2, inD, '/');
    y2 = atoi(inD.c_str());

    cout << Color_Off;

    ns = db->searchDate(Datetime{ y, m, d }, Datetime{ y2, m2, d2 });
  }

  clear();
  for (auto it = ns.begin(); it != ns.end(); it++)
  {
    cout << space << Purple<<"+---------------------------------------------------------------------+" << endl;
    cout << space << Blue<<"| ID: " << it->id << endl;
    cout << space << "| Title: " << it->title << endl;
    cout << space << White<<"+---------------------------------------------------------------------+" << endl;
    cout << space << Blue<<"| Published By: " << publishers->at(db->searchPublisherId(it->publisherId)).name << endl;
    cout << space << Blue<<"| Published At: " << Datetime::datetimeToS(it->createdAt) << endl;
    // Uncomment if you want to display the content
    // cout << "| Content: " << it->content << endl;
    cout << space << Purple<<"+---------------------------------------------------------------------+" << endl;
    cout << space << endl;
  }

  cout << endl << space << On_ICyan << "Press space to continue..." << Color_Off;
  string i;
  getline(cin, i);

  clear();

  int id, index;
  print("");
  while (true)
  {
    slowPrint("Enter News ID to read (enter -1 to exit):", 40, UWhite);
    id = inputNumber(5, 0);
    try
    {
      index = db->searchNewsId(id);
      break;
    }
    catch(const char* c)
    {
      ROW -= 3;
      center(to_string(id).length());
      print(string(to_string(id).length(), ' '));
      ROW -= 2;
      center(9);
      print(string(7, ' '));
      ROW -= 3;
      print(c, Red);
      continue;
    }    
  }
  clear();

  News n = news->at(index);

  slowPrint(n.title, 80, UYellow);
  print("");
  slowPrint("Published By: " + publishers->at(db->searchPublisherId(n.publisherId)).name, 40, Cyan);
  slowPrint("Date Published:" + Datetime::datetimeToS(n.createdAt), 40, Cyan);
  slowPrint("Likes (" + to_string(n.numOfLikes) + ")", 40, On_IGreen);
  slowPrint("Dislikes (" + to_string(n.numOfDislikes) + ")", 40, On_IRed);
  print("");
  print("");
  stringstream ss(n.content);
  string line;
  // getline(ss, line, '\n');
  // slowPrint(line, 0);
  while(getline(ss, line, '\n'))
  {
    slowPrint(line, 0);
  }
  print("");
  print("[END OF NEWS]");
  string itext = inputText(0, 0, "");

  slowPrint("Do you like or dislike this news? [Y/n]", 40, Yellow);

  string res = inputText(1, 0, "", On_IYellow);

  if (res == "N" || res == "n")
    db->dislike(id);
  else
    db->like(id);
}

void editProfile()
{
  clear();
  string nName, nAbout, nPhone;
  print("EDIT PROFILE");
  slowPrint("Organization Name: ");
  nName = inputText(20, 3, this_pub.name);
  slowPrint("Organization About: ");
  nAbout = inputText(20, 3, this_pub.about);
  slowPrint("Phone Number: ");
  nPhone = inputText(20, 3, this_pub.phone);

  db->editPublisher(this_pub.id, this_pub.email, this_pub.password, nName, nAbout, nPhone);
  this_pub = publishers->at(PID);
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
