/*-------------------------------------------------------[ CREDITS ]--------------------------------------------------------------------*/

/**
 * @file main.cpp
 * @author Alya, Irfan, Khilfi, Rusydina
 * @brief INTEC Insider is a campus news app that brings together all wonderful stories and events around the campus in one place for everyone to see and benefit from.
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
*/

// TODO: Create all function prototypes
// TODO: Siapkan different parts of UI and flow
// TODO: Dominate all the other groups by introducing some absurd feature (sound effects, image, data analytics)

/*----------------------------------------------------[ HEADERS & INCLUDES ]------------------------------------------------------------*/

#include "headers/Database.h"
#include <iostream>
#include <iomanip>
#include <csignal>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

/*-----------------------------------------------------[ GLOBAL VARIABLES ]--------------------------------------------------------------*/

/** MENU numbers */
#define ENTRY 0
#define SIGN_UP 1
#define SIGN_IN 2
#define MAIN_MENU 3
#define CREATE_NEWS 4
#define EDIT_NEWS 5
#define DELETE_NEWS 6
#define EDIT_PROFILE 7
#define CALENDAR 8

/** Publisher ID of current user */
int PID = 0;

/** Current Menu number the user is interacting with */
int MENU = 0;

/** Stores all publishers data */
const vector<Publisher>* publishers;

/** Stores all news data */
const vector<News>* news;

/*----------------------------------------------------[ FUNCTION PROTOTYPES ]------------------------------------------------------------*/

int PublisherManager::totalPublishers = 0;
int PublisherManager::nextPublisherId = 1;
int NewsManager::totalNews = 0;
int NewsManager::nextNewsId = 1;
string Database::version = "0.0.1";

string toLowerCase(const string& str);

/*-----------------------------------------------------[ MAIN PROGRAM ]------------------------------------------------------------------*/
















































void entryMenu()
{
    int s = 0;
    cout << "SIGN IN / UP";

    cin >> s;

    if (s == 0)
        MENU = 1;
    else
        MENU = 2;
}

void mainMenu()
{
    Publisher p = publishers->at(PID);
    cout << p.name;
}

int main()
{
    Database db = Database();
    publishers = db.getAllPublishers();
    
    mainMenu();
}
