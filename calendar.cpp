#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() 
{
    const int daysInWeek = 7;
    const int weeksInMonth = 5;  // Keep this as 5 to match the new reduced `calendar` array
    
    // Events for each day of the week in November (reduced to match `weeksInMonth = 5`)
    const string calendar[weeksInMonth][daysInWeek] = {
        {"SCC Conf", "Morning Swim", "Topic of Ed", "Jazz Choir", "Swim & Anxiety", "Jazz Choir", "Theater"},
        {"Choir", "Evening Yoga", "Deerfield Orch", "Morning Swim", "Yoga Night", "Rock Concert", "Production"},
        
        {"Open Swim", "Staff Mtg", "Swim Meet", "Yoga Class", "Workshop", "Book Club", "Basketball"},
        {"Art Exhibit", "Topic of Ed", "Office Hours", "Yoga & Stretch", "Swim Session", "Game Night", "Theater"},
        
        {"School Band", "Meeting", "Yoga Workshop", "Deerfield Orch", "Med. Workshop", "Family Movie", "Art Display"}
    };

    // Start date for the month (1st of November is a Friday in 2024)
    int startDate = 5;  // Friday
    int currentDay = 1; // Starting day number
    
    // Display calendar header
    cout << "+------------------+------------------+------------------+------------------+------------------+------------------+------------------+\n";
    cout << "|     Sun          |     Mon          |     Tue          |     Wed          |     Thu          |     Fri          |     Sat          |\n";
    cout << "+------------------+------------------+------------------+------------------+------------------+------------------+------------------+\n";
    
    // Loop through each week
    for (int week = 0; week < weeksInMonth; ++week) {
        for (int day = 0; day < daysInWeek; ++day) {
            // Display empty spaces for days before the 1st of the month
            if (week == 0 && day < startDate) {
                cout << "|                  ";
            } else if (currentDay <= 30) {  // Only print up to the 30th day
                // Format: date followed by the event, left-aligned within a 13-character width
                cout << "| " << setw(2) << currentDay << " " << left << setw(14) << calendar[week][day];
                currentDay++;
            } else {
                // Print empty space after the last date of the month
                cout << "|               ";
            }
        }
        cout << "|\n";
        
        // Print a line of "-" symbols after each week
        if (week < weeksInMonth - 1) {
            cout << "+------------------+------------------+------------------+------------------+------------------+------------------+------------------+\n";
        } else {
            cout << "+==================+==================+==================+==================+==================+==================+==================+\n";
        }
    }
    
    return 0;
}
