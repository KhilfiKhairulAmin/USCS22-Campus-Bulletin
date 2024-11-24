#include "headers/Database.h"
#include <iostream>
#include <iomanip>
#include <csignal>
#include <cstdlib>
using namespace std;

int PID = -1;
const vector<Publisher>* publishers;
const vector<News>* news;

void signalHandler(int signal)
{
    cout << "\nCaught Ctrl + C (SIGINT). Exiting gracefully..." << endl;
    // Perform cleanup or exit the program
    int num;
    cin >> num;
    
}

int main()
{
    signal(SIGINT, signalHandler);

    cout << "Press Ctrl + C to terminate the program..." << endl;

    while(true)
    {
        cout << "Helo";
    }

    return 0;
}
