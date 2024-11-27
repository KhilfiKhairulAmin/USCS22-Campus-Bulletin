#include <iostream>
#include <iomanip>
#include "Colors.h"
#include <string>
using namespace std;

void calendar() 
{
    const int daysInWeek = 7;
    const int weeksInMonth = 5;

    // Events for the calendar
    const string calendar[weeksInMonth][daysInWeek] = {
        {"", "", "", "", "", "Cultural Night", "Study Group"},
        {"Research Meet", "INTEC Coding Fest", "Basketball Finals", "Art Workshop", "AI Project Demo", "Hackathon", "Study Camp"},
        {"Guest Lecture", "Peer Tutoring", "Campus Cleanup", "Music Rehearsal", "Career Workshop", "Movie Night", "Free Time"},
        {"Final Presentation", "Quiz Contest", "Open Mic Night", "INPRO Ceremony", "Coding Sprint", "Campus Walk", "Project Showcase"},
        {"", "", "", "", "", "", ""}
    };

    // Start date for the month (1st of November is a Friday in 2024)
    int startDate = 5;  
    int currentDay = 1; 

    // Display calendar header
    cout << Yellow << "+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+\n";
    cout << Yellow<<"|        Sun          |        Mon          |        Tue          |        Wed          |        Thu          |        Fri          |        Sat          |\n";
    cout << Yellow<<"+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+\n";

    // Loop through each week
    for (int week = 0; week < weeksInMonth; ++week) {
        for (int day = 0; day < daysInWeek; ++day) {
            if (week == 0 && day < startDate) {
                // Print empty cells before the start date
                cout << Yellow <<"|                     ";
            } else if (currentDay <= 30) {
                if (!calendar[week][day].empty()) {
                    // Print the date and event, aligned properly
                    cout << Yellow << "| " << right << setw(2) << currentDay << " " << left << setw(17) << calendar[week][day].substr(0, 17);
                } else {
                    // Print only the date for empty cells
                    cout << Yellow <<"| " << right << setw(2) << currentDay << "                  ";
                }
                currentDay++; // Increment only when a date is printed
            } else {
                // Print empty cells after the last date of the month
                cout << Yellow <<"|                     ";
            }
        }
        cout << Yellow << "|\n";
        cout << Yellow <<"+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+---------------------+\n";
    }
}
